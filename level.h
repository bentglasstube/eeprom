#pragma once

#include <vector>

#include "audio.h"
#include "graphics.h"

#include "crate.h"
#include "map.h"
#include "piston.h"
#include "player.h"

class Level {
  public:

    Player player;

    Level();

    void load(int level);

    void update(unsigned int elapsed);
    void draw(Graphics &graphics) const;

    void conveyors();
    bool step_pistons(Audio& audio);
    void run_program();

    Map::Tile player_tile() const;
    bool player_oob() const;

  private:

    static constexpr double kPushSpeed = 0.01;

    Map map_;
    std::vector<Piston> pistons_;
    std::vector<Crate> crates_;

    bool push_player(std::pair<int, int> from, std::pair<int, int> to);
    bool push_crate(int x, int y, int tx, int ty);

    void populate(std::vector<int> tiles);
};
