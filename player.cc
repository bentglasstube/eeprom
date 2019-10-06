#include "player.h"

std::string Player::instruction_text(Player::Instruction op) {
  switch (op) {
    case Instruction::NOP: return "NOP";
    case Instruction::MOV: return "MOV";
    case Instruction::SHL: return "SHL";
    case Instruction::SHR: return "SHR";
    default:               return "???";
  };
}

Player::Player() :
  sprites_("robots.png", 3, kTileSize, kTileSize),
  x_(0), y_(0), facing_(Facing::S),
  program_(), counter_(0) {}

void Player::set_position(int x, int y, Player::Facing facing) {
  x_ = x * kTileSize;
  y_ = y * kTileSize;
  facing_ = facing;
}

void Player::add_instruction(Player::Instruction op) {
  // TODO check max length
  program_.push_back(op);
}

void Player::remove_instruction() {
  program_.pop_back();
}

void Player::clear_program() {
  program_.clear();
}

std::vector<Player::Instruction> const& Player::listing() const {
  return program_;
}

int Player::counter() const {
  return counter_;
}

void Player::draw(Graphics& graphics) const {
  sprites_.draw(graphics, 0, x_, y_);
}
