#pragma once

#include "spritemap.h"

#include "object.h"

class Crate : public Object {
  public:

    Crate(int x, int y);
    virtual ~Crate();

    void draw(Graphics& graphics) const override;

  private:

    static constexpr int kTileSize = 16;

    SpriteMap tileset_;
};
