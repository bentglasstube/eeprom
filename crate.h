#pragma once

#include "spritemap.h"

class Crate {
  public:

    Crate(int x, int y);

    void update(unsigned int elapsed);
    void draw(Graphics& graphics) const;

    void push(int tx, int ty);

    int map_x() const;
    int map_y() const;

  private:

    static constexpr int kTileSize = 16;
    static constexpr double kPushSpeed = 0.01;

    SpriteMap tileset_;

    double x_, y_, tx_, ty_;

};
