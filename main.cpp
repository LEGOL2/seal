#include <seal.hpp>

using namespace seal;

void setup() {
    size(800, 600);
    title("My Animation");
}

void draw() {
    background(51);

    fill(150, 95, 200);
    ellipse(200, 200, 150, 100);
}

int main() { run(); }
