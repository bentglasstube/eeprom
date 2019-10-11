#include "piston.h"

Piston::Piston(int x, int y, Map::Facing facing, int freq, int first) :
  tileset_("tiles.png", 8, kTileSize, kTileSize),
  x_(x * kTileSize), y_(y * kTileSize), freq_(freq), counter_(first),
  timer_(0), frame_(0),
  facing_(facing), state_(State::Dormant)
{}

void Piston::update(unsigned int elapsed) {
  switch (state_) {
    case State::Dormant:
      break;

    case State::Extending:
      timer_ += elapsed;
      if (timer_ > kExtensionRate) {
        timer_ -= kExtensionRate;
        if (++frame_ == kFrames) {
          --frame_;
          state_ = State::Retracting;
        }
      }
      break;

    case State::Retracting:
      timer_ += elapsed;
      if (timer_ > kRetractionRate) {
        timer_ -= kRetractionRate;
        if (--frame_ == 0) {
          state_ = State::Dormant;
        }
      }
      break;
  }
}

void Piston::draw(Graphics& graphics) const {
  switch (facing_) {
    case Map::Facing::E:
      tileset_.draw(graphics, 8, x_, y_);
      tileset_.draw(graphics, 48 + frame_, x_ + 12, y_);
      break;

    case Map::Facing::W:
      tileset_.draw(graphics, 9, x_, y_);
      tileset_.draw(graphics, 56 + frame_, x_ - 12, y_);
      break;

    case Map::Facing::S:
      tileset_.draw(graphics, 10, x_, y_);
      tileset_.draw(graphics, 64 + frame_, x_, y_ + 12);
      break;

    case Map::Facing::N:
      tileset_.draw(graphics, 11, x_, y_);
      tileset_.draw(graphics, 72 + frame_, x_, y_ - 12);
      break;
  }
}

bool Piston::step() {
  if (--counter_ == 0) {
    state_ = State::Extending;
    counter_ = freq_;
    return true;
  } else {
    return false;
  }
}

std::pair<int, int> Piston::push_from() const {
  return std::make_pair(x_ / kTileSize + xdiff(), y_ / kTileSize + ydiff());
}

std::pair<int, int> Piston::push_to() const {
  return std::make_pair(x_ / kTileSize + 2 * xdiff(), y_ / kTileSize + 2 * ydiff());
}

int Piston::xdiff() const {
  switch (facing_) {
    case Map::Facing::W:
      return -1;
    case Map::Facing::E:
      return +1;
    default:
      return 0;
  }
}

int Piston::ydiff() const {
  switch (facing_) {
    case Map::Facing::N:
      return -1;
    case Map::Facing::S:
      return +1;
    default:
      return 0;
  }
}
