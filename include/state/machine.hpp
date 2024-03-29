#pragma once

#include "state.hpp"

class StateMachine {
 public:
  StateMachine();
  ~StateMachine();
  void changeState(State& state);

  void render(SDL_Renderer* renderer);
  void handleEvents();
  void update();

  int score;

 private:
  State* current;
  State* next;
};