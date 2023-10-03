#include "Board.h"
#include <iostream>
using namespace std;

//begin with basic board stuff
Board::Board() {
    //theres no default board?
}
Board::Board(unsigned int boardWidth, unsigned int boardHeight) {
    this->boardHeight = boardHeight;
    this->boardWidth = boardWidth;
    //nothign else to initialzie
}
unsigned int Board::GetBoardWidth() {
    return boardWidth;
}

unsigned int Board::GetBoardHeight() {
    return boardHeight;
}

unsigned int Board::GetBoardSize() {
    unsigned int boardArea = boardHeight * boardWidth;
    return boardArea;
}

//place stuff on board: mines, tiles, flags
//tiles
Tile& Board::GetTile(unsigned int chosenTile) {
    return board.at(chosenTile);
}
void Board::RevealTile(Tile* currentTile) {
    bool result = currentTile->RevealTile();
    //pointer to it? ask
    //recursive fucntion; careful

    if (result) {
        SetGameOver();
    }
}
//mines
int Board::GetTotalMines() {
    return totalMines;
}
//flags
void Board::ShowFlag(Tile* currentTile) {
    currentTile->ShowFlag(boardDebug);
}

int Board::GetTotalFlags()  {
    totalFlag = 0; //needs to reset the number of flags so as to not confuse the counter

    for (unsigned int i = 0; i < GetBoardSize(); i++) {
        //count every flag on the board
        if (board.at(i).GetTileState() == Tile::TileState::flagged)
            totalFlag++;
    }
    return totalFlag;
}



//main functions:
void Board::ClearBoard(int totalMines, int totalFlags, bool gameOver, bool victory) {
    gameOver = false;
    victory = false;
    totalMines = 0;
    totalFlag = 0;
}
void Board::Initialize(int load_board) {
    //intialize by reading file first
    //then we clear everything
    //then create the 32x32
    //and then call the neighbors
    vector<char> bombs = Extra::inputFile(load_board);

    // clear stuff
    //ClearBoard(totalMines,totalFlag,gameOver,victory);
    board.clear();
    gameOver = false;
    victory = false;
    totalMines = 0;
    totalFlag = 0;


    //now create the 32 x 32 board
    //this is the easy form of minesweeper? per geeksforgeeks
    for (unsigned int i = 0; i < boardHeight; i++) { //go across the columns and row
        //could i maybe use the vector?
        //NO LOL

        for (unsigned int j = 0; j < boardWidth; j++) {
            sf::Vector2f position = sf::Vector2f((float)(j) * 32, (float)(i) * 32); //need to do this in floats

            Tile::RevealedTileState rTileState;
            unsigned int value = (boardWidth * i) + j;

            if (bombs.at(value) == '1') { //i and j serve as x and y coord

                rTileState = Tile::RevealedTileState::bomb;
                totalMines++;
            }
            else {
                rTileState = Tile::RevealedTileState::none;
            }

            //debug mode mines must show
            //does flag or bomb matter? no
            if (boardDebug && rTileState == Tile::RevealedTileState::bomb) {
                Tile tempTile = Tile(position, "mine", rTileState);
                board.push_back(tempTile);
            }
            else {
                Tile tempTile = Tile(position, "tile_hidden", rTileState);
                board.push_back(tempTile);
            }
        }
    }
    //now call to the neighbors
    SetAllNeighbors();
    SetNeighborsStates();
}


void Board::InitializeRandom() {
    //firstly generate mine positions at random
    //then intialize and clear board
    //create the 32x32
    //then do the random bombs
    //stop calling them bombs itll be confusing
    vector<int> randomMines;

    randomMines.push_back(Random::Int(0, 399));

    //iterate through randomMines.size()
    //for (unsigned int i = 0; i < randomMines.size(); i ++)
    //dont use for loop, no i values to place
    //also size cant exclude 50
    while (randomMines.size() < 50) {

        int location = Random::Int(0,399);
        bool check = false;

        for (unsigned int i = 0; i < randomMines.size(); i++) {
            if (location == randomMines.at(i)) {
                check = true;
                break;
            }
        }
        if (!check)
            randomMines.push_back(location);
    }

    // Initialize Board
    //ClearBoard(totalMines,totalFlag,gameOver,victory);
    //clearboard for some reason does not clear the counter; jsut keep this
    board.clear();
    gameOver = false;
    victory = false;
    totalMines = 0;
    totalFlag = 0;


    //copy this? 32x32 code
    for (unsigned int i = 0; i < boardHeight; i++) {
        for (unsigned int j = 0; j < boardWidth; j++) {
            sf::Vector2f position = sf::Vector2f((float)(j) * 32, (float)(i) * 32); //float calc

            Tile::RevealedTileState rTileState = Tile::RevealedTileState::none;
            Tile tempTile = Tile(position, "tile_hidden", rTileState);

            board.push_back(tempTile);
        }
    }

    //random bombs!
    for (unsigned int i = 0; i < randomMines.size(); i++) { //iterate all the randomMines

        board.at(randomMines.at(i)).SetRevealedTileState(Tile::RevealedTileState::bomb);
        totalMines++;

        if (boardDebug == true)
            board.at(randomMines.at(i)).SetSprite("mine");
    }

    SetAllNeighbors();
    SetNeighborsStates();
}


//neighbors
void Board::SetAllNeighbors() {
    for (unsigned int i = 0; i < board.size(); i++) {
        //ok this si super confusing
        //switch method?
        //woudl have to create a ton of summs/values to do that
        //refernece how image vectors are drawn: project 2

        //top left
        if (i == 0) {
            board.at(i).AddNeighborTile(&board.at(1));
            board.at(i).AddNeighborTile(&board.at(boardWidth));
            board.at(i).AddNeighborTile(&board.at(boardWidth + 1));
        }
        //top right
        else if (i == boardWidth - 1) {
            board.at(i).AddNeighborTile(&board.at(i - 2));
            board.at(i).AddNeighborTile(&board.at(i * 2));
            board.at(i).AddNeighborTile(&board.at((i * 2) + 1));
        }
        //bottom left
        else if (i == (boardWidth * boardHeight) - boardWidth) {
            board.at(i).AddNeighborTile(&board.at(i - boardWidth));
            board.at(i).AddNeighborTile(&board.at(i - boardWidth + 1));
            board.at(i).AddNeighborTile(&board.at(i + 1));
        }
        //bottom right
        else if (i == (boardWidth * boardHeight) - 1) {
            board.at(i).AddNeighborTile(&board.at(i - boardWidth));
            board.at(i).AddNeighborTile(&board.at(i - boardWidth - 1));
            board.at(i).AddNeighborTile(&board.at(i - 1));
        }

        //sides now??
        //THIS IS SO TEDIOUS
        //top
        else if (i > 0 && i < boardWidth - 1) {
            board.at(i).AddNeighborTile(&board.at(i - 1));
            board.at(i).AddNeighborTile(&board.at(i + 1));
            board.at(i).AddNeighborTile(&board.at(i + boardWidth - 1));
            board.at(i).AddNeighborTile(&board.at(i + boardWidth));
            board.at(i).AddNeighborTile(&board.at(i + boardWidth + 1));
        }
        //bottom
        else if (i > (boardWidth * boardHeight) - boardWidth && i < (boardWidth * boardHeight) - 1) {
            board.at(i).AddNeighborTile(&board.at(i - boardWidth - 1));
            board.at(i).AddNeighborTile(&board.at(i - boardWidth));
            board.at(i).AddNeighborTile(&board.at(i - boardWidth + 1));
            board.at(i).AddNeighborTile(&board.at(i - 1));
            board.at(i).AddNeighborTile(&board.at(i + 1));
        }
         //right side
        else if ((i + 1) % boardWidth == 0) {
            board.at(i).AddNeighborTile(&board.at(i - 1));
            board.at(i).AddNeighborTile(&board.at(i - boardWidth));
            board.at(i).AddNeighborTile(&board.at(i + boardWidth));
            board.at(i).AddNeighborTile(&board.at(i - 1 - boardWidth));
            board.at(i).AddNeighborTile(&board.at(i - 1 + boardWidth));
        }
        //left side
        else if (i % boardWidth == 0) { //modulo super confusing to figoure out; why
            board.at(i).AddNeighborTile(&board.at(i + 1));
            board.at(i).AddNeighborTile(&board.at(i + 1 - boardWidth));
            board.at(i).AddNeighborTile(&board.at(i + 1 + boardWidth));
            board.at(i).AddNeighborTile(&board.at(i + boardWidth));
            board.at(i).AddNeighborTile(&board.at(i - boardWidth));
        }


         //others: bruh..
        else {
            board.at(i).AddNeighborTile(&board.at(i - 1));
            board.at(i).AddNeighborTile(&board.at(i - 1 + boardWidth));
            board.at(i).AddNeighborTile(&board.at(i - 1 - boardWidth));
            board.at(i).AddNeighborTile(&board.at(i + 1));
            board.at(i).AddNeighborTile(&board.at(i + 1 + boardWidth));
            board.at(i).AddNeighborTile(&board.at(i + 1 - boardWidth));
            board.at(i).AddNeighborTile(&board.at(i + boardWidth));
            board.at(i).AddNeighborTile(&board.at(i - boardWidth));
        }
    }
}


void Board::SetNeighborsStates() {
    for (unsigned int i = 0; i < board.size(); i++) {
        //first check if not a mine
        //then check neighbors for mines
        //then set the numbers based on this check for the neighbors in the board
        //this becomes their revealed state

        if (board.at(i).GetRevealedTileState() != Tile::RevealedTileState::bomb) {
            int neighboringMineCount = 0;

            //count all the neighboring mines
            //i love counting functions
            for (unsigned int j = 0; j < board.at(i).NeighborTileCount(); j++) {
                Tile* tempTile = board.at(i).GetNeighborTiles(j);

                if (tempTile->GetRevealedTileState() == Tile::RevealedTileState::bomb) {
                    neighboringMineCount++;
                }
            }

            // SWITCH TIME
            //this will set the revealed state to whatever the case is
            switch(neighboringMineCount) {
                case 1:
                    board.at(i).SetRevealedTileState(Tile::RevealedTileState::one);
                    break;
                case 2:
                    board.at(i).SetRevealedTileState(Tile::RevealedTileState::two);
                    break;
                case 3:
                    board.at(i).SetRevealedTileState(Tile::RevealedTileState::three);
                    break;
                case 4:
                    board.at(i).SetRevealedTileState(Tile::RevealedTileState::four);
                    break;
                case 5:
                    board.at(i).SetRevealedTileState(Tile::RevealedTileState::five);
                    break;
                case 6:
                    board.at(i).SetRevealedTileState(Tile::RevealedTileState::six);
                    break;
                case 7:
                    board.at(i).SetRevealedTileState(Tile::RevealedTileState::seven);
                    break;
                case 8:
                    board.at(i).SetRevealedTileState(Tile::RevealedTileState::eight);
                    break;
                default:
                    board.at(i).SetRevealedTileState(Tile::RevealedTileState::none);
            }
        }
    }
}

//debug mode now
void Board::ShowDebug() {
    if (boardDebug) {
        boardDebug = false;
    }
    else {
        boardDebug = true;
    }
    //if the game continues; write a continue function?
    if (!gameOver && !victory) {
        for (unsigned int i = 0; i < GetBoardSize(); i++) {

            if (boardDebug && board.at(i).GetRevealedTileState() == Tile::RevealedTileState::bomb)
                board.at(i).SetSprite("mine");

                //!boardDebug for these!
            else if (!boardDebug && board.at(i).GetRevealedTileState() == Tile::RevealedTileState::bomb)
                board.at(i).SetSprite("tile_hidden");

            else if (!boardDebug && board.at(i).GetTileState() == Tile::TileState::flagged)
                board.at(i).SetSprite("flag");

        }
    }
}

//final functions
//check if there is victory or loss
//can this be implemented in main? prob
bool Board::GetVictory() {

    //count the amount of revealed tiles there are
    int amountOfRevealedTiles = 0;
    for (unsigned int i = 0; i < GetBoardSize(); i++) {
        if (board.at(i).GetTileState() == Tile::TileState::revealed)
            amountOfRevealedTiles++;
    }

    //now check to see if the bombs are all gone
    if (GetBoardSize() - amountOfRevealedTiles - totalMines == 0) {
        for (unsigned int i = 0; i < board.size(); i++) {

            //when we have victory, dont need to click anymore
            //and we replace sprites
            board.at(i).LeftClick(false);
            board.at(i).RightClick(false);

            if (board.at(i).GetRevealedTileState() == Tile::RevealedTileState::bomb)
                board.at(i).SetSprite("flag");

        }
        victory = true;
        return true;
    }
    return false;
}

bool Board::GetGameOver() {
    return gameOver;
}

void Board::SetGameOver() {

    gameOver = true;

    //game over: no more clicking! tiles cannot be altered
    //cant just set gameOver to true
    for (unsigned int i = 0; i < board.size(); i++) {

        board.at(i).LeftClick(false);
        board.at(i).RightClick(false);

        if (board.at(i).GetRevealedTileState() == Tile::RevealedTileState::bomb)
            board.at(i).SetSprite("mine");

    }
}

Board::~Board() {
    //implement later
    //needed?
}
//references in main
