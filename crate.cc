#include "crate.h"

#include <cmath>

Crate::Crate(int x, int y) :
  tileset_("tiles.png", 8, kTileSize, kTileSize),
  x_(x), y_(y), tx_(x), ty_(y)
{}

void Crate::update(unsigned int elapsed) {
  const double delta = kPushSpeed * elapsed;

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

void Crate::draw(Graphics& graphics) const {
  tileset_.draw(graphics, 2, x_, y_);
}

void Crate::push(int tx, int ty) {
  tx_ = tx * kTileSize;
  ty_ = ty * kTileSize;
}

int Crate::map_x() const {
  return x_ / kTileSize;
}

int Crate::map_y() const {
  return y_ / kTileSize;
}
