#pragma once

#include <vector>

#include "screen.h"
#include "text.h"

#include "box.h"
#include "game_state.h"
#include "level.h"

class LevelScreen : public Screen {
  public:

    enum class State { Intro, Input, Execution, Reset, Outro };

    LevelScreen(GameState state);

    bool update(const Input& input, Audio& audio, unsigned int elapsed) override;
    void draw(Graphics& graphics) const override;

    Screen* next_screen() const override;

  private:

    static constexpr int kFadeTime = 1000;
    static constexpr int kBlinkTime = 250;
    static constexpr int kStepTime = 1000;

    Text text_;
    Box box_;

    GameState gs_;
    State state_;
    Level level_;
    Player player_;

    int timer_, choice_;

    double fade_amount() const;
    bool step_complete() const;
    bool robot_in_pit() const;
    bool robot_left() const;

    void set_choice(int choice);
    void transition(State state);
    void reset();
};
