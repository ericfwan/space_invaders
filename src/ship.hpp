#pragma once
#include <SFML/Graphics.hpp>
#include "game_system.hpp"

class Ship : public sf::Sprite {
public:
    Ship();
    Ship(const Ship &s);
    Ship(sf::IntRect ir);
    virtual ~Ship() = 0;

    virtual void update(const float &dt);
    bool is_exploded() const;
    virtual void explode();

protected:
    sf::IntRect _sprite;
    bool _exploded = false;

    void move_down(float amount = 24.f) { move(0.f, amount); }
};

// Invader class
class Invader : public Ship {
public:
    Invader();
    Invader(const Invader &inv);
    Invader(sf::IntRect ir, sf::Vector2f pos);
    void update(const float &dt) override;

    static bool direction;
    static float speed;
    static float acc;
};

// Player class
class Player : public Ship {
public:
    Player();
    void update(const float &dt) override;
};
