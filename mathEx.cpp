#include "GLM/glm.hpp"
#include <iostream>
glm::vec2 fromAngleDeg(float angle)
{
  angle *= 3.14159265358f / 180.0f;
  glm::vec2 result;
  result.x = cosf(angle);
  result.y = sinf(angle);
  return result;
}
