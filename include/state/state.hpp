#pragma once

#include "SDL_events.h"
#include "SDL_render.h"

class StateMachine;

class State {
 public:
  virtual ~State() = default;
  virtual void enter(StateMachine* m) = 0;
  virtual void exit(StateMachine* m) = 0;

  virtual void render(SDL_Renderer* renderer) = 0;
  virtual void handleEvent(SDL_Event* event) = 0;
  virtual void update() = 0;
};