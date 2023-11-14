#pragma once

#include "state.hpp"

class ExitState : public State {
 public:
  static ExitState& getInstance(StateMachine& m);
  void enter(StateMachine* m) override;
  void exit(StateMachine* m) override;

 private:
  ExitState(StateMachine& machine);
  ExitState(const ExitState&) = delete;
  ExitState& operator=(const ExitState&) = delete;
  StateMachine& machine;

 public:
  void render(Context* context) override;
  void handleEvent(SDL_Event* event) override;
  void update() override;
};