#include <seal/seal.hpp>

using namespace seal;

void setup() {
    size(800, 600);
    windowTitle("My Animation");
}

void draw() {
    background(51);

    strokeWeight(5);
quad(152, 124, 344, 80, 276, 252, 120, 304);}

int main() { run(); }
