#include "Noise.hpp"

Noise::Noise()
{
    for (int x = 0; x < 512; x++)
    {
        this->p[x] = this->permutation[x % 256];
    }
    return;
}

Noise::~Noise()
{
    return;
}

float Noise::grad(int hash, float x, float y, float z)
{
    int h = hash & 15;
    float u = h < 8 ? x : y;
    float v;

    if (h < 4)
        v = y;
    else if (h == 12 || h == 14)
        v = x;
    else
        v = z;
    return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
}

float Noise::fade(float t)
{
    return t * t * t * (t * (t * 6 - 15) + 10);
}

float Noise::lerp(float a, float b, float x)
{
    return a + x * (b - a);
}

float Noise::Perlin(float x, float y, float z)
{
    int xi = (int)x & 255;
    int yi = (int)y & 255;
    int zi = (int)z & 255;
    float xf = x - (int)x;
    float yf = y - (int)y;
    float zf = z - (int)z;
    float u = this->fade(xf);
    float v = this->fade(yf);
    float w = this->fade(zf);

    int a = this->p[xi] + yi;
    int aa = this->p[a] + zi;
    int ab = this->p[a + 1] + zi;
    int b = this->p[xi + 1] + yi;
    int ba = this->p[b] + zi;
    int bb = this->p[b + 1] + zi;

    float x1, x2, y1, y2;
    x1 = this->lerp(this->grad(this->p[aa], xf, yf, zf),
                grad(this->p[ba], xf - 1, yf, zf),
                u);
    x2 = this->lerp(this->grad(this->p[ab], xf, yf - 1, zf),
                this->grad(this->p[bb], xf - 1, yf - 1, zf),
                u);
    y1 = this->lerp(x1, x2, v);
    x1 = this->lerp(this->grad(this->p[aa + 1], xf, yf, zf - 1),
                this->grad(this->p[ba + 1], xf - 1, yf, zf - 1),
                u);
    x2 = this->lerp(this->grad(this->p[ab + 1], xf, yf - 1, zf - 1),
                    this->grad(this->p[bb + 1], xf - 1, yf - 1, zf - 1),
                    u);
    y2 = this->lerp(x1, x2, v);

    return (this->lerp(y1, y2, w) + 1) / 2;
}