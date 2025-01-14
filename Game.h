/*
Game class function signatures
*/

#ifndef GAME_H
#define GAME_H

// Include libraries
#include <SFML/Graphics.hpp>
// Include local header files
#include "Object3D.h"

// Game class
class Game {
  private:
    sf::RenderWindow* win;
    Object3D* obj_3d;
  public:
    // Create Game object with certain screen settings
    Game();
    // Game loop
    void gameLoop();
    // Render Game
    void renderGame();
    // Delete all Game related objects
    ~Game();
};

#endif