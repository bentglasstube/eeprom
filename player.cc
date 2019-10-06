#include "player.h"

#include "map.h"

#include <cmath>

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

void Player::convey(int dx, int dy, const Map& map) {
  if (moving()) return;
  set_target(x_ + dx * kTileSize, y_ + dy * kTileSize, kWalkSpeed, map);
}

void Player::push(int tx, int ty, const Map& map) {
  set_target(tx * kTileSize, ty * kTileSize, kShoveSpeed, map);
}

void Player::execute(const Map& map) {
  Instruction op = program_.at(counter_);

  switch (op) {
    case Instruction::NOP:
      // do nothing
      break;

    case Instruction::MOV:
      walk(map);
      break;

    case Instruction::SHL:
      rotate(false);
      break;

    case Instruction::SHR:
      rotate(true);
      break;
  }

  counter_ = (counter_ + 1) % program_.size();
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

void Player::set_target(int tx, int ty, double speed, const Map& map) {
  const int mx = tx / 16;
  const int my = ty / 16;

  if (map.tile(mx, my).solid()) {
    // TODO crush robot
    return;
  }

  tx_ = tx;
  ty_ = ty;
  v_ = speed;
}

void Player::walk(const Map& map) {
  switch (facing_) {
    case Facing::N:
      set_target(tx_, ty_ - kTileSize, kWalkSpeed, map);
      break;
    case Facing::E:
      set_target(tx_ + kTileSize, ty_, kWalkSpeed, map);
      break;
    case Facing::S:
      set_target(tx_, ty_ + kTileSize, kWalkSpeed, map);
      break;
    case Facing::W:
      set_target(tx_ - kTileSize, tx_, kWalkSpeed, map);
      break;
  }
  animate_ = true;
}

void Player::rotate(bool clockwise) {
  switch (facing_) {
    case Facing::N:
      facing_ = clockwise ? Facing::E : Facing::W;
      break;
    case Facing::E:
      facing_ = clockwise ? Facing::S : Facing::N;
      break;
    case Facing::S:
      facing_ = clockwise ? Facing::W : Facing::E;
      break;
    case Facing::W:
      facing_ = clockwise ? Facing::N : Facing::S;
      break;
  }
}
