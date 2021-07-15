#ifndef BIQUAD_FILTER_H_
#define BIQUAD_FILTER_H_

#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846f
#endif

/**
 * Biquad filter class.
 *
 * A biquad is a simple 2nd order digital filter.
 * This class includes creation functions for Butterworth 
 * filters.
 */
class BiquadFilter {
    
public:

    enum TYPE {
        TYPE_LOW_PASS = 0,
        TYPE_HIGH_PASS,
    };

    /**
     * Default constructor.
     */
    BiquadFilter(void);

    /**
     * Construct filter with computed coefficients.
     * 
     * @param Fs    Sample frequency
     * @param Fc    Cut-off frequency of filter
     * @param type  Type of filter (see TYPE enum)
     */
    BiquadFilter(float Fs, float Fc, TYPE type);

    /**
     * Construct filter with pre-computed coefficients.
     *
     * @param a     Numerator (normalized)
     * @param b     Denominator
     */
    BiquadFilter(float a[2], float b[3]);
    
    /**
     * Set new filter coefficients.
     */
    void setFilter(float a[2], float b[3]);
    void setFilter(float a1, float a2, float b0, float b1, float b2);
    void setFilter();

    /**
     * Set butterworth lowpass filter.
     */
    void setFilterButterLowpass(float Fs, float Fc);

    /**
     * Set butterworth highpass filter.
     */
    void setFilterButterHighpass(float Fs, float Fc);
    
    /**
     * Take a new sample, returned filtered value.
     */
    float sample(float x);

    /**
     * Reset filter to a value (0 by default).
     */
    void reset(float x = 0.0f);
    
private:

    /**
     * Reset internal states
     */
    void init();

    float a[2], b[3];
    float w[3];
    
};

#endif
