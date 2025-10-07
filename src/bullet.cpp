#include "bullet.hpp"
#include "game_parameters.hpp"

using param = Parameters;
using gs = GameSystem;

unsigned char Bullet::_bulletPointer = 0;
Bullet Bullet::_bullets[256];

Bullet::Bullet() {}

void Bullet::init() {
    for(int i = 0; i < 256; i++) {
        _bullets[i].setTexture(gs::spritesheet);
        _bullets[i].setOrigin(param::sprite_size / 2.f, param::sprite_size / 2.f);
        _bullets[i].setPosition(-100.f, -100.f);
    }
}

void Bullet::fire(const sf::Vector2f &pos, bool mode) {
    Bullet &b = _bullets[_bulletPointer++];
    if(_bulletPointer > 255) _bulletPointer = 0;

    b.setPosition(pos);
    b._mode = mode;
}

void Bullet::update(const float &dt) {
    for(int i = 0; i < 256; i++) {
        Bullet &b = _bullets[i];
        if (b.getPosition().y < 0 || b.getPosition().y > param::game_height) continue;
        b.move(0.f, (b._mode ? 1.f : -1.f) * dt * param::bullet_speed);
    }
}

void Bullet::render(sf::RenderWindow &window) {
    for(int i = 0; i < 256; i++) {
        if (_bullets[i].getPosition().y < 0 || _bullets[i].getPosition().y > param::game_height) continue;
        window.draw(_bullets[i]);
    }
}
