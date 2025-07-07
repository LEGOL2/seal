#include <seal.hpp>

using namespace seal;

void setup() {
    size(800, 600);
    title("My Animation");
}

void draw() {
    background(51);

    fill(150, 95, 200);
    stroke(255, 255, 255);

    quad(152, 124, 344, 80, 276, 252, 120, 304);
    square(600, 300, 150);
    triangle(120, 300, 400, 80, 344, 300);
}

int main() { run(); }
