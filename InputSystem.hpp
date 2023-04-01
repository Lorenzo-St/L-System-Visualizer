#pragma once
#include <vector>

class InputSystem
{
public:
  void UpdatePressed(unsigned char c);
  void UpdateReleased(unsigned char c);
  InputSystem();
  void RegisterEventHandler(unsigned char key, void (*func)(unsigned char c));
  void Loop(void);
private:
  typedef struct Event
  {
    bool triggered;
    unsigned char key;
    void (*func)(unsigned char c);
  } Event;
  int _registeredEvents;
  std::vector<Event> events;
};
