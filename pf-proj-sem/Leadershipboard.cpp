#include <sfml/graphics.hpp>
#include <sfml/window.hpp>
#include <sfml/audio.hpp>
#include <iostream>
#include "myfunctions.h"
#include"common.h"

ScreenState leaderboard(RenderWindow& window, View& gameview, Player players[100], int playerCount)
{
    ScreenState screenstate = LEADER;
    // Create a window with size 800x600 and title "Leaderboard"
    resizeView(window, gameview);
    window.setView(gameview);
    // Load texture for window background
    sf::Texture windowTexture;
    if (!windowTexture.loadFromFile("D:\\haajra\\battlefield_PF\\additional files\\2.png")) {
        std::cerr << "Error loading background texture!" << std::endl;
    }

    Texture backgroundtext;
    if (!backgroundtext.loadFromFile("d:\\haajra\\battlefield_pf\\additional files\\smoke-bw.jpg")) {
        cerr << "error loading texture!" << endl;
    }
    // Create a sprite for the background texture
    sf::Sprite background(windowTexture);
    background.setScale(
        (float)gameview.getSize().x / windowTexture.getSize().x,
        (float)gameview.getSize().y / windowTexture.getSize().y
    );
    const int topCount = 3;
    Player topThree[topCount];
    getTopThree(players, playerCount, topThree, topCount);

    for (int i = 0; i < topCount && i < playerCount; ++i) {
        std::cout << topThree[i].score << " " << topThree[i].name << "\n";
    }
    // Load a font for the text (ensure the font is in the correct path)
    sf::Font font;
    if (!font.loadFromFile("D:\\haajra\\battlefield_PF\\additional files\\crimson.semibold.ttf")) {
        std::cerr << "Error loading font!" << std::endl;
    }

    sf::Font headingfont;
    if (!headingfont.loadFromFile("D:\\haajra\\battlefield_PF\\additional files\\War is Over.ttf")) {
        std::cerr << "Error loading font!" << std::endl;
    }

    // Load a different font for the heading (use a different path for the heading font if needed)
    sf::Clock clock;
 
    // Heading text (brown color and different font)
    sf::Text heading;
    heading.setFont(headingfont);  // Using the new font for heading
    heading.setString("LEADERBOARD");
    heading.setCharacterSize(53);
    heading.setFillColor(sf::Color(139, 69, 19));  // Brown color
    heading.setPosition(300, 20);

    // Create the table (2 columns, 3 rows)
    sf::RectangleShape tableBackground(sf::Vector2f(600, 300));
    tableBackground.setTexture(&backgroundtext);
    tableBackground.setPosition(100, 120);  // Moved up

    // Create table columns and rows
    sf::VertexArray tableLines(sf::Lines, 4);

    // Column lines (vertical)
    tableLines[0].position = sf::Vector2f(300, 120);  // Adjusted
    tableLines[1].position = sf::Vector2f(300, 420);  // Adjusted

    tableLines[2].position = sf::Vector2f(500, 120);  // Adjusted
    tableLines[3].position = sf::Vector2f(500, 420);  // Adjusted

    // Row lines (horizontal)
    sf::VertexArray rowLines(sf::Lines, 4);
    rowLines[0].position = sf::Vector2f(100, 220);  // Adjusted
    rowLines[1].position = sf::Vector2f(700, 220);  // Adjusted

    rowLines[2].position = sf::Vector2f(100, 320);  // Adjusted
    rowLines[3].position = sf::Vector2f(700, 320);  // Adjusted

    // Data to be displayed in the table


    // Create the text for table content
    sf::Text tableText[6];
    for (int i = 0; i < 6; ++i) {
        tableText[i].setFont(font);
        tableText[i].setCharacterSize(34);
        tableText[i].setFillColor(Color::Black); 
        tableText[i].setOutlineColor(Color::White);
        tableText[i].setOutlineThickness(1);
// Brown color
    }

    // Set table text positions and values
    for (int i = 0; i < 3 && i < playerCount; ++i) {
        tableText[i].setString(topThree[i].name);
        tableText[i].setPosition(350.f, 160.f + (i * 80));  // Adjusted
    }

    for (int i = 3; i < 6 && i < playerCount + 3; ++i) {
        tableText[i].setString(to_string(topThree[i - 3].score));
        tableText[i].setPosition(500.f, 160.f + ((i - 3) * 80));  // Adjusted
    }

    // Create buttons
    sf::RectangleShape resumeButton(sf::Vector2f(175, 40));
    resumeButton.setFillColor(sf::Color(139, 69, 19,60));  // Brown button
    resumeButton.setPosition(150, 400);  // Moved up

    sf::Text resumeText;
    resumeText.setFont(font);
    resumeText.setString("Menu");
    resumeText.setCharacterSize(24);
    resumeText.setFillColor(sf::Color::White);
    resumeText.setOutlineColor(Color::Black);
    resumeText.setOutlineThickness(1.5);
    resumeText.setPosition(resumeButton.getPosition().x+20,resumeButton.getPosition().y);

    sf::RectangleShape newGameButton = resumeButton;  // Brown button
    newGameButton.setPosition(450, 400);  // Moved up

    sf::Text newGameText;
    newGameText.setFont(font);

    newGameText.setPosition(480, 410);

    newGameText = resumeText;
    newGameText.setString("New Game");
    newGameText.setPosition(480, newGameText.getPosition().y);
    // Exit Button (new button)
    sf::RectangleShape exitButton(sf::Vector2f(200, 50));
    exitButton.setFillColor(sf::Color(255, 0, 0));  // Red button
    exitButton.setPosition(300, 470);  // Placed between Resume and New Game

 

    // New Name and Same Name buttons (added the declaration and initialization)


    sf::RectangleShape sameNameButton(sf::Vector2f(300, 70));
    sameNameButton.setFillColor(sf::Color(139, 69, 19));
    sameNameButton.setPosition(250, 320);  // Adjusted position to be higher for better centering

    sf::Text sameNameText;
    sameNameText.setFont(font);
    sameNameText.setString("PLAYER NAME                          SCORE");
    sameNameText.setCharacterSize(28);
    sameNameText.setOutlineColor(Color::White);
    sameNameText.setOutlineThickness(0.5);
    sameNameText.setFillColor(Color(129, 59, 9));
    sameNameText.setPosition(tableBackground.getPosition().x+60,tableBackground.getPosition().y);  // Adjusted position


    bool additionalButtonsVisible = false;

    // default username for initialization
    string first, second, third;
    for (int i = 0; i < 6; i++)
    {
        tableText[i].setPosition(-300,tableText[i].getPosition().y);
     }

    float targetPosition = 180;
    float targetposition2 = 500;
    // Game loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            // Handle button clicks
            else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                Vector2i mousePixelPos = Mouse::getPosition(window); // Mouse position
                Vector2f mousePos = window.mapPixelToCoords(mousePixelPos);

                // Check if 'Resume Game' is clicked
                if (resumeButton.getGlobalBounds().contains(mousePos)) {
                    std::cout << "Resume Game button clicked.\n";
                    screenstate = MENU;
                    return screenstate;
  
                }

                // Check if 'New Game' is clicked
                if (newGameButton.getGlobalBounds().contains(mousePos))
                {
                    std::cout << "New Game button clicked.\n";
                    // Restart game logic here
                    screenstate = INITIAL;
                 
                    return screenstate;
                }


                // Check if 'New Name' is clicked (if additional buttons are visible)


            }


        }
        Time elapsed = clock.getElapsedTime();
        for (int i = 0; i < 3; i++)
        {
            if (tableText[i].getPosition().x < targetPosition) {
                float progress = elapsed.asSeconds() * 200; // Speed of the animation
                tableText[i].move(progress, 0);
                // Move horizontally
            }

            if (tableText[i + 3].getPosition().x < targetposition2)
            {
                float progress = elapsed.asSeconds() * 200; // Speed of the animation
                tableText[i+3].move(progress, 0);
            }
        }

        if (screenstate != LEADER)
        {
            return screenstate;
        }

        // Clear the window
        window.clear();

        // Draw everything
        window.draw(background);

        // Draw the heading and table if the additional buttons are not visible
        if (!additionalButtonsVisible) {
            window.draw(heading);
            window.draw(tableBackground);
         /*   window.draw(tableLines);
            window.draw(rowLines);*/

            // Draw table content
            for (int i = 0; i < 6; ++i) {
                window.draw(tableText[i]);
            }
            window.draw(sameNameText);
            // Draw other buttons (Resume and New Game)
            window.draw(resumeButton);
            window.draw(resumeText);
            window.draw(newGameButton);
            window.draw(newGameText);
        }

        // Draw Exit button
    

        // Draw the new buttons if they are visible

        // Display the contents of the window
        window.display();
    }
}