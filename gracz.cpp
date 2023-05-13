#include "gracz.h"

void Gracz::initVar()
{
    this->szybkoscporuszania=2.5f;
    this->attactCooldownMax = 10.f;
    this->attactCooldown = this->attactCooldownMax;

    this->hpMax = 100;
     this->hp = this->hpMax;

}

void Gracz::initTexture()
{
    if(!this->texture.loadFromFile("images/swinia.png"))
    {
        std::cout<<"Nie wczytano grafiki"<<std::endl;
    }
}

void Gracz::initSprite()
{
    this->sprite.setTexture(this->texture);
    this->sprite.scale(1.f,1.f);
}

Gracz::Gracz()
{
    this->initVar();
    this->initTexture();
    this->initSprite();
}

Gracz::~Gracz()
{

}

const sf::Vector2f &Gracz::getPos() const
{
    return this->sprite.getPosition();
}

const sf::FloatRect Gracz::getBounds() const
{
    return this->sprite.getGlobalBounds();
}

const bool Gracz::atakuje()
{
    if(this->attactCooldown>=this->attactCooldownMax)
    {
        this->attactCooldown=0.f;
        return true;
    }
    return false;
}
const int & Gracz::getHp() const
{
    return this->hp;
}

const int & Gracz::getHpMax() const
{
    return this->hpMax;
}
void Gracz::setPosition(const sf::Vector2f pos)
{
    this->sprite.setPosition(pos);
}
void Gracz::setPosition(const float x, const float y)
{
    this->sprite.setPosition(x, y);
}

void Gracz::setHp(const int hp)
{
    this->hp = hp;
}

void Gracz::loseHp(const int value)
{
    this->hp -= value;
    if (this->hp < 0)
        this->hp = 0;
}

void Gracz::poruszanie(const float dirx, const float diry)
{
    this->sprite.move(this->szybkoscporuszania * dirx, this->szybkoscporuszania * diry);
}

void Gracz::updateAttact()
{
    if (this->attactCooldown<this->attactCooldownMax)
    this->attactCooldown+=0.5f;
}

void Gracz::update()
{
    this->updateAttact();
}

void Gracz::Render(sf::RenderTarget& target)
{
    target.draw(this->sprite);
}
