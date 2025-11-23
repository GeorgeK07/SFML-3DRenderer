/*
Game class function definitions
*/

// Include libraries
#include <SFML/Graphics.hpp>
// Include local header files
#include "Object3D.h"
#include "Game.h"

// Create Game object with certain screen settings
Game::Game() {
  // Create 640x480 screen and scale 320x240 to it
  win = new sf::RenderWindow(sf::VideoMode({640, 480}), "SFML-SineScroller");
  sf::View view(sf::Vector2f(160, 120), sf::Vector2f(320, 240));
  win->setView(view);
  win->setPosition(
    sf::Vector2i(sf::VideoMode::getDesktopMode().size.x / 2 - 320,
    sf::VideoMode::getDesktopMode().size.y / 2 - 240));
  // Set framelimit to 60fps (Cannot be on at same time as vsync)
  // win->setFramerateLimit(60);
  win->setVerticalSyncEnabled(true); // Uncomment for vsync
  // Create an obj_3d
  obj_3d = new Object3D();
}

// Game loop
void Game::gameLoop() {
  // While the window is open, check if window has been closed, then render game
  while (win->isOpen()) {
    //  While events are polled, check if window close event has occured, and
    // close window if so
    while (const std::optional event = win->pollEvent()) {
      if (event->is<sf::Event::Closed>()) {
        win->close();
      }
    }
    // Calc 2d pos of 3d points
    obj_3d->getInputs(sf::Keyboard::Key::Left, sf::Keyboard::Key::Right, sf::Keyboard::Key::LShift,
      sf::Keyboard::Key::Space, sf::Keyboard::Key::Down, sf::Keyboard::Key::Up,
      sf::Keyboard::Key::Q, sf::Keyboard::Key::W, sf::Keyboard::Key::A,
      sf::Keyboard::Key::S, sf::Keyboard::Key::Z, sf::Keyboard::Key::X,
      sf::Keyboard::Key::E, sf::Keyboard::Key::R);
    // Set the 2d position of each 3d point
    obj_3d->set2DPosOfPoints();
    // Render Game
    renderGame();
  }
}

// Render Game
void Game::renderGame() {
  // Clear screen
  win->clear();
  // Draw obj_3d
  obj_3d->renderObject3D(win);
  // Draw text in obj_3d
  obj_3d->renderTextObject(win);
  // Display all objects drawn to screen
  win->display();
}

// Delete all Game related objects
Game::~Game() {
  // Delete obj_3d and window
  delete obj_3d;
  delete win;
}