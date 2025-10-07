#pragma once
#include <SFML/Graphics.hpp>
#include "game_system.hpp"

class Bullet : public sf::Sprite {
public:
    static void init();
    static void update(const float &dt);
    static void render(sf::RenderWindow &window);
    static void fire(const sf::Vector2f &pos, bool mode);

    ~Bullet() = default;

protected:
    Bullet();
    void _update(const float &dt);

    bool _mode; // true=enemy, false=player
    static unsigned char _bulletPointer;
    static Bullet _bullets[256];
};
