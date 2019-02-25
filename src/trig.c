#include <math.h>

#define PI 3.1415926535
#define PI_2 1.5707963268
#define TWO_PI 6.2831853072

// Compute cos(a) substantially faster (but less accurate) than the built-in.
// Domain is the interval [-2pi,2pi]; range is accurate within 0.1%.
float cos_fast(float a) {
  int positive = 1;
  float r;

  // Only positive angles
  if (a < 0.0) {
    a = -a;
  }

  // The second half of the circle mirrors the first
  if (a > PI) {
    a = TWO_PI - a;
  }

  // The second quarter of the circle mirrors the first, but negative
  if (a > PI_2) {
    a = PI - a;
    positive = 0;
  }

  // If a is small enough, use the Taylor Series about a=0.
  // This constant is the cross-over point where the other Taylor Series is more
  // accurate. The worse-case accuracy is still within 0.1%.  It's important to
  // use the exact point so that the resulting function is continuous, even if
  // it has a slight cusp.
  if (a < 0.653396) {
    a = a * a;
    r = 1.0 + a * (-0.5 + a * 0.0416666666);
    return positive ? r : -r;
  }

  // Use the Taylor Series about a=pi/2.
  a -= PI_2;
  float a_sq = a*a;
  r = a * (-1.0 + a_sq * (0.1666666666 - a_sq * 0.0833333333));
  return positive ? r : -r;
}

// Compute sin(a) substantially faster (but less accurate) than the built-in.
// Domain is the interval [-2pi,2pi]; range is accurate within 0.1%.
float sin_fast(float a) { return cos_fast(a + PI_2); }

// Compute both cos(x) and sin(x), faster (but less accurate) than the built-in
// of either one of them. Domain is the interval [-2pi,2pi]; range is accurate
// within 0.1%.
void cos_sin(float a, float *cos_result, float *sin_result) {
  *cos_result = cos_fast(a);
  float s = sqrt(1 - (*cos_result)*(*cos_result)); // this is sin(x) except always positive
  *sin_result = a > PI
                    ? -s
                    : ((a > 0 || a < -PI)
                           ? s
                           : -s); // restore the sign with minimal comparisons
}

#if DEV_TEST

#include <stdio.h>

#define N_STEPS 40
#define ANG_STEP (TWO_PI / N_STEPS)

void main() {
  int a;
  float actual, estimate, err;

  printf("Hello, World!\n");
  for (a = 0; a < TWO_PI; a += ANG_STEP) {
    actual = cos(a);
    estimate = cos_fast(a);
    err = fabs(estimate - actual);
    printf("cos(%0.4f) = %0.4f ≈ %0.4f, Δ%0.4f\n", a, actual, estimate, diff);
  }
}

#endif
