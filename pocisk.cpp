#include "pocisk.h"
Pocisk::Pocisk()
{

}
Pocisk::Pocisk(sf::Texture* texture,float pos_x,float pos_y,float dir_x, float dir_y, float szybkosc_poruszania)
{
    this->shape.setTexture(*texture);
    this->shape.setPosition(pos_x,pos_y);
    this->direction.x=dir_x;
    this->direction.y=dir_y;
    this->szybkoscporuszania=szybkosc_poruszania;
}

Pocisk::~Pocisk()
{

}

const sf::FloatRect Pocisk::getBounds() const
{
  return this->shape.getGlobalBounds();
}

void Pocisk::update()
{
    this->shape.move(this->szybkoscporuszania * this->direction);

}

void Pocisk::Render(sf::RenderTarget *target)
{
    target->draw(this->shape);
}
