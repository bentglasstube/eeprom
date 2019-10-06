#include "box.h"

Box::Box(const std::string& file, int width, int height) :
  file_(file), width_(width), height_(height)
{}

void Box::draw(Graphics& graphics, int x, int y, int w, int h) const {
  SDL_Rect source, dest;

  const int ex = x + w - width_;
  const int ey = y + h - height_;
  const int sw = w - 2 * width_;
  const int sh = h - 2 * height_;

  source = {0, 0, width_, height_ };
  dest = {x, y, width_, height_ };

  blit(graphics, 0, x, y, width_, height_);
  blit(graphics, 1, x + width_, y, sw, height_);
  blit(graphics, 2, ex, y, width_, height_);
  blit(graphics, 3, x, y + height_, width_, sh);
  blit(graphics, 4, x + width_, y + height_, sw, sh);
  blit(graphics, 5, ex, y + height_, width_, sh);
  blit(graphics, 6, x, ey, width_, height_);
  blit(graphics, 7, x + width_, ey, sw, height_);
  blit(graphics, 8, ex, ey, width_, height_);
}

void Box::blit(Graphics& graphics, int tile, int x, int y, int w, int h) const {
  SDL_Rect source = { width_ * (tile % 3), height_ * ( tile / 3 ), width_, height_ };
  SDL_Rect dest = { x, y, w, h };
  graphics.blit(file_, &source, &dest);
}
