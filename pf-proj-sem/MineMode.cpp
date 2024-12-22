//#include <SFML/Graphics.hpp>
//#include <iostream>
//#include <vector>
//#include <cmath>
//#include"common.h"
//using namespace sf;
//using namespace std;
//
//static std::vector<sf::CircleShape> particles;
//static std::vector<sf::Vector2f> particleVelocities;
//
//ScreenState MineMode(RenderWindow& window, View& gameView)
//{
//
//
//    sf::RenderWindow window(sf::VideoMode(800, 600), "Torchlight Fog Effect");
//    window.setFramerateLimit(60);
//
//    // Initialize Fog and Game
//    initializeFog();
//    initializeGameElements();
//
//    sf::Vector2f torchPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f);
//
//    while (window.isOpen()) {
//        Vector2i mousePixelPos = Mouse::getPosition(window); // Mouse position
//        Vector2f mousePos = window.mapPixelToCoords(mousePixelPos);
//        Event event;
//        while (window.pollEvent(event)) {
//            if (event.type == sf::Event::Closed)
//                window.close();
//     
//
//            else if (event.type == Event::MouseMoved)
//            {
//                torchPosition = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
//                updateGameElements();
//                updateFog(torchPosition);
//            }
//
//        // Render
//            window.clear();
//            drawGameElements(window); // Game board, ships, etc.
//            drawFog(window, torchPosition); // Overlay fog
//            window.display();
//    }
//}
//
//
//
