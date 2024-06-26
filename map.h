#pragma once

#include "spritemap.h"

#include <vector>

class Map {
  public:

    enum class TileType {
      Open, Block, Box,
      PusherN, PusherS, PusherE, PusherW,
      DoorN, DoorS, DoorE, DoorW,
      ConveyorN, ConveyorS, ConveyorE, ConveyorW,
      WallNW, WallN, WallNE, WallW, WallTop, WallE, WallSW, WallS, WallSE,
      WallInnerNW, WallInnerNE, WallInnerSW, WallInnerSE,
      HoleNW, HoleN, HoleNE, HoleW, HoleMid, HoleE, HoleSW, HoleS, HoleSE,
      OutOfBounds,
    };

    enum class Facing {
      N, S, E, W
    };

    struct Tile {
      TileType type;

      bool solid() const;
      bool conveyor() const;
      bool pit() const;
      double dx() const;
      double dy() const;
      int sprite(int timer) const;
    };

    static TileType tile_from_sprite(int sprite);

    Map();

    void draw(Graphics& graphics) const;
    void update(unsigned int elapsed);

    Tile tile(int x, int y) const;

    void set_size(int width, int height);
    void set_tile(int x, int y, TileType type);

    int width() const;
    int height() const;

    void populate(std::vector<int> tiles);

  private:

    static constexpr int kTileSize = 16;
    static constexpr int kMaxWidth = 16;
    static constexpr int kMaxHeight = 16;
    static constexpr int kAnimationFrames = 8;
    static constexpr int kFrameLength = 100;
    static constexpr Tile kNullTile = { TileType::OutOfBounds };

    SpriteMap tileset_;
    int width_, height_, timer_;
    TileType tiles_[kMaxHeight][kMaxWidth];

    int tile_sprite(const Tile& t) const;
};
