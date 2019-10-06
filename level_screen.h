#pragma once

#include <vector>

#include "screen.h"
#include "text.h"

#include "box.h"
#include "game_state.h"
#include "level.h"

class LevelScreen : public Screen {
  public:

    enum class State { Intro, Input, Execution, Death, Outro };

    LevelScreen(GameState state);

    bool update(const Input& input, Audio& audio, unsigned int elapsed) override;
    void draw(Graphics& graphics) const override;

    Screen* next_screen() const override;

  private:

    static constexpr int kFadeTime = 1000;

    Text text_;
    Box box_;

    GameState gs_;
    State state_;
    Level level_;
};
