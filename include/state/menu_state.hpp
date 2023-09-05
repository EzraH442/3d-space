#pragma once

#include "render/button.hpp"
#include "render/render_framework_2d.hpp"
#include "state.hpp"

class MenuState : public State {
 public:
  static MenuState& getInstance(StateMachine& m);
  void enter(StateMachine* m) override;
  void exit(StateMachine* m) override;

 private:
  MenuState(StateMachine& machine);
  MenuState(const MenuState&) = delete;
  MenuState& operator=(const MenuState&) = delete;
  RenderFramework2d fw;
  Button playButton;
  StateMachine& machine;

 public:
  void render(SDL_Renderer* renderer) override;
  void handleEvent(SDL_Event* event) override;
  void update() override;
};