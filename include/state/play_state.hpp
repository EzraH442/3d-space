#pragma once

#include "./state.hpp"

class PlayState : public State {
 public:
  static PlayState& getInstance();
  void enter(StateMachine* m) override;
  void exit(StateMachine* m) override;

 private:
  PlayState();
  PlayState(const PlayState&) = delete;
  PlayState& operator=(const PlayState&) = delete;

 public:
  void render(SDL_Renderer* renderer) override;
  void handleEvent(SDL_Event* event) override;
  void update() override;
};