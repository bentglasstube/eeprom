#include "level_screen.h"

LevelScreen::LevelScreen(GameState state) :
  text_("tinytext.png", 6, 8),
  box_("box.png", 8),
  gs_(state), state_(State::Intro), level_()
{}

bool LevelScreen::update(const Input&, Audio& audio, unsigned int elapsed) {
  level_.update(elapsed);

  return true;
}

void LevelScreen::draw(Graphics& graphics) const {
  level_.draw(graphics);

  box_.draw(graphics, 192, 0, 64, 160);
  text_.draw(graphics, "ROM Dump", 200, 8);

  const Player& p = level_.player();
  const auto& listing = p.listing();
  for (size_t i = 0; i < listing.size(); ++i) {
    const int y = 20 + 8 * i;
    text_.draw(graphics, Player::instruction_text(listing[i]), 202, y);
    if (i == p.counter()) text_.draw(graphics, ">", 196, y);
  }
}

Screen* LevelScreen::next_screen() const {
  return nullptr;
}
