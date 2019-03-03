
#define PI_2 HALF_PI

// Compute cos(a) substantially faster (but less accurate) than the built-in.
// Domain is the interval [-2pi,2pi]; range is accurate within 0.1%.
float cos_fast(float a) {
  int positive = 1;
  float r;

  // Only positive angles
  if (a < 0.0) {
    a = -a;
  }
  
  // Map multiples of 2π back to [0,2π]
  if (a > TWO_PI) {
	  a = fmod(a, TWO_PI);		// this function isn't fast, but there's no alternative; avoid by supplying angles inside [-2π,2π].
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
  // accurate. The worse-case accuracy is +0.0001 from cos(x).  It's important to
  // use the exact point so that the resulting function is continuous, even if
  // it has a slight cusp.
  if (a < 0.653395) {
    a = a * a;
    r = 1.0 + a * (-0.5 + a * 0.0416666666666);
    return positive ? r : -r;
  }

  // Use the Taylor Series about a=pi/2.
  a -= PI_2;
  float a_sq = a*a;
  r = a * (-1.0 + a_sq * (0.1666666666666 - a_sq * 0.00833333333333));
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

#define MAX_TEST_ANGLE PI_2
#define N_STEPS 100
#define ANG_STEP (MAX_TEST_ANGLE / N_STEPS)
#define ERR_THRESHOLD 0.0001

int main() {
  float a;
  float actual, estimate, err;

  printf("Hello, World!\n");
  for (a = 0; a < MAX_TEST_ANGLE; a += ANG_STEP) {
    actual = cos(a);
    estimate = cos_fast(a);
    err = fabs(estimate - actual);
	if (err > ERR_THRESHOLD) {
		printf("cos(%8.4f) = %8.4f ≈ %8.4f, Δ%8.4f\n", a, actual, estimate, err);
	}
  }
  
  return 0;
}

#endif
