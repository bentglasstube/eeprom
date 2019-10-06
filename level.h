#pragma once

#include "map.h"
#include "player.h"

class Level {
  public:

    Level();

    void update(unsigned int elapsed);
    void draw(Graphics &graphics) const;

    Player const& player() const;

  private:

    Map map_;
    Player player_;

};
