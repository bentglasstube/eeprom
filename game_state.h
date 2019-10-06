#pragma once

#include "player.h"

class GameState {
  public:

    GameState();

    static constexpr int kMaxLevel = 12;

    void next_level();

    int level() const;

    bool can_use(Player::Instruction op) const;
    size_t rom_size() const;

  private:

    int level_ = 1;

};
