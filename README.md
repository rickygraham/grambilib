# grambilib~

An ambisonics library for Pd and Max/MSP (v1.2), written in C. Available cross-platform.

[grambipan~], [grambiman~], and [grambidec~] are a series of ambisonic objects for Pd. They will form a large part of the new grambilib~ library I am finishing this semester, allowing a user to control angle and elevation using an audio-rate signal. 

All objects are written in the C programming language. The externals (collectively) allow a user to manipulate 1st (3d), 2nd (2d), 3rd (2d), and 7th (2d) order ambisonics for mono, stereo, quad, 5.0, hexagonal, octagonal, hexadecagonal and b-format cube (3d) array configurations.

These objects are largely based on my rg.ambi~ abstractions from 2015 (also available from my Github repositories). 

### `[grambipan~]`
A simple ambisonic panner with message and audio-rate controls for azimuth and elevation. Supports 1st (3d), 2nd (2d), and 3rd (2d) order.

### `[grambiman~]`
This object supports 3d b-format manipulations, including *rotate*, *tilt*, *tumble*, *rotate-tilt*, and *rotate-tilt-tumble*. 1st order support only. 

### `[grambidec~]`
A simple ambisonic decoder based on **FuMa** coefficients, including, *mono*, *stereo*, *quad*, *pent*, *hex*, *oct*, *hexadecagonal* and b-format *cube*.
