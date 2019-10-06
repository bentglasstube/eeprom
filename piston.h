#pragma once

#include "spritemap.h"

class Piston {
  public:

    enum class Facing { N, E, S, W };
    enum class State { Dormant, Extending, Retracting };

    Piston(int x, int y, Facing facing, int freq, int first);
    Piston(int x, int y, Facing facing, int freq) : Piston(x, y, facing, freq, freq) {}

    void update(unsigned int elapsed);
    void draw(Graphics& graphics) const;
    bool step();

  private:

    static constexpr int kFrames = 8;
    static constexpr int kExtensionRate = 25;
    static constexpr int kRetractionRate = kExtensionRate * 4;

    SpriteMap tileset_;

    int x_, y_, freq_, counter_;
    int timer_, frame_;
    Facing facing_;
    State state_;

};
