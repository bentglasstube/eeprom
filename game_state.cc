#include "game_state.h"

#include <cassert>

GameState::GameState() : level_(1) {}

void GameState::next_level() {
  ++level_;
}

int GameState::level() const {
  return level_;
}

bool GameState::can_use(Player::Instruction op) const {
  switch (op) {
    case Player::Instruction::NOP: return true;
    case Player::Instruction::MOV: return level_ > 1;
    case Player::Instruction::SHL: return level_ > 2;
    case Player::Instruction::SHR: return level_ > 3;
    default: return false;
  }
}

size_t GameState::rom_size() const {
  return level_ > 6 ? 34 : 17;
}
