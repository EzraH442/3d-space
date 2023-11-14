#pragma once

#include "render/context.hpp"
#include "state.hpp"

class StateMachine {
 public:
  StateMachine();
  ~StateMachine();
  void changeState(State& state);

  void render(Context* context);
  void handleEvents();
  void update();

  int score;

  Context ctx;

 private:
  State* current;
  State* next;
};