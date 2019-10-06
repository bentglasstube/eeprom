#pragma once

#include <vector>

#include "crate.h"
#include "map.h"
#include "piston.h"
#include "player.h"

class Level {
  public:

    Player player;

    Level();

    void update(unsigned int elapsed);
    void draw(Graphics &graphics) const;

    void conveyors();
    bool step_pistons();

  private:

    Map map_;
    std::vector<Piston> pistons_;
    std::vector<Crate> crates_;

};
