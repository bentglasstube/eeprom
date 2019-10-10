#pragma once

#include "map.h"

class Object {
  public:
    Object(int x, int y);

    void update(unsigned int elapsed);
    virtual void draw(Graphics& graphics) const = 0;

    bool push(double v, int tx, int ty, const Map& map);

    int map_x() const;
    int map_y() const;

  protected:

    static constexpr int kTileSize = 16;

    double x_, y_, v_, tx_, ty_;
};
