#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "ship.hpp"
#include "bullet.hpp"

struct GameSystem {
    static sf::Texture spritesheet;                  // Shared sprite sheet
    static std::vector<std::shared_ptr<Ship>> ships; // All ships

    static void init();
    static void clean();
    static void update(const float &dt);
    static void render(sf::RenderWindow &window);
};
