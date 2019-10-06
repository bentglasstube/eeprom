#pragma once

#include "spritemap.h"

class Crate {
  public:

    Crate(int x, int y);

    void update(unsigned int elapsed);
    void draw(Graphics& graphics) const;

    void push(int tx, int ty);

  private:

    static constexpr double kPushSpeed = 0.01;

    SpriteMap tileset_;

    double x_, y_, tx_, ty_;

};
