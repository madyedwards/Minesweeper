#include "TextureManager.h"

//redeclare the variable so the file knows it exists and can use it
unordered_map<string, sf::Texture> TextureManager::textures;

void TextureManager::LoadTexture(const char* fileName) {
    string path = "images/";
    path += fileName; //it doesn't like that as one line???
    path += ".png";

    textures[fileName].loadFromFile(path);
}

sf::Texture& TextureManager::GetTexture(const char* textureName) {
    //if texture does not exist
    if (textures.find(textureName) == textures.end()) {
        LoadTexture(textureName);
    }

    return textures[textureName];
}

void TextureManager::Clear() { //NEEDED; get a weird error its bc of not having this
    textures.clear();
}