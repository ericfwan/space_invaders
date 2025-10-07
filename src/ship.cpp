#include "ship.hpp"
#include "game_parameters.hpp"
#include "bullet.hpp"
#include <SFML/Window/Keyboard.hpp>

using param = Parameters;
using gs = GameSystem;

// --- Ship base class ---
Ship::Ship() {}
Ship::Ship(const Ship &s) : _sprite(s._sprite) {}
Ship::Ship(sf::IntRect ir) : _sprite(ir) {
    setTexture(gs::spritesheet);
    setTextureRect(_sprite);
}
Ship::~Ship() = default;

void Ship::update(const float &dt) {}
bool Ship::is_exploded() const { return _exploded; }
void Ship::explode() {
    setTextureRect(sf::IntRect(128, 32, 32, 32));
    _exploded = true;
}

// --- Invader ---
bool Invader::direction = true;
float Invader::speed = 50.f;
float Invader::acc = 5.f;

Invader::Invader() : Ship() {}
Invader::Invader(const Invader &inv) : Ship(inv) {}
Invader::Invader(sf::IntRect ir, sf::Vector2f pos) : Ship(ir) {
    setOrigin(16.f, 16.f);
    setPosition(pos);
}

void Invader::update(const float &dt) {
    Ship::update(dt);
    move(dt * (direction ? 1.f : -1.f) * speed, 0.f);

    if ((direction && getPosition().x > param::game_width - param::sprite_size / 2.f) ||
        (!direction && getPosition().x < param::sprite_size / 2.f)) {
        direction = !direction;
        speed += acc;
        for (auto &ship : gs::ships)
            ship->move_down();
    }

    // Random shooting (simplified)
    static float firetime = 0.f;
    firetime -= dt;
    if (firetime <= 0.f && rand() % 100 == 0) {
        Bullet::fire(getPosition(), true);
        firetime = 4.0f + (rand() % 60);
    }
}

// --- Player ---
Player::Player() : Ship(sf::IntRect(32*5, 32, 32, 32)) {
    setOrigin(param::sprite_size / 2.f, param::sprite_size / 2.f);
    setPosition(param::game_width / 2.f, param::game_height - static_cast<float>(param::sprite_size));
}

void Player::update(const float &dt) {
    Ship::update(dt);

    static float firetime = 0.f;
    firetime -= dt;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        move(-dt * 300.f, 0.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        move(dt * 300.f, 0.f);

    // Keep player on screen
    if (getPosition().x < param::sprite_size / 2.f) setPosition(param::sprite_size / 2.f, getPosition().y);
    if (getPosition().x > param::game_width - param::sprite_size / 2.f) setPosition(param::game_width - param::sprite_size / 2.f, getPosition().y);

    // Shooting
    if (firetime <= 0.f && sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        Bullet::fire(getPosition(), false);
        firetime = 0.7f;
    }
}
