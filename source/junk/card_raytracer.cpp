// De-golfed version of the Business Card Raytracer by Andrew Kensler

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

typedef int int32;
typedef float float32;

///////////////////////////////////////////////////////////////////////////////

// Vector
struct vec3 {
  float32 x, y, z;

  // default constructor
  vec3() { }

  // constructor
  vec3(float32 a, float32 b, float32 c) {
    x = a;
    y = b;
    z = c;
  }

};

///////////////////////////////////////////////////////////////////////////////

// Data - bitvector of sphere locations
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

///////////////////////////////////////////////////////////////////////////////

static vec3 vec3_add(const vec3& v1, const vec3& v2) {
  return vec3(
    v1.x + v2.x,
    v1.y + v2.y,
    v1.z + v2.z
  );
}


static vec3 vec3_scale(const vec3& v, float32 s) {
  return vec3(
    v.x * s,
    v.y * s,
    v.z * s
  );
}

static vec3 vec3_normalize(const vec3& v) {
  return vec3_scale(v, (1.0 / sqrt(
    (v.x * v.x) +
    (v.y * v.y) +
    (v.z * v.z)
  )));
}

static float32 dot(const vec3& v1, const vec3& v2) {
  return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

static vec3 vec3_cross(const vec3& v1, const vec3& v2) {
  return vec3(
    v1.y * v2.z - v1.z * v2.y,
    v1.z * v2.x - v1.x * v2.z,
    v1.x * v2.y - v1.y * v2.x
  );
}



static const float32 invRM = 1.0 / RAND_MAX;

// Random
static inline float32 frand() {
  return invRM * rand();
}

///////////////////////////////////////////////////////////////////////////////

// Trace
int32 trace(const vec3& o, const vec3& d, float32& t, vec3& n) {
  t         = 1e9;

  // Assume trace hits nothing
  int32   m = 0;
  float32 p = -o.z / d.z;

  // Check if trace maybe hits floor
  if (0.01 < p) {
    t = p,
    n = vec3(0.0, 0.0, 1.0),
    m = 1;
  }

  // Check if trace maybe hits a sphere
  for (int32 k = 19; k--;) {
    for (int32 j = 9; j--;) {
      if (data[j] & 1 << k) {
        vec3 p = vec3_add(o, vec3(-k, 0.0, -j - 4.0));
        float32
          b = dot(p, d),
          c = dot(p, p) - 1.0,
          q = b * b - c
        ;
        if (q > 0) {
          float32 s = -b - sqrt(q);
          if (s < t && s > 0.01) {
            t = s,
            n = vec3_normalize(
              vec3_add(p, vec3_scale(d, t))
            ),
            m = 2;
          }
        }
      }
    }
  }
  return m;
}

///////////////////////////////////////////////////////////////////////////////

// Sampling
vec3 sample(const vec3& o, const vec3& d) {
  float32 t;
  vec3 n;

  // Find where the ray intersects the world
  int32 m = trace(o, d, t, n);

  // Hit nothing? Sky shade
  if (!m) {
    return vec3_scale(
      vec3(0.7, 0.6, 1.0),
      pow(1.0 - d.z, 4.0)
    );
  }

  vec3
    h = vec3_add(o, vec3_scale(d, t)),

    l = vec3_normalize(
      vec3_add(
        vec3(
          9.0 + frand(),
          9.0 + frand(),
          16.0
        ),
        vec3_scale(h, -1.0)
      )
    ),

    r = vec3_add(
      d,
      vec3_scale(
        n,
        dot(n, d) * -2.0
      )
    )
  ;

  float32 b = dot(l, n);
  if (b < 0 || trace(h, l, t, n)) {
    b = 0;
  }

  float32 p = pow(dot(l, r) * (b > 0.0), 99.0);

  // Hit the floor plane
  if (m & 1) {
    h = vec3_scale(h, 0.2);
    return vec3_scale(
      (
        // Compute check colour
        (int32) (ceil(h.x) + ceil(h.y)) & 1 ?
        vec3(3.0, 1.0, 1.0) : // red
        vec3(3.0, 3.0, 3.0)   // white
      ),
      (b * 0.2 + 0.1)
    );
  }

  // Hit a sphere
  return vec3_add(
    vec3(p, p, p),
    vec3_scale(
      sample(h, r),
      0.5
    )
  );
}

///////////////////////////////////////////////////////////////////////////////

// Main
int32 main() {
  printf("P6 512 512 255 ");
  // camera direction
  vec3
    g = vec3_normalize(
      vec3(-6.0, -16.0, 0.0)
    ),

    a = vec3_scale(
      vec3_normalize(
        vec3_cross(
          vec3(0.0, 0.0, 1.0),
          g
        )
      ),
      0.002
    ),

    b = vec3_scale(
      vec3_normalize(
        vec3_cross(g, a)
      ),
      0.002
    ),

    c = vec3_add(
      vec3_scale(
        vec3_add(a, b),
        -256.0
      ),
      g
    )
  ;
  for (int32 y = 512; y--;) {
    for (int32 x = 512; x--;) {

      // Use a vector for the pixel
      vec3 pixel(13.0, 13.0, 13.0);

      // Cast 64 rays per pixel
      for (int32 r = 64; r--;) {
        vec3 t = vec3_add(
          vec3_scale(a, (frand() - 0.5) * 99.0),
          vec3_scale(b, (frand() - 0.5) * 99.0)
        );
        pixel  = vec3_add(
          vec3_scale(
            sample(
              vec3_add(
                vec3(17.0, 16.0, 8.0),
                t
              ),
              vec3_normalize(
                vec3_add(
                  vec3_scale(t, -1.0),
                  vec3_scale(
                    vec3_add(
                      vec3_scale(a, frand() + x),
                      vec3_add(
                        vec3_scale(b, frand() + y),
                        c
                      )
                    ),
                    16.0
                  )
                )
              )
            ),
            3.5
          ),
          pixel
        );
      }
      printf("%c%c%c", (int32)pixel.x, (int32)pixel.y, (int32)pixel.z);
    }
  }
  return 0;
}

