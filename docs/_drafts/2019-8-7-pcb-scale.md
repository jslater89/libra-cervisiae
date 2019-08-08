---
layout: post
title: A happy PCB update!
---

It's been a long time since I had real progress to report, but here we are: an assembled Libra Cervisiae PCB is actually reading from a load cell.

The problem is not one of design, at least for the single load cell case, but rather one of connectors. The latest revision of PCB uses standard 2.54mm Dupont connectors to attach the load cells. The load cells, however, come with very thin wires, and don't make good contact inside the terminal. I expect this can be solved by stripping more of the wire and double- or triple-folding it, or by putting a dab of solder in with each wire.

In the interim, I bodged together a solution using the little pin clip gaps on some of my test Dupont cables. I took a picture, but my phone died, so I'll update this post later with it.

The PCB is performing well—using big pours for the excitation and signal grounds, and paying attention to return paths, seems to have made the miniature scale pretty interference-free. It's precise to within about a gram, or about 150 nanovolts. Fun.

Anyway, having sussed out the issue, I can keep on pushing the design forward and get back to work on the full-size scale.
