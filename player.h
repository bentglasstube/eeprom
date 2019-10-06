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

    void draw(Graphics& graphics) const;

  private:

    static constexpr int kTileSize = 16;

    SpriteMap sprites_;

    int x_, y_;
    Facing facing_;

    std::vector<Instruction> program_;
    size_t counter_;

};
