#include "object.h"

Object::Object(int x, int y) :
  x_(x), y_(y), v_(0), tx_(x), ty_(y)
{}

void Object::update(unsigned int elapsed) {
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
}

void Object::push(double v, int tx, int ty) {
  tx_ = tx * kTileSize;
  ty_ = ty * kTileSize;
  v_ = v;
}

int Object::map_x() const {
  return x_ / kTileSize;
}

int Object::map_y() const {
  return y_ / kTileSize;
}
