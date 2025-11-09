#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(400, 300), "Paddle Ball Game");
    window.setFramerateLimit(60);

    // Ball setup
    sf::CircleShape ball(10.f);
    ball.setFillColor(sf::Color::White);
    sf::Vector2f initialBallPos(200.f, 150.f);
    ball.setPosition(initialBallPos);
    sf::Vector2f velocity(5.f, 5.f);

    // Paddle setup
    sf::RectangleShape paddle(sf::Vector2f(80.f, 30.f));
    paddle.setFillColor(sf::Color::Green);
    float paddleY = 280.f;
    paddle.setPosition(160.f, paddleY);
    float paddleSpeed = 5.f;

    // Load font for message
    sf::Font font;
    if (!font.loadFromFile("fonts/arial.ttf")) {
        // If font fails to load, exit
        return -1;
    }

    // Setup pause message
    sf::Text pauseText("Press Space to Continue", font, 20);
    pauseText.setFillColor(sf::Color::Yellow);
    // Center the text horizontally
    pauseText.setPosition((400 - pauseText.getGlobalBounds().width) / 2, 140.f);

    bool isPaused = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Paddle movement
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            paddle.move(-paddleSpeed, 0.f);
            if (paddle.getPosition().x < 0)
                paddle.setPosition(0, paddleY);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            paddle.move(paddleSpeed, 0.f);
            if (paddle.getPosition().x + paddle.getSize().x > 400)
                paddle.setPosition(400 - paddle.getSize().x, paddleY);
        }

        if (!isPaused) {
            // Move the ball
            ball.move(velocity);
            sf::Vector2f pos = ball.getPosition();

            // Ball collision with walls
            if (pos.x <= 0 || pos.x + ball.getRadius() * 2 >= 400)
                velocity.x = -velocity.x;
            if (pos.y <= 0)
                velocity.y = -velocity.y;

            // Ball collision with paddle
            if (pos.y + ball.getRadius() * 2 >= paddle.getPosition().y &&
                pos.x + ball.getRadius() * 2 >= paddle.getPosition().x &&
                pos.x <= paddle.getPosition().x + paddle.getSize().x) {
                velocity.y = -velocity.y;
                ball.setPosition(pos.x, paddle.getPosition().y - ball.getRadius() * 2);
            }

            // Ball missed paddle
            if (pos.y > 300) {
                isPaused = true;
            }
        } else {
            // Restart game on space bar
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                isPaused = false;
                ball.setPosition(initialBallPos);
                velocity = sf::Vector2f(3.f, 3.f);
            }
        }

        // Draw everything
        window.clear();
        window.draw(ball);
        window.draw(paddle);
        if (isPaused) {
            window.draw(pauseText);
        }
        window.display();
    }

    return 0;
}
