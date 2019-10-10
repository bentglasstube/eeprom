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
  sprites_("robots.png", 4, kTileSize, kTileSize),
  x_(0), y_(0), v_(0), tx_(0), ty_(0), rot_(0), timer_(0),
  facing_(Facing::S), animate_(false), falling_(false),
  program_(), counter_(0) {}

void Player::set_position(int x, int y, Player::Facing facing) {
  tx_ = x_ = x * kTileSize;
  ty_ = y_ = y * kTileSize;
  rot_ = 0;
  facing_ = facing;
  animate_ = falling_ = false;
}

void Player::add_instruction(Player::Instruction op) {
  // TODO check max length
  program_.push_back(op);
}

void Player::remove_instruction(Audio& audio) {
  if (!program_.empty()) {
    program_.pop_back();
    audio.play_sample("blip.wav");
  } else {
    audio.play_sample("nope.wav");
  }
}

void Player::clear_program() {
  program_.clear();
  counter_ = 0;
}

std::vector<Player::Instruction> const& Player::listing() const {
  return program_;
}

size_t Player::counter() const {
  return counter_;
}

void Player::update(unsigned int elapsed) {
  const double delta = v_ * elapsed;

  if (rot_ != 0) {
    const double dr = kTurnSpeed * elapsed * (falling_ ? 2 : 1);
    if (rot_ > 0) {
      rot_ = std::max(rot_ - dr, 0.0);
    } else {
      rot_ = std::min(rot_ + dr, 0.0);
    }
  }

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

  if (falling_) {
    timer_ += elapsed;
  } else if (animate_) {
    timer_ = (timer_ + elapsed) % (4 * kAnimationSpeed);
  }

  if (!moving()) {
    animate_ = false;
    v_ = 0;
  }
}

void Player::draw(Graphics& graphics) const {
  sprites_.draw_ex(graphics, frame(), x_, y_, false, rot_, 8, 8);
}

bool Player::moving() const {
  return tx_ != x_ || ty_ != y_ || rot_ != 0;
}

bool Player::dead() const {
  return falling_ && rot_ == 0;
}

void Player::convey(int dx, int dy, const Map& map) {
  if (moving()) return;
  set_target(x_ + dx * kTileSize, y_ + dy * kTileSize, kConveyorSpeed, map);
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
  const int base = falling_ ? 16 : static_cast<int>(facing_) * 4;
  const int anim = timer_ / kAnimationSpeed / (falling_ ? 2 : 1);
  return base + ((animate_ || falling_) ? anim : 0);
}

void Player::set_target(int tx, int ty, double speed, const Map& map) {
  const int mx = tx / 16;
  const int my = ty / 16;

  const auto tile = map.tile(mx, my);

  if (tile.solid()) {
    // TODO crush robot if going fast;
    tx_ = x_;
    ty_ = y_;
    v_ = 0;

    // TODO check for block
  } else {
    tx_ = tx;
    ty_ = ty;
    v_ = speed;
  }
}

int Player::xdiff() const {
  switch (facing_) {
    case Facing::E:
      return 1;
    case Facing::W:
      return -1;
    default:
      return 0;
  }
}

int Player::ydiff() const {
  switch (facing_) {
    case Facing::N:
      return -1;
    case Facing::S:
      return 1;
    default:
      return 0;
  }
}

void Player::walk(const Map& map) {
  set_target(tx_ + xdiff() * kTileSize, ty_ + ydiff() * kTileSize, kWalkSpeed, map);
  animate_ = true;
  timer_ = 0;
}

void Player::rotate(bool clockwise) {
  rot_ = 1.5 * (clockwise ? -1 : 1);

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

void Player::fall() {
  rot_ = 12;
  timer_ = 0;
  animate_ = falling_ = true;
}
