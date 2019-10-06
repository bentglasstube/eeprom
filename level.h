#pragma once

#include "map.h"
#include "player.h"

class Level {
  public:

    Player player;

    Level();

    void update(unsigned int elapsed);
    void draw(Graphics &graphics) const;

    void conveyors();

  private:

    Map map_;

};
