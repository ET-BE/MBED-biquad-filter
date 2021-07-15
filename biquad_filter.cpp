#include "biquad_filter.h"

// Constructor (with arrays)
BiquadFilter::BiquadFilter(float a_[2], float b_[3]) {

    setFilter(a_, b_);
    
    init();
}

// Constructor (compute)
BiquadFilter::BiquadFilter(float Fs, float Fc, TYPE type) {

    switch (type) {
    case TYPE_LOW_PASS:
        setFilterButterLowpass(Fs, Fc);
        break;

    case TYPE_HIGH_PASS:
        setFilterButterHighpass(Fs, Fc);
        break;
    }
    
    init();
}

// Constructor (empty)
BiquadFilter::BiquadFilter(void) {

    setFilter();
    
    init();
}

// General constructor stuff
void BiquadFilter::init()
{
    w[0] = 0.0f; // w[0] = w[n - 2]
    w[1] = 0.0f; // w[1] = w[n - 1]
    w[2] = 0.0f; // w[2] = w[n]
}

// Update filter
void BiquadFilter::setFilter(float a_[2], float b_[3])
{
    setFilter(a_[0], a_[1], b_[0], b_[1], b_[2]);
}
void BiquadFilter::setFilter(float a1, float a2, float b0, float b1, float b2) {
    a[0] = a1;
    a[1] = a2;
    b[0] = b0;
    b[1] = b1;
    b[2] = b2;
}
void BiquadFilter::setFilter() {
    a[0] = 0.0f;
    a[1] = 0.0f;
    b[0] = 0.0f;
    b[1] = 0.0f;
    b[2] = 0.0f;
}

// Run the butter algorithm
void BiquadFilter::setFilterButterLowpass(float Fs, float Fc)
{
    if (Fc >= Fs / 2.0f) {
        setFilter();
        return;
    }
    
    const float Q = sqrtf(0.5f);
    
    float K = tanf(M_PI * Fc / Fs);

    float norm = 1 / (1 + K / Q + K * K);
    
    b[0] = K * K * norm;
    b[1] = 2.0f * b[0];
    b[2] = b[0];
    a[0] = 2.0f * (K * K - 1.0f) * norm;
    a[1] = (1.0f - K / Q + K * K) * norm;
}

// Run the butter algorithm
void BiquadFilter::setFilterButterHighpass(float Fs, float Fc)
{
    if (Fc >= Fs / 2.0f) {
        setFilter();
        return;
    }
    
    const float Q = sqrtf(0.5f);
    
    float K = tanf(M_PI * Fc / Fs);

    float norm = 1 / (1 + K / Q + K * K);
    
    b[0] = norm;
    b[1] = -2.0f * b[0];
    b[2] = b[0];
    a[0] = 2.0f * (K * K - 1.0f) * norm;
    a[1] = (1.0f - K / Q + K * K) * norm;
}

// Get new filtered value
float BiquadFilter::sample(float x)
{
    // Sample with direct form II

    // Scooch w array
    w[0] = w[1];
    w[1] = w[2];
    
    // Apply new input
    w[2] = x - a[0] * w[1] - a[1] * w[0];
    
    // Return y
    return b[0] * w[2] + b[1] * w[1] + b[2] * w[0];
}

// Reset
void BiquadFilter::reset(float x) {

    w[0] = w[1] = w[2] = x / (1.0f + a[0] + a[1]);
}