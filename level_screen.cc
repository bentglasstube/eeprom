#include "level_screen.h"

LevelScreen::LevelScreen(GameState state) :
  text_("tinytext.png", 6, 8),
  box_("box.png", 8),
  gs_(state), state_(State::Reset), level_(),
  timer_(0), choice_(0)
{}

bool LevelScreen::update(const Input& input, Audio& audio, unsigned int elapsed) {

  timer_ += elapsed;

  switch (state_) {
    case State::Intro:

      // TODO show level name

      if (timer_ > kFadeTime) {
        transition(State::Input);
      }

      break;

    case State::Input:

      if (timer_ > kBlinkTime) timer_ -= kBlinkTime;

      if (input.key_pressed(Input::Button::Right)) set_choice(choice_ + 1);
      if (input.key_pressed(Input::Button::Left)) set_choice(choice_ - 1);
      if (input.key_pressed(Input::Button::Up)) set_choice(choice_ - 2);
      if (input.key_pressed(Input::Button::Down)) set_choice(choice_ + 2);

      if (input.key_pressed(Input::Button::Start) || input.key_pressed(Input::Button::A)) {
        switch (choice_) {
          case 0:
          case 1:
          case 2:
          case 3:
            if (player_.listing().size() < gs_.rom_size()) {
              player_.add_instruction(static_cast<Player::Instruction>(choice_));
              audio.play_sample("blip.wav");
            } else {
              audio.play_sample("nope.wav");
            }
            break;

          case 4:
            player_.remove_instruction(audio);
            break;

          case 5:
            player_.clear_program();
            audio.play_sample("blip.wav");
            break;

          case 6:
          case 7:
            if (player_.listing().empty()) {
              audio.play_sample("nope.wav");
            } else {
              audio.play_sample("blip.wav");
              transition(State::Execution);
            }
            break;
        }
      }

      break;

    case State::Execution:

      if (input.key_pressed(Input::Button::A)) {
        audio.play_sample("nope.wav");
        transition(State::Reset);
      }

      if (step_complete()) {
        player_.stop();
        timer_ = 0;

        if (player_.dead()) {
          transition(State::Outro);
        } else if (robot_left()) {
          gs_.next_level();
          audio.play_sample("powerup.wav");
          transition(State::Outro);
        } else if (robot_in_pit()) {
          audio.play_sample("fall.wav");
          player_.fall();
        } else {
          const auto& pushes = level_.step_pistons();
          if (!pushes.empty()) {
            audio.play_sample("slide.wav");
          }

          for (const auto& p : pushes) {
            if (player_.at(p.from)) {
              player_.push(p.dx(), p.dy(), level_);
            }
          }

          if (!player_.moving()) {
            player_.convey(level_);
            player_.execute(level_);
          }
        }
      }

      level_.update(elapsed);
      player_.update(elapsed);
      break;

    case State::Reset:

      reset();
      break;

    case State::Outro:

      if (timer_ > kFadeTime) {
        reset();
      }
      break;
  }

  return true;
}

void LevelScreen::transition(LevelScreen::State state) {
  state_ = state;
  timer_ = state == State::Execution ? kStepTime : 0;
}

void LevelScreen::draw(Graphics& graphics) const {
  level_.draw(graphics);
  player_.draw(graphics);

  const double alpha = fade_amount();
  if (alpha > 0) {
    const SDL_Rect map = { 0, 0, 192, 224 };
    graphics.draw_rect(&map, 255 * alpha, true);
  }

  box_.draw(graphics, 192, 0, 64, 160);
  text_.draw(graphics, "ROM Dump", 200, 8);

  const auto& listing = player_.listing();
  for (size_t i = 0; i < listing.size(); ++i) {
    const int y = 20 + 8 * i;
    text_.draw(graphics, Player::instruction_text(listing[i]), 202, y);
    if (state_ == State::Execution && i == player_.counter()) text_.draw(graphics, ">", 196, y);
  }

  box_.draw(graphics, 192, 160, 64, 64);

  if (state_ == State::Input) {
    for (int i = 0; i < 4; ++i) {
      const int x = 202 + 24 * (i % 2);
      const int y = 168 + i / 2 * 8;
      const Player::Instruction op = static_cast<Player::Instruction>(i);
      if (gs_.can_use(op)) text_.draw(graphics, Player::instruction_text(op), x, y);
    }

    text_.draw(graphics, "POP", 202, 192);
    text_.draw(graphics, "RST", 226, 192);

    text_.draw(graphics, "EXECUTE", 202, 208);

    if (timer_ < kBlinkTime / 2) {
      const int cx = (choice_ % 2 == 1 && choice_ < 6) ? 220 : 196;
      const int cy = std::max(choice_ / 2 * 16 + 160, 168);
      text_.draw(graphics, ">", cx, cy);
    }
  }
}

Screen* LevelScreen::next_screen() const {
  return nullptr;
}

double LevelScreen::fade_amount() const {
  const double progress = timer_ / (double) kFadeTime;

  switch (state_) {
    case State::Intro:
      return 1 - progress;

    case State::Outro:
    case State::Reset:
      return progress;

    default:
      return 0.0;
  }
}

void LevelScreen::set_choice(int choice) {
  const int d = choice - choice_;

  if (choice < 0) return;
  if (choice > 7) return;

  if (choice < 4) {
    Player::Instruction op = static_cast<Player::Instruction>(choice);
    if (!gs_.can_use(op)) return set_choice(choice + d);
  }

  choice_ = choice;
}

bool LevelScreen::step_complete() const {
  return timer_ >= kStepTime && !player_.moving();
}

bool LevelScreen::robot_in_pit() const {
  const auto tile = level_.tile(player_.map_x(), player_.map_y());
  return tile.pit();
}

bool LevelScreen::robot_left() const {
  if (player_.moving()) return false;
  if (level_.oob(player_.map_x(), player_.map_y())) return true;
  return false;
}

void LevelScreen::reset() {
  choice_ = 0;
  player_.clear_program();

  level_.load(gs_.level());
  player_.set_position(level_.start());

  transition(State::Intro);

}
