#pragma once
#include "rule.h"
#include <stack>
#include "GLM/glm.hpp"
class Camera2D;
class InputSystem;
class pattern
{
public:
  pattern();
  pattern(char axiom, float angle, int assignCount, struct rule *newAssings, bool nulled, char nulls);
  pattern(std::string axiom, float angle, int assignCount, struct rule *newAssings, bool nulled, char nulls);
  void iterate(int count);
  void display(void);
  void writeVerbosed(std::string fileName, int iterations);
  void write(std::string fileName, int iterations);
private:
  static const int count = 10;  
  int iteration;
  bool nullCharacter;
  char nullChar;
  float angle;
  std::stack<glm::vec2> PositionStack;
  std::stack<float> AngleStack;

  struct rule assigns[count];
  std::string iterString;
  std::string axiom;

private:
  void replace(void);
  friend void idle2D(void);

};

namespace globalPass
{
  extern pattern *toPass; 
  extern int windowWidth;
  extern int windowHeight;
  extern bool fullScreen;
  extern bool repeat;
  extern float length;
  extern glm::vec2 startPosition;
  extern float startingAngle;
  extern Camera2D camera;
  extern InputSystem system;
}

