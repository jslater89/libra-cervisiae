---
layout: post
title: PCBs and initial live testing
---

It's been a madcap few days with exciting news all around.

### Temperature compensation
![graph1](https://i.imgur.com/ZIMb5eO.png)

The chart pictured above shows about 28 hours of output data, temperature in blue and weight in red. There's a clear relationship between the weight and temperature; as the sensor gets warmer, it reads a lower weight. There's another feature of note which is more clearly revealed by the graph with correction enabled:

![graph2](https://i.imgur.com/jsxaQiz.png)

This chart has data for about twelve hours, from the morning to the early evening. The big dip in temperature occurs when the air conditioner comes on in the afternoon. Note that the load cell output still reflects a change in temperature, at least at first. This is because the load cell responds more slowly to temperature than the temperature sensor. The sensor cools off, so the correction kicks in too soon. As the load cell cools down, the value returns to average.

The magnitude of the correction is -75 raw output units per degree Fahrenheit. That's about one-third of a gram per degree Fahrenheit with the single-cell scale.

### PCB arrival
![pcb-front](https://i.imgur.com/VBthqI7.jpg)

The first-run PCBs have arrived! Unfortunately, they're no longer the state of the art design; fortunately, they should be sufficient to test the ESP-12 breakout portion, which is the one I'm most concerned about.

Testing indicates that somehow, I managed to get the pin spacing and board dimensions of the HX711 and CP2102 just about right. (I'm skipping the TP4056 module, since it's no longer part of the board.) It isn't perfect, though, so before I order the next revision of the board, I'm going to borrow some calipers and make sure I get the spacing and sizing just right.

In [this picture](https://i.imgur.com/ei60qSA.jpg), you can see the breakout boards in position. In [this one](https://i.imgur.com/Znatw0S.jpg), you can see the old but attractive logo.

### Test fermentation under way
![testrig](https://i.imgur.com/4O17rTa.jpg)

In the most exciting news of the day, test fermentation has begun with a duct-taped temperature probe and an old protein powder jar. (Obviously, I'm not super-concerned about infection here.) I didn't think about it, but the weight sensor has some impact on equipment weight. Attached like this, it adds about 8 grams. Hanging into the fermenter through a thermowell, I expect it would add a good bit more—the weight of the sensor head plus the weight of the cable run. That said, it isn't crucial to calibrate it in. All it affects is the volume estimation.

I only mixed up the fermentation sugar-wort about three and a half hours ago at the time of writing. It kicked off at 10.2 degrees Brix/1.042 SG and 2379 grams. It's started bubbling, but not enough to affect the weight reading yet. I'll have more to report as it moves along (I hope!).
