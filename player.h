#pragma once

#include <vector>

#include "graphics.h"
#include "spritemap.h"

class Player {
  public:

    enum class Facing {N, S, E, W};
    enum class Instruction { NOP, MOV, SHL, SHR };

    static std::string instruction_text(Instruction);

    Player();

    void set_position(int x, int y, Player::Facing facing);

    void add_instruction(Instruction op);
    void remove_instruction();
    void clear_program();

    std::vector<Instruction> const& listing() const;
    size_t counter() const;

    void update(unsigned int elapsed);
    void draw(Graphics& graphics) const;

    bool moving() const;
    void convey(int dx, int dy);
    void push(int dx, int dy);

    int map_x() const;
    int map_y() const;

  private:

    static constexpr int kTileSize = 16;
    static constexpr int kAnimationSpeed = 240;
    static constexpr double kWalkSpeed = 0.01;
    static constexpr double kShoveSpeed = 0.1;

    SpriteMap sprites_;

    double x_, y_, v_, tx_, ty_;
    int timer_;
    Facing facing_;
    bool animate_;

    std::vector<Instruction> program_;
    size_t counter_;

    int frame() const;
    void set_target(int tx, int ty, double speed);

};
