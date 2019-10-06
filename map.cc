#include "map.h"

#include <cmath>

Map::Map() : tileset_("tiles.png", 8, kTileSize, kTileSize), width_(0), height_(0) {}

void Map::draw(Graphics& graphics, int xo, int yo) const {
  for (int y = 0; y < height_; ++y) {
    const int gy = kTileSize * y - yo;
    if (gy < -kTileSize) continue;
    if (gy > graphics.height()) break;

    for (int x = 0; x < width_; ++x) {
      const int gx = kTileSize * x - xo;
      if (gx < -kTileSize) continue;
      if (gx > graphics.width()) break;

      tileset_.draw(graphics, itile(x, y).sprite(), gx, gy);
    }
  }
}

void Map::update(unsigned int elapsed) {
  timer_ += elapsed;
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

int Map::pixel_width() const {
  return width_ * kTileSize;
}

int Map::pixel_height() const {
  return height_ * kTileSize;
}

int Map::Tile::sprite() const {
  switch (type) {
    case Map::TileType::Open:           return 0;
    case Map::TileType::Block:          return 1;
    case Map::TileType::Box:            return 2;

    case Map::TileType::PusherEast:     return 8;
    case Map::TileType::PusherWest:     return 9;
    case Map::TileType::PusherSouth:    return 10;
    case Map::TileType::PusherNorth:    return 11;

    case Map::TileType::DoorNorth:      return 12;
    case Map::TileType::DoorSouth:      return 13;
    case Map::TileType::DoorWest:       return 14;
    case Map::TileType::DoorEast:       return 15;

    case Map::TileType::ConveyEast:     return 16 + anim;
    case Map::TileType::ConveyWest:     return 24 + anim;
    case Map::TileType::ConveySouth:    return 32 + anim;
    case Map::TileType::ConveyNorth:    return 40 + anim;

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
    case Map::TileType::HoleMiddle:     return 94;
    case Map::TileType::HoleW:          return 95;
    case Map::TileType::HoleNE:         return 101;
    case Map::TileType::HoleN:          return 102;
    case Map::TileType::HoleNW:         return 103;

    default: return 0;
  }
}
