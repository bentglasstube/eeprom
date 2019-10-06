#include "level.h"

Level::Level() : map_(), player() {
  map_.set_size(12, 14);

  map_.set_tile( 0,  0, Map::TileType::WallInnerNW);
  map_.set_tile( 1,  0, Map::TileType::WallN);
  map_.set_tile( 2,  0, Map::TileType::WallN);
  map_.set_tile( 3,  0, Map::TileType::WallNW);
  map_.set_tile( 4,  0, Map::TileType::DoorN);
  map_.set_tile( 5,  0, Map::TileType::WallNE);
  map_.set_tile( 6,  0, Map::TileType::WallN);
  map_.set_tile( 7,  0, Map::TileType::WallN);
  map_.set_tile( 8,  0, Map::TileType::WallN);
  map_.set_tile( 9,  0, Map::TileType::WallN);
  map_.set_tile(10,  0, Map::TileType::WallN);
  map_.set_tile(11,  0, Map::TileType::WallInnerNE);

  map_.set_tile( 0,  1, Map::TileType::WallW);
  map_.set_tile( 1,  1, Map::TileType::Box);
  map_.set_tile( 2,  1, Map::TileType::Open);
  map_.set_tile( 3,  1, Map::TileType::Open);
  map_.set_tile( 4,  1, Map::TileType::ConveyorS);
  map_.set_tile( 5,  1, Map::TileType::Open);
  map_.set_tile( 6,  1, Map::TileType::Open);
  map_.set_tile( 7,  1, Map::TileType::Open);
  map_.set_tile( 8,  1, Map::TileType::Box);
  map_.set_tile( 9,  1, Map::TileType::Box);
  map_.set_tile(10,  1, Map::TileType::Box);
  map_.set_tile(11,  1, Map::TileType::WallE);

  map_.set_tile( 0,  2, Map::TileType::WallW);
  map_.set_tile( 1,  2, Map::TileType::Box);
  map_.set_tile( 2,  2, Map::TileType::Box);
  map_.set_tile( 3,  2, Map::TileType::Open);
  map_.set_tile( 4,  2, Map::TileType::ConveyorS);
  map_.set_tile( 5,  2, Map::TileType::Open);
  map_.set_tile( 6,  2, Map::TileType::Open);
  map_.set_tile( 7,  2, Map::TileType::Open);
  map_.set_tile( 8,  2, Map::TileType::Open);
  map_.set_tile( 9,  2, Map::TileType::Open);
  map_.set_tile(10,  2, Map::TileType::Open);
  map_.set_tile(11,  2, Map::TileType::WallE);

  map_.set_tile( 0,  3, Map::TileType::WallW);
  map_.set_tile( 1,  3, Map::TileType::Box);
  map_.set_tile( 2,  3, Map::TileType::Box);
  map_.set_tile( 3,  3, Map::TileType::Open);
  map_.set_tile( 4,  3, Map::TileType::ConveyorS);
  map_.set_tile( 5,  3, Map::TileType::Open);
  map_.set_tile( 6,  3, Map::TileType::Open);
  map_.set_tile( 7,  3, Map::TileType::Open);
  map_.set_tile( 8,  3, Map::TileType::Open);
  map_.set_tile( 9,  3, Map::TileType::Open);
  map_.set_tile(10,  3, Map::TileType::Open);
  map_.set_tile(11,  3, Map::TileType::WallNE);

  map_.set_tile( 0,  4, Map::TileType::WallW);
  map_.set_tile( 1,  4, Map::TileType::Open);
  map_.set_tile( 2,  4, Map::TileType::Open);
  map_.set_tile( 3,  4, Map::TileType::PusherE);
  map_.set_tile( 4,  4, Map::TileType::ConveyorS);
  map_.set_tile( 5,  4, Map::TileType::ConveyorE);
  map_.set_tile( 6,  4, Map::TileType::ConveyorE);
  map_.set_tile( 7,  4, Map::TileType::ConveyorE);
  map_.set_tile( 8,  4, Map::TileType::ConveyorE);
  map_.set_tile( 9,  4, Map::TileType::ConveyorE);
  map_.set_tile(10,  4, Map::TileType::ConveyorE);
  map_.set_tile(11,  4, Map::TileType::ConveyorE);

  map_.set_tile( 0,  5, Map::TileType::WallW);
  map_.set_tile( 1,  5, Map::TileType::Open);
  map_.set_tile( 2,  5, Map::TileType::Open);
  map_.set_tile( 3,  5, Map::TileType::Open);
  map_.set_tile( 4,  5, Map::TileType::ConveyorS);
  map_.set_tile( 5,  5, Map::TileType::Open);
  map_.set_tile( 6,  5, Map::TileType::Open);
  map_.set_tile( 7,  5, Map::TileType::Open);
  map_.set_tile( 8,  5, Map::TileType::Open);
  map_.set_tile( 9,  5, Map::TileType::Open);
  map_.set_tile(10,  5, Map::TileType::Open);
  map_.set_tile(11,  5, Map::TileType::WallSE);

  map_.set_tile( 0,  6, Map::TileType::WallW);
  map_.set_tile( 1,  6, Map::TileType::Open);
  map_.set_tile( 2,  6, Map::TileType::Open);
  map_.set_tile( 3,  6, Map::TileType::Open);
  map_.set_tile( 4,  6, Map::TileType::ConveyorS);
  map_.set_tile( 5,  6, Map::TileType::Open);
  map_.set_tile( 6,  6, Map::TileType::Open);
  map_.set_tile( 7,  6, Map::TileType::Open);
  map_.set_tile( 8,  6, Map::TileType::Open);
  map_.set_tile( 9,  6, Map::TileType::Open);
  map_.set_tile(10,  6, Map::TileType::Open);
  map_.set_tile(11,  6, Map::TileType::WallE);

  map_.set_tile( 0,  7, Map::TileType::WallW);
  map_.set_tile( 1,  7, Map::TileType::Open);
  map_.set_tile( 2,  7, Map::TileType::Open);
  map_.set_tile( 3,  7, Map::TileType::Open);
  map_.set_tile( 4,  7, Map::TileType::ConveyorS);
  map_.set_tile( 5,  7, Map::TileType::Open);
  map_.set_tile( 6,  7, Map::TileType::Open);
  map_.set_tile( 7,  7, Map::TileType::Block);
  map_.set_tile( 8,  7, Map::TileType::Block);
  map_.set_tile( 9,  7, Map::TileType::Open);
  map_.set_tile(10,  7, Map::TileType::Open);
  map_.set_tile(11,  7, Map::TileType::WallE);

  map_.set_tile( 0,  8, Map::TileType::WallW);
  map_.set_tile( 1,  8, Map::TileType::Open);
  map_.set_tile( 2,  8, Map::TileType::Open);
  map_.set_tile( 3,  8, Map::TileType::Open);
  map_.set_tile( 4,  8, Map::TileType::ConveyorS);
  map_.set_tile( 5,  8, Map::TileType::Open);
  map_.set_tile( 6,  8, Map::TileType::Open);
  map_.set_tile( 7,  8, Map::TileType::Block);
  map_.set_tile( 8,  8, Map::TileType::Block);
  map_.set_tile( 9,  8, Map::TileType::Open);
  map_.set_tile(10,  8, Map::TileType::Open);
  map_.set_tile(11,  8, Map::TileType::WallE);

  map_.set_tile( 0,  9, Map::TileType::WallW);
  map_.set_tile( 1,  9, Map::TileType::Open);
  map_.set_tile( 2,  9, Map::TileType::Open);
  map_.set_tile( 3,  9, Map::TileType::Open);
  map_.set_tile( 4,  9, Map::TileType::ConveyorS);
  map_.set_tile( 5,  9, Map::TileType::Open);
  map_.set_tile( 6,  9, Map::TileType::Open);
  map_.set_tile( 7,  9, Map::TileType::Open);
  map_.set_tile( 8,  9, Map::TileType::Open);
  map_.set_tile( 9,  9, Map::TileType::Open);
  map_.set_tile(10,  9, Map::TileType::Open);
  map_.set_tile(11,  9, Map::TileType::WallE);

  map_.set_tile( 0, 10, Map::TileType::WallW);
  map_.set_tile( 1, 10, Map::TileType::HoleSE);
  map_.set_tile( 2, 10, Map::TileType::HoleS);
  map_.set_tile( 3, 10, Map::TileType::HoleS);
  map_.set_tile( 4, 10, Map::TileType::HoleS);
  map_.set_tile( 5, 10, Map::TileType::HoleS);
  map_.set_tile( 6, 10, Map::TileType::HoleS);
  map_.set_tile( 7, 10, Map::TileType::HoleSW);
  map_.set_tile( 8, 10, Map::TileType::WallSE);
  map_.set_tile( 9, 10, Map::TileType::WallS);
  map_.set_tile(10, 10, Map::TileType::WallS);
  map_.set_tile(11, 10, Map::TileType::WallInnerSE);

  map_.set_tile( 0, 11, Map::TileType::WallW);
  map_.set_tile( 1, 11, Map::TileType::HoleE);
  map_.set_tile( 2, 11, Map::TileType::HoleMid);
  map_.set_tile( 3, 11, Map::TileType::HoleMid);
  map_.set_tile( 4, 11, Map::TileType::HoleMid);
  map_.set_tile( 5, 11, Map::TileType::HoleMid);
  map_.set_tile( 6, 11, Map::TileType::HoleMid);
  map_.set_tile( 7, 11, Map::TileType::HoleW);
  map_.set_tile( 8, 11, Map::TileType::WallE);
  map_.set_tile( 9, 11, Map::TileType::WallTop);
  map_.set_tile(10, 11, Map::TileType::WallTop);
  map_.set_tile(11, 11, Map::TileType::WallTop);

  map_.set_tile( 0, 12, Map::TileType::WallW);
  map_.set_tile( 1, 12, Map::TileType::HoleNE);
  map_.set_tile( 2, 12, Map::TileType::HoleN);
  map_.set_tile( 3, 12, Map::TileType::HoleN);
  map_.set_tile( 4, 12, Map::TileType::HoleN);
  map_.set_tile( 5, 12, Map::TileType::HoleN);
  map_.set_tile( 6, 12, Map::TileType::HoleN);
  map_.set_tile( 7, 12, Map::TileType::HoleNW);
  map_.set_tile( 8, 12, Map::TileType::WallE);
  map_.set_tile( 9, 12, Map::TileType::WallTop);
  map_.set_tile(10, 12, Map::TileType::WallTop);
  map_.set_tile(11, 12, Map::TileType::WallTop);

  map_.set_tile( 0, 13, Map::TileType::WallInnerSW);
  map_.set_tile( 1, 13, Map::TileType::WallS);
  map_.set_tile( 2, 13, Map::TileType::WallS);
  map_.set_tile( 3, 13, Map::TileType::WallS);
  map_.set_tile( 4, 13, Map::TileType::WallS);
  map_.set_tile( 5, 13, Map::TileType::WallS);
  map_.set_tile( 6, 13, Map::TileType::WallS);
  map_.set_tile( 7, 13, Map::TileType::WallS);
  map_.set_tile( 8, 13, Map::TileType::WallInnerSE);
  map_.set_tile( 9, 13, Map::TileType::WallTop);
  map_.set_tile(10, 13, Map::TileType::WallTop);
  map_.set_tile(11, 13, Map::TileType::WallTop);

  player.set_position(4, 1, Player::Facing::S);
}

void Level::update(unsigned int elapsed) {
  map_.update(elapsed);
}

void Level::draw(Graphics& graphics) const {
  map_.draw(graphics, 0, 0);
  player.draw(graphics);
}
