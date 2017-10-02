// De-golfed version of the Business Card Raytracer by Andrew Kensler
//
// Changes
//   * Renaming of types, functions and variables
//   * Replaced operator overloads with vanilla functions
//   * Added functions for explicit vector subtract which was realised
//     previously as v1 + (v2 * -1);
//   * Optimised away a pow() call for the sky gradient
//   * Moved the specular calculation to the point where the ray definitely
//     intersects a sphere.

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

typedef int int32;
typedef float float32;

///////////////////////////////////////////////////////////////////////////////

// Vector class. Replaced operator overloads with
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

const vec3 camera_dir(
  -6.0, -16.0, 0.0
);

const vec3 focal_point(
  17.0, 16.0, 8.0
);

const vec3 normal_up(
  0.0, 0.0, 1.0
);

const vec3 sky_rgb(
  0.7, 0.6, 1.0
);

const vec3 floor_red_rgb(
  3.0, 1.0, 1.0
);

const vec3 floor_white_rgb(
  3.0, 1.0, 1.0
);
///////////////////////////////////////////////////////////////////////////////

#ifdef NO_PASS_BY_REF
typedef const vec3 cvr3;
#else
typedef const vec3& cvr3;
#endif

///////////////////////////////////////////////////////////////////////////////

// Data - bitvector of sphere locations, 1 means a sphere, 0 means empty space
//
int32 data[] = {
  247570, // 0111100011100010010
  280596, // 1000100100000010100
  280600, // 1000100100000011000
  249748, // 0111100111110010100
  18578,  // 0000100100010010010
  18577,  // 0000100100010010001
  231184, // 0111000011100010000
  16,     // 0000000000000010000
  16      // 0000000000000010000
};

///////////////////////////////////////////////////////////////////////////////

// Sum two vec3
static inline vec3 vec3_add(cvr3 v1, cvr3 v2) {
  return vec3(
    v1.x + v2.x,
    v1.y + v2.y,
    v1.z + v2.z
  );
}

// Subtract two vec3
static inline vec3 vec3_sub(cvr3 v1, cvr3 v2) {
  return vec3(
    v1.x - v2.x,
    v1.y - v2.y,
    v1.z - v2.z
  );
}

// Scale a vec3 by a float
static inline vec3 vec3_scale(cvr3 v, float32 s) {
  return vec3(
    v.x * s,
    v.y * s,
    v.z * s
  );
}

// Get a normalised vec3
static inline vec3 vec3_normalize(cvr3 v) {
  return vec3_scale(v, (1.0 / sqrt(
    (v.x * v.x) +
    (v.y * v.y) +
    (v.z * v.z)
  )));
}

// Get the dot product of two vec3
static inline float32 dot(cvr3 v1, cvr3 v2) {
  return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

// Get the cross product for two vec3
static inline vec3 vec3_cross(cvr3 v1, cvr3 v2) {
  return vec3(
    v1.y * v2.z - v1.z * v2.y,
    v1.z * v2.x - v1.x * v2.z,
    v1.x * v2.y - v1.y * v2.x
  );
}

static const float32 invRM = 1.0 / RAND_MAX;

// Get a random number in the range 0.0 - 1.0
static inline float32 frand() {
  return invRM * rand();
}

///////////////////////////////////////////////////////////////////////////////

// Trace
int32 trace(cvr3 origin, cvr3 direction, float32& distance, vec3& normal) {
  distance         = 1e9;

  // Assume trace hits nothing
  int32   material = 0;
  float32 p = -origin.z / direction.z;

  // Check if trace maybe hits floor
  if (0.01 < p) {
    distance = p,
    normal   = normal_up,
    material = 1;
  }

  // Check if trace maybe hits a sphere
  for (int32 k = 19; k--;) {
    for (int32 j = 9; j--;) {
      if (data[j] & 1 << k) {
        vec3 p = vec3_sub(
          origin,
          vec3(k, 0.0, j + 4.0) // Sphere coordinate
        );

        float32
          b = dot(p, direction),
          eye_offset = dot(p, p) - 1.0,
          q = b * b - eye_offset
        ;
        if (q > 0) {
          float32 sphere_distance = -b - sqrt(q);
          if (sphere_distance < distance && sphere_distance > 0.01) {
            distance = sphere_distance,
            normal   = vec3_normalize(
              vec3_add(p, vec3_scale(direction, distance))
            ),
            material = 2; // Returning here is fast, but we'd get z fighting
          }
        }
      }
    }
  }

  return material;
}

///////////////////////////////////////////////////////////////////////////////

// Sampling
vec3 sample(cvr3 origin, cvr3 direction) {
  float32 distance;
  vec3 normal;

  // Find where the ray intersects the world
  int32 material = trace(origin, direction, distance, normal);

  // Hit nothing? Sky shade
  if (!material) {
    float32 gradient = 1.0 - direction.z;
    gradient *= gradient;
    gradient *= gradient;
    return vec3_scale(
      sky_rgb, // Blueish sky colour
      gradient
    );
  }

  vec3
    intersection = vec3_add(origin, vec3_scale(direction, distance)),

    // Calculate the lighting vector
    light = vec3_normalize(
      vec3_sub(
        vec3( // lighting direction, plus a bit of randomness to generate soft shadows.
          9.0 + frand(),
          9.0 + frand(),
          16.0
        ),
        intersection
      )
    ),

    half_vector = vec3_add(
      direction,
      vec3_scale(
        normal,
        dot(normal, direction) * -2.0
      )
    )
  ;

  // Calculate the lambertian illumuination factor
  float32 lambertian = dot(light, normal);
  if (lambertian < 0 || trace(intersection, light, distance, normal)) {
    lambertian = 0; // in shadow
  }

  // Hit the floor plane
  if (material & 1) {
    intersection = vec3_scale(intersection, 0.2);
    return vec3_scale(
      (
        // Compute check colour based on the position
        (int32) (ceil(intersection.x) + ceil(intersection.y)) & 1 ?
        floor_red_rgb : // red
        floor_white_rgb   // white
      ),
      (lambertian * 0.2 + 0.1)
    );
  }

  // Compute the specular highlight power
  float32 specular = pow(dot(light, half_vector) * (lambertian > 0.0), 99.0);

  // Hit a sphere
  return vec3_add(
    vec3(specular, specular, specular),
    vec3_scale(
      sample(intersection, half_vector),
      0.5
    )
  );
}

///////////////////////////////////////////////////////////////////////////////

// Main
int32 main() {
  int image_size = 512;
  printf("P6 %d %d 255 ", image_size, image_size);

  // camera direction vectors
  vec3
    camera_forward = vec3_normalize( // Unit forwards
      camera_dir
    ),

    camera_up = vec3_scale( // Unit up - Z is up in this system
      vec3_normalize(
        vec3_cross(
          normal_up,
          camera_forward
        )
      ),
      0.002
    ),

    camera_right = vec3_scale( // Unit right
      vec3_normalize(
        vec3_cross(camera_forward, camera_up)
      ),
      0.002
    ),

    eye_offset = vec3_add( // Offset frm eye to coner of focal plane
      vec3_scale(
        vec3_add(camera_up, camera_right),
        -(image_size >> 1)
      ),
      camera_forward
    )
  ;
  for (int32 y = image_size; y--;) {
    for (int32 x = image_size; x--;) {

      // Use a vector for the pixel. The values here are in the range 0.0 - 255.0 rather than the 0.0 - 1.0
      vec3 pixel(13.0, 13.0, 13.0);

      // Cast 64 rays per pixel for sampling
      for (int32 ray_count = 64; ray_count--;) {

        // Random delta to be added for depth of field effects
        vec3 delta = vec3_add(
          vec3_scale(camera_up,    (frand() - 0.5) * 99.0),
          vec3_scale(camera_right, (frand() - 0.5) * 99.0)
        );

        // Accumulate the sample result into the current pixel
        pixel  = vec3_add(
          vec3_scale(
            sample(
              vec3_add(
                focal_point,
                delta
              ),
              vec3_normalize(
                vec3_sub(
                  vec3_scale(
                    vec3_add(
                      vec3_scale(camera_up, frand() + x),
                      vec3_add(
                        vec3_scale(camera_right, frand() + y),
                        eye_offset
                      )
                    ),
                    16.0
                  ),
                  delta
                )
              )
            ),
            3.5
          ),
          pixel
        );
      }

      // Convert to integers and push out to ppm outpu stream
      printf("%c%c%c", (int32)pixel.x, (int32)pixel.y, (int32)pixel.z);
    }
  }
  return 0;
}

