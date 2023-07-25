#pragma once

#include "./state.hpp"

class MenuState : public State {
 public:
  static MenuState& getInstance();
  void enter(StateMachine* m) override;
  void exit(StateMachine* m) override;

 private:
  MenuState();
  MenuState(const MenuState&) = delete;
  MenuState& operator=(const MenuState&) = delete;

 public:
  void render(SDL_Renderer* renderer) override;
  void handleEvent(SDL_Event* event) override;
  void update() override;
};