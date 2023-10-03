#pragma once
#include "SFML/Graphics.hpp"
#include <unordered_map>
#include <string>
#include <iostream>
using std::unordered_map;
using std::string;

class TextureManager {
    //static = one of these in memory, ever
    static unordered_map<string, sf::Texture> textures;
    static void LoadTexture(const char* textureName);
public:
    static sf::Texture& GetTexture(const char* textureName);
    static void Clear();
};

//redeclare var so the file knows it exists
//if doesnt exist; find == end
//NEED TO CALL CLEAR!