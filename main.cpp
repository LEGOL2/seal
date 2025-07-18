#include <seal/seal.hpp>

using namespace seal;

void setup() {
    size(400, 400);
    windowTitle("My Animation");
}

void draw() {
    background(51);

    loadPixels();
    for (int y = 0; y < width(); y++) {
        for (int x = 0; x < height(); x++) {
            uint8_t g = noise(x*0.01, y*0.03)*255;
            setPixel(x, y, {g, g, g});
        }
    }
    seal::updatePixels();
}

int main() {
    run();
}
