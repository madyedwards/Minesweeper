
#include "TextureManager.h"
#include "Tile.h"
#include "Extra.h"
#include "Random.h"
#include <vector>
#include <iostream>
using namespace std;

class Board {
private:
    //board needs to have width and height dimensions
    //columns n rows?
    //also needs to contain and tracker of the total mines and flags; mine for the little numbers
    //push into vector later
    //according to fox, a map mightve been better....
    vector<Tile> board; //boardobject? eh
    unsigned int boardHeight;
    unsigned int boardWidth;

    int totalMines = 0; //INITIALIZE!
    int totalFlag = 0;

    bool boardDebug = false;
    bool victory = false;
    bool gameOver = false;//could call it loss but game over is more fun
public:
    //only thins to draw on BOARD: not screen!!!!!!!!!!!!
    //only include flags, tiles, and mines here
    //constructros
    Board();
    Board(unsigned int boardWidth, unsigned int boardHeight); //height x width?
    //NOT CHANGING THAT NEVERMINDDDD
    void Initialize(int board); //these are important to begin with
    void InitializeRandom();

    //get n set

    unsigned int GetBoardWidth();
    unsigned int GetBoardHeight();
    unsigned int GetBoardSize();
    int GetTotalFlags();
    int GetTotalMines();
    Tile& GetTile(unsigned int chosenTile);
    void SetNeighborsStates();
    void SetAllNeighbors();
    bool GetGameOver(); //show if game over or victory
    bool GetVictory();

    //extra
    void ShowDebug();
    void SetGameOver();
    void RevealTile(Tile* currentTile);
    void ShowFlag(Tile* currentTile);
    void ClearBoard(int totalMines, int totalFlags, bool gameOver, bool victory);

    //deconstructor
    ~Board();
};