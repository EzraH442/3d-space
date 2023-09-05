#pragma once

#include <SDL.h>

class StateMachine;

class State {
 public:
  State() = default;
  virtual ~State() = default;

  void handleEvents();

  virtual void enter(StateMachine* m) = 0;
  virtual void exit(StateMachine* m) = 0;
  virtual void render(SDL_Renderer* renderer) = 0;
  virtual void update() = 0;

 protected:
  virtual void handleEvent(SDL_Event* event) = 0;
};