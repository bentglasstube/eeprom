#pragma once

#include "map.h"

class Level {
  public:

    Level();

    void update(unsigned int elapsed);
    void draw(Graphics &graphics) const;

  private:

    Map map_;

};
