#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;
using namespace sf;
class Ship : public sf::Drawable, public sf::Transformable
{
public:
    Ship(int segments, float segmentWidth, float segmentHeight, float posX, float posY)
        : segmentWidth(segmentWidth), segmentHeight(segmentHeight), numSegments(segments), isSelected(false) {
        // Left rounded end
        leftCircle.setRadius(segmentHeight / 2);
        leftCircle.setPointCount(30);
        leftCircle.setFillColor(sf::Color(0, 255, 0)); // Green
        leftCircle.setOrigin(leftCircle.getRadius(), leftCircle.getRadius());
        leftCircle.setPosition(leftCircle.getRadius(), segmentHeight / 2);

        // Body segments
        for (int i = 0; i < segments; ++i) {
            sf::RectangleShape bodySegment(sf::Vector2f(segmentWidth, segmentHeight));
            bodySegment.setFillColor(sf::Color(0, 255, 0));
            bodySegment.setOrigin(0, segmentHeight / 2);
            bodySegment.setPosition(leftCircle.getRadius() + i * segmentWidth, segmentHeight / 2);
            bodySegmentsShapes.push_back(bodySegment);
        }

        // Right rounded end
        rightCircle.setRadius(segmentHeight / 2);
        rightCircle.setPointCount(30);
        rightCircle.setFillColor(sf::Color(0, 255, 0));
        rightCircle.setOrigin(rightCircle.getRadius(), rightCircle.getRadius());
        float rightCircleX = leftCircle.getRadius() + segments * segmentWidth;
        rightCircle.setPosition(rightCircleX, segmentHeight / 2);

        // Capsule dimensions
        capsuleWidth = leftCircle.getRadius() * 2 + segments * segmentWidth;
        setPosition(posX, posY);
    }

    // Set or unset the outline depending on selection state
    void setSelected(bool selected) {
        isSelected = selected;
        if (isSelected) {
            for (auto& segment : bodySegmentsShapes) {
                segment.setOutlineThickness(4);
                segment.setOutlineColor(sf::Color::Green);
            }
            leftCircle.setOutlineThickness(4);
            leftCircle.setOutlineColor(sf::Color::Green);
            rightCircle.setOutlineThickness(4);
            rightCircle.setOutlineColor(sf::Color::Green);
        }
        else {
            for (auto& segment : bodySegmentsShapes) {
                segment.setOutlineThickness(0);
            }
            leftCircle.setOutlineThickness(0);
            rightCircle.setOutlineThickness(0);
        }
    }


    void setColour(int R, int G, int B, int transparency) {
        leftCircle.setFillColor(sf::Color(R, G, B, transparency));
        leftCircle.setOutlineColor(sf::Color(R, G, B, transparency));
        rightCircle.setFillColor(sf::Color(R, G, B, transparency));
        rightCircle.setOutlineColor(sf::Color(R, G, B, transparency));
        for (auto& segment : bodySegmentsShapes) {
            segment.setOutlineColor(sf::Color(R, G, B, transparency));
            segment.setFillColor(sf::Color(R, G, B, transparency));
        }
    }
    int getSegments()
    {
        return numSegments;
    }
    // Get the local bounds of the ship
    sf::FloatRect getLocalBounds() const {
        float width = capsuleWidth;         // Total width of the capsule
        float height = segmentHeight;       // Total height of the capsule
        return sf::FloatRect(0.f, 0.f, width, height); // Local bounds in the ship's local coordinate space
    }

    // Check for collision with another ship
    bool intersects(const Ship& other) const {
        return getGlobalBounds().intersects(other.getGlobalBounds());
    }

    // Get the global bounds of the ship (transformed)
    sf::FloatRect getGlobalBounds() const {
        sf::FloatRect localBounds = getLocalBounds();
        sf::Transform transform = getTransform();
        sf::Vector2f topLeft = transform.transformPoint(localBounds.left, localBounds.top);
        sf::Vector2f bottomRight = transform.transformPoint(localBounds.left + localBounds.width, localBounds.top + localBounds.height);
        return sf::FloatRect(topLeft.x, topLeft.y, bottomRight.x - topLeft.x, bottomRight.y - topLeft.y);
    }

protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        states.transform *= getTransform();
        target.draw(leftCircle, states);
        for (const auto& segment : bodySegmentsShapes) {
            target.draw(segment, states);
        }
        target.draw(rightCircle, states);
    }

private:
    float segmentWidth, segmentHeight, capsuleWidth;
    int numSegments;
    sf::CircleShape leftCircle, rightCircle;
    std::vector<sf::RectangleShape> bodySegmentsShapes;
    bool isSelected;
};


struct Board
{
    Sprite grid[10][10];
    Ship ships[5] =
    {
          Ship(3, 8, 8,600, 110), // Ship with 3 segments
          Ship(4, 7,  8, 600, 160), // p=(segm,length,width,x pos, y pos)
          Ship(5, 5, -8, 600, 210),
          Ship(3, 8, 8, 600, 260),
          Ship(2, 10,  8, 600, 310)
          // Ship with 5 segments
    };
};

// Structure for each icon

struct MarkedPoints
{
    Vector2i Coord;
    bool hit;
};


inline void initializeSpriteGrid(Sprite grid[10][10], Texture& texture, int rows, int cols, float colsize, float rowsize, int offsetx, float scale, int tempoffsety)
{
    int offsety = tempoffsety;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            grid[i][j].setTexture(texture);
            // Position each sprite in the grid
            grid[i][j].setPosition(j * colsize * scale + offsety, i * rowsize * scale + offsetx);

            // Set the texture rectangle for each sprite to extract part of the texture
            grid[i][j].setTextureRect(IntRect(j * colsize, i * rowsize, colsize, rowsize));

            // Scale the sprite to fit the window
            grid[i][j].setScale(scale, scale);
        }
    }
}

inline void draw(RenderWindow& window, Sprite grid[10][10], int rows, int cols, RectangleShape movablesquare)
{
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            window.draw(grid[i][j]);
        }
    }
    window.draw(movablesquare);
}

inline RectangleShape setmovablesq(float colsize, float rowsize, float scale)
{
    RectangleShape movablesquare;
    movablesquare.setSize(Vector2f(colsize, rowsize));
    movablesquare.setScale(scale, scale);

    movablesquare.setOutlineColor(Color::Red);
    scale != 1 ? movablesquare.setOutlineThickness(15.0f) : movablesquare.setOutlineThickness(5.0f);
    movablesquare.setFillColor(Color::Transparent);
    return movablesquare;
}


//box drawing functiona
//
inline void setwoodenbox(Sprite box[1][5], Texture& texturewood, float width, float height, float positionx, float positiony, float colsize, float rowsize)
{
    float scalex = width / texturewood.getSize().x / 2.75;
    float scaley = height / texturewood.getSize().y / 2.75;
    float scale2 = min(scalex, scaley);
    for (int i = 0; i < 5; i++)
    {
        box[0][i].setTexture(texturewood);
        box[0][i].setScale(scale2, scale2);
        box[0][i].setTextureRect(IntRect(i * colsize, 0, colsize, rowsize));
        box[0][i].setPosition(i * colsize * scale2 + positionx, positiony);
    }

}


inline void addingship(float& scaleship, Texture& textureship, float colsize, float rowsize, RectangleShape& ship, float posx, float posy, int level) {
    // Set the sprite's texture
    /*ship.setTexture(textureship);*/

    // Get the size of the texture
    Vector2u size = textureship.getSize();
    ship.setFillColor(Color::Green);
    // Calculate scaling factors
    float scalexship = colsize / static_cast<float>(size.x);
    float scaleyship = rowsize / static_cast<float>(size.y) * level / 5;;
    Vector2f sizeshape(rowsize, colsize);

    ship.setSize(sizeshape);
    // Use the smaller scale to fit within the box
    scaleship = max(scalexship, scaleyship);

    /*ship.setScale(scaleship, scaleship);*/

    // Set the origin to the center of the sprite
    ship.setOrigin(size.x / 2.0f, size.y / 2.0f);

    // Center the sprite within the specified position and size
    ship.setPosition(
        posx + colsize / 2.0f,
        posy + rowsize / 2.0f
    );

}


//void DoesIntersect1(Ship &tempship,Board board,int selectedShipIndex,bool &intersects,bool&sameclicked)
//{
//
//    intersects = 0;
//    FloatRect intersectionArea;
//    for (int i = 0; i < 5; i++)
//    {
//        FloatRect ShipGlobal = board.ships[i].getGlobalBounds();
//        if (tempship.intersects(board.ships[i]))
//        {
//            if (i != selectedShipIndex)
//            {
//                tempship.setColour(255, 0, 0, 200);
//                intersects = 1;
//                break;
//            }
//            else
//            {
//                sameclicked = 1;
//                break;
//            }
//        }
//    }
//    if (!intersects)
//        tempship.setColour(0, 0, 0, 200); // Valid placement
//}

inline void DoesIntersect1(Ship& tempship,Board board, int selectedShipIndex, bool& intersects, bool& sameclicked)
{
    FloatRect rect1 = tempship.getGlobalBounds();
    intersects = 0;
    float intersectionArea = 0;
    FloatRect intersection;
    for (int i = 0; i < 5; i++)
    {
        FloatRect ShipGlobal = board.ships[i].getGlobalBounds();
        if (rect1.intersects(ShipGlobal, intersection))
        {
            intersectionArea = intersection.width * intersection.height;
            if (i != selectedShipIndex && intersectionArea > 0.6f)
            {
                tempship.setColour(255, 0, 0, 200);
                intersects = 1;
                break;
            }
            else
            {
                sameclicked = 1;
                break;
            }
        }
    }
}

inline void validplacement(Ship& tempship, Board board, int selectedShipIndex, bool& intersects, bool& sameclicked, FloatRect boundingboxglobal, FloatRect tempshipglobal, bool& FullyContained)
{
    FullyContained = boundingboxglobal.contains(tempshipglobal.left, tempshipglobal.top) && boundingboxglobal.contains(tempshipglobal.left + tempshipglobal.width, tempshipglobal.top + tempshipglobal.height);
    //*&&boundingboxglobal.contains(tempshipglobal.left+tempshipglobal.width,tempshipglobal.top)*/;


    if (FullyContained)
    {
        sameclicked = 0;
        intersects = 0;

        DoesIntersect1(tempship, board, selectedShipIndex, intersects, sameclicked);

    }
    else
    {
        intersects = 1;
        tempship.setColour(255, 0, 0, 200); // Invalid placement
        cout << "\nShip does not fit in the bounding box.";
        /* cout << "BoundingBox: (" << boundingboxglobal.left << ", " << boundingboxglobal.top
             << ") -> (" << boundingboxglobal.left + boundingboxglobal.width << ", "
             << boundingboxglobal.top + boundingboxglobal.height << ")" << endl;

         cout << "TempShip: (" << tempshipglobal.left << ", " << tempshipglobal.top
             << ") -> (" << tempshipglobal.left + tempshipglobal.width << ", "
             << tempshipglobal.top + tempshipglobal.height << ")" << endl;*/

    }
}

inline RectangleShape setwoodenbox(Texture& texturewood, float width, float height, float positionx, float positiony)
{
    RectangleShape box;
    Vector2f size(width, height);
    box.setSize(size);
    box.setPosition(positionx, positiony);
    box.setTexture(&texturewood);
    return box;
}

inline bool DoesIntersect(const sf::FloatRect& rect1, const sf::FloatRect& rect2, float& intersectionArea) {
    sf::FloatRect intersection;
    if (rect1.intersects(rect2, intersection)) {
        intersectionArea = intersection.width * intersection.height;  // Calculate intersection area
        return true;
    }
    intersectionArea = 0.f;  // No intersection
    return false;
}


inline void ComputerInitialize(int gridval2[10][10], Board board, int shipindex, bool vertical,MarkedPoints CompPosition[5][5])
{
    srand(time(NULL));
    bool placed = 0, available;
    while (!placed)
    {
        placed = 0;
        int row = rand() % 10;
        int col = rand() % 10;
        if (vertical)
        {
            available = 1;
            for (int i = row; i < row + board.ships[shipindex].getSegments() && available; i++)
            {
                if (gridval2[i][col] != 0||i>9)
                {
                    available = 0;
                }
            }
            if (available)
            {
                int count = 0;
                placed = 1;
                for (int i = row; i < row + board.ships[shipindex].getSegments(); i++)
                {
                    gridval2[i][col] = 1;
                    CompPosition[shipindex][count++].Coord =Vector2i( i,col);
                }
            }

        }
        else
        {
            available = 1;
            for (int i = col; i < col + board.ships[shipindex].getSegments() && available; i++)
            {
                if (gridval2[row][i] != 0||i>9)
                {
                    available = 0;
                }
            }
            if (available)
            {
                placed = 1;
                int count = 0;
                for (int i = col; i < col + board.ships[shipindex].getSegments(); i++)
                {
                    placed = 1;
                    gridval2[row][i] = 1;
                    CompPosition[shipindex][count++].Coord = Vector2i(row,i);
                }
            }

        }
    }
}


inline bool AllSunk(MarkedPoints gridpoints[5][5], Vector2i hitpoint,int &shipnum,bool&exists,Board board)
{
    exists = 0;
    bool allsunk = 1;
    shipnum = -1;
    for (int i = 0; i < 5&&!exists; i++)//ships
    {
        for (int j = 0; j < 5&&!exists; j++)//all areas they cover
        {
            if (gridpoints[i][j].Coord== hitpoint)
            {
                cout << "exists" << endl;
                gridpoints[i][j].hit = 1;
                exists = 1;
            }

            if (exists)
            {
                for (int k = 0; k < board.ships[i].getSegments() && allsunk; k++)
                {
                    cout << "checking if all hit...." << endl;
                    shipnum = i;
                    if (gridpoints[i][k].hit != 1)
                    {
                        allsunk = 0;
                    }
                }
                cout << "all sunk?" << allsunk<<endl;
            }
        }
    }
    return allsunk;
}

inline int Lastelement(MarkedPoints player[5][5], int shipnum)
{
    int elem=0;

    while (player[shipnum][elem].Coord != Vector2i(-1, -1))
        elem++;

    return elem;
}


/////menu functions


struct Icon {
    sf::ConvexShape diamond;
    sf::Texture* texture = nullptr;  // Pointer to a texture
    float currentAngle = 1.0f;    // Tracks the position of the diamond along the circular layout.
    bool isZoomedIn = false;
};

// Function to create a simple diamond shape
inline void createDiamond(Icon& icon, float size) {
    icon.diamond.setPointCount(4);
    icon.diamond.setPoint(0, sf::Vector2f(0, -size));   // Top vertex
    icon.diamond.setPoint(1, sf::Vector2f(size, 0));    // Right vertex
    icon.diamond.setPoint(2, sf::Vector2f(0, size));    // Bottom vertex
    icon.diamond.setPoint(3, sf::Vector2f(-size, 0));   // Left vertex

    icon.diamond.setOrigin(0, 0); // Optional: Center the diamond
}


enum ScreenState
{
    POPUP,
    INITIAL,
    GAME,
    CLASSIC,
    NEWMODE,
    SETTINGS,
    MENU,
    EXIT,
    LEADER
};

inline void resizeView(sf::RenderWindow& window, sf::View& view) 
{
    // Get the new window size
    sf::Vector2u windowSize = window.getSize();

    // Calculate the aspect ratio of the window and the game
    float windowAspectRatio = static_cast<float>(windowSize.x) / windowSize.y;
    float gameAspectRatio = 800.f / 600.f;

    // Adjust the viewport to maintain the aspect ratio
    if (windowAspectRatio > gameAspectRatio) {
        // Window is wider, add black bars on the sides
        float newWidth = gameAspectRatio / windowAspectRatio;
        view.setViewport(sf::FloatRect((1.f - newWidth) / 2.f, 0.f, newWidth, 1.f));
    }
    else {
        // Window is taller, add black bars on the top and bottom
        float newHeight = windowAspectRatio / gameAspectRatio;
        view.setViewport(sf::FloatRect(0.f, (1.f - newHeight) / 2.f, 1.f, newHeight));
    }

    view.zoom(1.1f); // Increase the zoom factor slightly to make the screen appear smaller
    window.setView(view);
}

struct ShipsHit
{
    bool hit=0;
    Ship ship;
   
};


// Function to set fullscreen scaling and viewport
inline void applyFullscreenScaling(RenderWindow& window, float originalWidth, float originalHeight, View &view) {
    VideoMode fullscreenMode = VideoMode::getDesktopMode();
    float screenWidth = fullscreenMode.width;
    float screenHeight = fullscreenMode.height;

    // Calculate aspect ratios
    float gameAspectRatio = originalWidth / originalHeight;
    float screenAspectRatio = screenWidth / screenHeight;

    // Determine scaling factor
    float scaleFactor;
    float xOffset = 0, yOffset = 0;

    if (screenAspectRatio > gameAspectRatio) {
        // Fit height and minimize bars on the sides
        scaleFactor = screenHeight / originalHeight;
        xOffset = (screenWidth - (originalWidth * scaleFactor)) / 2.0f;
    }
    else {
        // Fit width and minimize bars on the top/bottom
        scaleFactor = screenWidth / originalWidth;
        yOffset = (screenHeight - (originalHeight * scaleFactor)) / 2.0f;
    }

    // Calculate the new viewport
    float scaledWidth = originalWidth * scaleFactor;
    float scaledHeight = originalHeight * scaleFactor;

    // Create and set a view
    View gameView(FloatRect(0, 0, originalWidth, originalHeight));
    gameView.setViewport(FloatRect(xOffset / screenWidth, yOffset / screenHeight,
    scaledWidth / screenWidth, scaledHeight / screenHeight));
    window.setView(gameView);
}

    



// comp strike functions

inline bool isValid(int x, int y, int SIZE, int parallel[10][10])
{
    return x >= 0 && x < SIZE && y >= 0 && y < SIZE && parallel[x][y] != 0;
}
// Perform a random strike
inline bool randomStrike(int  parallel[10][10], int& x, int &y)
{
    bool placed = 0;
    srand(time(NULL));
    do
    {
        x = rand() % 10;
        y = rand() % 10;
     
    } while (parallel[x][y] == 2); //ensuring that it not generates a number that has alr been hit
    placed = 1;
    return placed;

}
////////////////////leaderboard functions
struct Player {
    std::string name;
    int score;
};

// Function to read data from the file
inline int readFile(const std::string& filename, Player players[], int maxPlayers) {
    std::ifstream inputFile(filename);
    if (!inputFile || inputFile.peek() == std::ifstream::traits_type::eof()) {
        return 0; // Return 0 if the file doesn't exist or is empty
    }

    int count = 0;
    while (count < maxPlayers && inputFile >> players[count].score) {
        inputFile.ignore(); // Ignore the space after the score
        std::getline(inputFile, players[count].name); // Read the rest as the name
        ++count;
    }
    inputFile.close();
    return count;
}



// Function to write data back to the file
inline void writeFile(const std::string& filename, Player players[], int playerCount) {
    std::ofstream outputFile(filename);
    for (int i = 0; i < playerCount; ++i) {
        outputFile << players[i].score << " " << players[i].name << "\n";
    }
    outputFile.close();
}

// Function to update or append the player data
inline void updateOrAppend(Player players[], int& playerCount, int maxPlayers, const Player& newPlayer) {
    bool found = false;
    for (int i = 0; i < playerCount; ++i) {
        if (players[i].name == newPlayer.name) {
            // Update score only if the new score is higher
            if (newPlayer.score > players[i].score) {
                players[i].score = newPlayer.score;
            }
            found = true;
            break;
        }
    }

    // If the player is not found and there's space, add them
    if (!found && playerCount < maxPlayers) {
        players[playerCount++] = newPlayer;
    }
}



// Function to get the top three players
inline void getTopThree(Player players[], int playerCount, Player topThree[], int topCount) {
    // Sort players manually to avoid using STL for a simpler look
    for (int i = 0; i < playerCount - 1; ++i) {
        for (int j = i + 1; j < playerCount; ++j) {
            if (players[i].score < players[j].score) {
                Player temp = players[i];
                players[i] = players[j];
                players[j] = temp;
            }
        }
    }

    for (int i = 0; i < topCount && i < playerCount; ++i) {
        topThree[i] = players[i];
    }
}


inline string getUsernameFromFile(string& name) {
    std::ifstream inFile("username.txt");
    std::string username;
    std::string lastUsername;

    if (inFile.is_open()) {
        while (std::getline(inFile, username)) {
            lastUsername = username;  // Keep overwriting until the last line
        }
        inFile.close();
    }
    else {
        std::cerr << "Error opening file to read username!" << std::endl;
    }

    return lastUsername;  // This will contain the last line

}


inline void getLastTwoLines(const std::string& filename, std::string& line1, std::string& line2) {
    std::ifstream file(filename, std::ios::in);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file: " << filename << std::endl;
        line1.clear();
        line2.clear();
        return;
    }

    std::string currentLine;
    line1.clear(); // To store the second last line
    line2.clear(); // To store the last line

    while (std::getline(file, currentLine)) {
        line1 = line2; // Move the previous last line to the second last line
        line2 = currentLine; // Update the last line
    }

    file.close();
}

inline void boardreinitialize(Board &board,Texture texture)
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            continue;
          
        }
    }
}

