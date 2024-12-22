#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include "myfunctions.h"
#include"common.h"
using namespace sf;
using namespace std;

//signatures


ScreenState MineMode(sf::RenderWindow& window, Board& board,Board&board2 ,sf::Texture& texture, int positions[5][2],int positions2[5][2], sf::View gameView,string name1,string name2)
{

	ScreenState screenstate = NEWMODE;
	void initializeSpriteGrid(Sprite grid[10][10], Texture & texture, int rows, int cols, float colsize, float rowsize, int offset, float scale, int tempoffsety = 66);
	void draw(RenderWindow & window, Sprite grid[10][10], int rows, int cols, RectangleShape movablesquare);
	RectangleShape setmovablesq(float colsize, float rowsize, float scale);
	RectangleShape setwoodenbox(Texture & texturewood, float width, float height, float positionx, float positiony);
	RectangleShape setmovablesq(float colsize, float rowsize, float scale = 1);
	srand(time(NULL));
	//resizeView(window, gameView);
	getLastTwoLines("username.txt", name1, name2);
	resizeView(window, gameView);
	window.setView(gameView);
	RectangleShape backgroundbox;
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
	if (!background.loadFromFile("d:\\haajra\\battlefield_pf\\additional files\\smoke-bw.jpg")) {
		cerr << "error loading texture!" << endl;
	}

	Font namefont;
	if (!namefont.loadFromFile("d:\\haajra\\battlefield_pf\\additional files\\GeistMonoBold.ttf")) {
		cerr << "error loading font" << endl;
	}

	Font geistefont;
	if (!geistefont.loadFromFile("d:\\haajra\\battlefield_pf\\additional files\\crimson.semibold.ttf")) {
		cerr << "error loading font" << endl;
	}
	float accumulatedTime = 0.0f;
	
	window.setFramerateLimit(60);

	// Initialize Fog and Game

	sf::Vector2f torchPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f);



	RectangleShape popup4(Vector2f(400, 300));
	FloatRect popup4Bounds = popup4.getGlobalBounds();


	Text playerScoreText;
	Text computerScoreText;
	Texture scorebg;
	if (!scorebg.loadFromFile("d:\\haajra\\battlefield_pf\\additional files\\throne.JPG")) {
		cerr << "error loading texture!" << endl;
	}
	popup4.setTexture(&scorebg);
	computerScoreText.setFont(namefont);
	playerScoreText.setFont(namefont);
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
	winnerText.setFont(namefont);
	winnerText.setCharacterSize(36);
	winnerText.setFillColor(Color::White);
	winnerText.setOutlineColor(Color::Black);
	winnerText.setOutlineThickness(2);
	winnerText.setPosition(popup4.getPosition().x + 50, popup4.getPosition().y + 150);




	//make the window
	//RenderWindow window(VideoMode(width, height), "Board");

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

	bool firsttime = 0;
	float scaleX = static_cast<float>(width) / textureWidth / 3;
	float scaleY = static_cast<float>(height) / textureHeight / 3;
	float scale = std::max(scaleX, scaleY);

	float ratio = scale / initialscale;
	// Set size of each grid cell and general position
	float colsize = textureWidth / (cols);
	float rowsize = textureHeight / (rows);
	int offset = (width / 2 - (textureWidth * scale)) / 2;
	int offsety = (width / 2 + offset);
	cout << ratio << endl;

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

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			board2.grid[i][j].setPosition(j * colsize * scale + offsety, i * rowsize * scale + offset);
		}

	}



	/*bool vertical;
	for (int i = 0; i < 5; i++)
	{
		vertical = rand() & 2;
		ComputerInitialize(gridval2, board, i, vertical, CompPoints);
		cout << "vertical:" << vertical << endl << endl;
	}*/

	/*for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			cout << gridval2[i][j] << " ";
		}
		cout << endl;
	}*/
	RectangleShape shipboxx;

	Color greycol = Color(255, 255, 255, 100);
	RectangleShape movablesquare = setmovablesq(colsize, rowsize, scale);

	
	//Making a box
	int positionybox = (textureHeight * scale) + 2 * offset;
	float gridx = (board.grid[0][0].getPosition().x - 5);
	float gridy = board.grid[0][0].getPosition().y - 5.0;
	Vector2f pos = Vector2f(gridx, gridy);
	float bboxvertical = board.grid[9][0].getPosition().y - pos.y + colsize * scale;
	float bboxhorizontal = board.grid[0][9].getPosition().x - pos.x + rowsize * scale;
	RectangleShape boundingbox = setmovablesq(bboxhorizontal + 5, bboxvertical + 5);
	boundingbox.setPosition(pos);

	float grid2x = (board2.grid[0][0].getPosition().x - 5);
	float grid2y = board2.grid[0][0].getPosition().y - 5.0;
	pos = Vector2f(grid2x, grid2y);
	float bbox2vertical = board2.grid[9][0].getPosition().y - pos.y + colsize * scale;
	float bbox2horizontal = board2.grid[0][9].getPosition().x - pos.x + rowsize * scale;
	RectangleShape boundingbox2 = setmovablesq(bbox2horizontal + 5, bbox2vertical + 5);
	boundingbox2.setPosition(pos);
	RectangleShape box = setwoodenbox(texturewood, textureWidth * scale, 175, offset, positionybox);
	RectangleShape box2 = setwoodenbox(texturewood, textureWidth * scale, 175, offsety, positionybox);

	
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
	FloatRect shipBounds2[5];
	for (int k = 0; k < 5; k++) 
	{
		board.ships[k].setScale(ratio, ratio);
		int row = positions[k][0];
		int col = positions[k][1];
		board.ships[k].setPosition(
			board.grid[row][col].getPosition().x + (rowsize * scale / 1.5),
			board.grid[row][col].getPosition().y + (colsize * scale / 2)
		);

		board2.ships[k].setScale(ratio, ratio);
		row = positions2[k][0];
		col = positions2[k][1];
		board2.ships[k].setPosition(
			board2.grid[row][col].getPosition().x + (rowsize * scale / 1.5),
			board2.grid[row][col].getPosition().y + (colsize * scale / 2)
		);

		SetOne[k].ship.setRotation(90);
		SetOne[k].ship.setPosition(30 + (colwidth * k) + box.getPosition().x, box.getPosition().y + 20);
		SetTwo[k].ship.setRotation(90);
		SetTwo[k].ship.setPosition(30 + (colwidth * k) + box2.getPosition().x, box2.getPosition().y + 20);
		shipBounds[k] = board.ships[k].getGlobalBounds();
		shipBounds2[k] = board2.ships[k].getGlobalBounds();
		
	}

	Clock clock;

	Clock movetime;
	Text playername;
	Text CompName;


	string justname1, justname2;
	justname1 = name1;
	justname2 = name2;
	name1 = name1 + "'s fleet";
	name2 = name2 + "'s fleet";
	playername.setFont(namefont);
	playername.setString(name1);
	playername.setCharacterSize(25);
	playername.setFillColor(sf::Color::White);
	
	playername.setOutlineColor(sf::Color::Black);
	playername.setOutlineThickness(2);
	FloatRect textBounds = playername.getLocalBounds();
	playername.setOrigin((textBounds.left + textBounds.width )/ 2,(textBounds.top + textBounds.height) / 2);
	playername.setPosition((boundingbox.getGlobalBounds().width + boundingbox.getGlobalBounds().left) / 1.7, boundingbox.getGlobalBounds().height + boundingbox.getGlobalBounds().top + 20);
	CompName = playername;
	textBounds = CompName.getLocalBounds();
	CompName.setOrigin((textBounds.left + textBounds.width) / 2, (textBounds.top + textBounds.height) / 2);
	CompName.setString(name2);
	CompName.setPosition((boundingbox2.getGlobalBounds().width + boundingbox2.getGlobalBounds().left) /1.2,boundingbox2.getGlobalBounds().height + boundingbox2.getGlobalBounds().top + 20);


	Text playertime;
	Text Comptime;

	playertime = playername;
	playertime.setCharacterSize(60);
	/*playertime.setPosition(board.grid[0][0].getPosition().x+40, 20);*/
	playertime.setFont(geistefont);
	Comptime.setCharacterSize(60);
	//Comptime.setPosition(90, 20);
	Comptime.setFont(geistefont);
	playertime.setFillColor(Color::Green);
	Comptime.setFillColor(Color::Green);

	// Example of setting timer positions
// Position 'playertime' to the top left corner
	playertime.setPosition(boundingbox.getGlobalBounds().left+30, boundingbox.getGlobalBounds().top - 50); // Adjust x and y for desired location

	// Position 'Comptime' to the top right corner
	float windowWidth = static_cast<float>(window.getSize().x);
	Comptime.setPosition(boundingbox2.getGlobalBounds().left,boundingbox2.getGlobalBounds().top-70); // Adjust x for desired right alignment, y for vertical placement

	playertime.setString("180");
	Comptime.setString("180");
	string playerstring;
	string computerstring;
	//playername.setPosition(boundingbox.getGlobalBounds().width / 2, board.grid[9][0].getPosition().y + 15);
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
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			FloatRect boxglbl = board2.grid[i][j].getGlobalBounds();

			// Check for intersections with all ships
			for (int k = 0; k < 5; k++) {
				float intersectionArea = 0;
				if (DoesIntersect(boxglbl, shipBounds2[k], intersectionArea)) {
					if (intersectionArea / (boxglbl.width * boxglbl.height) >= 0.25) {
						gridval2[i][j] = 1; // Mark the grid cell as intersected
						int elem = Lastelement(CompPoints, k);
						CompPoints[k][elem].Coord = Vector2i(i, j);
						cout << "for ship:" << k << " part number:" << elem << " val:" << i << "," << j << endl;
					}
				}
			}
		}
	}


	int playerhitcount = 0, comphitcount = 0;
	////////////////////////////////////
		// Create a render texture to handle blackout and spotlight effect
	sf::RenderTexture blackoutTexture;
	blackoutTexture.create(window.getSize().x, window.getSize().y);

	// Blackout rectangle
	sf::RectangleShape blackout(sf::Vector2f(boundingbox.getSize().x-10, boundingbox.getSize().y- 10));
	blackout.setFillColor(sf::Color::Black);
	blackout.setPosition(board2.grid[0][0].getPosition());
	// Spotlight effect (transparent in the middle, soft edges around)
	float spotlightRadius = colsize*scale; // Adjust the radius as per your preference
	sf::CircleShape spotlight(spotlightRadius);
	sf::CircleShape glow(spotlightRadius);
	spotlight.setOrigin(spotlightRadius, spotlightRadius); // Center origin
	spotlight.setFillColor(sf::Color(0, 0, 0, 0)); // Transparent center
	spotlight.setOutlineThickness(colsize*scale/4); // Thickness of soft edges
	spotlight.setOutlineColor(sf::Color(0, 0, 0, 150)); // Semi-transparent outline for soft edges

	float outlineThickness = colsize*scale/7; // Glow area thickness
	CircleShape layers[4];
	int marker = 150;
	for (int i = 0; i < 4; i++)
	{
		layers[i].setFillColor(Color::Transparent);
		float radius = spotlightRadius - (i*2);
		layers[i].setRadius(radius);
		layers[i].setOrigin(radius, radius);
		layers[i].setOutlineThickness(colsize * scale /(4-i));
		layers[i].setOutlineColor(sf::Color(0, 0, 0, marker - 10));

	}


	bool delayfinished = false;
	int computerscore =100,playerscore = 100;
	int playertimeleft = 180, computertimeleft = 180;
	//////////////////////////////////////////////////////////////////////////////////////////////
		//Handlin sg Events
	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}
			else if ((event.type == Event::KeyPressed) && (event.key.code == Keyboard::Tab))
			{
				screenstate = LEADER;
				return screenstate;
			}

			else if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left && !delayfinished)
			{
				bool placed = 0;
				Vector2i mousePixelPos = Mouse::getPosition(window); // Mouse position
				Vector2f mousePos = window.mapPixelToCoords(mousePixelPos);
				for (int i = 0; i < rows&&!placed; i++)
				{
					for (int j = 0; j < cols&&!placed; j++)
					{
						FloatRect cellBounds = board.grid[i][j].getGlobalBounds();
						cellBounds.width -= 0.5;
						cellBounds.height -=0.5;
						cellBounds.top -= 0.25;
						cellBounds.left +=0.25;
						FloatRect cellBounds2 = board2.grid[i][j].getGlobalBounds();
						cellBounds2.width -= 0.5;
						cellBounds2.height -= 0.5;
						cellBounds2.top -= 0.25;
						cellBounds2.left += 0.25;
						if (!player)
						{
							if (cellBounds.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
							{
								placed = 0;
								if (gridval[i][j] == 1)
								{
									board.grid[i][j].setColor(Color::Red);
									placed = 1;

								}
								else if (gridval[i][j] == 0)
								{
									board.grid[i][j].setColor(Color::Green);
									placed = 1;
									computerscore--;
								}

								if (placed)
								{
									bool exists = 0;
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


											computerScoreText.setString(justname2 +" Score: " + to_string(computerscore));
											playerScoreText.setString(justname1 +" Score: " + to_string(playerscore));

											winnerText.setString(justname2+" won!");
											screenstate = POPUP;
										}
											
									}


									boundingbox2.setOutlineColor(Color::Green);
									boundingbox.setOutlineColor(greycol);
								
									gridval[i][j] = 2;

									delayfinished = true;
									clock.restart();
									movetime.restart();
									break;

								}
								break;
							}
						}
						else
						{
							if (cellBounds2.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
							{
								placed = 0;
								cout << "here at:" << i << "," << j << endl;
								if (gridval2[i][j] == 0)
								{
									board2.grid[i][j].setColor(Color::Green);
									placed = 1;
									playerscore--;
								}
								else if (gridval2[i][j] == 1)
								{

									board2.grid[i][j].setColor(Color::Red);
									placed = 1;

								}

								if (placed)
								{
									bool exists = 0;
									if (AllSunk(CompPoints, Vector2i(i, j), shipnum, exists, board) && exists)
									{
										for (int i = 0; i < board.ships[shipnum].getSegments(); i++)
										{
											board2.grid[CompPoints[shipnum][i].Coord.x][CompPoints[shipnum][i].Coord.y].setColor(Color::Black);
										}
										SetTwo[shipnum].hit = 1;
										playerhitcount++;


										if (playerhitcount == 5)
										{
										
											computerScoreText.setString(name2 + " Score: " + to_string(computerscore));
											playerScoreText.setString(name1 + " Score: " + to_string(playerscore));

											winnerText.setString(name1+" won!");
											screenstate = POPUP;

										}
									}
									boundingbox2.setOutlineColor(greycol);
									boundingbox.setOutlineColor(Color::Green);
									movetime.restart();
									gridval2[i][j] = 2;
									delayfinished = true;
									clock.restart();
								}

							}
						}


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
						FloatRect cellBounds2 = board2.grid[i][j].getGlobalBounds();
						if (!player)
						{
							if (cellBounds.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
							{
								blackout.setPosition(board.grid[0][0].getPosition());
								boundingbox.setFillColor(Color::Transparent);
								// Update game elements and fog
								spotlight.setPosition(mousePos.x, mousePos.y);
								for (int i = 0; i < 4; i++)
								{
									layers[i].setPosition(mousePos.x, mousePos.y);
								}
								movablesquare.setPosition(j * colsize * scale + offset, i * rowsize * scale + offset);

								break;

							}
						}
						else
						{

							if (cellBounds2.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) 
							{
								blackout.setPosition(board2.grid[0][0].getPosition());
								boundingbox2.setFillColor(Color::Transparent);
								spotlight.setPosition(mousePos.x, mousePos.y);
								for (int i = 0; i < 4; i++)
								{
									layers[i].setPosition(mousePos.x, mousePos.y);
								}
								
								movablesquare.setPosition(j * colsize * scale + offsety, i * rowsize * scale + offset);
								break;
							}
						}


					}
				}
			}
			else if (event.type == Event::KeyPressed && event.key.code == Keyboard::Enter && screenstate == POPUP)
			{
				screenstate = MENU;
				return screenstate;
			}
			if (clock.getElapsedTime().asSeconds() >= 2.0f && delayfinished)
			{
				if (player)//about to be computer's turn, handle player's board as active
				{

					boundingbox2.setFillColor(Color::Black);
					movablesquare.setPosition(board.grid[0][0].getPosition());
					player = !player;
					delayfinished = false;
					clock.restart();
					movetime.restart();
				}
				else//about to be player's turn
				{
					boundingbox.setFillColor(Color::Black);
					movablesquare.setPosition(board2.grid[0][0].getPosition());
					player = !player;
					delayfinished = false;
					clock.restart();
					movetime.restart();

				}

			}


			backgroundbox.setSize(Vector2f(window.getSize()));
			backgroundbox.setTexture(&background);
			backgroundbox.setFillColor(Color(greycol));

			// Update spotlight position to follow mouse
			// Update spotlight position to follow mouse
			sf::Vector2i mousePixelPos = sf::Mouse::getPosition(window);
			sf::Vector2f mousePos = window.mapPixelToCoords(mousePixelPos);
			/*spotlight.setPosition(mousePos);*/

			// Clear the render texture
			blackoutTexture.clear(sf::Color::Transparent);

			// Draw blackout over the entire screen
			blackoutTexture.draw(blackout);

			// Draw the glowing spotlight with smooth blending
			blackoutTexture.draw(spotlight, sf::BlendNone); // BlendAdd for glow-like blending

			// Display the blackout texture
			blackoutTexture.display();

			// Convert the render texture to a sprite for drawing
			
			
			
		}

		if (player)
		{
			
			playerstring = to_string(playertimeleft);
			playertime.setString(playerstring);
			float elapsed = movetime.restart().asSeconds();
			accumulatedTime += elapsed;

			// Update the timer once per second
			if (accumulatedTime >= 1.0f)
			{
				player ? playertimeleft -= 1.0f : computertimeleft -= 1.0f;
				accumulatedTime = 0; // Remove 1 second from accumulated time
				if (playertimeleft < 0) playertimeleft = 0;
				else if (playertimeleft < 50)playertime.setFillColor(Color::Red);
				else if (playertimeleft < 100)playertime.setFillColor(Color::Yellow);

			}
		
		}
		else
		{
		
			computerstring = to_string(computertimeleft);
			Comptime.setString(computerstring);
			float elapsed = movetime.restart().asSeconds();
			accumulatedTime += elapsed;

			// Update the timer once per second
			if (accumulatedTime >= 1.0f)
			{
				player ? playertimeleft -= 1.0f : computertimeleft -= 1.0f;
				accumulatedTime = 0; // Remove 1 second from accumulated time
				if (computertimeleft < 0) computertimeleft = 0;
				else if(computertimeleft < 50)Comptime.setFillColor(Color::Red);
				else if (computertimeleft < 100)Comptime.setFillColor(Color::Yellow);
			

			}
			
		}
		sf::Sprite blackoutSprite(blackoutTexture.getTexture());
		// Drawing game element
		window.clear();
		window.draw(backgroundbox);
		// Background
		draw(window, board.grid, rows, cols, movablesquare); // Grid 1
		draw(window, board2.grid, rows, cols, movablesquare);      // Grid 2
		//window.draw(box);        // Game elements
		//window.draw(box2);
		window.draw(boundingbox);
		window.draw(boundingbox2);
		window.draw(playername);
		window.draw(CompName);
		for (int i = 0; i < 4; i++)
		{
			window.draw(layers[i]);
		}
		for (int i = 0; i < 5; i++)
		{
			if (SetOne[i].hit == 0)
				window.draw(SetOne[i].ship);
			if (SetTwo[i].hit == 0)
				window.draw(SetTwo[i].ship);

		}

		if (screenstate == POPUP)
		{
			window.draw(popup4);
			window.draw(playerScoreText);
			window.draw(computerScoreText);
			window.draw(winnerText);
		}
		// Draw the blackout texture with the glowing spotlight
		if(!screenstate==POPUP)
		window.draw(blackoutSprite);
		window.draw(playertime);
		window.draw(Comptime);
		window.display();

		}

	}

