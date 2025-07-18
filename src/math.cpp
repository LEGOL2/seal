#include <ctime>
#include <random>
#include <seal/seal.hpp>

namespace {
// Improved Perlin noise implementation by Adrian Biagioli https://adrianb.io/2014/08/09/perlinnoise.html
class PerlinNoise {
   public:
    PerlinNoise() { reseed(time(nullptr)); }

    float noise(float x, float y = 0.f, float z = 0.f) const {
        float total = 0;
        float frequency = 1;
        float amplitude = 1;
        float maxValue = 0;
        for (int i = 0; i < octaves; i++) {
            total += generate(x * frequency, y * frequency, z * frequency) * amplitude;

            maxValue += amplitude;

            amplitude *= falloff;
            frequency *= 2;
        }

        return total / maxValue;
    }

    void reseed(uint32_t seed) {
        engine.seed(seed);
        for (int i = 0; i < 256; i++) {
            p[i] = dist(engine);
        }
        std::memcpy(&p[256], p, 256 * sizeof(int));
    }

    void noiseDetail(int octaves, float falloff) {
        this->octaves = octaves;
        this->falloff = falloff;
    }

   private:
    float generate(float x, float y = 0.f, float z = 0.f) const {
        int xi = static_cast<int>(x) & 255;
        int yi = static_cast<int>(y) & 255;
        int zi = static_cast<int>(z) & 255;
        float xf = x - static_cast<int>(x);
        float yf = y - static_cast<int>(y);
        float zf = z - static_cast<int>(z);

        float u = fade(xf);
        float v = fade(yf);
        float w = fade(zf);

        int aaa, aba, aab, abb, baa, bba, bab, bbb;
        aaa = p[p[p[xi] + yi] + zi];
        aba = p[p[p[xi] + inc(yi)] + zi];
        aab = p[p[p[xi] + yi] + inc(zi)];
        abb = p[p[p[xi] + inc(yi)] + inc(zi)];
        baa = p[p[p[inc(xi)] + yi] + zi];
        bba = p[p[p[inc(xi)] + inc(yi)] + zi];
        bab = p[p[p[inc(xi)] + yi] + inc(zi)];
        bbb = p[p[p[inc(xi)] + inc(yi)] + inc(zi)];

        float x1, x2, y1, y2;
        x1 = lerp(grad(aaa, xf, yf, zf), grad(baa, xf - 1, yf, zf), u);
        x2 = lerp(grad(aba, xf, yf - 1, zf), grad(bba, xf - 1, yf - 1, zf), u);
        y1 = lerp(x1, x2, v);

        x1 = lerp(grad(aab, xf, yf, zf - 1), grad(bab, xf - 1, yf, zf - 1), u);
        x2 = lerp(grad(abb, xf, yf - 1, zf - 1), grad(bbb, xf - 1, yf - 1, zf - 1), u);
        y2 = lerp(x1, x2, v);

        return (lerp(y1, y2, w) + 1) / 2;
    }

    float fade(float t) const {
        return t * t * t * (t * (t * 6 - 15) + 10);  // 6t^5 - 15t^4 + 10t^3
    }

    int inc(int num) const {
        num++;
        return num;
    }

    float lerp(float a, float b, float x) const { return a + x * (b - a); }

    float grad(int hash, float x, float y, float z) const {
        switch (hash & 0xF) {
            case 0x0:
                return x + y;
            case 0x1:
                return -x + y;
            case 0x2:
                return x - y;
            case 0x3:
                return -x - y;
            case 0x4:
                return x + z;
            case 0x5:
                return -x + z;
            case 0x6:
                return x - z;
            case 0x7:
                return -x - z;
            case 0x8:
                return y + z;
            case 0x9:
                return -y + z;
            case 0xA:
                return y - z;
            case 0xB:
                return -y - z;
            case 0xC:
                return y + x;
            case 0xD:
                return -y + z;
            case 0xE:
                return y - x;
            case 0xF:
                return -y - z;
            default:
                return 0;  // never happens
        }
    }

    std::minstd_rand engine;
    std::uniform_int_distribution<int> dist{0, 255};
    int p[512];
    int octaves{4};
    float falloff{0.5f};
};

PerlinNoise g_noiseGenerator;
std::mt19937 g_randomEngine;
std::uniform_real_distribution<float> g_randomDist{0.f, 1.f};
}  // namespace

float seal::noise(float x) { return g_noiseGenerator.noise(x); }
float seal::noise(float x, float y) { return g_noiseGenerator.noise(x, y); }
float seal::noise(float x, float y, float z) { return g_noiseGenerator.noise(x, y, z); }
void seal::noiseDetail(int lod, float falloff) { g_noiseGenerator.noiseDetail(lod, falloff); }
void seal::randomSeed(int seed) { g_randomEngine.seed(seed); }
float seal::random(float high) { return g_randomDist(g_randomEngine) * high; }
float seal::random(float low, float high) { return low + (high - low) * g_randomDist(g_randomEngine); }
