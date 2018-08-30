---
layout: post
title: PCB assembly and other development news
---

![assembled](https://i.imgur.com/wUKRPYY.jpg)

There you have it! An assembled Libra Cervisiae PCB.

After some head-scratching and trial and error, it even works—it's sitting on the table next to me, running the Libra Cervisiae software and playing hotspot. There are some caveats. We'll come back to those.

There was a good bit of trial and error involved in getting the build settings right, but I have a good set of them now. I'll be sure to add those to the manual when I get around to it.

I upgraded my Arduino IDE to 1.8.6, and upgraded the project structure to be one Arduino sketch file (libra-cervisiae.ino), and a bunch of C++-compatible headers and source files. This is better for organization, permitting actual, proper control of variable scope and whatnot, and doesn't depend on arcane features of the Arduino IDE pre-build munge-tabs-together step. Improvements all around.

There are several problems to take care of. First, I had some issues with booting into UART download mode, which went away after a bit of reworking. Either I had bad solder joins or a short between GPIO15 and GPIO2 (fixed by adding some solder and hitting it with the hot air rework thing to make sure it reflowed correctly), or the 10k pulldown resistor was too large. (I swapped in a 1.2k resistor at the same time as I did the other rework.) I can verify which one it was by switching back to the 10kohm resistor, which is planned for this evening. I'd like to keep the 10k resistor, because that's one fewer distinct part to include.

I had some trouble with resets until I checked the schematic and saw that I had the scale's clock and data pins backward, which caused hangs and resets. Now that that's squared away, I'm on to other troubles with sensors, namely that the on-board temperature sensor isn't showing up, and that there seems to be quite a bit of noise in the weight sensor readings, and that it looks to be drifting fairly substantially over time as I check back in on the output through the course of my work day, from about 1650 up to 1950 now in raw output. It may have to do with static, capacitive coupling, or board heating, or possibly noise from the CP2102 board. It's hard to say without an oscilloscope.

For the temperature sensor stuff, I have a few things to try—verify a temperature sensor on a breadboard, try plugging one in to the socket on the PCB, use a stronger pullup resistor. For the weight sensor, that's a bit trickier. I'll probably add a second, smaller filtering capacitor next to the HX711, and throw in more filtering near the ESP8266 for good measure. I may also add an analog ground plane to the bottom of the board on the corner with the load cell, to allow for a cleaner ground for the load cell's S- lines. In doing so, I can probably also eliminate vias altogether on that part of the board, and may be able to match trace length a little more closely.

Anyway, that's the state of things. Still moving forward, but PCB changes and debugging are harder and slower than doing it all on breadboards with pre-built boards. Stay tuned.
