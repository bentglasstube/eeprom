#include "level_screen.h"

LevelScreen::LevelScreen(GameState state) :
  gs_(state), state_(State::Intro), level_(), fade_timer_(0) {}

bool LevelScreen::update(const Input&, Audio& audio, unsigned int elapsed) {
  level_.update(elapsed);

  return true;
}

void LevelScreen::draw(Graphics& graphics) const {
  level_.draw(graphics);
}

Screen* LevelScreen::next_screen() const {
  return nullptr;
}
