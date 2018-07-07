---
layout: post
title: Load cells and initial results
---

![cells](https://i.imgur.com/LDUMFeS.jpg)

My load cells arrived on Thursday, so I took a few minutes to solder the headers onto the HX711 breakout board, wired everything up, and tried a few things out. Initial results were promising: although the load cells aren't hyper-sensitive, they do seem to have pretty decent performance, and the measurements via the HX711 are low-noise and consistent even at the 128x gain setting.

Before I get on to last night's test results, it's time for a little math interlude. All of the load cells I obtained have an output rating of 1 mV/V at their rated capacity. So, the 500g cell I'm testing with, if fed 3.3V, will provide an output of 3.3mV when loaded with 500 grams. The thing is, we're not interested in measuring 500 grams. Really, we're interested in measuring something between one tenth of a gram and one third of a gram. 3.3mV over 500 grams is 6.6 microvolts or 6600 nanovolts per gram. That means 660 nanovolts per tenth-gram.

The HX711 documentation says that its input noise is 90 nanovolts in 80Hz output mode; assuming we don't add too much noise on the PCB or via the wires from the sensor to the PCB, we've got much more signal than we do noise. We also have the option of soldering across a pad to go to the lower-noise 10Hz output mode, but I don't think I'm aiming to do that unless it turns out to be necessary.

Anyway, some playing around with a growler (whose neck is somewhat narrower than a carboy neck; it's good to over-engineer) suggests that the L-shaped tilt-it-through method is untenable. I'll try it on the carboy on brew day tomorrow, but I think the cantilevered torque-type mount is the solution we'll be going with.

![benchtop](https://i.imgur.com/nOTUOqT.jpg)

So, I built one on my workbench and put enough nickels in a plastic cylinder to make a 65-gram weight, then tied a bit of thread around the cylinder and hung it from the end of the load cell assembly. I'm gratified to say that the results look promising. The sensor outputs a value of about 106000 without the weight, and 155000 with it, depending on the exact tilt. It also seems to be able to measure the weight of a short jumper wire, which weighs something like half a gram. I took a little [video](https://photos.app.goo.gl/Fzg2QcWucn6WXUmT7) so you can see it in action.

Taking 40 samples over two seconds (i.e., one sample every 50 milliseconds) with a constant weight, the difference between the maximum and minimum readings usually ends up being about 175-200. After the system stabilizes, each 40-sample read is within ±30 of a 20-second/10-read rolling average reliably, and within about ±50 at the outside.

One thing I have noticed is that tilting the sensor slightly (as in the pictures), instead of letting it hang vertically, yields better measurements—the force on the sensor does better at bending it, which is what the strain gauge ultimately measures. That may lead to a need for per-batch calibration—take an initial reading with your refractometer or hydrometer, enter the reading in the Pendulum UI. By comparing its reading with the entered reading, the software can calculate an adjustment factor. We'll see if it's necessary.

I also had to add a pull-up resistor to the PCB, because the temperature sensor requires one. (There are internal pullups on the ESP8266, but they're very weak and I don't think there's any harm in having one on the board.) That change is in the repo now.
