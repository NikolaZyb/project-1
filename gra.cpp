#include "gra.h"
#include <SFML/Graphics.hpp>
#include "pocisk.h"
#include <SFML/System.hpp>
#include "gracz.h"
#include<SFML/Window.hpp>
#include <SFML\OpenGL.hpp>
#include <iostream>
#include <windows.h>
#include <stdlib.h>

gra::gra()
{

    this->Okno();

    this->initTextures();
    this->Graczz();
    this->initGUI();
    this->initWrogowie();
    this->initWorld();

}
gra::~gra()
{
    delete this->window;
    delete this->gracz;
    for(auto &i:this->textures)
    {
        delete i.second;
    }
    for(auto *i:this->pociski)
    {
        delete i;
    }
    for(auto *i:this->wrogowie)
    {
        delete i;
    }
}

void gra::Okno()
{
     this->window = new sf::RenderWindow(sf::VideoMode(800, 600), "Fast & Pink", sf::Style::Close | sf::Style::Titlebar);
    this->window->setFramerateLimit(144);
    this->window->setVerticalSyncEnabled(false);

}

void gra::initTextures()
{
    this->textures["POCISK"]=new sf::Texture();
    this->textures["POCISK"]->loadFromFile("images/pocisk.png");
}

void gra::initWrogowie()
{
    this->spawnTimerMax=50.f;
    this->spawnTimer=this->spawnTimerMax;
}

void gra::Graczz()
{
    this->gracz=new Gracz();
}
void gra::run()
{
    while(this->window->isOpen())
    {
    this->update();
    this->Render();
    }
}
void gra::initSystems()
{
    this->punkty = 0;
}
void gra::initWorld()
{
    if (!this->worldBackgroundTex.loadFromFile("images/background1.jpg"))
        {
            std::cout << "Blad przy wczytywaniu tla" << "\n";
        }

        this->worldBackground.setTexture(this->worldBackgroundTex);
}
void gra::initGUI()
{
    this->font.loadFromFile("images/PixellettersFull.ttf");
    this->pointText.setPosition(700.f, 25.f);
    this->gracz->setPosition(380.f, 470.f);
    this->pointText.setFont(this->font);
    this->pointText.setCharacterSize(20);
    this->pointText.setFillColor(sf::Color::White);
    this->pointText.setString("test");
    this->gameOverText.setFont(this->font);
    this->gameOverText.setCharacterSize(60);
    this->gameOverText.setFillColor(sf::Color::Red);
    this->gameOverText.setString("Game Over!");
    this->gameOverText.setPosition(
     this->window->getSize().x / 2.f - this->gameOverText.getGlobalBounds().width / 2.f,
     this->window->getSize().y / 2.f - this->gameOverText.getGlobalBounds().height / 2.f);
    this->playerHpBar.setSize(sf::Vector2f(300.f, 25.f));
    this->playerHpBar.setFillColor(sf::Color::Red);
    this->playerHpBar.setPosition(sf::Vector2f(20.f, 20.f));
    this->playerHpBarBack = this->playerHpBar;
    this->playerHpBarBack.setFillColor(sf::Color(25, 25, 25, 200));
}
void gra::updatePollEvents()
{
    sf::Event E;
    while(this->window->pollEvent(E))
    {
        if(E.Event::type== sf::Event::Closed)
             this->window->close();
        if(E.Event::KeyPressed && E.Event::key.code==sf::Keyboard::Escape)
            this->window->close();
    }
}

void gra::updateInput()
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        this->gracz->poruszanie(-1.f,0.f);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        this->gracz->poruszanie(1.f,0.f);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        this->gracz->poruszanie(0.f,-1.f);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        this->gracz->poruszanie(0.f,1.f);
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)&&this->gracz->atakuje())
    {
        this->pociski.push_back(new Pocisk(this->textures["POCISK"],this->gracz->getPos().x,this->gracz->getPos().y,0.f,-1.f,5.f));
    }
}

void gra::updateGUI()
{
    std::stringstream ss;

    ss << "Points: " << this->punkty;

   this->pointText.setString(ss.str());

    float hpPercent = static_cast<float>(this->gracz->getHp()) / this->gracz->getHpMax();
   this->playerHpBar.setSize(sf::Vector2f(300.f * hpPercent, this->playerHpBar.getSize().y));
}

void gra::updateCollision()
{

    if (this->gracz->getBounds().left < 0.f)
    {
        this->gracz->setPosition(0.f, this->gracz->getBounds().top);
    }

    else if (this->gracz->getBounds().left + this->gracz->getBounds().width >= this->window->getSize().x)
    {
        this->gracz->setPosition(this->window->getSize().x - this->gracz->getBounds().width, this->gracz->getBounds().top);
    }


    if (this->gracz->getBounds().top < 0.f)
    {
        this->gracz->setPosition(this->gracz->getBounds().left, 0.f);
    }

    else if (this->gracz->getBounds().top + this->gracz->getBounds().height >= this->window->getSize().y)
    {
        this->gracz->setPosition(this->gracz->getBounds().left, this->window->getSize().y - this->gracz->getBounds().height);
    }
}
void gra::updatePocisk()
{
    int counter=0;
    for(auto *pocisk:this->pociski)
    {
        pocisk->update();
        if(pocisk->getBounds().top+pocisk->getBounds().height<0.f)
        {
           delete this->pociski.at(counter);
            this->pociski.erase(this->pociski.begin()+counter);
            counter--;
        }
        counter++;
    }
}

void gra::updateWrogowie()
{
    this->spawnTimer +=0.5f;
    if(this->spawnTimer>=this->spawnTimerMax)
    {
        this->wrogowie.push_back(new Wrog(rand()%this->window->getSize().x-20.f,-100.f));
        this->spawnTimer=0.f;
    }

    unsigned counter = 0;
    for (auto *wrog : this->wrogowie)
    {
        wrog->update();
        if (wrog->getBounds().top > this->window->getSize().y)
        {
            delete this->wrogowie.at(counter);
            this->wrogowie.erase(this->wrogowie.begin() + counter);
        }
        else if(wrog->getBounds().intersects(this->gracz->getBounds()))
        {
            this->gracz->loseHp(this->wrogowie.at(counter)->getDamage());
            delete this->wrogowie.at(counter);
            this->wrogowie.erase(this->wrogowie.begin() + counter);
        }

        ++counter;
    }
}
void gra::updateCombat()
{
    for (int i = 0; i < this->wrogowie.size(); ++i)
        {
            bool enemy_deleted = false;
            for (size_t k = 0; k < this->pociski.size() && enemy_deleted == false; k++)
            {
                if (this->wrogowie[i]->getBounds().intersects(this->pociski[k]->getBounds()))
                {
                    this->punkty += this->wrogowie[i]->getPoints();

                    delete this->wrogowie[i];
                    this->wrogowie.erase(this->wrogowie.begin() + i);

                    delete this->pociski[k];
                    this->pociski.erase(this->pociski.begin() + k);

                    enemy_deleted = true;
                }
            }
        }
}
void gra::update()
{
    this->updatePollEvents();
    this->updateInput();
    this->gracz->update();
    this->updatePocisk();
    this->updateWrogowie();
    this->updateCombat();
    this->updateGUI();

}
void gra::renderGUI()
{
    this->window->draw(this->pointText);
    this->window->draw(this->playerHpBarBack);
    this->window->draw(this->playerHpBar);
}
void gra::renderWorld()
{
    this->window->draw(this->worldBackground);
}
void gra::Render()
{
    this->window->clear();
    this->renderWorld();

    this->gracz->Render(*this->window);
    for(auto *pocisk:this->pociski)
    {
        pocisk->Render(this->window);
    }
    for(auto *wrog:this->wrogowie)
    {
        wrog->Render(this->window);
    }
    this->renderGUI();

        if (this->gracz->getHp() <= 0)
            this->window->draw(this->gameOverText);

        this->window->display();
}
