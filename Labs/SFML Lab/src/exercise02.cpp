#include <SFML/Graphics.hpp>

int main(){
    sf::VideoMode videoMode(300, 400);

    sf::RenderWindow window(videoMode, "STOP Sign");

    sf::CircleShape Circle(80);
    Circle.setFillColor(sf::Color::White);
    Circle.setOutlineColor(sf::Color::Red);
    Circle.setOutlineThickness(20);
    Circle.setPosition(300/2 - 80, 40);

    sf::RectangleShape Post(sf::Vector2f(30.f, 200.f));
    Post.setFillColor(sf::Color::Black);
    Post.setPosition(300/2 - 30/2, 40 + 80*2 + 20 - 1);

    
    sf::Font font;
    font.loadFromFile("./fonts/arial.ttf");
    sf::Text stop_text("STOP", font, 50);
    stop_text.setFillColor(sf::Color::Black);
    sf::FloatRect textBounds = stop_text.getLocalBounds();
    stop_text.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
    stop_text.setPosition(sf::Vector2f(300/2, 40 + 80));


    while (window.isOpen()) {
    // Event polling (for handling window close, etc.)
    sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
    
    window.clear(sf::Color::Cyan);
    window.draw(Post);
    window.draw(Circle);
    window.draw(stop_text);
    window.display();

    }

}