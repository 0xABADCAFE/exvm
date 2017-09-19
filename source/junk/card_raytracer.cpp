// De-golfed version of the Business Card Raytracer by Andrew Kensler

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

typedef int int32;
typedef float float32;

// Vector
struct vec3 {
  float32 x, y, z;

  // vector add
  vec3 operator+(const vec3& r) const {
    return vec3(x + r.x, y + r.y, z + r.z);
  }

  // scale
  vec3 operator*(float32 r) const {
    return vec3(x * r, y * r, z * r);
  }

  // dot product
  float32 operator%(const vec3& r) const {
    return x * r.x + y * r.y + z * r.z;
  }

  // default constructor
  vec3() { }

  // Cross product
  vec3 operator^(const vec3& r) const {
    return vec3(y * r.z - z * r.y, z * r.x - x * r.z, x * r.y - y * r.x);
  }

  // constructor
  vec3(float32 a, float32 b, float32 c) {
    x = a;
    y = b;
    z = c;
  }

  // Normalise
  vec3 operator!() const {
    return *this * (1.0 / sqrt(*this % *this));
  }
};

// Data
int32 data[] = {
  247570,
  280596,
  280600,
  249748,
  18578,
  18577,
  231184,
  16,
  16
};

// Random
static inline float32 frand() {
  return (float32) rand() / RAND_MAX;
}

// Trace
static inline int32 trace(const vec3& o, const vec3& d, float32& t, vec3& n) {
  t         = 1e9;
  int32   m = 0;
  float32 p = -o.z / d.z;

  if (0.01 < p) {
    t = p;
    n = vec3(0, 0, 1);
    m = 1;
  }

  for (int32 k = 19; k--;) {
    for (int32 j = 9; j--;) {
      if (data[j] & 1 << k) {
        vec3 p = o + vec3(-k, 0.0, -j - 4.0);
        float32 b = p % d;
        float32 c = p % p - 1.0;
        float32 q = b * b - c;
        if (q > 0) {
          float32 s = -b - sqrt(q);
          if (s < t && s > 0.01) {
            t = s;
            n = !(p + d * t);
            m = 2;
          }
        }
      }
    }
  }
  return m;
}

// Sampling
static inline vec3 sample(const vec3& o, const vec3& d) {
  float32 t;
  vec3 n;

  // Find where the ray intersects the world
  int32 m = trace(o, d, t, n);

  // No intersection, sky
  if (!m) {
    return vec3(0.7, 0.6, 1.0) * pow(1.0 - d.z, 4.0);
  }

  vec3 h = o + d * t;
  vec3 l = !(vec3(9.0 + frand(), 9.0 + frand(), 16.0) + h * -1.0);
  vec3 r = d + n * (n % d * -2);
  float32 b = l % n;
  if (b < 0 || trace(h, l, t, n)) {
    b = 0;
  }

  float32 p = pow(l % r * (b > 0.0), 99.0);
  if (m & 1) {
    h = h * 0.2;
    return ( (int32) (ceil(h.x) + ceil(h.y)) & 1 ? vec3(3.0, 1.0, 1.0) : vec3(3.0, 3.0, 3.0)) * (b * 0.2 + 0.1);
  }
  return vec3(p, p, p) + sample(h, r) * 0.5;
}


// Main
int32 main() {
  printf("P6 512 512 255 ");
  // camera direction
  vec3 g = !vec3(-6.0, -16.0, 0.0);
  vec3 a = !(vec3(0.0, 0.0, 1.0) ^ g) * 0.002;
  vec3 b = !(g ^ a) * 0.002;
  vec3 c = (a + b) * -256 + g;
  for (int32 y = 512; y--;) {
    for (int32 x = 512; x--;) {
      vec3 pixel(13.0, 13.0, 13.0);

      // Cast 64 rays per pixel
      for (int32 r = 64; r--;) {
        vec3 t = a * (frand() - 0.5) * 99.0 + b * (frand() - 0.5) * 99.0;
        pixel = sample(
          vec3(17.0, 16.0, 8.0) + t,
          !(t * -1.0 + (a * (frand() + x) + b * (y + frand()) + c) * 16.0)
        ) * 3.5 + pixel;
      }
      printf("%c%c%c", (int32)pixel.x, (int32)pixel.y, (int32)pixel.z);
    }
  }
  return 0;
}

