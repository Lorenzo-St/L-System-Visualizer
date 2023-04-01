#include "Camera.hpp"
#include "OGL/inc/freeglut.h"
#include <iostream>

void drawLoop();
void InputCallBack(unsigned char c, int i1, int i2);


void Camera2D::Draw(glm::vec2 const &location)
{
  // std::cout << "Drawing " << location.x << "," << location.y << std::endl;
  glVertex2d((location.x - positionVector.x), (location.y - positionVector.y));

}

void Camera2D::SetColor(Color const &color)
{
  this->color = color;
  glColor4f(color.r, color.g, color.b, color.a);
}

void Camera2D::MovePosition(glm::vec2 const &position)
{
  this->positionVector = position;
  // std::cout << "Position: " << this->positionVector.x  << ", " << this->positionVector.y << std::endl;
}

glm::vec2 Camera2D::GetPosition(void)
{
  return this->positionVector;
}


void Camera2D::InitWindow(void (*drawFunc)(), void (*keyboardFunc)(unsigned char, int, int), void (*keyboardReleaseFunc)(unsigned char, int, int))
{
  glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - globalPass::windowWidth) / 2,
                         (glutGet(GLUT_SCREEN_HEIGHT) - globalPass::windowHeight) / 2);
  glutInitWindowSize(globalPass::windowWidth, globalPass::windowHeight);
  glutCreateWindow("OpenGL Setup Test");
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
  glutReshapeWindow(globalPass::windowWidth, globalPass::windowHeight);
  glutDisplayFunc(drawFunc);
  glutKeyboardFunc(keyboardFunc);
  glutKeyboardUpFunc(keyboardReleaseFunc);
}