#pragma once

#include <unordered_map>

#include "game.hpp"
#include "render/drawable_3d.hpp"
#include "render/render_framework_3d.hpp"

class PlayState : public State {
 public:
  static PlayState& getInstance(StateMachine& m);
  void enter(StateMachine* m) override;
  void exit(StateMachine* m) override;

 private:
  StateMachine& machine;
  PlayState(StateMachine& m);
  PlayState(const PlayState&) = delete;
  PlayState& operator=(const PlayState&) = delete;

 public:
  void render(SDL_Renderer* renderer) override;
  void handleEvent(SDL_Event* event) override;
  void update() override;

 private:
  std::unordered_map<int, bool> keys;
  std::unordered_map<int, bool> mouse;
  Board b;
  Game g;
  RenderFramework3d fw;
};