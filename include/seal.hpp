#pragma once

#include <stdint.h>

extern void setup();
extern void draw();

namespace seal {
// Runtime management
void init();
void run();

// Drawing
void background(uint8_t gray);
void background(uint8_t red, uint8_t green, uint8_t blue);
void fill(uint8_t gray);
void fill(uint8_t red, uint8_t green, uint8_t blue);
void rect(float x, float y, float w, float h);

// Window settings
void size(uint32_t w, uint32_t h);
void title(const char* title);

// Input
float mouseX();
float mouseY();
bool mousePressed();
}  // namespace seal
