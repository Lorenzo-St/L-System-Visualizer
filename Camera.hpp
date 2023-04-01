#pragma once
#include "GLM\glm.hpp"
#include "color.h"
#include "OGL/inc/freeglut.h"
class Camera2D
{
private:
  float zoom;
  Color color;
  glm::vec2 positionVector;
  glm::vec2 rotationVector;

public:
  Camera2D(float zoom) : zoom(zoom)
  {
    positionVector = glm::vec2(0, 0);
    rotationVector = glm::vec2(0, 0);
    color = {1, 1, 1, 1};
    glColor4f(color.r, color.g, color.b, color.a);
  };
  Camera2D(const Camera2D &c) : zoom(c.zoom),
                                positionVector(c.positionVector),
                                rotationVector(c.rotationVector)
  {
    color = {1, 1, 1, 1};
    glColor4f(color.r, color.g, color.b, color.a);
  };

  Camera2D(float zoom, glm::vec2 const &position) : zoom(zoom),
                                                    positionVector(position)
  {
    color = {1, 1, 1, 1};
    glColor4f(color.r, color.g, color.b, color.a);
  };

  void Camera2D::InitWindow(void (*drawFunc)(), void (*keyboardFunc)(unsigned char, int, int), void (*keyboardReleaseFunc)(unsigned char, int, int));
  void Draw(glm::vec2 const &location);
  void SetColor(Color const &color);
  void MovePosition(glm::vec2 const &position);
  glm::vec2 GetPosition(void);
};

namespace globalPass
{
  extern Camera2D camera;
  extern int windowWidth, windowHeight;
}