#include <SFML/Graphics.hpp>
#define M_PI 3.14159265358979323846
#include <SFML/Audio.hpp>
#include <cmath>
#include <vector>
#include <iostream>
#include "common.h"
#include "myfunctions.h"

using namespace sf;
using namespace std;

ScreenState menu(RenderWindow& window, sf::View gameView,Board board)
{
    ScreenState screenstate = MENU;
    resizeView(window, gameView);
    window.setView(gameView);


    // Declare popups and UI elements
    RectangleShape popup2(Vector2f(400, 200)); // For the second popup
    RectangleShape popup3(Vector2f(400, 350)); // For the third popup
    sf::Text soundtext;       // For sound-related text
    sf::Text instructiontext; // For instruction-related text
    sf::Text headtext;        // For header in instructions popup
    sf::RectangleShape musicToggleButton(sf::Vector2f(40, 40)); // For the music toggle button
    sf::Text musicToggleText; // For text associated with music toggle button
    RectangleShape backButton(Vector2f(60.f, 25.f)); // For the back button
    sf::Text backText;        // For text of the back button
    sf::Text settingBack;

    const int WINDOW_WIDTH = 800;
    const int WINDOW_HEIGHT = 600;
    const int NUM_ICONS = 5;
    const float ICON_RADIUS = 125.0f;
    const float DIAMOND_SIZE = 50.0f;
    const float ROTATION_SPEED = 2.0f; // Speed of rotation (degrees per frame)
    const float ZOOM_SCALE = 1.2f;

    bool showpopup2 = false, showpopup3 = false;
    //sf::RectangleShape musicToggleButton(sf::Vector2f(50, 50));
    bool isMusicPlaying = true;
    // Center of the window
    sf::Vector2f center(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f);

    // Load background texture and sprite
    sf::Texture bgtexture;
    if (!bgtexture.loadFromFile("d:\\haajra\\battlefield_pf\\additional files\\warroomnew2.png"))
    {
        cout << "Background texture not found." << endl;

    }
    sf::Texture soundbtexture;
    if (!soundbtexture.loadFromFile("d:\\haajra\\battlefield_pf\\additional files\\soundbutton.PNG")) {
        std::cout << "texture not found";
    }
    sf::Texture popup3texture;
    if (!popup3texture.loadFromFile("d:\\haajra\\battlefield_pf\\additional files\\instruction.JPEG")) {
        std::cout << "texture not found";
    }
    sf::Sprite sprite(bgtexture);
    sprite.setScale(
        static_cast<float>(WINDOW_WIDTH) / bgtexture.getSize().x,
        static_cast<float>(WINDOW_HEIGHT) / bgtexture.getSize().y
    );

    // Load background music
    sf::Music backgroundMusic;
    if (!backgroundMusic.openFromFile("d:\\haajra\\battlefield_pf\\additional files\\warsound.mp3")) {
        cout << "Music not found." << endl;
    }
    else {
        backgroundMusic.setLoop(true);
        backgroundMusic.setVolume(50);
        backgroundMusic.play();
    }
    sf::Font font, headerFont;
    if (!font.loadFromFile("d:\\haajra\\battlefield_pf\\additional files\\GeistMonoBold.ttf") ||
        !headerFont.loadFromFile("d:\\haajra\\battlefield_pf\\additional files\\Stenstreet.ttf")) {
        cout << "Font not found." << endl;

    }
    std::string instructions =
        "1- The goal is to sink all of the \n"
        "opponent's ships first. \n"
        "2- Each player has a grid to place their \n"
        "ships secretly.\n"
        "3- Ships have different sizes.\n"
        "4- Player takes turns guessing a coordinate.\n"
        "5- If a guess hits a ship, the box is \n "
        "highlighted red; otherwise, green.'\n"
        "6- If all parts of a ship are hit \n "
        "the ship is highlighted black.'\n"
        "7- The computer guesses randomly or strategically \n "
        "during its turn.\n"
        "8- The game ends when one side sinks all the \n"
        "other’s ships.";



    //RectangleShape popup1(Vector2f(400, 200));
    //FloatRect popup1Bounds = popup1.getGlobalBounds();
    ////popup2 SETTINGS
    //RectangleShape popup2(Vector2f(400, 200));
    //FloatRect popup2Bounds = popup2.getGlobalBounds();
    //RectangleShape backButton(Vector2f(60.f, 25.f)); // For the back button
    //        // For text of the back button
    //sf::Text settingBack;
    //sf::Text musicToggleText;
    //sf::RectangleShape musicToggleButton(sf::Vector2f(40, 40)); // For the music toggle button
    //sf::Text soundtext;       // For sound-related text




    ////popup3 INSTRUCTIONS 
    //RectangleShape popup3(Vector2f(400, 350));
    //FloatRect popup3Bounds = popup3.getGlobalBounds();
    //RectangleShape backButton(Vector2f(60.f, 25.f));
    //Text backText("Back", font, 17.5);
    //backText.setFillColor(Color::White);
    //backText.setPosition(Vector2f(372, 450));
    //Text instructiontext;
    //Text headtext;
    //
    RectangleShape inspop(Vector2f(400, 200));
    FloatRect inspopBounds = inspop.getGlobalBounds();
    bool showinspop = false;
    // Header text
    sf::Text headerText;
    headerText.setFont(headerFont);
    headerText.setString("BattleScar");
    headerText.setCharacterSize(70);
    headerText.setFillColor(sf::Color::White);
    headerText.setPosition(WINDOW_WIDTH / 2.0f - headerText.getLocalBounds().width / 2.0f, 20);
    headerText.setOutlineThickness(10);
    headerText.setOutlineColor(sf::Color::Black);

    // Labels for menu items
    String labels[NUM_ICONS] = { "New Game", "Mission Mode", "Settings", "Instructions", "Leaderboard" };

    // Load textures
    sf::Texture textureFiles;
    if (!textureFiles.loadFromFile("d:\\haajra\\battlefield_pf\\additional files\\button1.jpg")) {
        cout << "Button texture not found." << endl;

    }

    // Create icons and text
    Icon icons[NUM_ICONS];
    sf::Text texts[NUM_ICONS];

    for (int i = 0; i < NUM_ICONS; ++i) {
        float angle = i * (360.0f / NUM_ICONS) + 90.0f;
        float rad = angle * (M_PI / 180.0f);
        float x = center.x + ICON_RADIUS * std::cos(rad);
        float y = center.y + ICON_RADIUS * std::sin(rad);

        createDiamond(icons[i], DIAMOND_SIZE);
        icons[i].texture = &textureFiles;
        icons[i].diamond.setTexture(icons[i].texture);
        icons[i].diamond.setPosition(x, y);
        icons[i].currentAngle = angle;

        texts[i].setFont(font);
        texts[i].setString(labels[i]);
        texts[i].setCharacterSize(20);
        texts[i].setFillColor(sf::Color::White);
        sf::FloatRect textBounds = texts[i].getLocalBounds();
        texts[i].setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
        texts[i].setPosition(x, y + DIAMOND_SIZE + 10);
    }

    // Menu state variables
    bool isRotating = false;
    int rotatingIconIndex = -1;
    int previousZoomedIndex = -1;

    // Main loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (screenstate == MENU) {
                sf::Vector2i mousePixelPos = sf::Mouse::getPosition(window);
                sf::Vector2f mousePos = window.mapPixelToCoords(mousePixelPos);

                // Hover effect
                for (int i = 0; i < NUM_ICONS; ++i) {
                    if (!isRotating && icons[i].diamond.getGlobalBounds().contains(mousePos)) {
                        icons[i].diamond.setOutlineColor(sf::Color::Yellow);
                        icons[i].diamond.setOutlineThickness(5.0f);
                    }
                    else if (i != previousZoomedIndex) {
                        icons[i].diamond.setOutlineColor(sf::Color::Transparent);
                        icons[i].diamond.setOutlineThickness(0.0f);
                    }
                }

                // Click handling
                if (!isRotating && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    for (int i = 0; i < NUM_ICONS; ++i) {
                        if (icons[i].diamond.getGlobalBounds().contains(mousePos)) {
                            if (previousZoomedIndex != -1 && previousZoomedIndex != i) {
                                icons[previousZoomedIndex].diamond.setFillColor(sf::Color::White);
                                icons[previousZoomedIndex].diamond.setScale(1.0f, 1.0f);
                                icons[previousZoomedIndex].diamond.setOutlineThickness(0.0f);
                                icons[previousZoomedIndex].isZoomedIn = false;
                            }
                            else if (previousZoomedIndex == i)
                            {
                                if (i == 0)//newgame 
                                {

                                    screenstate = CLASSIC;
                                    return screenstate;
                                }
                                else if (i == 1)
                                {
                                    screenstate = NEWMODE;
                                    return screenstate;
                                }

                                else if (i == 2)//settings 
                                {
                                    screenstate = POPUP;
                                    showpopup2 = 1;
                                    previousZoomedIndex = -1;
                                }
                                else if (i == 3)//instructions 
                                {
                                    screenstate = POPUP;
                                    showpopup3 = 1;
                                    previousZoomedIndex = -1;
                                }
                                  else if (previousZoomedIndex == 4)
                                  {
                                      screenstate = LEADER;
                                      return screenstate;
                                  }
                            }
                            isRotating = true;
                            rotatingIconIndex = i;
                            icons[i].diamond.setFillColor(sf::Color::Green);
                            icons[i].diamond.setScale(ZOOM_SCALE, ZOOM_SCALE);
                            icons[i].diamond.setOutlineColor(sf::Color::Yellow);
                            icons[i].diamond.setOutlineThickness(5.0f);
                            icons[i].isZoomedIn = true;
                            previousZoomedIndex = i;
                            break;
                        }
                    }
                }
            }
        }

        // Rotation logic
        if (isRotating) {
            float targetAngle = -270.0f;
            float& currentAngle = icons[rotatingIconIndex].currentAngle;
            float diff = targetAngle - currentAngle;

            if (diff > 180.0f) diff -= 360.0f;
            if (diff < -180.0f) diff += 360.0f;

            if (std::abs(diff) > ROTATION_SPEED) {
                currentAngle += (diff > 0 ? ROTATION_SPEED : -ROTATION_SPEED);
            }
            else {
                currentAngle = targetAngle;
                isRotating = false;
            }

            for (int i = 0; i < NUM_ICONS; ++i) {
                float angleStep = 360.0f / NUM_ICONS;
                icons[i].currentAngle = fmod(currentAngle + (i - rotatingIconIndex) * angleStep + 360.0f, 360.0f);
                float rad = icons[i].currentAngle * (M_PI / 180.0f);
                float x = center.x + ICON_RADIUS * std::cos(rad);
                float y = center.y + ICON_RADIUS * std::sin(rad);

                icons[i].diamond.setPosition(x, y);
                texts[i].setPosition(x, y + DIAMOND_SIZE + 10);
            }
        }
        else if (screenstate == POPUP)
        {
            if (showpopup3)//instructions 
            {
                popup3.setPosition(sf::Vector2f(200, 140));
                showpopup2 = 0;


                popup3.setTexture(&popup3texture);


                instructiontext.setFont(font);
                instructiontext.setString(instructions);
                instructiontext.setCharacterSize(12);
                instructiontext.setFillColor(sf::Color::White);
                instructiontext.setPosition(sf::Vector2f(230, 225));

                headtext.setFont(headerFont);
                headtext.setString("Instructions");
                headtext.setCharacterSize(35);
                headtext.setFillColor(sf::Color::White);
                headtext.setPosition(sf::Vector2f(240, 170));

                backButton.setPosition(Vector2f(372, 450));
                backButton.setFillColor(Color::Black);
                backButton.setOutlineThickness(4);

                backText.setFont(font);
                backText.setString("Back");
                backText.setCharacterSize(16);
                backText.setFillColor(sf::Color::White);
                backText.setPosition(sf::Vector2f(383.f, 450.f));


                if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left && showpopup3)
                {
                    sf::Vector2i mousePixelPos = sf::Mouse::getPosition(window);
                    sf::Vector2f mousePos = window.mapPixelToCoords(mousePixelPos);
                    if (backButton.getGlobalBounds().contains(mousePos))
                    {

                        showpopup3 = false;

                        screenstate = MENU;
                    }
                }

            }
            else if (showpopup2)///instruction 
            {





                popup2.setPosition(sf::Vector2f(200, 150));
                popup2.setTexture(&popup3texture);
                soundtext.setFont(headerFont);
                soundtext.setString("Settings");
                soundtext.setCharacterSize(35);
                soundtext.setFillColor(sf::Color::White);
                soundtext.setPosition(sf::Vector2f(280, 170));
                soundtext.setOutlineColor(Color::Black);

                backButton.setPosition(Vector2f(372, 300));
                backButton.setFillColor(Color::Black);
                backButton.setOutlineColor(Color::White);
                backButton.setOutlineThickness(4);




                musicToggleButton.setPosition(Vector2f(320, 230));

                musicToggleButton.setTexture(&soundbtexture);




                musicToggleText.setFont(font);
                musicToggleText.setString("Click to Mute");
                musicToggleText.setCharacterSize(14);
                musicToggleText.setFillColor(sf::Color::White);
                musicToggleText.setPosition(370, 240);

                settingBack.setFont(font);
                settingBack.setString("Back");
                settingBack.setCharacterSize(16);
                settingBack.setFillColor(sf::Color::White);
                settingBack.setPosition(382, 302);



                if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left && showpopup2) {

                    sf::Vector2i mousePixelPos = sf::Mouse::getPosition(window);
                    sf::Vector2f mousePos = window.mapPixelToCoords(mousePixelPos);
                    if (musicToggleButton.getGlobalBounds().contains(mousePos)) {
                        if (isMusicPlaying) {
                            backgroundMusic.stop();
                        }
                        else {
                            backgroundMusic.play();


                        }
                        isMusicPlaying = !isMusicPlaying;
                    }
                }




                showpopup3 = 0;

                if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left && showpopup2)
                {
                    sf::Vector2i mousePixelPos = sf::Mouse::getPosition(window);
                    sf::Vector2f mousePos = window.mapPixelToCoords(mousePixelPos);
                    if (backButton.getGlobalBounds().contains(mousePos))
                    {

                        showpopup2 = false;

                        screenstate = MENU;
                    }
                }

            }

        }

        // Render
        window.clear();
        window.draw(sprite);
        window.draw(headerText);

        for (int i = 0; i < NUM_ICONS; ++i) {
            window.draw(icons[i].diamond);
            window.draw(texts[i]);
        }

        if (screenstate == POPUP) {
            if (showpopup2) {
                window.draw(popup2);
                window.draw(soundtext);
                window.draw(backButton);
                window.draw(settingBack);
                window.draw(musicToggleButton);
                window.draw(musicToggleText);
            }
            if (showpopup3) {
                window.draw(popup3);
                window.draw(instructiontext);
                window.draw(headtext);
                window.draw(backButton);
                window.draw(backText);
            }



        }

        window.display();
    }
}
