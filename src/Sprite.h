#ifndef SPRITE_H
#define SPRITE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Sprite {
public:
    Sprite() {
        position = glm::vec3(400.0f, 300.0f, 0.0f);
        scale = glm::vec3(120.0f, 120.0f, 1.0f);
        angle = 0.0f;
        flipX = false;
        
        nAnimations = 1;
        nFrames = 6;
        iAnimation = 0;
        iFrame = 0;
        frameRate = 10.0f;
        lastTime = 0.0;
        isMoving = false;
        
        VAO = VBO = EBO = 0;
        textureID = 0;
        shaderID = 0;
    }
    
    ~Sprite() {
        if (VAO) glDeleteVertexArrays(1, &VAO);
        if (VBO) glDeleteBuffers(1, &VBO);
        if (EBO) glDeleteBuffers(1, &EBO);
    }
    
    void initialize(GLuint shaderID, int nAnimations, int nFrames) {
        this->shaderID = shaderID;
        this->nAnimations = nAnimations;
        this->nFrames = nFrames;
        setupMesh();
    }
    
    void setupMesh() {
        float vertices[] = {
            -0.5f, -0.5f, 0.0f,  0.0f, 1.0f,
             0.5f, -0.5f, 0.0f,  1.0f, 1.0f,
             0.5f,  0.5f, 0.0f,  1.0f, 0.0f,
            -0.5f,  0.5f, 0.0f,  0.0f, 0.0f
        };
        
        unsigned int indices[] = {
            0, 1, 2,
            0, 2, 3
        };
        
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);
        
        glBindVertexArray(VAO);
        
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
        
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        
        glBindVertexArray(0);
    }
    
    void update() {
        if (isMoving) {
            updateFrame();
        }
        isMoving = false;
    }
    
    void updateFrame() {
        double currentTime = glfwGetTime();
        
        if (currentTime - lastTime >= 1.0 / frameRate) {
            iFrame = (iFrame + 1) % nFrames;
            lastTime = currentTime;
        }
    }
    
    void render() {
        glUseProgram(shaderID);
        
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, position);
        model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::scale(model, scale);
        
        glm::mat4 projection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, -1.0f, 1.0f);
        
        GLint modelLoc = glGetUniformLocation(shaderID, "model");
        GLint projLoc = glGetUniformLocation(shaderID, "projection");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
        
        float offsetX = (float)iFrame / (float)nFrames;
        float offsetY = (float)iAnimation / (float)nAnimations;
        
        GLint offsetXLoc = glGetUniformLocation(shaderID, "offsetX");
        GLint offsetYLoc = glGetUniformLocation(shaderID, "offsetY");
        GLint nFramesLoc = glGetUniformLocation(shaderID, "nFrames");
        GLint nAnimationsLoc = glGetUniformLocation(shaderID, "nAnimations");
        GLint flipXLoc = glGetUniformLocation(shaderID, "flipX");
        
        glUniform1f(offsetXLoc, offsetX);
        glUniform1f(offsetYLoc, offsetY);
        glUniform1f(nFramesLoc, (float)nFrames);
        glUniform1f(nAnimationsLoc, (float)nAnimations);
        glUniform1i(flipXLoc, flipX ? 1 : 0);
        
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureID);
        glUniform1i(glGetUniformLocation(shaderID, "texture1"), 0);
        
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }
    
    void setPosition(glm::vec3 pos) { position = pos; }
    void setScale(glm::vec3 sc) { scale = sc; }
    void setTexture(GLuint tex) { textureID = tex; }
    void setAnimation(int anim) { if (anim >= 0 && anim < nAnimations) iAnimation = anim; }
    void setAngle(float newAngle) { angle = newAngle; }
    
    void setDirection(int key) {
        switch (key) {
            case GLFW_KEY_W:
            case GLFW_KEY_UP:
                angle = 90.0f;
                flipX = false;
                break;
            case GLFW_KEY_S:
            case GLFW_KEY_DOWN:
                angle = -90.0f;
                flipX = false;
                break;
            case GLFW_KEY_A:
            case GLFW_KEY_LEFT:
                angle = 0.0f;
                flipX = true;
                break;
            case GLFW_KEY_D:
            case GLFW_KEY_RIGHT:
                angle = 0.0f;
                flipX = false;
                break;
        }
    }
    
    void moveUp(float speed) { 
        position.y += speed; 
        isMoving = true;
    }
    void moveDown(float speed) { 
        position.y -= speed; 
        isMoving = true;
    }
    void moveLeft(float speed) { 
        position.x -= speed; 
        isMoving = true;
    }
    void moveRight(float speed) { 
        position.x += speed; 
        isMoving = true;
    }

private:
    GLuint VAO, VBO, EBO;
    GLuint textureID;
    GLuint shaderID;
    
    glm::vec3 position;
    glm::vec3 scale;
    float angle;
    bool flipX;
    
    int nAnimations;
    int nFrames;
    int iAnimation;
    int iFrame;
    float frameRate;
    double lastTime;
    bool isMoving;
};

#endif