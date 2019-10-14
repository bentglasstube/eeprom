#include "crate.h"

#include <cmath>

Crate::Crate(int x, int y) :
  Object(x, y),
  tileset_("tiles.png", 8, kTileSize, kTileSize)
{}

Crate::~Crate() {}

void Crate::draw(Graphics& graphics) const {
  tileset_.draw(graphics, 2, x_, y_);
}
