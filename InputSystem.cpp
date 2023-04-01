#include "OGL/inc/freeglut.h"
#include "InputSystem.hpp"
#include <iostream>
#include <cctype>
void InputSystem::UpdatePressed(unsigned char c)
{
  c = tolower(c);
  // std::cout << "===== Pressed =====" << std::endl;
  for (auto event : events)
  {
    if (event.key == c)
      event.triggered = true;
    // std::cout << c << ","<<  event.triggered << std::endl;

  }
}

void InputSystem::UpdateReleased(unsigned char c)
{
  c = tolower(c);
  // std::cout << "===== Released =====" << std::endl;

  for (auto event : events)
  {
    // std::cout << c << ","<<  event.triggered << std::endl;
    if (event.key == c)
      event.triggered = false;
  }
}


void InputSystem::RegisterEventHandler(unsigned char key, void (*func)(unsigned char c))
{
  Event e = {false, key, func};
  events.push_back(e);
}

InputSystem::InputSystem()
{
  events.reserve(10);
}

void InputSystem::Loop(void)
{
  // std::cout << "Looping..." << std::endl;
  for (auto event : events ) 
  {
    if (event.triggered == true) 
    {
      // std::cout << "calling " << std::endl;
      event.func(event.key);
    }
  }
}
