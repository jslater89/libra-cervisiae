# Pendulum
![pcb](https://jslater89.github.io/pendulum/images/pcb.png)

Pendulum is a wireless hydrometer powered by the ESP-8266.

Development updates can be found at the project's [github pages site](https://jslater89.github.io/pendulum).

## Pendulum Reborn
The original Pendulum concept was a tilting hydrometer, but the patent for that idea is owned is owned by the makers of the Tilt hydrometer.

So, what _is_ a hydrometer, actually? It's a device which measures buoyancy. How high does a manual hydrometer float? How far does a tilting hydrometer tilt? Both questions ask about the strength of the buoyant force. The higher the float or the steeper the tilt, the stronger the buoyant force is. Given that neither flavor of hydrometer changes volume, a stronger buoyant force means that the liquid displaced weighs more. If one liquid weighs more than another for a given, fixed volume, it's denser than the other.

That's the ticket, then. The trouble is, measuring the height at which an object is floating is not trivial for computers. There are cheap-ish float sensors which run $20 or so, but they're bulky, heavy, and hard to clean. There are expensive solid-state sensors, but those cost $50, and at that price, you might as well just buy a Tilt.

Measuring buoyant force, however, doesn't require a floating object. If you hang a mass from a scale and put it underwater, it weighs less than it does in the air. Measuring this difference is hard for humans, which is why manual hydrometers float. (We can see liquid levels on a cylinder way easier than we can determine that this object weighs 10% more.) It's easy for computers, though.

## Design
Pendulum has two components.

First, the microcontroller. This goes in a box outside the fermentation vessel. It'll be able to run in a low-power mode on battery for several weeks at least, which sends updates to a remote [Graviton](https://github.com/jslater89/graviton) server or Google Sheets on a half-hourly schedule. It'll also be able to run in a high-power mode, either as a standalone hotspot or connected to your wifi, sending updates to a remote destination while also listening for requests for current status over the network.

Second, the stopper assembly. Most of Pendulum's delicate electronics stay outside the fermentation vessel. Attached to the stopper is a load cell to measure the force exerted by a sinker, which measures specific gravity. The sinker is entirely inert, and the load cell sits above the surface of the wort. Also attached to the stopper by insulated wire is a temperature sensor float, which sits on or just below the surface of the wort to monitor fermentation temperature.

## Current Status
Since we just switched to a nearly new design, there's some breadboard prototyping and Arduino re-coding to be done before it makes sense to order the PCBs and set up for final assembly.

## BrewPerfect Patent Compliance
I believe Pendulum does not infringe on BrewPerfect's patent (outdated application [here](https://patents.google.com/patent/US20160252440A1/en?oq=US20160252440A1)), based on amendments made after the linked application was rejected.

The updated patent application substitutes claim 4 (wherein said sensor measures the deflection of the deflecting load beam by measuring the capacitance between the sensor and said deflecting load beam) for the generic sensor called for in claim 1, which limits BrewPerfect to enforcing their patent, once it's granted, against others using capacitive sensing. Pendulum uses strain gauge-type load cells, which are purely resistive sensors which do not measure capacitance in any way.
