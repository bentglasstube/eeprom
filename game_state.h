#pragma once

class GameState {
  public:

    GameState();

    static constexpr int kMaxLevel = 12;

    void next_level();

    int level() const;

  private:

    int level_ = 1;

};
