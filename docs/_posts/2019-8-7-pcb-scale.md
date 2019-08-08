---
layout: post
title: A happy PCB update!
---

It's been a long time since I had real progress to report, but here we are: an assembled Libra Cervisiae PCB is actually reading from a load cell.

The problem is not one of design, at least for the single load cell case, but rather one of connectors. The latest revision of PCB uses standard 2.54mm Dupont connectors to attach the load cells. The load cells, however, come with very thin wires, and don't make good contact inside the terminal. I expect this can be solved by stripping a little more of the wire and folding the exposed part under the insulator before crimping. If that doesn't work, I can always try putting a little dab of solder in the terminal.

To verify it was the connectors after all, I ensured that the load cell was making good contact by getting the load cell wires in direct contact with the openings on some Dupont jumpers:

![](https://i.imgur.com/Sg0Hd3N.jpg)

The PCB is performing well—using big pours for the excitation and signal grounds, and paying attention to return paths, seems to have made the miniature scale pretty interference-free. It's precise to within about a gram, or about 150 nanovolts. Fun.

Slightly less fun is that there are a few grams' worth of error depending on which of the four hookups the load cell is attached to. It might have to do with traces of slightly different length and therefore slightly different resistance. I might fatten the + traces up a bit to try to mitigate that, but at the same time, the use case here doesn't require perfect accuracy every time. We are, after all, basically integrating for better accuracy over the entire course of fermentation.

Anyway, having sussed out the issue, I can keep on pushing the design forward and get back to work on the full-size scale.
