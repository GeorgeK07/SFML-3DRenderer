/*
Object3D class function definitions
*/

// Include libraries
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
// Include local header files
#include "Object3D.h"

// Create Object3D object
Object3D::Object3D() {
  // Set coords for each point
  x_coords = new double[8]{1, 1, -1, -1, 1, 1, -1, -1};
  y_coords = new double[8]{1, -1, 1, -1, 1, -1, 1, -1};
  z_coords = new double[8]{-1, -1, -1, -1, 1, 1, 1, 1};
  // Set focal length and camera position
  focal_length = 5;
  camera = new double[3]{0, 0, -2};
  // Set pitch, yaw, and roll angles
  pitch_angle = 0;
  yaw_angle = 0;
  roll_angle = 0;
  // Set prev 3d coords arrays to empty
  prev_x_3d_pos = new double[8]{0};
  prev_y_3d_pos = new double[8]{0};
  // Create a vertex array
  vertices = sf::VertexArray(sf::Points, 8);
  //  Calc 2d pos of 3d points for first time, also cache them so x and y camera
  // movements don't need to recompute y and x 2d coords
  set2DPosOfPoints();
  // Load font
  font = new sf::Font;
  font->loadFromFile("PublicPixel.ttf");
  font->setSmooth(false);
  if (!font->loadFromFile("PublicPixel.ttf")) {
    std::cout << "Font failed to load.\n";
    exit(1);
  }
  // Create new text object and set properties
  text_obj = new sf::Text;
  text_obj->setFont(*font);
  text_obj->setCharacterSize(8);
  text_obj->setFillColor(sf::Color::White);
  text_obj->setPosition(4, 4);
}

// Get inputs and do stuff with them
void Object3D::getInputs(sf::Keyboard::Key x_dec, sf::Keyboard::Key x_inc,
  sf::Keyboard::Key y_dec, sf::Keyboard::Key y_inc,
  sf::Keyboard::Key z_dec, sf::Keyboard::Key z_inc,
  sf::Keyboard::Key x_angle_dec, sf::Keyboard::Key x_angle_inc,
  sf::Keyboard::Key y_angle_dec, sf::Keyboard::Key y_angle_inc,
  sf::Keyboard::Key z_angle_dec, sf::Keyboard::Key z_angle_inc,
  sf::Keyboard::Key focal_dec, sf::Keyboard::Key focal_inc) {
  // If user presses key, move/rotate points
  if (sf::Keyboard::isKeyPressed(x_dec)) {
    camera[0] += -0.1;
  }
  if (sf::Keyboard::isKeyPressed(x_inc)) {
    camera[0] += 0.1;
  }
  if (sf::Keyboard::isKeyPressed(y_dec)) {
    camera[1] += -0.1;
  }
  if (sf::Keyboard::isKeyPressed(y_inc)) {
    camera[1] += 0.1;
  }
  if (sf::Keyboard::isKeyPressed(z_dec)) {
    camera[2] += -0.1;
  }
  if (sf::Keyboard::isKeyPressed(z_inc)) {
    camera[2] += 0.1;
  }
  if (sf::Keyboard::isKeyPressed(x_angle_dec)) {
    pitch_angle += -0.1;
  }
  if (sf::Keyboard::isKeyPressed(x_angle_inc)) {
    pitch_angle += 0.1;
  }
  if (sf::Keyboard::isKeyPressed(y_angle_dec)) {
    yaw_angle += -0.1;
  }
  if (sf::Keyboard::isKeyPressed(y_angle_inc)) {
    yaw_angle += 0.1;
  }
  if (sf::Keyboard::isKeyPressed(z_angle_dec)) {
    roll_angle += -0.1;
  }
  if (sf::Keyboard::isKeyPressed(z_angle_inc)) {
    roll_angle += 0.1;
  }
  if (sf::Keyboard::isKeyPressed(focal_dec)) {
    focal_length += -0.1;
  }
  if (sf::Keyboard::isKeyPressed(focal_inc)) {
    focal_length += 0.1;
  }
  // Set 2d xpos of each 3d point if camera has changed
  if (sf::Keyboard::isKeyPressed(x_dec) || sf::Keyboard::isKeyPressed(x_inc)) {
    // For loop that uses functions to calc 2d position for each 3d point
    for (int i = 0; i < 8; i++) {
      prev_x_3d_pos[i] = calc2DXPos(i);
      vertices[i].position = sf::Vector2f(prev_x_3d_pos[i] + 160, prev_y_3d_pos[i] + 120);
    }
  }
  if (sf::Keyboard::isKeyPressed(y_dec) || sf::Keyboard::isKeyPressed(y_inc)) {
    // For loop that uses functions to calc 2d position for each 3d point
    for (int i = 0; i < 8; i++) {
      prev_y_3d_pos[i] = calc2DYPos(i);
      vertices[i].position = sf::Vector2f(prev_x_3d_pos[i] + 160, prev_y_3d_pos[i] + 120);
    }
  }
  if (sf::Keyboard::isKeyPressed(z_dec) || sf::Keyboard::isKeyPressed(z_inc)) {
    set2DPosOfPoints();
  }
  // Set rotation of each 3d point if angle has changed
  if (sf::Keyboard::isKeyPressed(z_angle_dec) || sf::Keyboard::isKeyPressed(z_angle_inc)) {
    for (int i = 0; i < 8; i++) {
      calcRoll(i);
    }
    set2DPosOfPoints();
  }
  if (sf::Keyboard::isKeyPressed(x_angle_dec) || sf::Keyboard::isKeyPressed(x_angle_inc)) {
    for (int i = 0; i < 8; i++) {
      calcPitch(i);
    }
    set2DPosOfPoints();
  }
  if (sf::Keyboard::isKeyPressed(y_angle_dec) || sf::Keyboard::isKeyPressed(y_angle_inc)) {
    for (int i = 0; i < 8; i++) {
      calcYaw(i);
    }
    set2DPosOfPoints();
  }
}

// Calc pitch (x rotation)
void Object3D::calcPitch(int i) {
  y_coords[i] = cos(pitch_angle) * (y_coords[i] - camera[1]) + sin(pitch_angle) * (camera[2] - z_coords[i]) + camera[1];
  z_coords[i] = sin(pitch_angle) * (y_coords[i] - camera[1]) + cos(pitch_angle) * (z_coords[i] - camera[2]) + camera[2];
}

// Calc yaw (y rotation)
void Object3D::calcYaw(int i) {
  x_coords[i] = cos(yaw_angle) * (x_coords[i] - camera[0]) + sin(yaw_angle) * (camera[2] - z_coords[i]) + camera[0];
  z_coords[i] = sin(yaw_angle) * (x_coords[i] - camera[0]) + cos(yaw_angle) * (z_coords[i] - camera[2]) + camera[2];
}

// Calc roll (z rotation)
void Object3D::calcRoll(int i) {
  x_coords[i] = x_coords[i] * cos(roll_angle) - z_coords[i] * sin(roll_angle);
  z_coords[i] = x_coords[i] * sin(roll_angle) - z_coords[i] * cos(roll_angle);
}

// Set the 2d position of each 3d point
void Object3D::set2DPosOfPoints() {
  // For loop that uses functions to calc 2d position for each 3d point
  for (int i = 0; i < 8; i++) {
    prev_x_3d_pos[i] = calc2DXPos(i);
    prev_y_3d_pos[i] = calc2DYPos(i);
    vertices[i].position = sf::Vector2f(prev_x_3d_pos[i] + 160, prev_y_3d_pos[i] + 120);
  }
}

// Calc 2d xpos
double Object3D::calc2DXPos(int i) {
  std::cout << "2D X of point index " << i << ": " << focal_length * (x_coords[i] - camera[0]) / (z_coords[i] - camera[2]) << std::endl;
  return focal_length * (x_coords[i] - camera[0]) / (z_coords[i] - camera[2]);
}

// Calc 2d ypos
double Object3D::calc2DYPos(int i) {
  std::cout << "2D Y of point index " << i << ": " << focal_length * (y_coords[i]  - camera[1]) / (z_coords[i] - camera[2]) << std::endl;
  return focal_length * (y_coords[i]  - camera[1]) / (z_coords[i] - camera[2]);
}

// Render Object3D
void Object3D::renderObject3D(sf::RenderWindow* win) {
  win->draw(vertices);
}

// Render text object
void Object3D::renderTextObject(sf::RenderWindow* win) {
  // Change string set
  text_obj->setString("CAM X: " + std::to_string(camera[0]) +
    "\nCAM Y: " + std::to_string(camera[1]) +
    "\nCAM Z: " + std::to_string(camera[2]) +
    "\nFOCAL LENGTH: " + std::to_string(focal_length) +
    "\nPITCH ANGLE: " + std::to_string(pitch_angle) +
    "\nYAW ANGLE: " + std::to_string(yaw_angle) +
    "\nROLL ANGLE: " + std::to_string(roll_angle));
  win->draw(*text_obj);
}

// Delete all Object3D related objects
Object3D::~Object3D() {}