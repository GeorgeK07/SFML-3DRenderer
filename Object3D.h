/*
Object3D class function signatures
*/

#ifndef OBJECT3D_H
#define OBJECT3D_H

// Include libraries
#include <SFML/Graphics.hpp>

// Object3D class
class Object3D {
  private:
    // Stores x,y,z coords of all vertices
    double* x_coords;
    double* y_coords;
    double* z_coords;
    // Focal length
    double focal_length;
    // Camera position
    double* camera;
    // Pitch, yaw, roll angles
    double pitch_angle;
    double yaw_angle;
    double roll_angle;
    // Prev 3d x and y pos
    double* prev_x_3d_pos;
    double* prev_y_3d_pos;
    // Stores temp x,y,z coords of all vertices when rotated
    double* x_rot_coords;
    double* y_rot_coords;
    double* z_rot_coords;
    // Stores all final vertices to show onscreen
    sf::VertexArray vertices;
    // Text object that shows all coords and stuff
    sf::Text* text_obj;
    sf::Font* font;
  public:
    // Create Object3D object
    Object3D();
    // Get inputs and do stuff with them
    void getInputs(sf::Keyboard::Key x_dec, sf::Keyboard::Key x_inc,
      sf::Keyboard::Key y_dec, sf::Keyboard::Key y_inc,
      sf::Keyboard::Key z_dec, sf::Keyboard::Key z_inc,
      sf::Keyboard::Key x_angle_dec, sf::Keyboard::Key x_angle_inc,
      sf::Keyboard::Key y_angle_dec, sf::Keyboard::Key y_angle_inc,
      sf::Keyboard::Key z_angle_dec, sf::Keyboard::Key z_angle_inc,
      sf::Keyboard::Key focal_dec, sf::Keyboard::Key focal_inc);
    // Calc pitch (x rotation)
    void calcPitch(int i);
    // Calc yaw (y rotation)
    void calcYaw(int i);
    // Calc roll (z rotation)
    void calcRoll(int i);
    // Set the 2d position of each 3d point
    void set2DPosOfPoints();
    // Calc 2d xpos
    double calc2DXPos(int i);
    // Calc 2d ypos
    double calc2DYPos(int i);
    // Render Object3D
    void renderObject3D(sf::RenderWindow* win);
    // Render text object
    void renderTextObject(sf::RenderWindow* win);
    // Delete all char_obj related objects
    ~Object3D();
};

#endif