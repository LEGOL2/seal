#include <seal.hpp>

using namespace seal;

float x{0};

void setup() {
    size(800, 600);
    title("My Animation");
}

void draw() {
    background(51);

    fill(150, 95, 200);
    rect(x, 100, 120, 50);

    x += 0.5;
    if (x > 800) x = 0;
}

int main() { run(); }
