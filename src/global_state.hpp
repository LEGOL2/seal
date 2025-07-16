#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <seal/seal.hpp>

// Global state
extern std::unique_ptr<sf::RenderWindow> g_window;
extern uint32_t g_width, g_height;
extern sf::String g_currentTitle;

extern enum seal::EllipseMode g_currentEllipseMode;

extern sf::Color g_currentBackground;
extern sf::Color g_currentFill;
extern bool g_fillEnabled;
extern sf::Color g_currentStroke;
extern float g_currentStrokeWeight;
extern bool g_strokeEnabled;

extern float g_mouseX, g_mouseY;
extern bool g_mouseIsPressed;
