#include <SFML/Graphics.hpp>

int main() {
    // Create a video mode object (window size 800x600)
    sf::VideoMode videoMode(800, 600);

    // Create a render window
    sf::RenderWindow window(videoMode, "Move Rectangle with Arrow Keys");

    // Set the frame rate limit to make movement smoother
    window.setFramerateLimit(60);

    // Create a rectangle shape (size 100x50)
    sf::RectangleShape rectangle(sf::Vector2f(100.f, 50.f));

    // Set the rectangle's initial position
    rectangle.setPosition(350.f, 275.f); // Center of the window

    // Set the rectangle's fill color
    rectangle.setFillColor(sf::Color::Green);

    // Movement speed (pixels per frame)
    float movementSpeed = 5.0f;

    // Main game loop
    while (window.isOpen()) {
        // Event polling (for handling window close, etc.)
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Real-time input for moving the rectangle
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            rectangle.move(0.f, -movementSpeed);  // Move up
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            rectangle.move(0.f, movementSpeed);   // Move down
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            rectangle.move(-movementSpeed, 0.f); // Move left
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            rectangle.move(movementSpeed, 0.f);  // Move right
        }

        const float windowWidth = window.getSize().x;
        const float windowHeight = window.getSize().y;

        sf::Vector2f pos = rectangle.getPosition();
        sf::FloatRect bounds = rectangle.getGlobalBounds();

        // --- Logical reposition (only when completely off screen) ---
        if (pos.x > windowWidth)
            rectangle.setPosition(-bounds.width, pos.y);
        if (pos.x + bounds.width < 0)
            rectangle.setPosition(windowWidth, pos.y);
        if (pos.y > windowHeight)
            rectangle.setPosition(pos.x, -bounds.height);
        if (pos.y + bounds.height < 0)
            rectangle.setPosition(pos.x, windowHeight);

        // --- Drawing section ---
        window.clear();

        // Draw main rectangle
        window.draw(rectangle);

        // Draw wrapping copies for smooth transition
        sf::RectangleShape copy = rectangle;

        // Horizontal wraps
        if (pos.x + bounds.width > windowWidth) {
            copy.setPosition(pos.x - windowWidth, pos.y);
            window.draw(copy);
        }
        if (pos.x < 0) {
            copy.setPosition(pos.x + windowWidth, pos.y);
            window.draw(copy);
        }

        // Vertical wraps
        if (pos.y + bounds.height > windowHeight) {
            copy.setPosition(pos.x, pos.y - windowHeight);
            window.draw(copy);
        }
        if (pos.y < 0) {
            copy.setPosition(pos.x, pos.y + windowHeight);
            window.draw(copy);
        }

        // Corner wraps (diagonal edges)
        if (pos.x < 0 && pos.y < 0) {
            copy.setPosition(pos.x + windowWidth, pos.y + windowHeight);
            window.draw(copy);
        }
        if (pos.x + bounds.width > windowWidth && pos.y < 0) {
            copy.setPosition(pos.x - windowWidth, pos.y + windowHeight);
            window.draw(copy);
        }
        if (pos.x < 0 && pos.y + bounds.height > windowHeight) {
            copy.setPosition(pos.x + windowWidth, pos.y - windowHeight);
            window.draw(copy);
        }
        if (pos.x + bounds.width > windowWidth && pos.y + bounds.height > windowHeight) {
            copy.setPosition(pos.x - windowWidth, pos.y - windowHeight);
            window.draw(copy);
        }

        // Display the rendered frame
        window.display();
    }

    return 0;
}
