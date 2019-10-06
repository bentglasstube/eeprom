#include "level.h"

#include <iostream>

Level::Level() : player(), map_() {
  map_.set_size(12, 14);

  map_.populate({
      Map::TileType::WallInnerNW,
      Map::TileType::WallN,
      Map::TileType::WallN,
      Map::TileType::WallNW,
      Map::TileType::DoorN,
      Map::TileType::WallNE,
      Map::TileType::WallN,
      Map::TileType::WallN,
      Map::TileType::WallN,
      Map::TileType::WallN,
      Map::TileType::WallN,
      Map::TileType::WallInnerNE,

      Map::TileType::WallW,
      Map::TileType::Box,
      Map::TileType::Open,
      Map::TileType::Open,
      Map::TileType::ConveyorS,
      Map::TileType::Open,
      Map::TileType::Open,
      Map::TileType::Open,
      Map::TileType::Box,
      Map::TileType::Box,
      Map::TileType::Box,
      Map::TileType::WallE,

      Map::TileType::WallW,
      Map::TileType::Box,
      Map::TileType::Box,
      Map::TileType::Open,
      Map::TileType::ConveyorS,
      Map::TileType::Open,
      Map::TileType::Open,
      Map::TileType::Open,
      Map::TileType::Open,
      Map::TileType::Open,
      Map::TileType::Open,
      Map::TileType::WallE,

      Map::TileType::WallW,
      Map::TileType::Box,
      Map::TileType::Box,
      Map::TileType::Open,
      Map::TileType::ConveyorS,
      Map::TileType::Open,
      Map::TileType::Open,
      Map::TileType::Open,
      Map::TileType::Open,
      Map::TileType::Open,
      Map::TileType::Open,
      Map::TileType::WallNE,

      Map::TileType::WallW,
      Map::TileType::Open,
      Map::TileType::Open,
      Map::TileType::PusherE,
      Map::TileType::ConveyorS,
      Map::TileType::ConveyorE,
      Map::TileType::ConveyorE,
      Map::TileType::ConveyorE,
      Map::TileType::ConveyorE,
      Map::TileType::ConveyorE,
      Map::TileType::ConveyorE,
      Map::TileType::ConveyorE,

      Map::TileType::WallW,
      Map::TileType::Open,
      Map::TileType::Open,
      Map::TileType::Open,
      Map::TileType::ConveyorS,
      Map::TileType::Open,
      Map::TileType::Open,
      Map::TileType::Open,
      Map::TileType::Open,
      Map::TileType::Open,
      Map::TileType::Open,
      Map::TileType::WallSE,

      Map::TileType::WallW,
      Map::TileType::Open,
      Map::TileType::Open,
      Map::TileType::Open,
      Map::TileType::ConveyorS,
      Map::TileType::Open,
      Map::TileType::Open,
      Map::TileType::Open,
      Map::TileType::Open,
      Map::TileType::Open,
      Map::TileType::Open,
      Map::TileType::WallE,

      Map::TileType::WallW,
      Map::TileType::Open,
      Map::TileType::Open,
      Map::TileType::Open,
      Map::TileType::ConveyorS,
      Map::TileType::Open,
      Map::TileType::Open,
      Map::TileType::Block,
      Map::TileType::Block,
      Map::TileType::Open,
      Map::TileType::Open,
      Map::TileType::WallE,

      Map::TileType::WallW,
      Map::TileType::Open,
      Map::TileType::Open,
      Map::TileType::Open,
      Map::TileType::ConveyorS,
      Map::TileType::Open,
      Map::TileType::Open,
      Map::TileType::Block,
      Map::TileType::Block,
      Map::TileType::Open,
      Map::TileType::Open,
      Map::TileType::WallE,

      Map::TileType::WallW,
      Map::TileType::Open,
      Map::TileType::Open,
      Map::TileType::Open,
      Map::TileType::ConveyorS,
      Map::TileType::Open,
      Map::TileType::Open,
      Map::TileType::Open,
      Map::TileType::Open,
      Map::TileType::Open,
      Map::TileType::Open,
      Map::TileType::WallE,

      Map::TileType::WallW,
      Map::TileType::HoleSE,
      Map::TileType::HoleS,
      Map::TileType::HoleS,
      Map::TileType::HoleS,
      Map::TileType::HoleS,
      Map::TileType::HoleS,
      Map::TileType::HoleSW,
      Map::TileType::WallSE,
      Map::TileType::WallS,
      Map::TileType::WallS,
      Map::TileType::WallInnerSE,

      Map::TileType::WallW,
      Map::TileType::HoleE,
      Map::TileType::HoleMid,
      Map::TileType::HoleMid,
      Map::TileType::HoleMid,
      Map::TileType::HoleMid,
      Map::TileType::HoleMid,
      Map::TileType::HoleW,
      Map::TileType::WallE,
      Map::TileType::WallTop,
      Map::TileType::WallTop,
      Map::TileType::WallTop,

      Map::TileType::WallW,
      Map::TileType::HoleNE,
      Map::TileType::HoleN,
      Map::TileType::HoleN,
      Map::TileType::HoleN,
      Map::TileType::HoleN,
      Map::TileType::HoleN,
      Map::TileType::HoleNW,
      Map::TileType::WallE,
      Map::TileType::WallTop,
      Map::TileType::WallTop,
      Map::TileType::WallTop,

      Map::TileType::WallInnerSW,
      Map::TileType::WallS,
      Map::TileType::WallS,
      Map::TileType::WallS,
      Map::TileType::WallS,
      Map::TileType::WallS,
      Map::TileType::WallS,
      Map::TileType::WallS,
      Map::TileType::WallInnerSE,
      Map::TileType::WallTop,
      Map::TileType::WallTop,
      Map::TileType::WallTop
  });

  player.set_position(4, 1, Player::Facing::S);

  pistons_.emplace_back(3, 4, Piston::Facing::E, 4, 4);
}

void Level::update(unsigned int elapsed) {
  map_.update(elapsed);
  player.update(elapsed);

  for (auto& p : pistons_) {
    p.update(elapsed);
  }

  for (auto& c : crates_) {
    c.update(elapsed);
  }
}

void Level::draw(Graphics& graphics) const {
  map_.draw(graphics);
  player.draw(graphics);

  for (const auto& p : pistons_) {
    p.draw(graphics);
  }

  for (const auto& c : crates_) {
    c.draw(graphics);
  }
}

Map::Tile Level::player_tile() const {
  const int px = player.map_x();
  const int py = player.map_y();

  return  map_.tile(px, py);
}

void Level::conveyors() {
  if (player.moving()) return;

  const auto tile = player_tile();
  if (tile.conveyor()) {
    player.convey(tile.dx(), tile.dy());
  }
}

bool Level::step_pistons() {
  for (auto& p : pistons_) {
    if (p.step()) {
      // TODO see if something was pushed
      const auto from = p.push_from();
      const auto to = p.push_to();

      if (push_player(from.first, from.second, to.first, to.second)) {
      }
    }
  }

  return false;
}

bool Level::push_player(int x, int y, int tx, int ty) {
  std::cerr << "Trying to push player" << std::endl;
  std::cerr << "From " << x << ", " << y << " to " << tx << ", " << ty << std::endl;

  if (player.map_x() == x && player.map_y() == y) {
    std::cerr << "Player is present, shove!" << std::endl;
    player.push(tx, ty);
    // TODO check if map is solid
    return true;
  } else {
    std::cerr << "Player is not present" << std::endl;
    return false;
  }
}

bool Level::push_crate(int x, int y, int tx, int ty) {
  for (auto &c : crates_) {
    if (c.map_x() == x && c.map_y() == y) {
      c.push(tx, ty);
      // TODO check if map is solid
      return true;
    }
  }
  return false;
}

bool Level::player_oob() const {
  if (player.map_x() < 0) return true;
  if (player.map_x() >= map_.width()) return true;
  if (player.map_y() < 0) return true;
  if (player.map_y() >= map_.height()) return true;

  return false;
}
