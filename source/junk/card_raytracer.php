<?php

// De-golfed version of the Business Card Raytracer by Andrew Kensler



///////////////////////////////////////////////////////////////////////////////

// Vector class. Replaced operator overloads with
class vec3 {
  public $x, $y, $z;

  // constructor
  public function __construct(float $a, float $b, float $c) {
    $this->x = $a;
    $this->y = $b;
    $this->z = $c;
  }

  // Sum two vec3
  public static function add(vec3 $v1, vec3 $v2) : vec3 {
    return new vec3(
      $v1->x + $v2->x,
      $v1->y + $v2->y,
      $v1->z + $v2->z
    );
  }

  // Subtract two vec3
  public static function sub(vec3 $v1, vec3 $v2) : vec3 {
    return new vec3(
      $v1->x - $v2->x,
      $v1->y - $v2->y,
      $v1->z - $v2->z
    );
  }

  // Scale a vec3 by a float
  public static function scale(vec3 $v, float $s) : vec3 {
    return new vec3(
      $v->x * $s,
      $v->y * $s,
      $v->z * $s
    );
  }

  // Get a normalised vec3
  public static function normalize(vec3 $v) : vec3 {
    return self::scale($v, (1.0 / sqrt(
      ($v->x * $v->x) +
      ($v->y * $v->y) +
      ($v->z * $v->z)
    )));
  }

  // Get the dot product of two vec3
  public static function dot(vec3 $v1, vec3 $v2) : float {
    return $v1->x * $v2->x + $v1->y * $v2->y + $v1->z * $v2->z;
  }

  // Get the cross product for two vec3
  public static function cross(vec3 $v1, vec3 $v2) : vec3 {
    return new vec3(
      $v1->y * $v2->z - $v1->z * $v2->y,
      $v1->z * $v2->x - $v1->x * $v2->z,
      $v1->x * $v2->y - $v1->y * $v2->x
    );
  }

};

///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////

// Data - bitvector of sphere locations, 1 means a sphere, 0 means empty space
//
$data = [
  247570, // 0111100011100010010
  280596, // 1000100100000010100
  280600, // 1000100100000011000
  249748, // 0111100111110010100
  18578,  // 0000100100010010010
  18577,  // 0000100100010010001
  231184, // 0111000011100010000
  16,     // 0000000000000010000
  16      // 0000000000000010000
];

///////////////////////////////////////////////////////////////////////////////

$invRM = 1.0 / (float)getrandmax();

// Get a random number in the range 0.0 - 1.0
function frand() : float {
  global $invRM;
  return $invRM * rand();
}

///////////////////////////////////////////////////////////////////////////////

// Trace
function trace(vec3 $origin, vec3 $direction, &$distance, vec3& $normal) : int {
  global $data;

  $distance = 1e9;

  // Assume trace hits nothing
  $material = 0;
  $p = -$origin->z / $direction->z;

  // Check if trace maybe hits floor
  if (0.01 < $p) {
    $distance = $p;
    $normal   = new vec3(0.0, 0.0, 1.0);
    $material = 1;
  }

  // Check if trace maybe hits a sphere
  for ($k = 19; $k--;) {
    for ($j = 9; $j--;) {
      if ($data[$j] & 1 << $k) {
        $p = vec3::sub(
          $origin,
          new vec3($k, 0.0, $j + 4.0) // Sphere coordinate
        );

        $b = vec3::dot($p, $direction);
        $eye_offset = vec3::dot($p, $p) - 1.0;
        $q = $b * $b - $eye_offset;

        if ($q > 0) {
          $sphere_distance = -$b - sqrt($q);
          if ($sphere_distance < $distance && $sphere_distance > 0.01) {
            $distance = $sphere_distance;
            $normal   = vec3::normalize(
              vec3::add($p, vec3::scale($direction, $distance))
            );
            $material = 2; // Returning here is fast, but we'd get z fighting
          }
        }
      }
    }
  }
  return $material;
}

///////////////////////////////////////////////////////////////////////////////

// Sampling
function sample(vec3 $origin, vec3 $direction) : vec3 {

  $normal = new vec3(0.0, 0.0, 0.0);

  // Find where the ray intersects the world
  $material = trace($origin, $direction, $distance, $normal);

  // Hit nothing? Sky shade
  if (!$material) {
    $gradient = 1.0 - $direction->z;
    $gradient *= $gradient;
    $gradient *= $gradient;
    return vec3::scale(
      new vec3(0.7, 0.6, 1.0), // Blueish sky colour
      $gradient
    );
  }

  $intersection = vec3::add($origin, vec3::scale($direction, $distance));

  // Calculate the lighting vector
  $light = vec3::normalize(
    vec3::sub(
      new vec3( // lighting direction, plus a bit of randomness to generate soft shadows.
        9.0 + frand(),
        9.0 + frand(),
        16.0
      ),
      $intersection
    )
  );

  $half_vector = vec3::add(
    $direction,
    vec3::scale(
      $normal,
      vec3::dot($normal, $direction) * -2.0
    )
  );

  // Calculate the lambertian illumuination factor
  $lambertian = vec3::dot($light, $normal);
  if ($lambertian < 0 || trace($intersection, $light, $distance, $normal)) {
    $lambertian = 0; // in shadow
  }

  // Hit the floor plane
  if ($material & 1) {
    $intersection = vec3::scale($intersection, 0.2);
    return vec3::scale(
      (
        // Compute check colour based on the position
        (int) (ceil($intersection->x) + ceil($intersection->y)) & 1 ?
        new vec3(3.0, 1.0, 1.0) : // red
        new vec3(3.0, 3.0, 3.0)   // white
      ),
      ($lambertian * 0.2 + 0.1)
    );
  }

  // Compute the specular highlight power
  $specular = pow(vec3::dot($light, $half_vector) * ($lambertian > 0.0), 99.0);

  // Hit a sphere
  return vec3::add(
    new vec3($specular, $specular, $specular),
    vec3::scale(
      sample($intersection, $half_vector),
      0.5
    )
  );
}

///////////////////////////////////////////////////////////////////////////////

// Main
function main() {
  $image_size = 512;
  printf("P6 %d %d 255 ", $image_size, $image_size);

  // camera direction vectors
  $camera_forward = vec3::normalize( // Unit forwards
    new vec3(-6.0, -16.0, 0.0)
  );

  $camera_up = vec3::scale( // Unit up - Z is up in this system
    vec3::normalize(
      vec3::cross(
        new vec3(0.0, 0.0, 1.0),
        $camera_forward
      )
    ),
    0.002
  );

  $camera_right = vec3::scale( // Unit right
    vec3::normalize(
      vec3::cross($camera_forward, $camera_up)
    ),
    0.002
  );

  $eye_offset = vec3::add( // Offset frm eye to coner of focal plane
    vec3::scale(
      vec3::add($camera_up, $camera_right),
      -($image_size >> 1)
    ),
    $camera_forward
  );
  for ($y = $image_size; $y--;) {
    for ($x = $image_size; $x--;) {

      // Use a vector for the pixel. The values here are in the range 0.0 - 255.0 rather than the 0.0 - 1.0
      $pixel = new vec3(13.0, 13.0, 13.0);

      // Cast 64 rays per pixel for sampling
      for ($ray_count = 64; $ray_count--;) {

        // Random delta to be added for depth of field effects
        $delta = vec3::add(
          vec3::scale($camera_up, (frand() - 0.5) * 99.0),
          vec3::scale($camera_right, (frand() - 0.5) * 99.0)
        );

        // Accumulate the sample result into the current pixel
        $pixel  = vec3::add(
          vec3::scale(
            sample(
              vec3::add(
                new vec3(17.0, 16.0, 8.0), // Focal point
                $delta
              ),
              vec3::normalize(
                vec3::sub(
                  vec3::scale(
                    vec3::add(
                      vec3::scale($camera_up, frand() + $x),
                      vec3::add(
                        vec3::scale($camera_right, frand() + $y),
                        $eye_offset
                      )
                    ),
                    16.0
                  ),
                  $delta
                )
              )
            ),
            3.5
          ),
          $pixel
        );
      }

      // Convert to integers and push out to ppm outpu stream
      printf("%c%c%c", (int)$pixel->x, $pixel->y, $pixel->z);
    }
  }
}

main();

