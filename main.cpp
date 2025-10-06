#include <SFML/Graphics.hpp>  // SFML graphics library (sprites, textures, windows)
#include <iostream>            // For std::cerr and std::cout debugging

// -----------------------------
// Global variables
// -----------------------------
sf::Texture spritesheet;  // Holds the sprite sheet image
sf::Sprite invader;       // Represents a single sprite from the sheet

// -----------------------------
// Initialization function
// -----------------------------
void init() {
    // First, try to load the sprite sheet assuming running inside Visual Studio IDE
    std::string path = "img/invaders_sheet.png";  
    if (!spritesheet.loadFromFile(path)) {
        // If that fails, try running from build/bin (after CMake copy)
        path = "../resources/img/invaders_sheet.png";  
        if (!spritesheet.loadFromFile(path)) {
            // If it still fails, print an error and stop initialization
            std::cerr << "Failed to load sprite sheet from any path!" << std::endl;
            return;
        }
    }

    // Assign the texture to the sprite
    invader.setTexture(spritesheet);

    // Set the portion of the sprite sheet to use (top-left 32x32 pixels)
    invader.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(32, 32)));
}

// -----------------------------
// Render function
// -----------------------------
void render(sf::RenderWindow& window) {
    window.clear(sf::Color::Black); // Clear the window with black
    window.draw(invader);            // Draw the sprite
    window.display();                // Display the rendered frame
}

// -----------------------------
// Main function
// -----------------------------
int main() {
    // Create a window of size 800x600 with title "Space Invaders"
    sf::RenderWindow window(sf::VideoMode(800, 600), "Space Invaders");

    // Initialize the sprite and load the texture
    init();

    // Main game loop runs while the window is open
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            // Close window if the close button is pressed
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Render the frame
        render(window);
    }

    return 0; // Exit program
}
