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

I'm running an experiment now with the 500g cell and an 8.5g weight delta. Temperature-corrected readings range from about 1.0565 to 1.058. 0.0015 isn't bad as error goes, but it's still unnecessarily high, and leads to an amplification of the temperature effect (a percentage of the cell's capacity, not the reading).

### Temperature compensation
Test run from 7/9/18, 20,000-unit calibration range with 1.097 actual reading, 20g weight, sans temperature compensation (gray line gravity, red line temperature):

![chart1](https://i.imgur.com/UY4O1Bi.png)

Test run from 7/10/18, 20,000-unit calibration range with 1.065 actual reading, 20g weight, with temperature compensation (gray line gravity, red line temperature):

![chart2](https://i.imgur.com/gKuIX31.png)

To make the results even more dramatic, when the 7/9/18 line smooths at the end of 7/10/18, that's when I was testing temperature compensation. Happily, load cell temperature response appears to be linear. Less happily, on the scale we're interested in, temperature response appears to be a little under three gravity points per degree Fahrenheit with a 500g load cell, or closer to one gravity point per degree Fahrenheit with a 200g load cell. Temperature compensation, then, is going to be very important. Hopefully it's similar across load cells of the same design, so that I can set a factory parameter that's close enough for most Pendulums.

### Next steps
I've been using the github Projects boards to organize my tasks. On my list while the 200g load cell is in transit:

1. Build a stopper assembly. Eventually, I want to have stoppers with holes just the right size for whatever the hanger ends up being, so that friction is the main thing holding it in, and the glue is just for stability. This one's going to be a little more provisional; I'm just going to squirt hot glue down the hole with the wee hex wrench and hope for the best.
2. Make a 100g sinker sized to fit in a growler or perhaps a gallon milk jug. That'll be my test rig for an actual fermentation. (Granted, most likely a fermentation of sugar water using baker's yeast, but you go to war with the army you have.)
3. Do some work on the software, and in particular the hotspot mode webpages. Mainly, I want to break calibration and configuration out into separate pages, so I can go into a little more detail on calibration, perhaps add a temperature calibration thing, and organize the configuration page better.

### Other items
If, for some reason, the weigh-a-sinker system doesn't work out, I hit upon the idea of weighing the entire fermentation vessel. Given an initial gravity, you get a fairly precise measure of volume in the fermenter, and you only have to measure a 5-gallon batch to within 20 grams or so to get a resolution of one gravity point.

I might pursue that one separately, or after this project has gotten to an acceptable state of completion.
