#include "level_screen.h"

LevelScreen::LevelScreen(GameState state) :
  text_("text.png"),
  gs_(state), state_(State::Intro), level_()
{}

bool LevelScreen::update(const Input&, Audio& audio, unsigned int elapsed) {
  level_.update(elapsed);

  return true;
}

void LevelScreen::draw(Graphics& graphics) const {
  level_.draw(graphics);

  const Player& p = level_.player();
  const auto& listing = p.listing();
  for (size_t i = 0; i < listing.size(); ++i) {
    text_.draw(graphics, Player::instruction_text(listing[i]), 208, 16 * i);
  }

  text_.draw(graphics, ">", 200, 16 * p.counter());
}

Screen* LevelScreen::next_screen() const {
  return nullptr;
}
