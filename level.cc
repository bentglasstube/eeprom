#include "level.h"

#include <iostream>

Level::Level() : player(), map_() {
  map_.set_size(12, 14);

}

void Level::load(int level) {
  pistons_.clear();
  crates_.clear();

  switch (level) {
    case 1:
      populate({
        84,98,98,99,13,97,98,98,98,98,98,85,
        91,3,1,1,33,1,1,1,3,3,3,89,
        91,3,3,1,33,1,1,1,1,1,1,89,
        91,3,3,1,33,1,1,1,1,1,1,97,
        91,1,1,9,33,17,17,17,17,17,17,17,
        91,1,1,1,33,1,1,1,1,1,1,81,
        91,1,1,1,33,1,1,2,2,1,1,89,
        91,1,1,1,33,1,1,2,2,1,1,89,
        91,1,1,1,33,1,1,1,1,1,1,89,
        91,1,1,1,33,1,1,81,82,82,82,93,
        91,86,87,87,87,87,88,89,90,90,90,90,
        91,94,95,95,95,95,96,89,90,90,90,90,
        91,102,103,103,103,103,104,89,90,90,90,90,
        92,82,82,82,82,82,82,93,90,90,90,90
        });

      player.set_position(4, 1, Player::Facing::S);
      pistons_.emplace_back(3, 4, Piston::Facing::E, 4);

      break;

    case 2:
      populate({
          84,98,98,98,98,98,98,98,98,98,98,85,
          91,3,3,86,87,87,88,3,3,3,3,89,
          91,3,1,94,95,95,96,1,1,3,3,89,
          99,1,1,102,103,103,104,11,1,3,3,97,
          15,17,17,17,17,17,17,1,1,1,1,1,
          83,1,1,12,12,1,12,33,1,1,1,81,
          91,1,1,1,1,1,1,33,1,1,3,89,
          91,1,3,1,1,3,1,33,1,3,3,89,
          91,1,3,3,3,1,1,33,1,3,1,89,
          91,1,1,3,3,1,1,33,1,1,1,89,
          91,86,87,87,87,87,87,87,87,87,88,89,
          91,94,95,95,95,95,95,95,95,95,96,89,
          91,102,103,103,103,103,103,103,103,103,104,89,
          92,82,82,82,82,82,82,82,82,82,82,93
          });

      player.set_position(1, 4, Player::Facing::E);
      pistons_.emplace_back(3, 5, Piston::Facing::N, 4, 3);
      pistons_.emplace_back(4, 5, Piston::Facing::N, 4, 3);
      pistons_.emplace_back(6, 5, Piston::Facing::N, 4, 3);
      pistons_.emplace_back(7, 3, Piston::Facing::S, 4, 3);

      break;
  }
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

void Level::populate(std::vector<int> tiles) {
  int x = 0, y = 0;

  for (auto t : tiles) {
    map_.set_tile(x, y, Map::tile_from_sprite(t));

    if (t == 3) crates_.emplace_back(x * 16, y * 16);

    if (++x >= map_.width()) {
      x = 0;
      ++y;
    }
    if (y >= map_.height()) return;
  }
}
