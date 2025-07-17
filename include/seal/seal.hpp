#pragma once

#include <cstdint>

extern void setup();
extern void draw();

namespace seal {
enum EllipseMode { CENTER, RADIUS, CORNER, CORNERS };

class Color {
   public:
    constexpr Color() = default;
    constexpr Color(std::uint8_t red, std::uint8_t green, std::uint8_t blue, std::uint8_t alpha = 255);
    std::uint8_t r{};
    std::uint8_t g{};
    std::uint8_t b{};
    std::uint8_t a{255};
};

// Runtime management
void init();
void run();

// Data

// Input
// Files
// Time & Date
// Keyboard
// Mouse
bool mousePressed();
float mouseX();
float mouseY();

// Constants

// Typography

// Rendering

// Image
//   Pixels
Color getPixel(uint32_t x, uint32_t y);
void loadPixels();
void setPixel(uint32_t x, uint32_t y, const Color& color);
void updatePixels();

// Shape
//   2D Primitives
void arc(float a, float b, float c, float d, float start, float stop);
void arc(float a, float b, float c, float d, float start, float stop, float mode);
void circle(float x, float y, float radius = 1);
void ellipse(float a, float b, float c, float d);
void line(float x1, float y1, float x2, float y2);
void point(float x, float y);
void quad(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);
void rect(float x, float y, float w, float h);
void square(float x, float y, float extent);
void triangle(float x1, float y1, float x2, float y2, float x3, float y3);
//   Attributes
void ellipseMode(EllipseMode mode);
void strokeWeight(float weight);

// Output

// Math

// Lights & Camera

// Color
//   Creating & Reading
//   Setting
void background(uint8_t gray, uint8_t alpha = 255);
void background(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha = 255);
void fill(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha = 255);
void fill(uint8_t gray, uint8_t alpha = 255);
void noFill();
void noStroke();
void stroke(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha = 255);

// Transform

// Structure
void popStyle();
void pushStyle();

// Control

// Environment
uint32_t height();
void size(uint32_t w, uint32_t h);
uint32_t width();
void windowTitle(const char* title);
}  // namespace seal
