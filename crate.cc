#include "crate.h"

#include <cmath>

Crate::Crate(int x, int y) :
  tileset_("tiles.png", 8, 16, 16),
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
