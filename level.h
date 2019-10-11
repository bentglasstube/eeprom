#pragma once

#include <vector>

#include "audio.h"
#include "graphics.h"

#include "crate.h"
#include "map.h"
#include "piston.h"

class Level {
  public:

    Level();

    struct Push {
      std::pair<int, int> from, to;

      Push(std::pair<int, int> from, std::pair<int, int> to);
      int dx() const;
      int dy() const;
    };

    struct Start {
      int x, y;
      Map::Facing facing;
    };

    void load(int level);

    void update(unsigned int elapsed);
    void draw(Graphics &graphics) const;

    std::vector<Push> step_pistons();

    bool oob(int x, int y) const;
    Map::Tile tile(int x, int y) const;
    Start start() const;

    bool open(int px, int py) const;
    bool push(int px, int py, int tx, int ty);

  private:

    static constexpr double kPushSpeed = 0.04;

    Map map_;
    Start start_;
    std::vector<Piston> pistons_;
    std::vector<Crate> crates_;

    bool push_player(std::pair<int, int> from, std::pair<int, int> to);

    void populate(std::vector<int> tiles);
};
