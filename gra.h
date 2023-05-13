#ifndef GRA_H
#define GRA_H
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "gracz.h"
#include<map>
#include "pocisk.h"
#include "wrog.h"
#include<sstream>

class gra
{
private:
    sf::RenderWindow* window;
    std::map<std::string,sf::Texture*> textures;
    std::vector<Pocisk*>pociski;
    void Okno();
    Gracz* gracz;
    float spawnTimer;
    float spawnTimerMax;
    std::vector<Wrog*>wrogowie;
    void initTextures();
    void initWrogowie();
    void Graczz();
    unsigned int punkty;
    sf::Texture worldBackgroundTex;
    sf::Sprite worldBackground;
    sf::Font font;
    sf::Text pointText;
    sf::Text gameOverText;
    sf::RectangleShape playerHpBar;
    sf::RectangleShape playerHpBarBack;
    void initGUI();
    void initWorld();
    void initSystems();

public:

    gra();
    virtual ~gra();
    void run();
    void updatePollEvents();
    void updateInput();
    void updatePocisk();
    void updateWrogowie();
    void updateCombat();
    void updateCollision();
    void updateGUI();
    void update();
    void Render();
    void renderGUI();
    void renderWorld();
    void render();
};



#endif // GRA_H
