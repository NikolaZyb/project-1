#include "wrog.h"

void Wrog::initVar()
{
    this->pointCount = rand() % 8 + 3;
    this->type		= 0;
    this->speed		= static_cast<float>(this->pointCount/3);
    this->hpMax		= static_cast<int>(this->pointCount);
    this->hp		= this->hpMax;
    this->damage	= this->pointCount;
    this->points	= this->pointCount;
}

void Wrog::initShape()
{
    this->shape.setRadius(rand()%20+20);
    this->shape.setPointCount(rand()%20+3);
    this->shape.setFillColor(sf::Color(rand()%255+1,rand()%255+1,rand()%255+1));
}

Wrog::Wrog(float posX,float posY)
{
    this->initShape();
    this->initVar();
    this->shape.setPosition(posX,posY);

}

Wrog::~Wrog()
{

}
const int & Wrog::getPoints() const
{
    return this->points;
}

const int & Wrog::getDamage() const
{
    return this->damage;
}
const sf::FloatRect Wrog::getBounds() const
{
   return this->shape.getGlobalBounds();
}

void Wrog::update()
{
    this->shape.move(0.f,this->speed);
}

void Wrog::Render(sf::RenderTarget *target)
{
    target->draw(this->shape);
}
