#ifndef POCISK_H
#define POCISK_H
#include<iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Pocisk
{
    private:
        sf::Sprite shape;
        sf::Vector2f direction;
        float szybkoscporuszania;
    public:
        Pocisk();
        Pocisk(sf::Texture* texture,float pos_x,float pos_y,float dir_x, float dir_y, float szybkosc_poruszania);
        virtual ~Pocisk();
        const sf::FloatRect getBounds() const;
        void update();
        void Render(sf::RenderTarget* target);
};

#endif // POCISK_H
