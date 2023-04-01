#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <cctype>
#include <chrono>
#include <thread>
#include "OGL/inc/freeglut.h"
#include "GLM/glm.hpp"
#include "pattern.hpp"
#include "rule.h"
#include "mathEx.hpp"
#include "line.h"
#include "Camera.hpp"
#include "inputSystem.hpp"
namespace globalPass
{
  pattern *toPass = nullptr;
  int windowWidth = 1280;
  int windowHeight = 720;
  bool fullScreen = false;
  bool repeat = false;
  float length = 50;
  glm::vec2 startPosition = {0, 0};
  float startingAngle = 0;
  std::vector<Line> lines;
  Camera2D camera = Camera2D(1);
  InputSystem system;
}

void OnMove(unsigned char c)
{
  c = toupper(c);
  glm::vec2 position = globalPass::camera.GetPosition();
  std::cout << c << std::endl;
  switch(c)
  {
    case 'W':
    position.y += (5.0f/globalPass::windowHeight);
    break;
    case 'A':
    position.x -= (5.0f/globalPass::windowWidth);
    break;
    case 'S':
    position.y -= (5.0f/globalPass::windowHeight);
    break;
    case 'D':
    position.x += (5.0f/globalPass::windowWidth);
    break;
  }
  // std::cout << position.x << "," << position.y << std::endl;
  globalPass::camera.MovePosition(position);
}

void InputPressedCallBack(unsigned char c, int i1, int i2)
{
  globalPass::system.UpdatePressed(c);

}

void InputReleasedCallBack(unsigned char c, int i1, int i2)
{
  globalPass::system.UpdateReleased(c);

}

void drawLoop(void)
{
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  
  for(auto line : globalPass::lines)
  {
    drawLine(line);
  }
  glFlush();

}

std::string lowerIt(std::string& string)
{
  std::string temp;
  for(auto character : string)
  {
    temp += tolower(character);
  }
  return temp;
}

void ScreenInputs(void)
{
  std::string fs;
  
  std::cout << "Full Screen? (y/n)";
  std::cin >> fs;
  
  fs = lowerIt(fs);
  if (fs == "y")
    globalPass::fullScreen = true;
  else
    globalPass::fullScreen = false;
  if (globalPass::fullScreen == false)
  {
    std::cout << "Please enter window X size: ";
    std::cin >> globalPass::windowWidth;

    std::cout << "Please enter window Y size: ";
    std::cin >> globalPass::windowHeight;

  }
  else
  {
    globalPass::windowWidth = glutGet(GLUT_SCREEN_WIDTH);
    globalPass::windowHeight = glutGet(GLUT_SCREEN_HEIGHT);
  }

}

void TakeUserInput(pattern &p, int& iterations)
{

  std::string axiom;
  float angle;
  int count;
  struct rule *rules;
  char nulls = 0; 
  bool nullCharacter = false;
  std::string fs;
  std::cout << "\nPlease enter the axiom: ";
  std::cin >> axiom;
  
  std::cout << "\nIs there a non-drawing character? (y/n) ";
  std::cin >> fs;

  fs = lowerIt(fs);
  if (fs == "y")
    nullCharacter = true;
  else
    nullCharacter = false;

  if (nullCharacter)
  {
    std::cout << "what is the non-drawn character? ";
    std::cin >> nulls;
    std::cout << nulls << std::endl;

  }

  std::cout << "\nwhat angle is used here: ";
  std::cin >> angle;

  std::cout << "\nHow many rules are there: ";
  std::cin >> count;

  rules = new rule[count];
  for (int i = 0; i < count; i++)
  {
    std::cout << "Rule #" << i + 1<< std::endl;
    std::cout << "What letter is associated with this rule: ";
    std::cin >> rules[i].letter;
    std::cout << "What pattter is associated with this rule: ";
    std::cin >> rules[i].string;
  }
  std::cout << "How many iterations? ";
  std::cin >> iterations;

  std::cout << "What is the starting X position? ";
  std::cin >> globalPass::startPosition.x;

  std::cout << "What is the starting Y position? ";
  std::cin >> globalPass::startPosition.y;

  std::cout << "what is the Starting angle? ";
  std::cin >> globalPass::startingAngle;

  std::cout << "what is the length? ";
  std::cin >> globalPass::length;

  std::cout << "Repeat Draw? (y/n)";
  std::cin >> fs;
  fs = lowerIt(fs);
  if (fs == "y")
    globalPass::repeat = true;
  else
    globalPass::repeat = false;

  std::cout << "Should the rules be saved? (y/n)";
  std::cin >> fs;
  p = pattern(axiom, angle, count, rules, nullCharacter, nulls);
  fs = lowerIt(fs);
  if(fs == "y")
  {
    std::cout << "What shall the file be named? ";
    std::string fileName;
    std::cin >> fileName;
    p.write(fileName, iterations);
  }

}

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  
  globalPass::camera = Camera2D(1);
  globalPass::system.RegisterEventHandler('w', OnMove);
  globalPass::system.RegisterEventHandler('a', OnMove);
  globalPass::system.RegisterEventHandler('s', OnMove);
  globalPass::system.RegisterEventHandler('d', OnMove);
  std::cout << glutGet(GLUT_SCREEN_WIDTH) << std::endl;
  std::cout << glutGet(GLUT_SCREEN_HEIGHT) << std::endl;
  globalPass::camera.InitWindow(drawLoop, InputPressedCallBack, InputReleasedCallBack);
  glutIgnoreKeyRepeat(true);

  // Local Variables 
  ScreenInputs();

  pattern p;
  int iterations = 1;
  TakeUserInput(p, iterations);
  
  std::cout << "Performing Iterations! Please Wait..." << std::endl;
  p.iterate(iterations);
  
  std::cout << "Iterations Done! Now Drawing..." << std::endl;
  p.display();
  
  return 0;
}
