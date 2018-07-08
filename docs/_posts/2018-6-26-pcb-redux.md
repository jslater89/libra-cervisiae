---
layout: post
title: More on PCB Design
---

## On the implied pun
![1.0.0-rc.5](https://i.imgur.com/MIPV4ql.png)

Moron PCB design would be an adequate title for this post, too. I'm a software engineer by trade. Going from a world where there's just 'true' and 'false' to a world where there's 'on', 'off', and 'maybe somewhere in between?' has caused me no end of trouble.

In this iteration, the ground pour has expanded even further, to hit pretty much every ground pad on the board, which I guess is what you're supposed to do anyway. There are more capacitors, one to filter the USB power input, and one to filter EMI from the battery monitor-to-ADC trace, both changes made based on feedback from r/PrintedCircuitBoards again. They're great folks.

There's also a functioning battery disconnect circuit, which uses the USB+ line to pull a p-channel MOSFET gate high, therefore cutting off the battery from the circuit. It's buffered by a 47uF capacitor, which hopefully will provide enough oomph to handle switching. I'd aimed to do something like this on my own, but ended up copying a circuit from the Arduino forum, which fixes some faulty assumptions of mine and correctly isolates both the battery from the USB voltage and the MOSFET gate from the battery voltage.

Generally, though, if you've been following along, the board has been changing less and less between updates. I think I'm getting close to a final design, one I can send off to a fabricator for some prototype production.

## Board production
![1.0.0-rc.5](https://i.imgur.com/AB8XbFr.png)

Now that a board design is close, I think it's time to talk a bit about production.

### Version numbering
Repository watchers may have noticed version numbers counting up. I figure I'll maintain two sets of releases: pcb-x.x.x-prerelease.x for PCBs, and esp-x.x.x-prerelease.x for the software.

For the PCB, I don't see much use in distinguishing between alpha, beta, and rc. All pre-production boards will be rc.x boards. The first board I order will be 1.0.0. Any required design changes will be part of 1.0.1-rc.x, and the second hardware revision will be 1.0.1. Functional changes will bump the middle number, and redesigns will bump the first number.

The software versioning will be a little more ordinary, starting at 1.0.0-alpha.1 and counting up as you'd expect.

### Near-final bill of materials
Now that the PCB design is nearly finalized, so is the [bill of materials](https://docs.google.com/spreadsheets/d/1zar1gR90osImwsAmGcO47G6zN50gNiWxno9D_cdoG40/). The electrical components come to $11.64 per board, if you can buy in bulk, or a lot more than that if you can't. Mechanical components and a plastic enclosure represent another $5.36.

Most of the parts, and all of the electrical components, are sourced from AliExpress. With the exception of the standoffs and screws for mounting in the enclosure, the mechanical parts all come from Amazon.

### Things for sale
There's a little problem with the bill of materials. One PCB costs $11.64, but requires you to buy $55.85 worth of parts. Wastage for the other categories is equally pronounced. I hope to benefit both people who want a Pendulum and, to a degree, myself, by passing on most of the savings from bulk purchasing by selling kits, and maybe even assembled boards.

In both cases, I believe that puts me under the FCC's regulatory authority for unintentional RF emitters. (Kits are a bit of a gray area, but kits intended to be assembled into a specific final product are less so, and assembled products for sale are literally the opposite of a gray area.) Because that's a significant startup expense (amount to come; I'm getting in touch with a local EMC testing house), I plan on running a Kickstarter to help defray the cost, in addition to the cost of some other tools which will help with assembling boards.

To reiterate, that's still some time off. I'm still waiting on the load cells and temperature sensor, and before I get into working out the PCB prototype, I want to get the coding done, along with the stopper and load cell design. For both tasks, I'll still be working against the same development board I've been using. Given the lesser physical constraints on this project, you can probably figure out how to do the same, if you want to follow along.

Once I've established that everything works with the dev board, built a load cell assembly which fits through a carboy neck, and hand-soldered the first Pendulum PCB prototype, then it's probably time to get into a production kind of mindset.
