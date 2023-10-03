#include <iostream>
#include "TextureManager.h"
#include <vector>
using namespace std;


class Tile {
public:
    //sets the states of the tiles
    /*struct TileState { //the state of the tile above
        string tileState; //this can be hidden, revealed, or flagged

        //default in entire tile default constuctor
    };
     */
    //help? enum class to fix unidentified id error 8
    //should i change the second struct to this too?
    enum class TileState { //these three options to choose from
        hidden,
        revealed,
        flagged};
    TileState tileState;
    TileState GetTileState();
    void SetTileState(TileState tileStateChange);

    //struct class?
    enum class RevealedTileState{
        one,
        two,
        three,
        four,
        five,
        six,
        seven,
        eight,
        bomb,
        none }; //the state of the tile underneath
    RevealedTileState revealedTileState; //this can be empty, one-eight, or bomb
    RevealedTileState GetRevealedTileState();
    void SetRevealedTileState(RevealedTileState revealedTileStateChange);


private:
    //need to implement a sprite to create the image
    //vectore to store all the tiles in the board
    //vector to store the neighbors
    //create struct for if the tile is hidden, revealed, or flagged
    //and another for if it is empty, has bomb, or 1-8
    //then also values for if it is left clicked or right clicked
    //how to setup mouse click?
    sf::Sprite tileSprite;
    sf::Vector2f tilePosition;
    vector<Tile*> tileNeighbors;
    int leftClickable; //make bool?
    int rightClickable;

public:

    //now constructors
    Tile();
    Tile(sf::Vector2f tilePosition, const char* tileTexture, RevealedTileState revealedTileState); //no passing in the top state

    //getters n setters
    //need to create sprites and change them
    //and to get neighbors, need to be able to change and add them, and take count
    sf::Sprite& GetSprite();
    Tile* GetNeighborTiles(unsigned int tileNeighbor);
    void SetSprite(const char* tileTexture);
    void LeftClick(bool clickableStateL);//true or false can it be clicked
    void RightClick(bool clickableStateR);

    //extras
    bool RevealTile();
    //reveal tile will also check if a bomb has been found
    void ShowFlag(bool flagDebugging); //debugging with flags
    void AddNeighborTile(Tile* newNeighborTile);
    unsigned int NeighborTileCount();

    //deconstructor? not sure, because they need ot stay after done with them
    ~Tile();
};

