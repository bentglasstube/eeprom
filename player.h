#pragma once

#include <vector>

#include "audio.h"
#include "graphics.h"
#include "map.h"
#include "spritemap.h"

class Player {
  public:

    enum class Facing {N, S, E, W};
    enum class Instruction { NOP, MOV, SHL, SHR };

    static std::string instruction_text(Instruction);

    Player();

    void set_position(int x, int y, Player::Facing facing);

    void add_instruction(Instruction op);
    void remove_instruction(Audio& audio);
    void clear_program();

    std::vector<Instruction> const& listing() const;
    size_t counter() const;

    void update(unsigned int elapsed);
    void draw(Graphics& graphics) const;

    bool moving() const;
    bool dead() const;

    void convey(int dx, int dy, const Map& map);
    void push(int dx, int dy, const Map& map);
    void execute(const Map& map);
    void fall();
    void stop();

    int map_x() const;
    int map_y() const;

  private:

    static constexpr int kTileSize = 16;
    static constexpr int kAnimationSpeed = 120;
    static constexpr double kWalkSpeed = 0.03;
    static constexpr double kConveyorSpeed = 0.01;
    static constexpr double kShoveSpeed = 0.1;
    static constexpr double kTurnSpeed = 0.005;

    SpriteMap sprites_;

    double x_, y_, v_, tx_, ty_;
    double rot_;
    int timer_;
    Facing facing_;
    bool animate_, falling_;

    std::vector<Instruction> program_;
    size_t counter_;

    int frame() const;
    void set_target(int tx, int ty, double speed, const Map& map);

    void walk(const Map& map);
    void rotate(bool clockwise);

    int xdiff() const;
    int ydiff() const;
};
