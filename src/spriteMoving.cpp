#include <iostream>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include "Sprite.h"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
GLuint loadTexture(const char* path);
GLuint createShaderProgram();

const GLuint WIDTH = 800, HEIGHT = 600;

Sprite sprite;
float moveSpeed = 5.0f;

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Sprite Controller - Use WASD para mover e rotacionar", nullptr, nullptr);
    if (!window) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);
    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    
    glViewport(0, 0, WIDTH, HEIGHT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    GLuint shaderProgram = createShaderProgram();
    
    GLuint texture = loadTexture("../assets/sprites/Walk.png");
    if (texture == 0) {
        std::cout << "Aviso: Textura não carregada. Verifique o caminho da imagem." << std::endl;
    }
    
    sprite.initialize(shaderProgram, 1, 6);
    sprite.setTexture(texture);
    sprite.setScale(glm::vec3(120.0f, 120.0f, 1.0f));
    sprite.setPosition(glm::vec3(400.0f, 300.0f, 0.0f));
    
    std::cout << "Use WASD ou setas para mover o sprite!" << std::endl;
    
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        
        sprite.update();
        
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        sprite.render();
        
        glfwSwapBuffers(window);
    }
    
    glfwTerminate();
    return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
        return;
    }
    
    if (action == GLFW_PRESS || action == GLFW_REPEAT) {
        sprite.setDirection(key);
        
        switch (key) {
            case GLFW_KEY_W:
            case GLFW_KEY_UP:
                sprite.moveUp(moveSpeed);
                sprite.setAnimation(0);
                break;
            case GLFW_KEY_S:
            case GLFW_KEY_DOWN:
                sprite.moveDown(moveSpeed);
                sprite.setAnimation(0);
                break;
            case GLFW_KEY_A:
            case GLFW_KEY_LEFT:
                sprite.moveLeft(moveSpeed);
                sprite.setAnimation(0);
                break;
            case GLFW_KEY_D:
            case GLFW_KEY_RIGHT:
                sprite.moveRight(moveSpeed);
                sprite.setAnimation(0);
                break;
        }
    }
}

GLuint loadTexture(const char* path) {
    GLuint textureID;
    glGenTextures(1, &textureID);
    
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);
    
    if (data) {
        GLenum format;
        if (nrChannels == 1)
            format = GL_RED;
        else if (nrChannels == 3)
            format = GL_RGB;
        else if (nrChannels == 4)
            format = GL_RGBA;
        
        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        
        std::cout << "Textura carregada: " << width << "x" << height << " canais: " << nrChannels << std::endl;
    } else {
        std::cout << "Falha ao carregar textura: " << path << std::endl;
        textureID = 0;
    }
    
    stbi_image_free(data);
    return textureID;
}

GLuint createShaderProgram() {
    const char* vertexShaderSource = R"(
        #version 330 core
        layout (location = 0) in vec3 aPos;
        layout (location = 1) in vec2 aTexCoord;
        
        out vec2 TexCoord;
        
        uniform mat4 model;
        uniform mat4 projection;
        uniform float offsetX;
        uniform float offsetY;
        uniform float nFrames;
        uniform float nAnimations;
        uniform int flipX;
        
        void main() {
            gl_Position = projection * model * vec4(aPos, 1.0);
            
            vec2 spriteSize = vec2(1.0 / nFrames, 1.0 / nAnimations);
            
            float texCoordX = aTexCoord.x;
            if (flipX == 1) {
                texCoordX = 1.0 - aTexCoord.x;
            }
            
            TexCoord = vec2(
                (texCoordX * spriteSize.x) + offsetX,
                (aTexCoord.y * spriteSize.y) + offsetY
            );
        }
    )";
    
    const char* fragmentShaderSource = R"(
        #version 330 core
        out vec4 FragColor;
        
        in vec2 TexCoord;
        uniform sampler2D texture1;
        
        void main() {
            vec4 texColor = texture(texture1, TexCoord);
            
            if(texColor.a < 0.1)
                discard;
                
            if(texColor.r > 0.95 && texColor.g > 0.95 && texColor.b > 0.95)
                discard;
                
            FragColor = texColor;
        }
    )";
    
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "Erro vertex shader: " << infoLog << std::endl;
    }
    
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "Erro fragment shader: " << infoLog << std::endl;
    }
    
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "Erro linking shader: " << infoLog << std::endl;
    }
    
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
    return shaderProgram;
}