---
layout: post
title: Ongoing load cell testing
---

For once, I'll put the conclusions above the fold. First, testing has convinced me that 25x150mm or 27x150mm is the right size tube. Given the cantilever-style mount, measuring more precisely than about 0.07 grams seems ill-advised. Second, the ideal cylinder mass seems to me to be about 100 grams, so that the observed weights (for a 27mm cylinder) are on the order of 10-20 grams across a 1.000 to 1.100 gravity range. Third, even the 500g load cell is probably too large a range, and I think a 200g cell probably hits the sweet spot. Finally, temperature compensation for the load cell is going to be a necessity.

And now for the detail!

### Volume
The volume of the cylinder directly determines the weight change per gravity point. The bigger the cylinder, the more it displaces; the more it displaces, the larger the mass of the displaced liquid for a given density. For an 85cc volume (just about the volume of the 27mm cylinder), one gravity point difference in the density of the liquid means a difference of 0.085 grams. That's a little under three times the weight of a single grain of long rice.

To put it another way, the entire range of measurement is about as much as a US quarter and penny, or a single two-euro coin. These are extremely fine measurements, which I expect are already pushing these inexpensive sensors to their limits. Going much finer seems like a bad idea.

### Cylinder mass
The mass of the cylinder is less important, except in that it may affect the load cell's response because of hysteresis and creep effects. (Hysteresis means that the reading for 50g is different if the baseline is different; reading(50 - 0g) is different from reading(100 - 50g). Creep means that, given a constant load, the reading changes over time.) That's why I want to keep the mass low: a 100g, 85cc cylinder puts a load of at most 15g on the load cell when in use. On a 200g cell, 15g should be light enough to avoid creep effects. Calibrating in water will avoid hysteresis affects.

### Load cell rating
The 500g load cell works fine to measure a 20-gram range, which happily corresponds to about 20,000 load cell output units. The maximal moment-to-moment noise of about ±50 (over two-second readings) seems sufficiently low that going to an 8.5-gram range (8500 units) would also work. That said, a 200g load cell with an 8.5-gram weight delta would hit the required sensitivity with roughly the same output range as the 500g load cell and a 20-gram weight delta. The noise goes from about 1.1% of the output range to 0.4% with the smaller cell.

### Temperature compensation
Test run from 7/9/18, 20,000-unit calibration range with 128000 top-end, 20g weight, sans temperature compensation (gray line gravity, red line temperature):

Test run from 7/10/18, 20,000-unit calibration range with 135000 top-end, 20g weight, with temperature compensation (gray line gravity, red line temperature):

To make the results even more dramatic, when the 7/9/18 line smooths at the end of 7/10/18, that's when I was testing temperature compensation. A linear adjustment of ((68F - observedTemp) * 0.000935) applied to the gravity reading seems to work.
