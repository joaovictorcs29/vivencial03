// JOGO ISOMÉTRICO - PROJETO PROCESSAMENTO GRÁFICO
// Desenvolvido com OpenGL e GLFW

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <string>
#include <random>
#include <set>

// ESTRUTURAS DE DADOS DO JOGO
struct TileProps {
    bool walkable;
    int  swapTo;
};

struct GameObject {
    std::string type;
    int x, y;
};

int WIN_W = 800, WIN_H = 600;

// FUNÇÃO PARA CARREGAR TEXTURAS
GLuint loadTexture(const std::string& path, int& outW, int& outH) {
    int nr;
    unsigned char* data = stbi_load(path.c_str(), &outW, &outH, &nr, 4);
    if(!data){ std::cerr<<"Falha ao ler "<<path<<"\n"; return 0; }
    GLuint tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA, outW, outH, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    stbi_image_free(data);
    return tex;
}

int main(){
    // INICIALIZAÇÃO DO OPENGL E GLFW
    if(!glfwInit()){ std::cerr<<"GLFW Init falhou\n"; return -1; }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,1);
    GLFWwindow* window = glfwCreateWindow(WIN_W, WIN_H, "Jogo Isométrico", nullptr, nullptr);
    if(!window){ std::cerr<<"Janela falhou\n"; return -1; }
    glfwMakeContextCurrent(window);
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cerr<<"GLAD falhou\n"; return -1;
    }

    // CONFIGURAÇÃO OPENGL - BLENDING E PROJEÇÃO ORTOGRÁFICA
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, WIN_W, WIN_H, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);

    // CARREGAMENTO DAS CONFIGURAÇÕES DO TILESET
    std::ifstream inCfg("../assets/config/tileset.cfg.txt");
    std::string line, tilesetFile;
    int tileCount=0, tileW=0, tileH=0;
    while(std::getline(inCfg,line)){
        if(line.empty()|| line[0]=='#') continue;
        auto p=line.find('=');
        if(p == std::string::npos) continue;
        auto key=line.substr(0,p), val=line.substr(p+1);
        if(key=="tileset")   tilesetFile=val;
        if(key=="tileCount") tileCount = std::stoi(val);
        if(key=="tileWidth") tileW     = std::stoi(val);
        if(key=="tileHeight")tileH     = std::stoi(val);
    }

    // CARREGAMENTO DA TEXTURA DO TILESET
    int texW, texH;
    GLuint tilesetTex = loadTexture(tilesetFile, texW, texH);
    int cols = texW / tileW;

    // PROPRIEDADES DOS TILES - TODOS CAMINHÁVEIS
    std::vector<TileProps> props(7);
    for(int i = 0; i < 7; i++) {
        props[i] = {true, -1}; // Todos os tiles são caminháveis
    }

    // DEFINIÇÃO DO MAPA 15x15 ISOMÉTRICO
    int mapW = 15, mapH = 15;
    std::vector<std::vector<int>> mapData = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 2, 2, 0, 0, 0, 3, 0, 0, 2, 2, 0, 0, 1},
        {1, 0, 2, 2, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 1},
        {1, 0, 0, 0, 2, 2, 0, 0, 0, 2, 2, 0, 0, 0, 1},
        {1, 0, 3, 0, 2, 2, 0, 0, 0, 2, 2, 0, 3, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 3, 0, 2, 2, 0, 0, 0, 2, 2, 0, 3, 0, 1},
        {1, 0, 0, 0, 2, 2, 0, 0, 0, 2, 2, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 1},
        {1, 0, 2, 2, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 1},
        {1, 0, 2, 2, 0, 0, 3, 0, 0, 2, 2, 0, 0, 0, 1},
        {1, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    };
    
    std::cout << "=== MAPA CARREGADO - MOVIMENTO LIVRE ===" << std::endl;

    // CARREGAMENTO DOS OBJETOS DO JOGO
    std::ifstream inObj("../assets/config/objects.txt");
    std::vector<GameObject> gameObjects;
    std::string objType;
    int objX, objY;
    
    while(inObj >> objType >> objX >> objY) {
        gameObjects.push_back({objType, objX, objY});
    }

    // INICIALIZAÇÃO DO MAPA DE OBJETOS
    std::vector<std::vector<std::string>> objectMap(mapH, std::vector<std::string>(mapW,""));
    std::map<std::string, GLuint> objTex;

    // CARREGAMENTO DAS TEXTURAS DOS OBJETOS
    int w, h;
    objTex["coin"] = loadTexture("../assets/coin.png", w, h);
    objTex["trap"] = loadTexture("../assets/trap.png", w, h);
    objTex["key"] = loadTexture("../assets/key.png", w, h);
    objTex["exit"] = loadTexture("../assets/exit.png", w, h);

    // POSICIONAMENTO DOS OBJETOS NO MAPA
    for(const auto& obj : gameObjects) {
        if(obj.x >= 0 && obj.x < mapW && obj.y >= 0 && obj.y < mapH) {
            objectMap[obj.y][obj.x] = obj.type;
        }
    }

    // POSICIONAMENTO DA PORTA NO FINAL DO MAPA (CANTO INFERIOR DIREITO)
    objectMap[13][13] = "exit"; // Porta posicionada em (13,13)

    // CARREGAMENTO DO PERSONAGEM
    int pw, ph;
    GLuint playerTex = loadTexture("../assets/Vampirinho.png", pw, ph);
    int px=1, py=1; // Posição inicial do player

    // VARIÁVEIS DO JOGO
    int coins=0, targetCoins=1;
    int lives=3, maxLives=3;
    bool hasKey = false;
    
    // CÂMERA QUE SEGUE O PLAYER
    float cameraX = 0.0f, cameraY = 0.0f;

    std::cout << "=== JOGO INICIADO ===" << std::endl;
    std::cout << "Colete moeda + chave, vá para a porta no final!" << std::endl;

    // LOOP PRINCIPAL DO JOGO
    while(!glfwWindowShouldClose(window)){
        glfwPollEvents();

        // SISTEMA DE MOVIMENTO - UMA TILE POR FRAME
        static bool moved = false;
        if(!moved){
            int dx=0, dy=0;
            if(glfwGetKey(window,GLFW_KEY_UP   )==GLFW_PRESS) { dy=-1; moved=true; }
            if(glfwGetKey(window,GLFW_KEY_DOWN )==GLFW_PRESS) { dy=+1; moved=true; }
            if(glfwGetKey(window,GLFW_KEY_RIGHT)==GLFW_PRESS) { dx=+1; moved=true; }
            if(glfwGetKey(window,GLFW_KEY_LEFT )==GLFW_PRESS) { dx=-1; moved=true; }
            
            int nx = px+dx, ny = py+dy;
            
            // VERIFICA LIMITES DO MAPA E MOVE O PLAYER
            if((dx||dy) && nx>=0 && nx<mapW && ny>=0 && ny<mapH){
                px=nx; py=ny; // Movimento livre
                
                // ATUALIZAÇÃO DA CÂMERA PARA SEGUIR O PLAYER
                cameraX = WIN_W*0.5f - (px - py) * (tileW * 0.5f);
                cameraY = WIN_H*0.5f - (px + py) * (tileH * 0.25f);
                
                // SISTEMA DE COLETA DE OBJETOS
                auto &ot = objectMap[ny][nx];
                if(!ot.empty()) {
                    if(ot=="coin"){
                        coins++;
                        std::cout << "Moeda coletada! " << coins << "/" << targetCoins << std::endl;
                        ot.clear();
                    } 
                    else if(ot=="key"){
                        hasKey = true;
                        std::cout << "Chave coletada!" << std::endl;
                        ot.clear();
                    }
                    else if(ot=="trap"){
                        lives--;
                        std::cout << "Armadilha! Vidas: " << lives << std::endl;
                        ot.clear();
                        
                        if(lives <= 0) {
                            std::cout << "GAME OVER!" << std::endl;
                            glfwSetWindowShouldClose(window, 1);
                        }
                    } 
                    else if(ot=="exit"){
                        // CONDIÇÃO DE VITÓRIA
                        if(coins >= targetCoins && hasKey) {
                            std::cout << "VITÓRIA! Parabéns!" << std::endl;
                            glfwSetWindowShouldClose(window, 1);
                        } else {
                            std::cout << "Precisa de moeda e chave!" << std::endl;
                        }
                    }
                }
            }
        }
        
        // RESET DO SISTEMA DE MOVIMENTO
        if(glfwGetKey(window,GLFW_KEY_UP   )==GLFW_RELEASE &&
           glfwGetKey(window,GLFW_KEY_DOWN )==GLFW_RELEASE &&
           glfwGetKey(window,GLFW_KEY_RIGHT)==GLFW_RELEASE &&
           glfwGetKey(window,GLFW_KEY_LEFT )==GLFW_RELEASE) {
            moved = false;
        }

        // === RENDERIZAÇÃO ===
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glLoadIdentity();

        // RENDERIZAÇÃO DO MAPA ISOMÉTRICO
        glBindTexture(GL_TEXTURE_2D, tilesetTex);
        glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
        
        for(int y=0; y<mapH; y++){
            for(int x=0; x<mapW; x++){
                int id = mapData[y][x];
                
                // FILTRO: NÃO RENDERIZA LAVA, ÁGUAS E TERRENO ROSA
                if(id == 3 || id == 4 || id == 5 || id == 6) continue;
                
                if(id < 0 || id >= tileCount) continue;
                
                // CÁLCULO DA TEXTURA DO TILE
                float u0 = (id % cols) * (tileW / (float)texW);
                float v0 = (id / cols) * (tileH / (float)texH);
                float u1 = u0 + tileW / (float)texW;
                float v1 = v0 + tileH / (float)texH;

                // PROJEÇÃO ISOMÉTRICA COM CÂMERA
                float pxscr = (x - y) * (tileW * 0.5f) + cameraX;
                float pyscr = (x + y) * (tileH * 0.25f) + cameraY;

                float x0 = pxscr;
                float y0 = pyscr;
                float x1 = pxscr + tileW;
                float y1 = pyscr + tileH;

                // RENDERIZAÇÃO DO QUAD
                glBegin(GL_QUADS);
                  glTexCoord2f(u0,v0); glVertex2f(x0,y0);
                  glTexCoord2f(u1,v0); glVertex2f(x1,y0);
                  glTexCoord2f(u1,v1); glVertex2f(x1,y1);
                  glTexCoord2f(u0,v1); glVertex2f(x0,y1);
                glEnd();
            }
        }

        // RENDERIZAÇÃO DOS OBJETOS COLECIONÁVEIS
        for(int y=0; y<mapH; y++){
            for(int x=0; x<mapW; x++){
                auto &ot = objectMap[y][x];
                if(ot.empty() || objTex.find(ot) == objTex.end()) continue;
                
                glBindTexture(GL_TEXTURE_2D, objTex[ot]);
                glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

                // PROJEÇÃO ISOMÉTRICA PARA OBJETOS
                float pxscr = (x - y) * (tileW * 0.5f) + cameraX;
                float pyscr = (x + y) * (tileH * 0.25f) + cameraY;
                
                // OBJETOS MENORES QUE OS TILES
                float objScale = 0.3f;
                float objW = tileW * objScale;
                float objH = tileH * objScale;
                
                // CENTRALIZAÇÃO DO OBJETO NO TILE
                float x0 = pxscr + (tileW - objW) * 0.5f;
                float y0 = pyscr + (tileH - objH) * 0.5f;
                float x1 = x0 + objW;
                float y1 = y0 + objH;

                glBegin(GL_QUADS);
                  glTexCoord2f(0,0); glVertex2f(x0,y0);
                  glTexCoord2f(1,0); glVertex2f(x1,y0);
                  glTexCoord2f(1,1); glVertex2f(x1,y1);
                  glTexCoord2f(0,1); glVertex2f(x0,y1);
                glEnd();
            }
        }

        // RENDERIZAÇÃO DO PERSONAGEM
        glBindTexture(GL_TEXTURE_2D, playerTex);
        glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
        {
            // PROJEÇÃO ISOMÉTRICA DO PLAYER
            float pxscr = (px - py) * (tileW * 0.5f) + cameraX;
            float pyscr = (px + py) * (tileH * 0.25f) + cameraY;
            
            // PLAYER COM ESCALA MAIOR
            float playerScale = 1.2f;
            float w = pw * playerScale;
            float h = ph * playerScale;
            
            // POSICIONAMENTO CENTRALIZADO
            float x0 = pxscr + (tileW - w) * 0.5f;
            float y0 = pyscr + (tileH - h) * 0.8f;
            float x1 = x0 + w;
            float y1 = y0 + h;

            glBegin(GL_QUADS);
              glTexCoord2f(0,0); glVertex2f(x0,y0);
              glTexCoord2f(1,0); glVertex2f(x1,y0);
              glTexCoord2f(1,1); glVertex2f(x1,y1);
              glTexCoord2f(0,1); glVertex2f(x0,y1);
            glEnd();
        }

        glfwSwapBuffers(window);
    }

    // FINALIZAÇÃO
    glfwTerminate();
    return 0;
}