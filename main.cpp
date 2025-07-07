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
    strokeWeight(5);
    line(200, 200, 70, 30);
}

int main() { run(); }
