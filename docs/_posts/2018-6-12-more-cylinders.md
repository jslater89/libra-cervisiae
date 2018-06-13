---
layout: post
title: More news on the cylinder front
---

The 27mm outside diameter cylinders arrived, and unfortunately, they've caused more problems than solutions.

The first news was good news: the Wemos board, with the battery tray removed from the bottom, does indeed fit—barely—into these cylinders. I had to remove the threads—they're substantially narrower than the rest of the cylinder. Once I hacksawed the top off, leaving a straight-sided cylinder of roughly 130mm length, the microcontroller slid in without too much trouble.

Unfortunately, the 90mm board and the 65mm battery add to more than 130mm; they won't fit in one cylinder. That's a problem.

### What next?
Well, I have a few ideas.

#### Wired float
Build a wired float with the MPU6050 only, using a cable running out through the carboy stopper and to the microcontroller, which sits outside the carboy altogether.

This has a few benefits. It allows for infinite lifetime, since the microcontroller can be charged while the float is in the wort, and for high-power applications. The microcontroller could respond to HTTP requests with a JSON object containing a current reading, for instance, or display the current status on an LCD screen.

It also has some difficulties and drawbacks, primarily in cable choice. The cable literally has its finger on the scale. My testing this evening suggests that a very, very fine cable would be required to avoid weighing down or pulling up on the float. A standard USB cable, for instance, is right out.

Experiments did show, however, that a cable hot-glued through a stopper is sufficiently waterproof for this sort of thing.

#### Two-cylinder hydrometer
Use one cylinder to house the microcontroller and MPU6050, and a second cylinder to house a battery (or batteries). Connect the two cylinders with a cable.

The second cylinder would be big enough to fit a pair of batteries, for a really tremendously long lifespan. (On a single 2600mAh li-ion battery, the setup on my workbench has gone from 4.2 volts to 3.85 volts in eight days.) Although the battery cylinder would tug on the sensor cylinder, it would do so in a predictable and repeatable way. With the batteries pushed to one side of the cylinder by a well-designed sled, it would even roll-stabilize the sensor float, for better accuracy.

For this setup, I can put the MPU6050 near the bottom of the float, so that it rests under the surface of the wort. This is likely to improve the accuracy of the wort temperature readings.

I think this is the most promising; it doesn't rely on solving any currently-unsolved problems, with the exception of working out how best to fish it out of the wort. (I'm thinking probably hot-glue some fishing line to the bottom of the battery cylinder.)

#### Spliced one-cylinder hydrometer
Cut the necks off of two cylinders, and the bottom off of one. Splice them together to make a ~250mm cylinder. I gave this a try, and wasn't able to get a waterproof seal. I have plenty of cylinders to work with, however, so I'm going to keep at it. It would be the most straightforward bit of construction.

### Other options
While I'm nearly to a functioning setup, and one of the options above seems likely to work, I'm a little iffy about using these particular cylinders. They're a nonstandard size, and so far I've only found them in one place, from an Amazon retailer. That seems sub-optimal. It may behoove me to come up with a design that fits into a 25mm tube instead of a 27mm tube; the former is a standard test tube size and much more easily located.

#### Use a smaller development board
The Adafruit Feather HUZZAH is 23mm wide and 51mm long, with every feature found on the Wemos board currently called for. Given that the 25mm Wemos board fits into 27mm cylinders, it seems reasonable to hope that the 23mm Adafruit board would fit into a 25mm cylinder.

There's also an [even smaller ESP32 board](https://www.tindie.com/products/onehorse/smallest-esp32-development-board/), measuring a hair under 18mm across, but it's also handmade by a guy in California, and is correspondingly expensive. Also, if this project takes off, I'd feel bad subjecting him to a wave of orders.

#### Use a bare ESP12 and a custom PCB
Build a custom PCB designed to be user-friendly. Rather than solder on tiny surface-mount components, provide through-hole mounts for breakout boards. An ESP12, some buttons for flash/reset, a battery charging chip and voltage regulator, a GY521, and a serial interface on a PCB would be a reasonably easy soldering project for an amateur. I suspect it could be done in maybe 20mm by 70mm, likely with a bit of stacking of chips. Adding an 18650 cell, that leaves an excess of 15mm to fit into readily-available 25x150mm cylinders.

This is probably the best option, and leaves end users with the most latitude to fit it into various containers. It's also a bit down the road; I'm going to be exploring the options with the Wemos D1 board for now.
