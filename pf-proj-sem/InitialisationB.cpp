#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include "myfunctions.h"
#include"common.h"
#include<fstream>
using namespace sf;
using namespace std;

enum ScreenState screenOne(sf::RenderWindow& window, Board& board, sf::Texture& texture, int positions[5][2], sf::View gameView, ScreenState nextstate, bool showpopup, bool mission,bool newgame)
{
    // Function definition
    bool showPopUp2 = showpopup;
    ScreenState screenstate;
    if (showpopup)
        screenstate = POPUP;
    else
        screenstate = INITIAL;
    string newusername;
    sf::Text usernameText;
    bool flag = true;
    sf::Font font;
    RectangleShape textbox(Vector2f(240.f, 30.f));
    RectangleShape continueButton(Vector2f(100.f, 25.f));
    bool clickstartgame = false;
    Text continueText("Continue", font, 20);

    // 2. Load the font
    if (!font.loadFromFile("D:\\haajra\\battlefield_PF\\additional files\\GeistMonoBold.ttf")) {
        std::cerr << "Error loading font!" << std::endl;

    }
    Text inputText("", font, 18);


    // 2. Load the font
   
    Texture popup2texture;
    if (!popup2texture.loadFromFile("D:\\haajra\\battlefield_PF\\additional files\\pop.png")) {
        std::cerr << "Error loading background texture!" << std::endl;
    }

    Texture initialbg;
    if (!initialbg.loadFromFile("D:\\haajra\\battlefield_PF\\additional files\\village.jpg")) {
        std::cerr << "Error loading background texture!" << std::endl;
    }
    sf::Sprite sprite(initialbg);

    
    Texture iniboardtex;
    if (!iniboardtex.loadFromFile("D:\\haajra\\battlefield_PF\\additional files\\iniboard.jpg")) {
        std::cerr << "Error loading background texture!" << std::endl;
    }
    RectangleShape iniboard(Vector2f(200, 300));
    iniboard.setPosition(Vector2f(50, 98));
    iniboard.setTexture(&iniboardtex);

    if (!texture.loadFromFile("D:\\haajra\\battlefield_PF\\additional files\\field-bg.jpg")) {
        cerr << "Error loading texture!" << endl;
    }

    //Texture popup2texture;
    //if (!popup2texture.loadFromFile("D:\\haajra\\battlefield_PF\\additional files\\instruction.jpeg")) {
    //    std::cerr << "Error loading background texture!" << std::endl;
    //}
    sf::Text instructions;
    instructions.setFont(font);
    std::string text = "1-Select a ship with \n"
        "your mouse and drag  \n"
        "it along the board \n"
        "2-Press tab and use \n"
        "left and right arrow \n "
        " keys for rotation \n"
        "3-Press enter button once \n "
        "location is \n"
        "confirmed";
    instructions.setString(text);
    instructions.setCharacterSize(14);
    instructions.setFillColor(sf::Color::Black);
    instructions.setPosition(sf::Vector2f(78.f, 150.f));


    std::string username = "";
 
    RectangleShape setmovablesq(float colsize, float rowsize, float scale = 1);
    

    const int width = 800;
    const int height = 600;


    sprite.setScale(
        static_cast<float>(width) / initialbg.getSize().x,
        static_cast<float>(height) / initialbg.getSize().y);
    window.setFramerateLimit(60);
    bool GridVal[10][10] = { 0 };
    /*  Texture texture;*/
   
    const int rows = 10, cols = 10;
    float cellSize = 50.f;


    float textureWidth = static_cast<float>(texture.getSize().x);
    float textureHeight = static_cast<float>(texture.getSize().y);

    float scaleX = static_cast<float>(width) / textureWidth / 2;
    float scaleY = static_cast<float>(height) / textureHeight / 2;
    float scale = min(scaleX, scaleY);

    float colsize = textureWidth / cols;
    float rowsize = textureHeight / rows;

    // Center the grid
    float gridOffsetY = width / 3;
    float gridOffsetX = height / 6;

    initializeSpriteGrid(board.grid, texture, rows, cols, colsize, rowsize, gridOffsetX, scale, gridOffsetY);

    RectangleShape movablesquare = setmovablesq(colsize, rowsize, scale);
    movablesquare.setPosition(board.grid[0][0].getPosition());

    // Ships (initialize on the right side of the board)
    float startypos = height * 0.517;
    board.ships[0] = Ship(3, colsize * scale - 8, rowsize * scale - 9, 700, 110); // Ship with 3 segments
    board.ships[1] = Ship(4, colsize * scale - 7, rowsize * scale - 8, 700, 160); // p=(segm,length,width,x pos, y pos)
    board.ships[2] = Ship(5, colsize * scale - 5, rowsize * scale - 6, 700, 210);
    board.ships[3] = Ship(3, colsize * scale - 8, rowsize * scale - 9, 700, 260);
    board.ships[4] = Ship(2, colsize * scale - 10, rowsize * scale - 11, 700, 310);
    // Ship with 5 segments

    //tempship details
    bool isDragging = false;
    int draggedShipIndex = -1;
    Vector2f offset;
    Ship tempship = board.ships[0];
    tempship.setColour(0, 0, 0, 0);
    tempship.setPosition(board.ships[0].getPosition());
    FloatRect shipBbox = tempship.getGlobalBounds();
    RectangleShape shipbox = setmovablesq(shipBbox.width, shipBbox.height);
    shipbox.setPosition(tempship.getPosition());
    Color greycol = Color(255, 255, 255, 100);
    //bounding box specs
    float gridx = (board.grid[0][0].getPosition().x - 5);
    float gridy = board.grid[0][0].getPosition().y - 5.0;
    Vector2f pos = Vector2f(gridx, gridy);
    float bboxvertical = board.grid[9][0].getPosition().y - pos.y + colsize * scale;
    float bboxhorizontal = board.grid[0][9].getPosition().x - pos.x + rowsize * scale;
    RectangleShape boundingbox = setmovablesq(bboxhorizontal + 5, bboxvertical + 5);
    boundingbox.setPosition(pos);
    FloatRect boundingboxglobal = boundingbox.getGlobalBounds();
    Vector2f rotationpoint = Vector2f((colsize * scale / 2), shipBbox.height / 2);
    RectangleShape boundingBoxShape;
    int countplaced = 0;
    //main logic 
    //flags
    bool vertical = 0;
    int selectedShipIndex = -1;
    bool shipClicked = 0, intersects = 0, fullyContained = 1, sameclicked = 0, KeyLock = 0;
    Vector2f horizontalOrigin, verticalorigin;
    double lastwidth = 0;
    for (int i = 0; i < 5; i++)
    {
        FloatRect localbounds = board.ships[i].getLocalBounds();
        horizontalOrigin = Vector2f(localbounds.width / 2, localbounds.height / 2);
        board.ships[i].setOrigin(localbounds.width / 2, localbounds.height / 2);
    }
    RectangleShape popup2(Vector2f(400, 200));

    FloatRect popup2Bounds = popup2.getGlobalBounds();

    /*resizeView(window, gameView);*/

    //start button 
    RectangleShape StartButton(Vector2f(100.f, 30.f));

    StartButton.setPosition(Vector2f(372, 450));
    StartButton.setFillColor(Color(139, 69, 19));
    StartButton.setOutlineColor(Color::White);
    StartButton.setOutlineThickness(3);


    Text startgameText("Start Game", font, 17.5);
    startgameText.setFillColor(Color::White);
    startgameText.setPosition(Vector2f(372, 455));
    while (window.isOpen())
    {
        Vector2i mousePixelPos = Mouse::getPosition(window); // Mouse position
        Vector2f mousePos = window.mapPixelToCoords(mousePixelPos);
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed) {
                window.close();
            }

            // Left Mouse Button Pressed
            if (screenstate == INITIAL)
            {
                if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
                {
                    // Check if a ship is clicked
                    shipClicked = false;
                    for (int i = 0; i < 5; i++) {
                        if (board.ships[i].getGlobalBounds().contains(mousePos))
                        {
                            if (intersects && selectedShipIndex != -1)
                            {
                                board.ships[selectedShipIndex].setSelected(false);
                                /* ships[j].setSelected(false);*/
                                selectedShipIndex = -1;

                            }
                            else

                            {
                                selectedShipIndex = i; // Mark the ship as selected
                                shipClicked = true;

                                // Update ship selection states
                                for (int j = 0; j < 5; j++)
                                {
                                    board.ships[j].setSelected(j == i); // Only the clicked ship is selected
                                }
                                break; // No need to check further ship
                            }
                        }
                    }

                    // If a grid cell is clicked and a ship is selected
                    if (((!shipClicked && selectedShipIndex != -1) || sameclicked))
                    {
                        bool boxClicked = false;

                        for (int k = 0; k < rows && !boxClicked; k++)
                        {
                            for (int l = 0; l < cols && !boxClicked; l++)
                            {
                                if (board.grid[k][l].getGlobalBounds().contains(mousePos))
                                {
                                    // Place the selected ship at the grid 
                                    if (fullyContained)
                                    {
                                        if (!intersects)
                                        {

                                            lastwidth = tempship.getGlobalBounds().width + tempship.getGlobalBounds().left;
                                            FloatRect thisbounds = board.ships[selectedShipIndex].getGlobalBounds();
                                            /*board.ships[selectedShipIndex].setPosition(thispos.x+abs(thisbounds.left-thispos.x),(thispos.y+abs(thisbounds.top-thispos.y)));*/

                                            /*          ships[selectedShipIndex].setRotation(tempship.getRotation());*/

                                            board.ships[selectedShipIndex].setPosition(tempship.getPosition());

                                            if (sameclicked)
                                                sameclicked = 0;
                                            else
                                                board.ships[selectedShipIndex].setSelected(false); // Deselect the ship
                                            selectedShipIndex = -1; // Clear the selection
                                            boxClicked = true; // Break out of the grid loop
                                        }
                                    }
                                    else
                                        board.ships[selectedShipIndex].setSelected(false);
                                }
                            }
                        }

                        // If no box was clicked, deselect the ship
                        if (!boxClicked)
                        {
                            board.ships[selectedShipIndex].setSelected(false);
                            selectedShipIndex = -1;
                        }


                    }
                    if (StartButton.getGlobalBounds().contains(mousePos))
                    {


                        for (int i = 0; i < rows; i++)
                        {
                            for (int j = 0; j < cols; j++)
                            {
                                for (int k = 0; k < 5; k++)
                                {

                                    Vector2f thispos = board.ships[k].getPosition();

                                    if (board.grid[i][j].getGlobalBounds().contains(thispos))
                                    {
                                        positions[k][0] = i;
                                        positions[k][1] = j;

                                        countplaced++;
                                    }
                                }

                            }

                        }

                        if (countplaced > 4)
                        {
                            clickstartgame = true;
                            screenstate = POPUP;

                        }
                        else
                        {
                            countplaced = 0;
                        }

                    }
                }
                // Mouse Moved (Highlight the grid cell under the mouse)
                else if (event.type == Event::MouseMoved)
                {

                    intersects = 0;

                    for (int i = 0; i < rows; i++) {
                        for (int j = 0; j < cols; j++) {
                            if (board.grid[i][j].getGlobalBounds().contains(mousePos))
                            {

                                if (selectedShipIndex != -1)
                                {
                                    if (board.ships[selectedShipIndex].getRotation() == 90)
                                        vertical = 1;
                                    else
                                        vertical = 0;

                                    FloatRect boundingBox = tempship.getGlobalBounds();

                                    boundingBoxShape.setSize(Vector2f(boundingBox.width, boundingBox.height));
                                    boundingBoxShape.setOrigin(tempship.getOrigin());

                                    // Customize the bounding box appearance
                                    boundingBoxShape.setOutlineThickness(2.0f);
                                    boundingBoxShape.setOutlineColor(Color::Red);
                                    boundingBoxShape.setFillColor(Color(0, 0, 0, 0));
                                    boundingBoxShape.setPosition(tempship.getPosition());
                                    movablesquare.setOutlineColor(Color::Transparent);
                                    tempship = board.ships[selectedShipIndex];
                                    FloatRect tempshipglobal = tempship.getLocalBounds();
                                    /*if (!vertical)
                                        tempship.setPosition(board.grid[i][j].getPosition().x + (colsize * scale / 2), board.grid[i][j].getPosition().y + (colsize * scale / 2));
                                    else
                                    {
                                        cout << "positioning vertical" << endl;
                                        tempship.setPosition(board.grid[i][j].getPosition().x + (colsize * scale / 2), board.grid[i][j].getPosition().y+ (colsize * scale / 2));
                                    }*/
                                    if (!vertical)
                                    {
                                        if (tempship.getSegments() % 2 != 0)
                                            tempship.setPosition(board.grid[i][j].getPosition().x - (tempshipglobal.height / 2), board.grid[i][j].getPosition().y + (colsize * scale / 2));
                                        else
                                            tempship.setPosition(board.grid[i][j].getPosition().x - (tempshipglobal.height / 10), board.grid[i][j].getPosition().y + (colsize * scale / 2));
                                    }
                                    else
                                        tempship.setPosition(board.grid[i][j].getPosition().x + (tempshipglobal.height / 2), board.grid[i][j].getPosition().y + (tempshipglobal.height / 2));
                                    tempshipglobal = tempship.getGlobalBounds();
                                    if (!intersects)
                                        boundingBoxShape.setPosition(tempship.getPosition());
                                    else
                                        tempship.setColour(0, 0, 0, 0);

                                    validplacement(tempship, board, selectedShipIndex, intersects, sameclicked, boundingboxglobal, tempshipglobal, fullyContained);
                                    FloatRect thisbounds = board.grid[i][j].getGlobalBounds();



                                }
                                else
                                {
                                    movablesquare.setOutlineColor(Color::Red);
                                    movablesquare.setPosition(board.grid[i][j].getPosition());
                                }

                            }
                        }
                    }
                }



                else if ((event.type == Event::KeyPressed) && (event.key.code == Keyboard::Right || event.key.code == Keyboard::Enter) &&
                    selectedShipIndex != -1)
                {
                    if (event.key.code == Keyboard::Right)
                    {

                        sf::Vector2f currentPosition = tempship.getPosition();
                        FloatRect preRotationBounds = tempship.getGlobalBounds();
                        FloatRect preRotationLocal = tempship.getLocalBounds();

                        // Perform the rotation
                        if (tempship.getRotation() == 0)
                        {
                            tempship.setRotation(90);
                            tempship.setOrigin(preRotationBounds.width / 2, preRotationBounds.height / 2);
                        }
                        else {
                            tempship.setRotation(0);
                            tempship.setOrigin(preRotationLocal.width / 2, preRotationLocal.height / 2);
                        }

                        // Get the ship's global bounds after rotation
                        FloatRect postRotationBounds = tempship.getGlobalBounds();

                        float offsetX = (preRotationBounds.left + preRotationBounds.width / 2) -
                            (postRotationBounds.left + postRotationBounds.width / 2);
                        float offsetY = (preRotationBounds.top + preRotationBounds.height / 2) -
                            (postRotationBounds.top + postRotationBounds.height / 2);

                        tempship.setPosition(currentPosition.x + offsetX, currentPosition.y + offsetY);
                        validplacement(tempship, board, selectedShipIndex, intersects, sameclicked, boundingboxglobal, tempship.getGlobalBounds(), fullyContained);
                    }

                    else if (event.key.code == Keyboard::Enter)
                    {
                        if (!intersects)
                        {
                            board.ships[selectedShipIndex].setOrigin(tempship.getOrigin());
                            board.ships[selectedShipIndex].setRotation(tempship.getRotation());
                            board.ships[selectedShipIndex].setPosition(tempship.getPosition());

                        }
                        if (board.ships[selectedShipIndex].getRotation() != 0)
                            cout << "\nBounding box calculations" << board.ships[selectedShipIndex].getGlobalBounds().width / 2 << "," <<
                            board.ships[selectedShipIndex].getGlobalBounds().height / 2 << "\norigin:"
                            << board.ships[selectedShipIndex].getOrigin().x << "," << board.ships[selectedShipIndex].getOrigin().y << "\nlocal bounds:" <<
                            board.ships[selectedShipIndex].getLocalBounds().width / 2 << "," <<
                            board.ships[selectedShipIndex].getLocalBounds().height / 2 << endl;
                        else
                            cout << "\nBounding box calculations" << board.ships[selectedShipIndex].getGlobalBounds().width / 2 << "," <<
                            board.ships[selectedShipIndex].getGlobalBounds().height / 2 << "\norigin:"
                            << board.ships[selectedShipIndex].getOrigin().x << "," << board.ships[selectedShipIndex].getOrigin().y << "\nlocal bounds:" <<
                            board.ships[selectedShipIndex].getLocalBounds().width / 2 << "," <<
                            board.ships[selectedShipIndex].getLocalBounds().height / 2 << endl;

                        /*        ships[selectedShipIndex].setOrigin(myorigin);*/
                        board.ships[selectedShipIndex].setSelected(false); // Reset tempship color
                        selectedShipIndex = -1;
                        vertical = 0;
                    }

                }
            }
          
            else if (screenstate == POPUP)
            {
                popup2.setPosition(sf::Vector2f(200, 150));
                popup2.setTexture(&popup2texture);

                usernameText.setFont(font);
                usernameText.setString("Enter Username");
                usernameText.setStyle(sf::Text::Underlined);
                usernameText.setCharacterSize(20);
                usernameText.setFillColor(sf::Color::White);
                usernameText.setPosition(sf::Vector2f(305, 200));


                textbox.setFillColor(Color::Black);
                textbox.setPosition(280, 240);



                continueButton.setFillColor(Color::Black);  // Green color
                continueButton.setPosition(350.f, 310.f);
                continueButton.setOutlineColor(Color::White);
                continueButton.setOutlineThickness(3);
                // Set up "Continue" text

                continueText.setFillColor(Color::White);
                continueText.setPosition(353.f, 310.f);


                inputText.setFillColor(Color::White);
                inputText.setPosition(310.f, 240.f);


                if (event.type == Event::TextEntered) 
                {
                    flag = true;
                    // If the user pressed Enter, save the username and return
                    if (event.text.unicode == '\r') {  // Enter key
                        // Save the username to a file in append mode
                        std::ofstream outFile("username.txt", std::ios::app);  // Open file in append mode
                        if (outFile.is_open()) {
                            outFile << username << "\n";  // Append the username followed by a newline
                            outFile.close();
                        }
                        else {
                            std::cerr << "Failed to append the username!" << std::endl;
                        }
                    }

                    // Handle backspace (remove last character)
                    if (event.text.unicode == '\b' && !username.empty()) {
                        username.pop_back();
                    }
                    // Handle normal text input (add character)
                    else if (event.text.unicode < 128) {
                        username += static_cast<char>(event.text.unicode);
                    }

                    // Update the text that displays the username
                    inputText.setString(username);
                }





                if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left && clickstartgame) {

                  
                  
                    if (StartButton.getGlobalBounds().contains(mousePos))
                    {

                      
                        for (int i = 0; i < rows; i++)
                        {
                            for (int j = 0; j < cols; j++)
                            {
                                for (int k = 0; k < 5; k++)
                                {

                                    Vector2f thispos = board.ships[k].getPosition();

                                    if (board.grid[i][j].getGlobalBounds().contains(thispos))
                                    {
                                        positions[k][0] = i;
                                        positions[k][1] = j;

                                        countplaced++;

                                    }
                                }

                            }
                            cout << "here";
                            screenstate = GAME; // Go back to game
                            clickstartgame = false;
                       
                            if (!mission)
                            {
                                getUsernameFromFile(newusername);

                                cout << newusername << "          vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv" << endl;

                            }
                            return nextstate;
                        }
                    }
                }

                else if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left && showPopUp2)
                {
                    if (continueButton.getGlobalBounds().contains(mousePos) && flag)
                    {
                        std::ofstream outFile("username.txt", std::ios::app);  // Open file in append mode
                        if (outFile.is_open()) {
                            outFile << username<<"\n";  // Append the username followed by a newline
                            outFile.close();
                        }
                        else {
                            std::cerr << "Failed to append the username!" << std::endl;
                        }
                        showPopUp2 = false;
                        screenstate = INITIAL;
                    }
                }




            }




            // Drawing the scene
            window.clear();
            window.draw(sprite);
            for (int i = 0; i < rows; ++i) {
                for (int j = 0; j < cols; ++j) {
                    window.draw(board.grid[i][j]);
                }
            }
            for (int i = 0; i < 5; i++) {
                window.draw(board.ships[i]);
            }
            if (selectedShipIndex != -1)
                window.draw(tempship);
            /* window.draw(boundingbox);
             window.draw(boundingBoxShape);*/

            window.draw(movablesquare);

            if (countplaced < 4)
                StartButton.setFillColor(greycol);
            else
                StartButton.setFillColor(Color(139, 69, 19));
            window.draw(StartButton);
            window.draw(startgameText);
            window.draw(iniboard);
            window.draw(instructions);
        
            if (showPopUp2)
            {
                window.draw(popup2);
                window.draw(usernameText);
                window.draw(textbox);
                window.draw(continueButton);
                window.draw(continueText);
                window.draw(inputText);

            }
            window.display();




        }
    }
}