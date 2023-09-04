#pragma once

#include "./state.hpp"
#include "render/render_framework_2d.hpp"

class MenuState : public State {
 public:
  static MenuState& getInstance();
  void enter(StateMachine* m) override;
  void exit(StateMachine* m) override;

 private:
  MenuState();
  MenuState(const MenuState&) = delete;
  MenuState& operator=(const MenuState&) = delete;
  RenderFramework2d fw;

 public:
  void render(SDL_Renderer* renderer) override;
  void handleEvent(SDL_Event* event) override;
  void update() override;
};