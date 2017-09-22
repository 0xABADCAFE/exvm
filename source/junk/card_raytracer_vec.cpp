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

typedef float32 vec4f __attribute__ ((vector_size (16))) __attribute__ ((aligned (16)));

///////////////////////////////////////////////////////////////////////////////


typedef vec4f cv4f;

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

// Sum two vec4f
static inline vec4f vec4f_add(cv4f v1, cv4f v2) {
  return v1 + v2;
}

// Subtract two vec4f
static inline vec4f vec4f_sub(cv4f v1, cv4f v2) {
  return v1 - v2;
}

// Scale a vec4f by a float
static inline vec4f vec4f_scale(cv4f v, float32 s) {
  return v * s;
}

// Get a normalised vec4f
static inline vec4f vec4f_normalize(cv4f v) {
  return vec4f_scale(v, (1.0 / sqrt(
    (v[0] * v[0]) +
    (v[1] * v[1]) +
    (v[2] * v[2])
  )));
}

// Get the dot product of two vec4f
static inline float32 dot(cv4f v1, cv4f v2) {
  return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
}

// Get the cross product for two vec4f
static inline vec4f vec4f_cross(cv4f v1, cv4f v2) {
  vec4f r = {
    v1[1] * v2[2] - v1[2] * v2[1],
    v1[2] * v2[0] - v1[0] * v2[2],
    v1[0] * v2[1] - v1[1] * v2[0],
    0.0
  };
  return r;
}

static const float32 invRM = 1.0 / RAND_MAX;

// Get a random number in the range 0.0 - 1.0
static inline float32 frand() {
  return invRM * rand();
}

///////////////////////////////////////////////////////////////////////////////

static vec4f up = {0.0, 0.0, 1.0, 0.0};

// Trace
int32 trace(cv4f origin, cv4f direction, float32& distance, vec4f& normal) {
  distance         = 1e9;

  // Assume trace hits nothing
  int32   material = 0;
  float32 p = -origin[2] / direction[2];

  // Check if trace maybe hits floor
  if (0.01 < p) {
    distance = p,
    normal   = up,
    material = 1;
  }

  // Check if trace maybe hits a sphere
  for (int32 k = 19; k--;) {
    for (int32 j = 9; j--;) {
      if (data[j] & 1 << k) {
        vec4f sphere_coord = { k, 0.0, j + 4.0, 0.0 };
        vec4f p = vec4f_sub(
          origin,
          sphere_coord
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
            normal   = vec4f_normalize(
              vec4f_add(p, vec4f_scale(direction, distance))
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
vec4f sample(cv4f origin, cv4f direction) {
  float32 distance;
  vec4f normal;

  static vec4f red   = { 3.0, 1.0, 1.0, 0.0 };
  static vec4f white = { 3.0, 3.0, 3.0, 0.0 };
  static vec4f sky   = { 0.7, 0.6, 1.0, 0.0 };

  // Find where the ray intersects the world
  int32 material = trace(origin, direction, distance, normal);

  // Hit nothing? Sky shade
  if (!material) {
    float32 gradient = 1.0 - direction[2];
    gradient *= gradient;
    gradient *= gradient;
    return vec4f_scale(
      sky, // Blueish sky colour
      gradient
    );
  }

  vec4f
    intersection = vec4f_add(origin, vec4f_scale(direction, distance)),

    light_dir = {
      9.0 + frand(),
      9.0 + frand(),
      16.0,
      0.0
    },

    // Calculate the lighting vector
    light = vec4f_normalize(
      vec4f_sub(
        light_dir,
        intersection
      )
    ),

    half_vector = vec4f_add(
      direction,
      vec4f_scale(
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
    intersection = vec4f_scale(intersection, 0.2);
    return vec4f_scale(
      (
        // Compute check colour based on the position
        (int32) (ceil(intersection[0]) + ceil(intersection[1])) & 1 ?
        red :
        white   // white
      ),
      (lambertian * 0.2 + 0.1)
    );
  }

  // Compute the specular highlight power
  float32 specular = pow(dot(light, half_vector) * (lambertian > 0.0), 99.0);

  vec4f specular_colour = { specular, specular, specular, 0.0 };

  // Hit a sphere
  return vec4f_add(
    specular_colour,
    vec4f_scale(
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
  vec4f
    camera_dir = {-6.0, -16.0, 0.0, 0.0 },

    camera_forward = vec4f_normalize( // Unit forwards
      camera_dir
    ),

    camera_up = vec4f_scale( // Unit up - Z is up in this system
      vec4f_normalize(
        vec4f_cross(
          up,
          camera_forward
        )
      ),
      0.002
    ),

    camera_right = vec4f_scale( // Unit right
      vec4f_normalize(
        vec4f_cross(camera_forward, camera_up)
      ),
      0.002
    ),

    eye_offset = vec4f_add( // Offset frm eye to coner of focal plane
      vec4f_scale(
        vec4f_add(camera_up, camera_right),
        -(image_size >> 1)
      ),
      camera_forward
    ),

    focal_point = {17.0, 16.0, 8.0, 0.0 }
  ;
  for (int32 y = image_size; y--;) {
    for (int32 x = image_size; x--;) {

      // Use a vector for the pixel. The values here are in the range 0.0 - 255.0 rather than the 0.0 - 1.0
      vec4f pixel = {13.0, 13.0, 13.0, 0.0};

      // Cast 64 rays per pixel for sampling
      for (int32 ray_count = 64; ray_count--;) {

        // Random delta to be added for depth of field effects
        vec4f delta = vec4f_add(
          vec4f_scale(camera_up, (frand() - 0.5) * 99.0),
          vec4f_scale(camera_right, (frand() - 0.5) * 99.0)
        );

        // Accumulate the sample result into the current pixel
        pixel  = vec4f_add(
          vec4f_scale(
            sample(
              vec4f_add(
                focal_point,
                delta
              ),
              vec4f_normalize(
                vec4f_sub(
                  vec4f_scale(
                    vec4f_add(
                      vec4f_scale(camera_up, frand() + x),
                      vec4f_add(
                        vec4f_scale(camera_right, frand() + y),
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
      printf("%c%c%c", (int32)pixel[0], (int32)pixel[1], (int32)pixel[2]);
    }
  }
  return 0;
}

