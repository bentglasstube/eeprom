#include "map.h"

#include <cmath>
#include <cassert>

Map::Map() : tileset_("tiles.png", 8, kTileSize, kTileSize), width_(0), height_(0), timer_(0) {}

bool Map::Tile::solid() const {
  return false;
}

bool Map::Tile::conveyor() const {
  switch (type) {
    case Map::TileType::ConveyorN:
    case Map::TileType::ConveyorE:
    case Map::TileType::ConveyorS:
    case Map::TileType::ConveyorW:
      return true;
    default:
      return false;
  }
}

bool Map::Tile::pit() const {
  switch (type) {
    case Map::TileType::HoleNW:
    case Map::TileType::HoleN:
    case Map::TileType::HoleNE:
    case Map::TileType::HoleW:
    case Map::TileType::HoleMid:
    case Map::TileType::HoleE:
    case Map::TileType::HoleSW:
    case Map::TileType::HoleS:
    case Map::TileType::HoleSE:
      return true;
    default:
      return false;
  }
}

double Map::Tile::dx() const {
  switch (type) {
    case Map::TileType::ConveyorW:
      return -1;
    case Map::TileType::ConveyorE:
      return 1;
    default:
      return false;
  }
}

double Map::Tile::dy() const {
  switch (type) {
    case Map::TileType::ConveyorN:
      return -1;
    case Map::TileType::ConveyorS:
      return 1;
    default:
      return false;
  }
}

void Map::draw(Graphics& graphics) const {
  const int frame = timer_ / kFrameLength;

  for (int y = 0; y < height_; ++y) {
    const int gy = kTileSize * y;
    if (gy < -kTileSize) continue;
    if (gy > graphics.height()) break;

    for (int x = 0; x < width_; ++x) {
      const int gx = kTileSize * x;
      if (gx < -kTileSize) continue;
      if (gx > graphics.width()) break;

      const int s = tile(x, y).sprite(frame);
      tileset_.draw(graphics, s > 80 ? 4 + (frame / 2) : 0, gx, gy);
      tileset_.draw(graphics, s, gx, gy);
    }
  }
}

void Map::update(unsigned int elapsed) {
  timer_ = (timer_ + elapsed) % (kAnimationFrames * kFrameLength);
}

Map::Tile Map::tile(int x, int y) const {
  Tile tile;

  if (x < 0 || x >= width_ || y < 0 || y >= height_) {
    tile.type = TileType::Block;
  } else {
    tile.type = tiles_[y][x];
  }

  tile.top = y * kTileSize;
  tile.left = x * kTileSize;
  tile.right = tile.left + kTileSize;
  tile.bottom = tile.top + kTileSize;

  return tile;
}

void Map::set_size(int width, int height) {
  assert(width <= kMaxWidth);
  assert(height <= kMaxHeight);

  width_ = width;
  height_ = height;
}

void Map::set_tile(int x, int y, TileType type) {
  if (y < 0 || y > kMaxHeight) return;
  if (x < 0 || x > kMaxWidth) return;

  tiles_[y][x] = type;
}

int Map::Tile::sprite(int frame) const {
  switch (type) {
    case Map::TileType::Open:           return 0;
    case Map::TileType::Block:          return 1;
    case Map::TileType::Box:            return 2;

    case Map::TileType::PusherE:        return 8;
    case Map::TileType::PusherW:        return 9;
    case Map::TileType::PusherS:        return 10;
    case Map::TileType::PusherN:        return 11;

    case Map::TileType::DoorN:          return 12;
    case Map::TileType::DoorS:          return 13;
    case Map::TileType::DoorW:          return 14;
    case Map::TileType::DoorE:          return 15;

    case Map::TileType::ConveyorE:      return 16 + frame;
    case Map::TileType::ConveyorW:      return 24 + frame;
    case Map::TileType::ConveyorS:      return 32 + frame;
    case Map::TileType::ConveyorN:      return 40 + frame;

    case Map::TileType::WallSE:         return 80;
    case Map::TileType::WallS:          return 81;
    case Map::TileType::WallSW:         return 82;
    case Map::TileType::WallE:          return 88;
    case Map::TileType::WallTop:        return 89;
    case Map::TileType::WallW:          return 90;
    case Map::TileType::WallNE:         return 96;
    case Map::TileType::WallN:          return 97;
    case Map::TileType::WallNW:         return 98;
    case Map::TileType::WallInnerNW:    return 83;
    case Map::TileType::WallInnerNE:    return 84;
    case Map::TileType::WallInnerSW:    return 91;
    case Map::TileType::WallInnerSE:    return 92;

    case Map::TileType::HoleSE:         return 85;
    case Map::TileType::HoleS:          return 86;
    case Map::TileType::HoleSW:         return 87;
    case Map::TileType::HoleE:          return 93;
    case Map::TileType::HoleMid:        return 94;
    case Map::TileType::HoleW:          return 95;
    case Map::TileType::HoleNE:         return 101;
    case Map::TileType::HoleN:          return 102;
    case Map::TileType::HoleNW:         return 103;

    default: return 0;
  }
}

int Map::width() const {
  return width_;
}

int Map::height() const {
  return height_;
}
