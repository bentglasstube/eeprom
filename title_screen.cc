#include "title_screen.h"

#include "level_screen.h"

TitleScreen::TitleScreen(GameState state) :
  bg_("title.png"), text_("text.png"),
  gs_(state), timer_(0)
{}

bool TitleScreen::update(const Input& input, Audio&, unsigned int elapsed) {
  timer_ = (timer_ + elapsed) % 1000;

  if (input.key_pressed(Input::Button::A) || input.key_pressed(Input::Button::Start)) {
    return false;
  }

  return true;
}

void TitleScreen::draw(Graphics& graphics) const {
  bg_.draw(graphics);
  if (timer_ < 500) text_.draw(graphics, "Press Start", 128, 216, Text::Alignment::Center);
}

Screen* TitleScreen::next_screen() const {
  LevelScreen* s = new LevelScreen(gs_);
  return s;
}
