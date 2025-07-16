#pragma once

#include <stdint.h>

extern void setup();
extern void draw();

namespace seal {
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

// Shape
//   2D Primitives
void arc(float a, float b, float c, float d, float start, float stop);
void arc(float a, float b, float c, float d, float start, float stop, float mode);
void circle(float x, float y, float radius = 1);
void ellipse(float x, float y, float width, float height);
void line(float x1, float y1, float x2, float y2);
void point(float x, float y);
void quad(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);
void rect(float x, float y, float w, float h);
void square(float x, float y, float extent);
void triangle(float x1, float y1, float x2, float y2, float x3, float y3);
//   Attributes
void strokeWeight(float weight);

// Output

// Math

// Lights & Camera

// Color
//   Creating & Reading
//   Setting
void background(uint8_t gray);
void background(uint8_t red, uint8_t green, uint8_t blue);
void fill(uint8_t gray);
void fill(uint8_t red, uint8_t green, uint8_t blue);
void noFill();
void noStroke();
void stroke(uint8_t red, uint8_t green, uint8_t blue);

// Transform

// Structure

// Control

// Environment
void size(uint32_t w, uint32_t h);
void windowTitle(const char* title);
}  // namespace seal
