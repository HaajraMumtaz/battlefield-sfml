#ifndef COMMON_H
#define COMMON_H

#include "myfunctions.h"
#include <SFML/Graphics.hpp>
#include <string>

static string filename="scores.txt";
// Function declarations
ScreenState maingame(sf::RenderWindow& window, Board& board, sf::Texture& texture, int positions[5][2],View gameView, Player players[100], int &playerCount);

ScreenState screenOne(sf::RenderWindow& window, Board& board, sf::Texture& texture, int positions[5][2],
    sf::View gameView, ScreenState screenState, bool showPopup = true,
    bool mission = false, bool newGame = true);

ScreenState menu(sf::RenderWindow& window, sf::View gameView,Board board);

ScreenState MineMode(sf::RenderWindow& window, Board& board1, Board& board2, sf::Texture& texture,
    int positions1[5][2], int positions2[5][2], sf::View gameView,
    std::string name1, std::string name2);

ScreenState leaderboard(RenderWindow& window, View& gameview, Player players[100], int playerCount);
#endif // COMMON_H
