#ifndef GRACZ_H
#define GRACZ_H
#include<iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Gracz
{
private:
    sf::Sprite sprite;
    sf::Texture texture;
    float szybkoscporuszania;
    float attactCooldown;
    float attactCooldownMax;
    void initVar();
    void initTexture();
    void initSprite();
    int hp;
    int hpMax;
public:
   Gracz();
    virtual ~Gracz();
    const sf::Vector2f& getPos()const;
    const sf::FloatRect getBounds() const;
    const int& getHp() const;
    const int& getHpMax() const;
    void setPosition(const sf::Vector2f pos);
    void setPosition(const float x, const float y);
    void setHp(const int hp);
    void loseHp(const int value);
    const bool atakuje();
    void poruszanie(const float dirx, const float diry);
    void updateAttact();
    void update();
    void Render(sf::RenderTarget& target);
};

#endif // GRACZ_H
