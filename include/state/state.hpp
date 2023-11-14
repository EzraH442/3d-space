#pragma once

#include <SDL.h>

#include "render/context.hpp"

class StateMachine;

class State {
 public:
  State() = default;
  virtual ~State() = default;

  void handleEvents(StateMachine& m);

  virtual void enter(StateMachine* m) = 0;
  virtual void exit(StateMachine* m) = 0;
  virtual void render(Context* context) = 0;
  virtual void update() = 0;

 protected:
  virtual void handleEvent(SDL_Event* event) = 0;
};