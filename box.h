#pragma once

#include <string>

#include "graphics.h"

class Box {
  public:

    Box(const std::string& file, int width, int height);
    inline Box(const std::string& file, int width) : Box(file, width, width) {}

    void draw(Graphics& graphics, int x, int y, int w, int h) const;

  private:

    std::string file_;
    int width_, height_;

    void blit(Graphics& graphics, int tile, int x, int y, int w, int h) const;
};
