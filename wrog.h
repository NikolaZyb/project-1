#ifndef WROG_H
#define WROG_H
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>


class Wrog
{
private:
    unsigned pointCount;
    sf::CircleShape shape;
    int hp;
    float speed;
    int hpMax;
    int damage;
    int points;
    int type;
    void initVar();
    void initShape();
public:
    Wrog(float posX,float posY);
    virtual ~Wrog();
    const sf::FloatRect getBounds() const;
    const int& getPoints() const;
    const int& getDamage() const;
    void update();
    void Render(sf::RenderTarget* target);
};

#endif // WROG_H
