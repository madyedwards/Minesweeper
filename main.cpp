#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "TextureManager.h"
#include "Board.h"
using namespace std;

void DrawBoard() {
    //nevermind, vars needed in main as public
}

int main()
{

    //my neck hurts :( (my neck my back...)
    //create the base game; this sets the data to draw the stuff at the bottom of main

    //window
    //Width = number of columns * 32
    //Height = (number of rows * 32) + 100
    //32 is the number of pixels on the side of a tile the extra 100 pixels is for the
    //space for the buttons on the bottom
    sf::RenderWindow gameWindow(sf::VideoMode(800, 600), "Minesweeper - Omg I can Write Up Here! Hello PM :)",
                            sf::Style::Close | sf::Style::Titlebar);

    //create background and board
    sf::RectangleShape gameBackground(sf::Vector2f(800, 600));
    gameBackground.setFillColor(sf::Color(200, 200, 200));
    Board gameBoard = Board(25, 16);
    gameBoard.InitializeRandom();


    //face
    sf::Sprite faceIcon(TextureManager::GetTexture("face_happy"));
    faceIcon.setPosition(350, 512);

    //button setting
    //debug, test1, test2, test3
    sf::Sprite debugButton(TextureManager::GetTexture("debug"));
    debugButton.setPosition(500, 512);
    sf::Sprite test1Button(TextureManager::GetTexture("test_1"));
    test1Button.setPosition(564, 512);
    sf::Sprite test2Button(TextureManager::GetTexture("test_2"));
    test2Button.setPosition(628, 512);
    sf::Sprite test3Button(TextureManager::GetTexture("test_3"));
    test3Button.setPosition(692, 512);


    //counter:
    //counts remaining mines
    //do this last! as last thing after milestone
    sf::Texture numberTexture = TextureManager::GetTexture("digits");
    //wtf is rects
    vector<sf::IntRect> numberRects;

    for (int i = 0; i < 211; i += 21) {//from doc
        numberRects.push_back(sf::IntRect(i, 0, 21, 32)); //stop telling me to call empalce
    }

    vector<int> nums = Extra::numbers(gameBoard.GetTotalMines());
    vector<sf::Sprite> numberDisplay;

    for (int i = 0, j = 50; i < 3; i++) { //create a for loop with multiple indices; online?
        numberDisplay.push_back(sf::Sprite(numberTexture)); //no map, no emplace!
        numberDisplay.at(i).setPosition(j, 512);
        numberDisplay.at(i).setTextureRect(numberRects.at(nums.at(i)));
        j = j + 21;
    }


    while (gameWindow.isOpen())
    {
        //need to heavily read the smfl
        //and reference that doc
        //TA?? pls
        //beginning of game
        sf::Event event;
        while (gameWindow.pollEvent(event))
        {
            //if you close the window
            //we have to code the window closing?????
            if (event.type == sf::Event::Closed) {
                gameWindow.close();
            }

            //finally working on mouse logic!!
            //was so confusing without it
            else if (event.type == sf::Event::MouseButtonPressed) {

                //WOW COOL
                //save this code for later in life
                //right one first bc less code
                //only one can be clicked at a time, so both if statements
                //right button: flags
                if (event.mouseButton.button == sf::Mouse::Right) {
                    sf::Vector2i position = sf::Mouse::getPosition(gameWindow);

                    //flga :)
                    if (position.y < 512) {
                        Tile* currentTile = &gameBoard.GetTile(25 * (position.y / 32) + (position.x / 32));
                        gameBoard.ShowFlag(currentTile);
                        nums = Extra::numbers(gameBoard.GetTotalMines() - gameBoard.GetTotalFlags());
                        for (int i = 0; i < 3; i++) {
                            numberDisplay.at(i).setTextureRect(numberRects.at(nums.at(i)));
                        }
                    }
                }

                //left mouse specifically
                //everythign other than flages; revealing tiles, bdebug buttons, tests 1-3, and face
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i position = sf::Mouse::getPosition(gameWindow);

                    //show a tile
                    if (position.y < 512) {
                        Tile* currentTile = &gameBoard.GetTile(25 * (position.y / 32) + (position.x / 32));
                        gameBoard.RevealTile(currentTile);

                        if (gameBoard.GetGameOver() == true) {
                            faceIcon.setTexture(TextureManager::GetTexture("face_lose"));
                        }
                        if (gameBoard.GetVictory() == true) {
                            faceIcon.setTexture(TextureManager::GetTexture("face_win"));

                            for (int i = 0; i < 3; i++) {
                                nums.at(i) = 0;
                                numberDisplay.at(i).setTextureRect(numberRects.at(nums.at(i)));
                            }
                        }
                    }

                    //BUTTONS
                    //debug buttom
                    //needs to be
                    else if ((position.x > 499 && position.x < 564) && (position.y > 512 && position.y < 576)) {
                        gameBoard.ShowDebug();
                    }

                    //test 1
                    else if ((position.x > 563 && position.x < 628) && (position.y > 512 && position.y < 576)) {
                        gameBoard.Initialize(1); //load in the board

                        nums = Extra::numbers(gameBoard.GetTotalMines() - gameBoard.GetTotalMines());
                        faceIcon.setTexture(TextureManager::GetTexture("face_happy"));
                        for (int i = 0; i < 3; i++) {
                            numberDisplay.at(i).setTextureRect(numberRects.at(nums.at(i)));
                        }
                    }

                    //test2
                    else if ((position.x > 627 && position.x < 692) && (position.y > 512 && position.y < 576)) {
                        gameBoard.Initialize(2);

                        nums = Extra::numbers(gameBoard.GetTotalMines() - gameBoard.GetTotalFlags());
                        faceIcon.setTexture(TextureManager::GetTexture("face_happy"));
                        for (int i = 0; i < 3; i++) {
                            numberDisplay.at(i).setTextureRect(numberRects.at(nums.at(i)));
                        }
                    }

                    //test 3
                    else if ((position.x > 691 && position.x < 756) && (position.y > 512 && position.y < 576)) {
                        gameBoard.Initialize(3);

                        nums = Extra::numbers(gameBoard.GetTotalMines() - gameBoard.GetTotalFlags());
                        faceIcon.setTexture(TextureManager::GetTexture("face_happy"));
                        for (int i = 0; i < 3; i++) {
                            numberDisplay.at(i).setTextureRect(numberRects.at(nums.at(i)));
                        }
                    }

                    //face bootton
                    else if ((position.x > 349 && position.x < 414) && (position.y > 512 && position.y < 576)) {
                        //start with random not regular intialize
                        gameBoard.InitializeRandom();

                        nums = Extra::numbers(gameBoard.GetTotalMines() - gameBoard.GetTotalFlags());
                        faceIcon.setTexture(TextureManager::GetTexture("face_happy"));
                        for (int i = 0; i < 3; i++) {
                            numberDisplay.at(i).setTextureRect(numberRects.at(nums.at(i)));
                        }
                    }
                }
            }
        }


        //draw the board: call the .hpp smfl for this


        //clear the window
        gameWindow.clear();

        //draw all background and buttons

        gameWindow.draw(gameBackground);
        gameWindow.draw(faceIcon);
        gameWindow.draw(debugButton);
        gameWindow.draw(test1Button);
        gameWindow.draw(test2Button);
        gameWindow.draw(test3Button);

        for (int i = 0; i < 3; i++) {
            gameWindow.draw(numberDisplay.at(i));
        }

        for (unsigned int i = 0; i < gameBoard.GetBoardSize(); i++)
            gameWindow.draw(gameBoard.GetTile(i).GetSprite());


        //now that everything is loaded, can display it
        //call once!
        gameWindow.display();
    }
    //fox: have to clear the texture manager afterwards, or else you get a weird error
    TextureManager::Clear();

}

/*
 * references:
 * https://www.geeksforgeeks.org/cpp-implementation-minesweeper-game/
 * https://www.sfml-dev.org/tutorials/2.5/window-window.php
 * https://cplusplus.com/forum/beginner/59662/
 * https://www.geeksforgeeks.org/switch-statement-cc/
 * https://stackoverflow.com/questions/10135244/how-to-fix-c-error-expected-unqualified-id
 * https://www.geeksforgeeks.org/nested-classes-in-c/#:~:text=A%20nested%20class%20is%20a,access%20rules%20shall%20be%20obeyed.
 * https://www.geeksforgeeks.org/enum-classes-in-c-and-their-advantage-over-enum-datatype/
 * https://www.geeksforgeeks.org/cpp-implementation-minesweeper-game/
 * https://www.geeksforgeeks.org/switch-statement-cc/
 */