---
layout: post
title: Libra Cervisiae, creep profiling, and batteries
---

I've come around fully to the Libra Cervisiae idea, given past experiments at [Homebrewtalk](https://www.homebrewtalk.com/forum/threads/estimating-alcohol-by-total-weight-during-fermentation.265716/#post-6913352) and [Hobbybrouwen.nl](https://www.hobbybrouwen.nl/forum/index.php/topic,35958.0.html). As I alluded to earlier, I don't think there are that many design challenges to be found here. I do have one software thing to think about, and one battery thing to think about.

### Creep and compensation
Creep, the characteristic of load cells to drift to a higher reading when a heavy load is placed on them, might cause some error worth correcting for. According to the datasheet for my load cells, they have a creep response of 0.03% of the full-scale reading over the first five minutes. These are 10kg units, so that's a creep of about 3 grams. For the planned four-cell design, each cell takes a quarter of the load and sees a quarter of the weight delta; that's 4.75g per gravity point.

Still, the creep response might be greater than the datasheet suggests; it'll be worth experimentation as I get closer to a completed design. If I do need to worry about creep correction, I have in mind a little creep calibration process: set the scale up with a fixed weight on it and start a profile run. The scale logs half an hour's worth of data to come up with a creep curve for the first half-hour and a linear creep compensation factor for the time thereafter. Bob's your uncle.

In terms of implementation, the creep curve is probably only worth doing in always-on mode. Besides writing to flash—a limited resource—there's not a good way to keep track of time-since-start in sleep-and-wake mode, and if the interval is half an hour, it would be using the linear creep compensation factor on the first wakeup anyway.

### Batteries
Since the controller is part of the scale and therefore rests on the ground, there's no real need to keep the battery on the inside anymore. As such, I think the right move is to skip the battery-on-board altogether, and recommend external USB power of some kind.

Wall power is easy, as is battery-only power; USB power packs are easily available. Even assuming the worst-case scenario, that the CP2102 breakout board will always run the CP2102 in high-power mode, a 10000mAh battery pack will still run the board in sleep-and-wake mode for three weeks, and a 27000mAh pack will run it for almost two months. A 27000mAh pack is probably good for a week of runtime even in always-on mode.

Wall power with battery backup is a bit trickier; only a subset of the USB power packs out there support passthrough power in the way we're looking for, switching back and forth from wall power to battery power as needed. Such products exist, evidently; RAVPower and a few other brands on Amazon have reviews saying as much. Some other products briefly cut power output when switching from AC to battery. Of course, even if power cuts out briefly, it isn't the end of the world; after the end of the half-hour creep compensation period described above, it should be entirely possible to get consistent readings after reboot and continue to send accurate data.
