#include<iostream>
#include"SFML/Graphics.hpp"
#include "myfunctions.h"
#include"common.h"
using namespace std;
using namespace sf;


int main()
{

    Player players[100];
    int playerCount;
    RenderWindow window(VideoMode::getDesktopMode(), "Screen Switch Example");
    int newmodestate = 0;
    ScreenState substate = GAME;
    cout << window.getSize().x << " " << window.getSize().y << endl;
    Board board;
    Texture texture;
    int positions[5][2] = { 0 };
    int positions2[5][2] = { 0 };
    View gameview(sf::FloatRect(0, 0, 800, 600));
    window.setView(gameview);
    //globalview.setCenter(400, 300);
    //window.setView(globalview);
    ScreenState currentState = MENU;
    Board board2 = board;
    string name1, name2;
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        if (currentState == MENU)
        {
            currentState = menu(window, gameview,board);

        }


        else if (currentState == CLASSIC)
        {
            substate=screenOne(window, board, texture, positions, gameview, GAME);

            if(substate==GAME)
                currentState=maingame(window, board, texture, positions, gameview,players, playerCount);
            
        }
        else if (currentState == NEWMODE)
        {
            if (newmodestate == 0)
            {
                newmodestate = 1;
                currentState = screenOne(window, board, texture, positions, gameview, NEWMODE, 1, 1, 1);
            

            }
            else if (newmodestate == 1)
            {
                getUsernameFromFile(name1);

                cout << name1;
                newmodestate = 2;
                currentState = screenOne(window, board2, texture, positions2, gameview, NEWMODE, 1, 1, 1);


            }
            else
            {
                   newmodestate = 0;
                getUsernameFromFile(name2);
                cout << name2;
                currentState = MineMode(window, board, board2, texture, positions, positions2, gameview, name1, name2);
             
            }


        }
        else if (currentState == SETTINGS)
        {
            continue;
        }
        else if (currentState == LEADER)
        {

            cout << "here capt";
            playerCount = readFile("leaderboard2.txt", players, 100);
            currentState = leaderboard(window, gameview,players,playerCount);

        }

    }

}






