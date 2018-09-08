---
layout: post
title: PCB testing
---

After a week or so of PCB testing, I have some results, and a 0.2.0 PCB on its way from the fabricator.

The big news is that all the on-board sensors are working. After buying a crimping tool I decided to switch to pin headers and Dupont connectors. The 1.25mm pitch pins are super-hard to DIY-assemble.

More big news is that the software is now almost all working. The double reset detector wasn't, last I tried, but sleep mode has kind of fallen by the wayside in favor of always-on station mode. I'll debug it further as I have time, but it's down the priority list.

The other big news is that the board seems pretty sensitive to heating from the ESP8266, which runs pretty hot and warms up the entire board. The temperature sensor (now working, with the substitution of a stronger pull-up resistor for the data line) reads about 10F warmer than ambient, which appears to skew the HX711's reading somewhat. (It may be heating of the traces.) I'm hoping that the separate copper pour for E- and S- on the HX711 helps there. In the same vein, I switched the on-board temperature sensor from being attached directly to the board to being a connector for a cabled sensor, so that it can more accurately measure the temperature at the load cells.

The other major design task is considering what I want to do for an enclosure. Most of them are larger, which means the PCBs get bigger, which would, granted, be a good thing for heat sinking. The downside is more careful measuring and possible incorrect measuring, which makes the 

That's about all for now—I've been busy on other projects, and have had a few weekends in a row with just about zero time to sit down and code, so the groovyLogger changes aren't any further along.

If you're looking for a way to contribute, here are two items. (I've made issues for them. Comment on the issue if you want it.)

* groovyLogger CLI and/or relay-to-Google-Sheets, or other improvements.
* Fritzing diagram for the breadboard version, for the DIYers with full parts cabinets already.
