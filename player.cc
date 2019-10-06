#include "player.h"

#include <cmath>
#include <iostream>

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
  x_(0), y_(0), v_(0), tx_(0), ty_(0), timer_(0),
  facing_(Facing::S), animate_(false),
  program_(), counter_(0) {}

void Player::set_position(int x, int y, Player::Facing facing) {
  tx_ = x_ = x * kTileSize;
  ty_ = y_ = y * kTileSize;
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

size_t Player::counter() const {
  return counter_;
}

void Player::update(unsigned int elapsed) {
  const double delta = v_ * elapsed;

  if (x_ < tx_) {
    x_ = std::min(x_ + delta, tx_);
  } else if (x_ > tx_) {
    x_ = std::max(x_ - delta, tx_);
  }

  if (y_ < ty_) {
    y_ = std::min(y_ + delta, ty_);
  } else if (y_ > ty_) {
    y_ = std::max(y_ - delta, ty_);
  }

  if (animate_) {
    timer_ = (timer_ + elapsed) % (4 * kAnimationSpeed);
    if (!moving()) animate_ = false;
  }
}

void Player::draw(Graphics& graphics) const {
  sprites_.draw(graphics, frame(), x_, y_);
}

bool Player::moving() const {
  return tx_ != x_ || ty_ != y_;
}

void Player::convey(int dx, int dy) {
  if (moving()) {
    std::cerr << "Player already moving, not conveying" << std::endl;
    return;
  } else {
    std::cerr << "Robot still, conveying" << std::endl;
    set_target(x_ + dx * kTileSize, y_ + dy * kTileSize, kWalkSpeed);
  }
}

void Player::push(int tx, int ty) {
  set_target(tx * kTileSize, ty * kTileSize, kShoveSpeed);
}

int Player::map_x() const {
  return x_ / kTileSize;
}

int Player::map_y() const {
  return y_ / kTileSize;
}

int Player::frame() const {
  const int base = static_cast<int>(facing_) * 3;
  const int anim = (timer_ > 3 * kAnimationSpeed) ? 1 : (kAnimationSpeed / 3);
  return base + (animate_ ? anim : 0);
}

void Player::set_target(int tx, int ty, double speed) {
  std::cerr << "Player moving to " << tx << ", " << ty << " at speed " << speed << std::endl;

  tx_ = tx;
  ty_ = ty;
  v_ = speed;
}
