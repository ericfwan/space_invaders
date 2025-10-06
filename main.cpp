#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

// -----------------------------
// Game objects
// -----------------------------
sf::Texture invaderTexture;
sf::Sprite invader;

// Window size
const int gameWidth = 800;
const int gameHeight = 600;

// -----------------------------
// Initialise game
// -----------------------------
void init() {
    // Load sprite sheet
    if (!invaderTexture.loadFromFile("img/invaders_sheet.png")) { // path relative to res
        std::cerr << "Failed to load spritesheet!" << std::endl;
    }
    invader.setTexture(invaderTexture);

    // Select the first sprite (top-left 32x32)
    invader.setTextureRect(IntRect(0, 0, 32, 32));

    // Position invader in middle
    invader.setPosition(gameWidth / 2.f, gameHeight / 2.f);
}

// -----------------------------
// Render everything
// -----------------------------
void render(sf::RenderWindow& window) {
    window.draw(invader);
}

// -----------------------------
// Main function
// -----------------------------
int main() {
    sf::RenderWindow window(sf::VideoMode(gameWidth, gameHeight), "Space Invaders");

    init();

    sf::Clock clock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Update logic can go here (animation, movement, etc.)

        window.clear(sf::Color::Black);
        render(window);
        window.display();
    }

    return 0;
}
