#pragma once

#include "render/button.hpp"
#include "render/render_framework_2d.hpp"
#include "state.hpp"

class EndState : public State {
 public:
  static EndState& getInstance(StateMachine& m);
  void enter(StateMachine* m) override;
  void exit(StateMachine* m) override;

 private:
  EndState(StateMachine& machine);
  EndState(const EndState&) = delete;
  EndState& operator=(const EndState&) = delete;
  RenderFramework2d fw;
  Button playAgainButton;
  Button menuButton;
  StateMachine& machine;
  int endScore;

 public:
  void render(Context* context) override;
  void handleEvent(SDL_Event* event) override;
  void update() override;
};