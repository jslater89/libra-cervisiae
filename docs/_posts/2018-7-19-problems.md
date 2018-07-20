---
layout: post
title: Design issues and proposed solutions
---

## Problems
My 200-gram load cell recently arrived, so I figured I'd sit down and build a Pendulum stopper assembly to see how it works.

As the heading suggests, I ran into some trouble.

### Rubber is springy
Shocker, I know. Rubber stoppers are, as it turns out, much springier than load cells, so loading the stopper assembly with a torque force mostly ends up applying the force to the stopper itself, rather than the load cell where we want it.

In practice, this means that the load cell readings are worth pretty much nothing; they're overwhelmed by the confounding factors.

### The stopper assembly is crowded
My little test chamber is a half-gallon milk jug. Getting the sinker and the temperature sensor in is proving to be a bit of a pain. This is, in part, because the sinker is quite tall compared to the milk jug, so the line connecting it to the load cell is quite short. In part, it's because a 27mm cylinder and a 3-4mm wire are hard to maneuver together.

### A three-hole stopper is hard to make
To build a Pendulum properly, you need three holes in a stopper: one for the airlock, about 3/8" diameter; one for the temperature sensor, about 1/4" diameter, and one for the load cell assembly, a little smaller than 1/4" diameter. That may be a tall order to fit into a standard #6.5 or #7 stopper.

## Solutions
Of course, there are ways to fix these problems, some more dramatic than others.

### A stopper topper
Cut a disc of plywood about the size of the top of a stopper. Drill three holes aligned with the holes in a Pendulum three-hole stopper. Glue the topper to the stopper, and affix the load cell hanging arm to the topper rather than the stopper. Plywood is much less bendy than rubber, and should be sufficiently supportive.

This option requires very little extra work, and all I have to do to test it is buy a hole saw and some drill bits, which I want anyway. It may have some function issues, and does tie kitbuilders more closely to a stopper of a certain size and design.

### A through-the-airlock load cell
It occurs to me that a weight hanging through an S-type airlock should still apply force to a load cell outside the airlock. Moving the load cell outside solves the moisture problem and likely the temperature sensitivity problem, because it 1) is away from the area where there's the greatest risk of moisture and 2) can be mounted in the traditional, horizontal orientation. In that orientation, the load cell's output voltage is much greater, because the shear strain on the gauge is also much greater.

On the other hand, it requires building some sort of outside-the-carboy tower to hold the load cell. That's not necessarily a simple engineering endeavor. This concept also depends on tension being transmitted through the airlock in a reasonable, linear fashion, which is not necessarily guaranteed. I'll be testing this after bottling day.

### A beer scale
Eagle-eyed observers might have noted the appearance of a 'Libra Cervisiae' folder in the repository. I've been thinking about it, and this idea has some serious merit. It's universal, it doesn't require any complicated engineering or very complicated assembly, and it's also not, to the best of my knowledge, patented or patent-pending.

So, you have a scale. Tare it so that it reads zero with your fermentation vessel and airlock resting on it. Fill your fermentation vessel with wort and provide an initial gravity reading. Now you know the precise volume of beer in your fermenter: you've provided a density, and the scale reads the weight of the wort.

Take weight readings over time. As the beer ferments, yeast turns sugar into alcohol, more yeast, and carbon dioxide. Karl Balling tells us the ratio: 2.0665 grams of sugar turn into 1 gram of ethanol, 0.11 grams of yeast biomass, and 0.9565 grams of carbon dioxide. Put another way, the beer gets 0.9565 grams lighter for every gram of alcohol produced.

Looking at it from another direction, the difference between (say) 19 liters of beer at 1.015 SG and 1.016 SG is about 19 grams (four US nickels, or two 2-euro coins). That's an easy difference to measure on a 20kg scale—about 0.1%, when load cell errors are on the order of 0.01%.

As further support for this idea, [it's already been done](https://www.homebrewtalk.com/forum/threads/estimating-alcohol-by-total-weight-during-fermentation.265716/#post-6913352).

I spent some time knocking together a slightly modified PCB design, which ditches the solder-on pads in favor of connectors for everything, and adds three more load cell connectors:

![nu-pcb](https://i.imgur.com/8qs8I31.png)

The benefits to this approach are several: as I said, it's universal, and the engineering is simple. It provides a precise reading on pre-fermentation volume, and can probably be used to work out current volume, too. It's also easy to scale up: if you're doing 10-gallon batches, build for 40kg capacity; the error is twice as much, but the sensitivity requirements are halved, as the change in mass in your beer is twice as large. You don't need a custom stopper; anything with a thermowell and a hole for your airlock suffices.

There are, of course, problems. Load cell creep is likely to play a much larger role. It's also more expensive—load cells are the expensive component in the torpedo method, and this needs four rather than one. It also calls for a bunch of difficult-to-ship materials: as much as four feet by two feet of plywood, for a two-foot by two-foot scale, and thirty-some nuts and bolts to tie everything together. I'd have to find two-meter temperature sensors to go from the controller up to the top of the fermentation vessel and back down.

Lastly, the cost per example shoots up to $25 or so from $15, and that's ignoring the cost of plywood for the scale surfaces. (There's probably a reasonable way to hack a Libra Cervisiae PCB into, say, a bathroom scale or shipping scale, however. That might be worth investigating.)

Still, though, I think the benefits outweigh the drawbacks. Simplicity is golden, and this has simplicity to spare.
