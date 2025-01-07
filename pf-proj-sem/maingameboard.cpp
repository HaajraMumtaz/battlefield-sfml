#include <SFML/Graphics.hpp>

#include <iostream>
#include <vector>
#include <cmath>
#include "myfunctions.h"
#include"common.h"
using namespace sf;
using namespace std;


ScreenState maingame(sf::RenderWindow& window, Board board, sf::Texture& texture, int positions[5][2], sf::View gameView, Player players[100], int& playerCount)
{
	ScreenState screenstate = GAME;
	void initializeSpriteGrid(Sprite grid[10][10], Texture & texture, int rows, int cols, float colsize, float rowsize, int offset, float scale, int tempoffsety = 66);
	void draw(RenderWindow & window, Sprite grid[10][10], int rows, int cols, RectangleShape movablesquare);
	RectangleShape setmovablesq(float colsize, float rowsize, float scale);
	RectangleShape setwoodenbox(Texture & texturewood, float width, float height, float positionx, float positiony);
	RectangleShape setmovablesq(float colsize, float rowsize, float scale = 1);
	srand(time(NULL));

	RectangleShape backgroundshape;
	//resizeView(window, gameView);
	RectangleShape overlay;
	const int rows = 10;
	const int cols = 10;
	int width = 800, height = 600;
	bool player = 1;
	//make the texttures
	/*Texture texture;
	if (!texture.loadFromFile("D:\\haajra\\battlefield_PF\\additional files\\field-bg.jpg")) {
		cerr << "Error loading texture!" << endl;
	}*/
	Texture texturewood;
	if (!texturewood.loadFromFile("d:\\haajra\\battlefield_pf\\additional files\\box_texture.jpeg")) {
		cerr << "error loading texture!" << endl;

	}

	Texture background;
	if (!background.loadFromFile("d:\\haajra\\battlefield_pf\\additional files\\bg11.png")) {
		cerr << "error loading texture!" << endl;
	}

	Texture homeButton;
	if (!homeButton.loadFromFile("d:\\haajra\\battlefield_pf\\additional files\\home1.png")) {
		cerr << "error loading texture!" << endl;
	}

	Texture play;
	if (!play.loadFromFile("d:\\haajra\\battlefield_pf\\additional files\\soundplay1.png")) {
		cerr << "error loading texture!" << endl;
	}
	Texture stop;
	if (!stop.loadFromFile("d:\\haajra\\battlefield_pf\\additional files\\nosound1.png")) {
		cerr << "error loading texture!" << endl;
	}
	Texture popup1tex;
	if (!popup1tex.loadFromFile("d:\\haajra\\battlefield_pf\\additional files\\instruction.JPEG")) {
		cerr << "error loading texture!" << endl;
	}
	sf::Font font, headerFont;
	if (!font.loadFromFile("d:\\haajra\\battlefield_pf\\additional files\\GeistMonoBold.ttf") ||
		!headerFont.loadFromFile("d:\\haajra\\battlefield_pf\\additional files\\Stenstreet.ttf")) {
		std::cout << "Font not found." << endl;

	}

	Music sound;
	if (!sound.openFromFile("d:\\haajra\\battlefield_pf\\additional files\\warsound.mp3")) {
		cout << "Music not found." << endl;
	}
	else {
		sound.setLoop(true);
		sound.setVolume(50);
		sound.play();
	}
	string secondlast, lastname;

	getLastTwoLines("username.txt", secondlast, lastname);
	//make the window
	//RenderWindow window(VideoMode(width, height), "Board");
	/*cout << "oooooooooooooooooooooo       " << lastname << endl;*/
	const int maxPlayers = 100;
	playerCount = readFile("leaderboard2.txt", players, maxPlayers);
	Player player1;
	Player player2;
	Sprite grid2[rows][cols];
	int gridval[10][10] = { 0 };
	int gridval2[10][10] = { 0 };
	// Get the texture size
	float textureWidth = static_cast<float>(texture.getSize().x);
	float textureHeight = static_cast<float>(texture.getSize().y);
	// Calculate scale factor to fit the window size

	float InitialscaleX = static_cast<float>(width) / textureWidth / 2;
	float InitialscaleY = static_cast<float>(height) / textureHeight / 2;
	float initialscale = min(InitialscaleX, InitialscaleY);

	RectangleShape popup1(Vector2f(400, 200));

	FloatRect popup1Bounds = popup1.getGlobalBounds();

	RectangleShape popup2(Vector2f(400, 200));

	FloatRect popup2Bounds = popup2.getGlobalBounds();
	bool showpopup1 = 0;
	bool showpopup2 = 0;
	float scaleX = static_cast<float>(width) / textureWidth / 3;
	float scaleY = static_cast<float>(height) / textureHeight / 3;
	float scale = std::max(scaleX, scaleY);

	float ratio = scale / initialscale;
	// Set size of each grid cell and general position
	float colsize = textureWidth / (cols);
	float rowsize = textureHeight / (rows);
	int offset = (width / 2 - (textureWidth * scale)) / 2;
	int offsety = (width / 2 + offset);
	//cout << ratio << endl;

	int shipnum;
	MarkedPoints CompPoints[5][5];
	MarkedPoints PlayerPoints[5][5];

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			CompPoints[i][j].Coord = PlayerPoints[i][j].Coord = Vector2i(-1, -1);
			CompPoints[i][j].hit = PlayerPoints[i][j].hit == 0;
		}
	}

	// Initialize the sprites
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			board.grid[i][j].setPosition(j * colsize * scale + offset, i * rowsize * scale + offset + 2);
		}

	}

	bool vertical;
	for (int i = 0; i < 5; i++)
	{
		vertical = rand() & 2;
		ComputerInitialize(gridval2, board, i, vertical, CompPoints);
		/*	cout << "vertical:" << vertical << endl << endl;*/
	}

	/*for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			cout << gridval2[i][j] << " ";
		}
		cout << endl;
	}*/
	RectangleShape shipboxx;

	//EXIT MENU BUTTON

	CircleShape exitmenubutton(40);
	exitmenubutton.setTexture(&homeButton);
	exitmenubutton.setPosition(0, 0);
	sf::Text backText;
	sf::Text exitGameText;
	sf::Text reallyexitText;
	sf::Text exitGameText2;

	RectangleShape backButton(Vector2f(60.f, 25.f));
	RectangleShape exitGameButton(Vector2f(100.f, 25.f));


	//SOUND
	CircleShape playButton(40);
	CircleShape stopButton(40);
	playButton.setTexture(&play);
	playButton.setPosition(60, 0);
	stopButton.setTexture(&stop);
	stopButton.setPosition(120, 0);



	RectangleShape popup4(Vector2f(400, 300));
	FloatRect popup4Bounds = popup4.getGlobalBounds();


	Text playerScoreText;
	Text computerScoreText;
	Texture scorebg;
	if (!scorebg.loadFromFile("d:\\haajra\\battlefield_pf\\additional files\\throne.JPG")) {
		cerr << "error loading texture!" << endl;
	}
	popup4.setTexture(&scorebg);
	computerScoreText.setFont(font);
	playerScoreText.setFont(font);
	playerScoreText.setCharacterSize(24);
	playerScoreText.setFillColor(Color::White);
	playerScoreText.setOutlineColor(Color::Black);
	playerScoreText.setOutlineThickness(2);
	popup4.setPosition(sf::Vector2f(200, 150));
	playerScoreText.setPosition(popup4.getPosition().x + 50, popup4.getPosition().y + 50);
	computerScoreText.setCharacterSize(24);
	computerScoreText.setFillColor(Color::White);
	computerScoreText.setOutlineColor(Color::Black);
	computerScoreText.setOutlineThickness(2);
	computerScoreText.setPosition(popup4.getPosition().x + 50, popup4.getPosition().y + 100);
	Text winnerText;
	winnerText.setFont(font);
	winnerText.setCharacterSize(36);
	winnerText.setFillColor(Color::White);
	winnerText.setOutlineColor(Color::Black);
	winnerText.setOutlineThickness(2);
	winnerText.setPosition(popup4.getPosition().x + 50, popup4.getPosition().y + 150);

	Clock clock;
	Color greycol = Color(255, 255, 255, 100);
	RectangleShape movablesquare = setmovablesq(colsize, rowsize, scale);
	initializeSpriteGrid(grid2, texture, rows, cols, colsize, rowsize, offset, scale, offsety);
	//Making a box
	int positionybox = (textureHeight * scale) + 2 * offset;
	float gridx = (board.grid[0][0].getPosition().x - 5);
	float gridy = board.grid[0][0].getPosition().y - 5.0;
	Vector2f pos = Vector2f(gridx, gridy);
	float bboxvertical = board.grid[9][0].getPosition().y - pos.y + colsize * scale;
	float bboxhorizontal = board.grid[0][9].getPosition().x - pos.x + rowsize * scale;
	RectangleShape boundingbox = setmovablesq(bboxhorizontal + 5, bboxvertical + 5);
	boundingbox.setPosition(pos);

	float grid2x = (grid2[0][0].getPosition().x - 5);
	float grid2y = grid2[0][0].getPosition().y - 5.0;
	pos = Vector2f(grid2x, grid2y);
	float bbox2vertical = grid2[9][0].getPosition().y - pos.y + colsize * scale;
	float bbox2horizontal = grid2[0][9].getPosition().x - pos.x + rowsize * scale;
	RectangleShape boundingbox2 = setmovablesq(bbox2horizontal + 5, bbox2vertical + 5);
	boundingbox2.setPosition(pos);
	RectangleShape box = setwoodenbox(texturewood, textureWidth * scale, 175, offset, positionybox);
	RectangleShape box2 = setwoodenbox(texturewood, textureWidth * scale, 175, offsety, positionybox);

	int playerscore = 100, compscore = 100;
	float colwidth = (textureWidth * scale) / 5;
	float newscale = scale * ratio;
	ShipsHit SetOne[5] =
	{
		  0,Ship(3, rowsize * 2 * scale / 3, rowsize * scale,600, 110), // Ship with 3 segments
		  0,Ship(4, rowsize * 2 * scale / 3, rowsize * scale, 600, 160), // p=(segm,length,width,x pos, y pos)
		  0,Ship(5,rowsize * 2 * scale / 3, rowsize * scale, 600, 210),
		  0,Ship(3, rowsize * 2 * scale / 3, rowsize * scale, 600, 260),
		 0,Ship(2, rowsize * 2 * scale / 3, rowsize * scale, 600, 310)
		 // Ship with 5 segments
	};

	ShipsHit SetTwo[5] =
	{
		  0,Ship(3, rowsize * 2 * scale / 3, rowsize * scale,600, 110), // Ship with 3 segments
		  0,Ship(4,rowsize * 2 * scale / 3, rowsize * scale, 600, 160), // p=(segm,length,width,x pos, y pos)
		  0,Ship(5,rowsize * 2 * scale / 3, rowsize * scale, 600, 210),
		  0,Ship(3, rowsize * scale / 2, rowsize * scale, 600, 260),
		 0,Ship(2, rowsize * 2 * scale / 3, rowsize * scale, 600, 310)
		 // Ship with 5 segments
	};
	cout << colsize * scale << "   " << rowsize * scale << "______________________________" << endl;
	// Cache ship bounds and positions
	FloatRect shipBounds[5];
	for (int k = 0; k < 5; k++) {
		board.ships[k].setScale(ratio, ratio);
		int row = positions[k][0];
		int col = positions[k][1];
		board.ships[k].setPosition(
			board.grid[row][col].getPosition().x + (rowsize * scale / 1.5),
			board.grid[row][col].getPosition().y + (colsize * scale / 2)
		);
		SetOne[k].ship.setRotation(90);
		SetOne[k].ship.setPosition(30 + (colwidth * k) + box.getPosition().x, box.getPosition().y + 20);
		SetTwo[k].ship.setRotation(90);
		SetTwo[k].ship.setPosition(30 + (colwidth * k) + box2.getPosition().x, box2.getPosition().y + 20);
		shipBounds[k] = board.ships[k].getGlobalBounds();
	}


	// Iterate over the grid
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			FloatRect boxglbl = board.grid[i][j].getGlobalBounds();

			// Check for intersections with all ships
			for (int k = 0; k < 5; k++) {
				float intersectionArea = 0;
				if (DoesIntersect(boxglbl, shipBounds[k], intersectionArea)) {
					if (intersectionArea / (boxglbl.width * boxglbl.height) >= 0.25) {
						gridval[i][j] = 1; // Mark the grid cell as intersected
						int elem = Lastelement(PlayerPoints, k);
						PlayerPoints[k][elem].Coord = Vector2i(i, j);
						cout << "for ship:" << k << " part number:" << elem << " val:" << i << "," << j << endl;
					}
				}
			}
		}
	}
	bool placed = 0;
	int playerhitcount = 0, comphitcount = 0;
	//Handling Events
	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed) {
				window.close();
			}

			if (screenstate == GAME)
			{
				if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
				{
					Vector2i mousePixelPos = Mouse::getPosition(window); // Mouse position
					Vector2f mousePos = window.mapPixelToCoords(mousePixelPos);


					if (playButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
						if (sound.getStatus() != sf::Music::Playing) { // Only play if not already playing
							sound.play();
						}
					}

					// Check if the stop button is clicked
					if (stopButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
						if (sound.getStatus() == sf::Music::Playing) { // Only stop if playing
							sound.stop();
						}
					}
					if (player)
					{
						placed = 0;
						for (int i = 0; i < rows && !placed; i++)
						{
							for (int j = 0; j < cols && !placed; j++)
							{
								FloatRect cellBounds = board.grid[i][j].getGlobalBounds();
								FloatRect cellBounds2 = grid2[i][j].getGlobalBounds();

								if (cellBounds2.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
								{

									cout << "here at:" << i << "," << j << endl;
									if (gridval2[i][j] == 0)
									{
										grid2[i][j].setColor(Color::Green);
										placed = 1;


									}
									else if (gridval2[i][j] == 1)
									{
										grid2[i][j].setColor(Color::Red);
										placed = 1;
									}
									playerscore--;
									if (placed)
									{
										bool exists = 0;
										if (AllSunk(CompPoints, Vector2i(i, j), shipnum, exists, board) && exists)
										{
											for (int i = 0; i < board.ships[shipnum].getSegments(); i++)
											{
												grid2[CompPoints[shipnum][i].Coord.x][CompPoints[shipnum][i].Coord.y].setColor(Color::Black);
											}
											SetTwo[shipnum].hit = 1;
											playerhitcount++;
											if (playerhitcount == 5)
											{
												cout << "player won!" << endl;
												player2.name = "Computer";
												player2.score = compscore;

												player1.name = lastname;
												player1.score = playerscore;
												std::cout << "Player Count Before Writing: " << playerCount << "\n";

												computerScoreText.setString("Computer Score: " + to_string(compscore));
												playerScoreText.setString("Player Score: " + to_string(playerscore));
												updateOrAppend(players, playerCount, maxPlayers, player1);

												winnerText.setString("Player Wins!");
												writeFile("leaderboard2.txt", players, playerCount);
												std::cout << "Player Count after Writing: " << playerCount << "\n";
												screenstate = POPUP;
												showpopup2 = 1;
												/*	leaderboard(window, gameView);*/
											}
										}


										gridval2[i][j] = 2;
										boundingbox.setFillColor(Color::Transparent);
										boundingbox2.setOutlineColor(greycol);
										boundingbox2.setFillColor(greycol);
										movablesquare.setPosition(board.grid[0][0].getPosition());
										player = !player;
										clock.restart();
										cout << "here where should be";

									}

								}
							}
						}


						if (exitmenubutton.getGlobalBounds().contains(mousePos))
						{
							cout << "yes bro" << endl;
							showpopup1 = true;
							screenstate = POPUP;
						}

					}


				}


				else if (event.type == Event::MouseMoved)
				{
					Vector2i mousePixelPos = Mouse::getPosition(window); // Mouse position
					Vector2f mousePos = window.mapPixelToCoords(mousePixelPos);

					for (int i = 0; i < rows; i++) {
						for (int j = 0; j < cols; j++) {
							FloatRect cellBounds = board.grid[i][j].getGlobalBounds();
							FloatRect cellBounds2 = grid2[i][j].getGlobalBounds();
							if(player)
							{
								if (cellBounds2.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
									boundingbox.setOutlineColor(greycol);
									boundingbox.setFillColor(greycol);
									movablesquare.setPosition(j * colsize * scale + offsety, i * rowsize * scale + offset);
									break;
								}
							}


						}
					}
				}
				else if (event.type == Event::KeyPressed && event.key.code == Keyboard::Tab)
				{
					for (int i = 0; i < 10; i++)
					{
						for (int j = 0; j < 10; j++)
							cout << gridval[i][j] << " ";
					}
					cout << endl;
				}
			}
			else if (screenstate == POPUP)
			{
				if (showpopup1)///instruction 
				{
					popup1.setPosition(sf::Vector2f(200, 150));
					popup1.setTexture(&popup1tex);
					/*	soundtext.setFont(headerFont);
						soundtext.setString("Settings");
						soundtext.setCharacterSize(35);
						soundtext.setFillColor(sf::Color::White);
						soundtext.setPosition(sf::Vector2f(280, 170));
						soundtext.setOutlineColor(Color::Black);*/

					backButton.setPosition(Vector2f(330, 280));
					backButton.setFillColor(Color::Black);


					backText.setFont(font);
					backText.setString("Back");
					backText.setCharacterSize(16);
					backText.setFillColor(sf::Color::White);
					backText.setPosition(sf::Vector2f(335.f, 280.f));


					exitGameText.setFont(headerFont);
					exitGameText.setString("Exit Game");
					exitGameText.setCharacterSize(25);
					exitGameText.setFillColor(sf::Color::White);
					exitGameText.setOutlineColor(sf::Color::Black);
					exitGameText.setOutlineThickness(6);
					exitGameText.setPosition(sf::Vector2f(310.f, 180.f));

					reallyexitText.setFont(font);
					reallyexitText.setString("Do you really want to exit?");
					reallyexitText.setCharacterSize(16);
					reallyexitText.setFillColor(sf::Color::White);
					reallyexitText.setPosition(sf::Vector2f(280.f, 240.f));

					exitGameButton.setPosition(Vector2f(400, 280));
					exitGameButton.setFillColor(Color::Black);

					exitGameText2.setFont(font);
					exitGameText2.setString("Exit Game");
					exitGameText2.setCharacterSize(16);
					exitGameText2.setFillColor(sf::Color::White);
					exitGameText2.setPosition(sf::Vector2f(400.f, 280.f));



					//musicToggleButton.setPosition(Vector2f(280, 230));

					//musicToggleButton.setTexture(&soundbtexture);



					//musicToggleText.setFont(font);
					//musicToggleText.setString("Click to Mute");
					//musicToggleText.setCharacterSize(14);
					//musicToggleText.setFillColor(sf::Color::White);
					//musicToggleText.setPosition(380, 230);
					if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left && showpopup1) {

						sf::Vector2i mousePixelPos = sf::Mouse::getPosition(window);
						sf::Vector2f mousePos = window.mapPixelToCoords(mousePixelPos);
						/*if (musicToggleButton.getGlobalBounds().contains(mousePos)) {
							if (isMusicPlaying) {
								backgroundMusic.stop();
							}
							else {
								backgroundMusic.play();

							}
							isMusicPlaying = !isMusicPlaying;
						}*/
						if (backButton.getGlobalBounds().contains(mousePos))
						{

							showpopup1 = false;

							screenstate = GAME;

						}
						else if (exitGameButton.getGlobalBounds().contains(mousePos))
						{

							showpopup1 = false;

							screenstate = MENU;
							return screenstate;
						}
					}
				}

				if (event.type == Event::KeyPressed && event.key.code == Keyboard::Enter && showpopup2)
				{
					screenstate = LEADER;
					return screenstate;
					showpopup2 = 0;
				}

			}


			Vector2f dimensions(width, height);
			backgroundshape.setTexture(&background);
			backgroundshape.setSize(dimensions);
			backgroundshape.setPosition(0, 0);
		}
		
	
		if (!player)////randomized computer turn
		{

			int i = 0;
			int j = 0;
			placed = 0;




			// Update the timer once per second
			if (clock.getElapsedTime().asSeconds() >= 1.0f)
			{
				while (placed == 0)
				{
					placed = randomStrike(gridval, i, j);

				}
				compscore--;
				bool exists = 0;
				if (gridval[i][j] == 1)
				{
					board.grid[i][j].setColor(Color::Red);

					gridval[i][j] = 2;
				}
				else if (gridval[i][j] == 0)
				{
					board.grid[i][j].setColor(Color::Green);
					gridval[i][j] = 2;
				}


				if (AllSunk(PlayerPoints, Vector2i(i, j), shipnum, exists, board) && exists)
				{
					for (int i = 0; i < board.ships[shipnum].getSegments(); i++)
					{
						board.grid[PlayerPoints[shipnum][i].Coord.x][PlayerPoints[shipnum][i].Coord.y].setColor(Color::Black);

					}

					SetOne[shipnum].hit = 1;
					comphitcount++;


					if (comphitcount == 5)
					{

						player2.name = "Computer";
						player2.score = compscore;

						player1.name = lastname;
						player1.score = playerscore;

						std::cout << "Player Count Before Writing: " << playerCount << "\n";

						updateOrAppend(players, playerCount, maxPlayers, player2);

						computerScoreText.setString("Computer Score: " + to_string(compscore));
						playerScoreText.setString("Player Score: " + to_string(playerscore));

						winnerText.setString("computer won!");
						writeFile("leaderboard2.txt", players, playerCount);
						std::cout << "Player Count after Writing: " << playerCount << "\n";
						screenstate = POPUP;
						showpopup2 = 1;
						/*leaderboard(window, gameView);*/
					}
				}

				gridval[i][j] = 2;
				boundingbox2.setFillColor(Color::Transparent);
				boundingbox.setOutlineColor(greycol);
				boundingbox.setFillColor(greycol);
				movablesquare.setPosition(grid2[0][0].getPosition());
				player = !player;

			}
			
		}


		window.clear();//clearing


		window.draw(backgroundshape);//drawing
		draw(window, board.grid, rows, cols, movablesquare);
		draw(window, grid2, rows, cols, movablesquare);
		window.draw(box);
		window.draw(box2);
		window.draw(boundingbox);
		window.draw(boundingbox2);
		window.draw(exitmenubutton);
		window.draw(playButton);
		window.draw(stopButton);

		for (int i = 0; i < 5; i++) {

			if (SetOne[i].hit != 1)
				window.draw(SetOne[i].ship);
			if (SetTwo[i].hit != 1)
				window.draw(SetTwo[i].ship);
		}

		if (screenstate == POPUP) {
			if (showpopup1) {
				window.draw(popup1);
				/*	window.draw(soundtext);*/
				window.draw(backButton);
				window.draw(exitGameButton);
				window.draw(backText);
				window.draw(exitGameText);
				window.draw(reallyexitText);

				window.draw(exitGameText2);
				/*window.draw(musicToggleButton);
				window.draw(musicToggleText);*/
			}

			if (showpopup2)
			{
				window.draw(popup4);
				window.draw(playerScoreText);
				window.draw(computerScoreText);
				window.draw(winnerText);


			}

		}
		/*window.draw(shipboxx);*/
		window.display();//displaying

	}

}

