#include "Tile.h"
#include <iostream>
using namespace std;
//i want to scream

Tile::Tile() {
    //anything? what is a default sprite
}

Tile::Tile(sf::Vector2f _position, const char* texture, RevealedTileState revealedTileState) {
    this->tileSprite = sf::Sprite(TextureManager::GetTexture(texture));
    this->tileSprite.setPosition(_position.x, _position.y);
    this->tilePosition = _position;
    this->tileState = TileState::hidden;
    this->revealedTileState = revealedTileState;
    this->leftClickable = 1;
    this->rightClickable = 1;
}
Tile::TileState Tile::GetTileState() { //can be made const?
    return tileState;
}
void Tile::SetTileState(Tile::TileState tileStateChange)  {
    tileState = tileStateChange;
}
Tile::RevealedTileState Tile::GetRevealedTileState() {
    return revealedTileState;
}
void Tile::SetRevealedTileState(Tile::RevealedTileState revealedTileStateChange) {
    revealedTileState = revealedTileStateChange;
}

//spite stuff!
sf::Sprite& Tile::GetSprite() {
    return tileSprite;
}
void Tile::SetSprite(const char* texture) {
    //FOX CODE

    tileSprite.setTexture(TextureManager::GetTexture(texture));
    tileSprite.setPosition(tilePosition);
}


//left n right clicks
void Tile::LeftClick(bool clickableStateL) {
    if (clickableStateL){
        leftClickable = 1;
    }
    else
        leftClickable = 0;
    //make bool?

}
void Tile::RightClick(bool clickableStateR) {
    if (clickableStateR){
        rightClickable = 1;
    }
    else {
        rightClickable = 0;
    }
}

//neighbors
void Tile::AddNeighborTile(Tile *newNeighborTile) {
    //pushback to tileneighbors vector
    //no need to create a variable dummy
    tileNeighbors.push_back(newNeighborTile);
}

Tile* Tile::GetNeighborTiles(unsigned int tileNeighbor) {
    //this will get the neighbors at a certain point from the vector
    //Tile* neighborSearch = tileNeighbors.at(tileNeighbor);
    //return neighborSearch;
    return tileNeighbors.at(tileNeighbor);
}
unsigned int Tile::NeighborTileCount() {
    //count is needed for the neighbor number thign!
    return tileNeighbors.size();
}

//main functionality
bool Tile::RevealTile() {
    //first check if you can left click

    if (leftClickable == 1) {
        if (tileState == TileState::hidden) {
            //then set the state to revealed
            //and iterate through and change the sprite!
            //then also change bool to be true; everythign else returns false
            tileState = TileState::revealed;
            switch(revealedTileState) {
                case RevealedTileState::one:
                    SetSprite("number_1");
                    return false;
                case RevealedTileState::two:
                    SetSprite("number_2");
                    return false;
                case RevealedTileState::three:
                    SetSprite("number_3");
                    return false;
                case RevealedTileState::four:
                    SetSprite("number_4");
                    return false;
                case RevealedTileState::five:
                    SetSprite("number_5");
                    return false;
                case RevealedTileState::six:
                    SetSprite("number_6");
                    return false;
                case RevealedTileState::seven:
                    SetSprite("number_7");
                    return false;
                case RevealedTileState::eight:
                    SetSprite("number_8");
                    return false;
                case RevealedTileState::bomb:
                    SetSprite("mine");
                    return true;
                case RevealedTileState::none:
                    SetSprite("tile_revealed");
                    for (unsigned int i = 0; i < NeighborTileCount(); i++)
                        GetNeighborTiles(i)->RevealTile();
                    //this will reveal all the neighboring tiles aroun it

                    return false;
            }
        }
    }
    return false;
}


//flag debuggin'
void Tile::ShowFlag(bool flagDebugging) {
    //first check if you can right click
    if (rightClickable == 1) {
        //flag the spot
        if (tileState == TileState::hidden) {
            leftClickable = 0;
            tileState = TileState::flagged;
            SetSprite("flag");
        }
        //remove the flag
        else if (tileState == TileState::flagged) {
            leftClickable = 1;
            tileState = TileState::hidden;
            SetSprite("tile_hidden");
        }
        //specific case if marking a mine
        else if (tileState == TileState::flagged && flagDebugging && revealedTileState == RevealedTileState::bomb) {
            leftClickable = 1;
            tileState = TileState::hidden;
            SetSprite("mine");
        }
    }
}

Tile::~Tile() {
    //maybe also empty
}

//references in main
