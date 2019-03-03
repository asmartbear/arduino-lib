
// Compute cos(a) substantially faster (but less accurate) than the built-in.
// Range is accurate within 0.1%.
float cos_fast(float a);

// Compute sin(a) substantially faster (but less accurate) than the built-in.
// Range is accurate within 0.1%.
float sin_fast(float a);

// Compute both cos(x) and sin(x), faster (but less accurate) than the built-in
// of either one of them. Range is accurate within 0.1%.
void cos_sin(float a, float *cos_result, float *sin_result);
