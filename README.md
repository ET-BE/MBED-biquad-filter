# Biquad Filters

Simply library that contains a second order digital filter (biquad filter) class, including Butterworth computation functions.

Class was originally written for the K64F with MBED-OS. However, the code should be generic enough for any platform.

## Example

```c++

BiquadFilter filter(1000.0f, 30.0f, TYPE_LOW_PASS);

float y = filter.sample(x);
```
