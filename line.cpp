#include "line.h"
#include "OGL/inc/freeglut.h"
#include "Camera.hpp"
#include <iostream>
void AddLine(glm::vec2 const &start, glm::vec2 const &end)
{
  Line l = {
      {start.x / globalPass::windowWidth, start.y / globalPass::windowHeight},
      {end.x   / globalPass::windowWidth, end.y   / globalPass::windowHeight} 
      };
  globalPass::lines.push_back(l);
}

void ClearLines(void)
{
  size_t i = globalPass::lines.capacity();
  // std::cout << i << std::endl; // Capacity Test
  globalPass::lines.clear();
  // std::cout << globalPass::lines.capacity() << std::endl; // Capacity Test

  globalPass::lines.reserve(i);
}

void drawLine(Line line)
{
  glBegin(GL_LINES);
  glPointSize(1.0f);
  globalPass::camera.Draw(line.startPosition);
  globalPass::camera.Draw(line.endPosition);
  glEnd();
}

bool operator==(const Line& lhs, const Line& rhs)
{
  return lhs.startPosition == rhs.startPosition && lhs.endPosition == rhs.endPosition;

}