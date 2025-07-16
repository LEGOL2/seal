#include <cmath>
#include <helper.hpp>

float distance(float x1, float y1, float x2, float y2) noexcept {
    const float dx = x2 - x1;
    const float dy = y2 - y1;
    return std::sqrt(dx * dx + dy * dy);
}
