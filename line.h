#pragma once
#include "GLM/glm.hpp"
#include <vector>
typedef struct Line 
{
  glm::vec2 startPosition;
  glm::vec2 endPosition;
}Line;

namespace globalPass
{
  extern int windowWidth;
  extern int windowHeight;
  extern std::vector<Line> lines;
}

void drawLine(Line line);
void AddLine(glm::vec2 const &start, glm::vec2 const& end);
void ClearLines(void);

bool operator==(const Line& lhs, const Line& rhs);
