#include <seal/seal.hpp>

using namespace seal;

void setup() {
    size(800, 600);
    windowTitle("My Animation");
}

void draw() {
    background(51);

    fill(50, 150, 175, 180);
    strokeWeight(5);
    quad(152, 124, 344, 80, 276, 252, 120, 304);
    fill(50, 150, 175, 50);
    strokeWeight(20);

    quad(200, 150, 344, 90, 300, 375, 150, 325);
}

int main() { run(); }
