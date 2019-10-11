#include "player.h"

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
  facing_(Map::Facing::S), animate_(false), falling_(false),
  program_(), counter_(0) {}

void Player::set_position(Level::Start position) {
  tx_ = x_ = position.x * kTileSize;
  ty_ = y_ = position.y * kTileSize;
  rot_ = 0;
  facing_ = position.facing;
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
}

void Player::stop() {
  animate_ = false;
  v_ = 0;
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

void Player::convey(const Level& level) {
  if (moving()) return;

  const auto tile = level.tile(map_x(), map_y());
  if (tile.conveyor()) {
    set_target(x_ + tile.dx() * kTileSize, y_ + tile.dy() * kTileSize, kConveyorSpeed, level);
  }
}

void Player::push(int tx, int ty, const Level& level) {
  set_target(tx * kTileSize, ty * kTileSize, kShoveSpeed, level);
}

void Player::execute(Level& level) {
  Instruction op = program_.at(counter_);

  switch (op) {
    case Instruction::NOP:
      // do nothing
      break;

    case Instruction::MOV:
      walk(level);
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

void Player::set_target(int tx, int ty, double speed, const Level& level) {
  if (level.open(tx, ty)) {
    tx_ = tx;
    ty_ = ty;
    v_ = speed;
  } else {
    // TODO crush robot if going fast;
    tx_ = x_;
    ty_ = y_;
    v_ = 0;
  }
}

void Player::set_target_push(int tx, int ty, double speed, Level& level) {
  if (level.open(tx, ty)) {
    tx_ = tx;
    ty_ = ty;
    v_ = speed;
  } else if (level.push(tx, ty, tx + xdiff() * kTileSize, ty + ydiff() * kTileSize)) {
    tx_ = tx;
    ty_ = ty;
    v_ = speed;
  } else {
    // TODO crush robot if going fast;
    tx_ = x_;
    ty_ = y_;
    v_ = 0;
  }
}

int Player::xdiff() const {
  switch (facing_) {
    case Map::Facing::E:
      return 1;
    case Map::Facing::W:
      return -1;
    default:
      return 0;
  }
}

int Player::ydiff() const {
  switch (facing_) {
    case Map::Facing::N:
      return -1;
    case Map::Facing::S:
      return 1;
    default:
      return 0;
  }
}

void Player::walk(Level& level) {
  int tx = x_ + xdiff() * kTileSize;
  int ty = y_ + ydiff() * kTileSize;

  // check if already moving from a conveyor
  if (tx_ != x_ && xdiff() != 0) tx += tx_ - x_;
  else if (ty_ != y_ && ydiff() != 0) ty += ty_ - y_;

  set_target_push(tx, ty, kWalkSpeed, level);
  animate_ = true;
  timer_ = 0;
}

void Player::rotate(bool clockwise) {
  rot_ = 1.5 * (clockwise ? -1 : 1);

  switch (facing_) {
    case Map::Facing::N:
      facing_ = clockwise ? Map::Facing::E : Map::Facing::W;
      break;
    case Map::Facing::E:
      facing_ = clockwise ? Map::Facing::S : Map::Facing::N;
      break;
    case Map::Facing::S:
      facing_ = clockwise ? Map::Facing::W : Map::Facing::E;
      break;
    case Map::Facing::W:
      facing_ = clockwise ? Map::Facing::N : Map::Facing::S;
      break;
  }
}

void Player::fall() {
  rot_ = 12;
  timer_ = 0;
  animate_ = falling_ = true;
}
