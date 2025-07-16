#include <seal.hpp>

using namespace seal;

void setup() {
    size(800, 600);
    windowTitle("My Animation");
}

void draw() {
    background(51);

    fill(150, 95, 200);
    stroke(25, 95, 200);
    strokeWeight(4);

    quad(152, 124, 344, 80, 276, 252, 120, 304);
    fill(50, 250, 175);
    triangle(50, 300, 145, 200, 300, 170);
    
    noFill();
    ellipse(400, 300, 100, 150);

    fill(150, 95, 200);
    noStroke();
    rect(600, 400, 150, 80);
}

int main() { run(); }
