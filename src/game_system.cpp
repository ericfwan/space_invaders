#include "game_system.hpp"
#include "game_parameters.hpp"
#include <iostream>

using param = Parameters;

sf::Texture GameSystem::spritesheet;
std::vector<std::shared_ptr<Ship>> GameSystem::ships;

void GameSystem::init() {
    // Load sprite sheet
    if (!spritesheet.loadFromFile("resources/img/invaders_sheet.png")) {
        std::cerr << "Failed to load spritesheet!" << std::endl;
        return;
    }

    // Spawn invaders
    for (int r = 0; r < param::rows; ++r) {
        for (int c = 0; c < param::columns; ++c) {
            sf::Vector2f pos(50.f + c * (param::sprite_size + 10.f), 50.f + r * (param::sprite_size + 10.f));
            auto inv = std::make_shared<Invader>(sf::IntRect(0, 0, param::sprite_size, param::sprite_size), pos);
            ships.push_back(inv);
        }
    }

    // Spawn player
    auto player = std::make_shared<Player>();
    ships.push_back(player);

    // Initialize bullets
    Bullet::init();
}

void GameSystem::clean() {
    for (auto &ship : ships)
        ship.reset();
    ships.clear();
}

void GameSystem::update(const float &dt) {
    for (auto &ship : ships)
        ship->update(dt);

    Bullet::update(dt);
}

void GameSystem::render(sf::RenderWindow &window) {
    for (const auto &ship : ships)
        window.draw(*ship);

    Bullet::render(window);
}
