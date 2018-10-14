---
layout: post
title: Scale testing and current state of affairs
---

It took me a while, thanks to some [other projects](https://manywords.press/rpj-a-free-open-tabletop-roleplaying-game-system) I ended up focusing on in September-October, but I finally got a full-size prototype built.

![top-off](https://i.imgur.com/VXcUXCp.jpg)

![top-on](https://i.imgur.com/XjE01XH.jpg)

![inside](https://i.imgur.com/JDlQIWe.jpg)

On the one hand, the mechanical design seems solid. The platform is 14" wide, which should accommodate any fermentation vessel under the 30ish-kg capacity of this load cell combination without much trouble, without being too large to fit into a fermentation freezer.

On the other hand, the electrical design has been causing me fits. Either I have one or more bad load cells, or my connector crimping is not up to snuff and I have one or more bad connectors, or I've been misled on the ease of [connecting load cells in parallel](http://www.marco-iw.nl/file/1355354080.2319WAfreS/2%20Loadcell%20cabling.pdf).

My present to-do list is four steps:

1. Write a scale-test function for the PCB firmware, which keeps the HX711 powered all the time and reads its output constantly, without much averaging.
2. Connect each load cell individually to the PCB via jumper wires or jumper wires+breadboard, and verify that each one works individually.
3. Assuming 2. shows four good load cells, re-crimp connectors for each load cell, perhaps with a dot of solder or a bit of solder paste, then verify that each load cell still works with the connector.
4. Reassemble everything and see what happens.

I'll report on my results as they happen.
