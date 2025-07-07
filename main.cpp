#include <seal.hpp>

using namespace seal;

void setup() {
    size(800, 600);
    title("My Animation");
}

void draw() {
    background(51);

    fill(150, 95, 200);
    stroke(150, 95, 200);
    strokeWeight(2);

    line(100, 100, 50, 70);
}

int main() { run(); }
