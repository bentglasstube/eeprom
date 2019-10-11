#pragma once

#include "spritemap.h"

#include "map.h"

class Piston {
  public:

    enum class State { Dormant, Extending, Retracting };

    Piston(int x, int y, Map::Facing facing, int freq, int first);
    Piston(int x, int y, Map::Facing facing, int freq) : Piston(x, y, facing, freq, freq) {}

    void update(unsigned int elapsed);
    void draw(Graphics& graphics) const;
    bool step();

    std::pair<int, int> push_from() const;
    std::pair<int, int> push_to() const;

  private:

    static constexpr int kTileSize = 16;
    static constexpr int kFrames = 8;
    static constexpr int kExtensionRate = 25;
    static constexpr int kRetractionRate = kExtensionRate * 4;

    SpriteMap tileset_;

    int x_, y_, freq_, counter_;
    int timer_, frame_;
    Map::Facing facing_;
    State state_;

    int xdiff() const;
    int ydiff() const;
};
