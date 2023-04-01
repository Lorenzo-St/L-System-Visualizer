#include <string>
#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
#include "OGL/inc/freeglut.h"
#include "mathEx.hpp"
#include "line.h"
#include "pattern.hpp"
#include "rule.h"
#include "Camera.hpp"
#include "inputSystem.hpp"

void drawLoop(void);

pattern::pattern()
{
}

void pattern::replace(void)
{

  std::string newIterString = std::string();
  for (auto character : iterString)
  {
    if (character == '+' || character == '-' || character == '[' || character == ']')
    {
      newIterString += character;
      continue;
    }
    for (auto assig : assigns)
    {
      if (assig.letter == '\0')
      {
        break;
      }
      if (character == assig.letter)
      {
        newIterString += assig.string;
        break;
      }
    }
  }
  iterString = newIterString;
}

void pattern::iterate(int count)
{

  while (iteration < count)
  {
    // std::cout << "========================\n";
    // std::cout << iterString << "\n";
    replace();
    // std::cout << std::endl;
    iteration++;
  }
}
void pattern::write(std::string fileName, int iterations)
{
  std::ofstream file(fileName);
  if (!file.is_open())
  {
    std::cerr << "Couldn't open file " << fileName << std::endl;
    exit(1);
  }
  file << (globalPass::fullScreen ? "y" : "n") << "\n";
  file << axiom << "\n";
  file << (nullCharacter ? "y" : "n") << "\n";
  if (nullCharacter)
    file << nullChar << "\n";
  file << angle << "\n";
  int rulecount = 0;
  for (int i = 0; i < count; i++)
    if (assigns[i].letter != '\0')
      rulecount++;
  file << rulecount << "\n";
  for (int i = 0; i < rulecount; i++)
  {
    file << assigns[i].letter << "\n";
    file << assigns[i].string << "\n";
  }
  file << iterations << "\n";
  file << globalPass::startPosition.x << "\n";
  file << globalPass::startPosition.y << "\n";
  file << globalPass::startingAngle << "\n";
  file << globalPass::length << "\n";
  file << (globalPass::repeat ? "y" : "n") << std::endl;

  file.close();
}
void pattern::writeVerbosed(std::string fileName, int iterations)
{
  std::ofstream file(fileName);
  if (!file.is_open())
  {
    std::cerr << "Couldn't open file " << fileName << std::endl;
    exit(1);
  }

  file << "axiom:" << axiom << "\n";
  file << "nullCharacter: " << (nullCharacter ? "true" : "false") << "\n";
  file << "nullChar: " << nullChar << "\n";
  file << "angle: " << angle << "\n";
  int rulecount = 0;
  for (int i = 0; i < count; i++)
    if (assigns[i].letter != '\0')
      rulecount++;
  file << "ruleCount: " << rulecount << "\n";
  for (int i = 0; i < rulecount; i++)
  {
    file << "character: " << assigns[i].letter << "\n";
    file << "string: " << assigns[i].string << "\n";
  }
  file << "iterations: " << iterations << "\n";
  file << "X: " << globalPass::startPosition.x << "\n";
  file << "Y: " << globalPass::startPosition.y << "\n";
  file << "Angle: " << globalPass::startingAngle << "\n";
  file << "Length: " << globalPass::length << "\n";
  file << "Repeat: " << (globalPass::repeat ? "true" : "false") << "\n";
  file << "n" << std::endl;
  file.close();
}

pattern::pattern(std::string axiom, float angle, int assignCount, rule *newAssings, bool nulled, char nulls) : axiom(axiom), angle(angle), nullCharacter(nulled), nullChar(nulls)
{
  for (int i = 0; i < assignCount; i++)
  {
    assigns[i] = newAssings[i];
  }
  for (int i = assignCount; i < count; i++)
  {
    assigns[i].letter = 0;
  }
  iteration = 0;
  iterString = std::string(axiom);
}

pattern::pattern(char axiom, float angle, int assignCount, rule *newAssings, bool nulled, char nulls) : angle(angle), nullCharacter(nulled), nullChar(nulls)
{
  this->axiom = std::string(&axiom);
  for (int i = 0; i < assignCount; i++)
  {
    assigns[i] = newAssings[i];
  }
  iteration = 0;
  iterString = std::string(1, axiom);
}
namespace globals
{
  glm::vec2 currentPos;
  glm::vec2 lastPos;
  float length;
  float angle;
  glm::vec2 moveVector;
  int curPos = 0;
}

void idle2D(void)
{
  if (globals::curPos == 0)
  {
    globals::angle = globalPass::startingAngle;
    globals::currentPos = globalPass::startPosition;
    globals::lastPos = globals::currentPos;
    globals::length = globalPass::length;
    globals::moveVector = fromAngleDeg(globals::angle) * globals::length;
  }

  // std::cout << character << "\n";
  pattern &local = *globalPass::toPass;
  if (globals::curPos >= local.iterString.length() && globalPass::repeat == true)
  {
    globals::curPos = 0;
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    ClearLines();
    return;
  }
  else if (globals::curPos >= local.iterString.length())
  {
    return;
  }

  char character = local.iterString.c_str()[globals::curPos];
  if (character == '+')
  {
    globals::angle -= local.angle;
  }
  else if (character == '-')
  {
    globals::angle += local.angle;
  }
  else if (character == '[')
  {
    local.PositionStack.push(globals::currentPos);
    local.AngleStack.push(globals::angle);
    globals::curPos++;
    return;
  }
  else if (character == ']')
  {
    globals::currentPos = local.PositionStack.top();
    globals::angle = local.AngleStack.top();
    local.PositionStack.pop();
    local.AngleStack.pop();
    globals::lastPos = globals::currentPos;
    globals::curPos++;
    return;
  }
  else if (character == local.nullChar)
  {
    globals::curPos++;
    return;
  }
  else
  {
    globals::currentPos += globals::moveVector;
  }
  // std::cout << "Current Position: (" << currentPos.x << "," << currentPos.y << ")\n";
  // std::cout << "Last Position: (" << lastPos.x << "," << lastPos.y << ")\n";
  // std::cout << "Current MoveVector: (" << moveVector.x << "," << moveVector.y << ")\n";
  // std::cout << "Angle: " << angle << "\n";
  globals::moveVector = fromAngleDeg(globals::angle);
  globals::moveVector *= globals::length;
  AddLine(globals::lastPos, globals::currentPos);
  globals::lastPos = globals::currentPos;
  // std::this_thread::sleep_for(std::chrono::milliseconds(10));

  globals::curPos++;
  globalPass::system.Loop();
  glutPostRedisplay();
}

void pattern::display(void)
{
  globalPass::toPass = this;

  glutIdleFunc(idle2D);
  if (globalPass::fullScreen)
    glutFullScreen();
  glutMainLoop();
}