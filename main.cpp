/*
Driver file
*/

// Include libraries
#include <SFML/Graphics.hpp>
// Include local header files
#include "Game.h"

// Main function
int main() {
  // Create object of class game
  Game newGame;
  newGame.gameLoop();
  return 0;
}