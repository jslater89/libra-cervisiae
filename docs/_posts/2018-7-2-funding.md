---
layout: post
title: Certification, funding, and electromagnetic compatibility
---

### Certification
I heard back from the local EMC testing lab today; their quote of $1350 for the required unintentional-radiator testing is broadly in keeping with what I'd expected. Lacking testing doesn't limit my development work, or anyone's ability to assemble a Pendulum on their own. All it does is prevent me (or anyone) from selling full kits or assembled versions until someone does the testing work.

### Funding
I can't really absorb that kind of cost, so absent a mysterious benefactor, it's going to take some crowdfunding down the road if I want to sell kits, partially-assembled kits, or fully-assembled projects. I think it's probably worth a shot at a Kickstarter. It isn't a very big ask for what it is. Eventually, I'd like to have a little Etsy shop or something, where I can sell kits and assembled boards on an ongoing basis, and perhaps fund a second revision which is designed for professional assembly. (That scales a whole lot better than me paintstakingly assembling things by hand in my basement workshop.)

Exactly how big an ask? I've been playing around with a spreadsheet to figure that out. Assuming I very approximately double my cost of materials for the backer rewards which are actually Pendulum units, between 60% and 70% of the Kickstarter haul goes to fees, taxes, and materials costs for reward fulfillment. If I take in about $4000, the Kickstarter haul covers the certification cost. If I take in $5000, it covers certification and some tools to make assembly a bit less blindness-inducing.

Of course, both of those only pay for one round of EMC testing. It's entirely possible that the board will fail the first round and have to go back in after a redesign, for another $1350. That's obviously something to be avoided, but a Kickstarter banner number of about $8500 gets me tools plus two rounds of testing.

To get those numbers, prices start at $35 plus shipping for a completely unassembled PCB-only kit, up to $70 plus shipping for everything fuly assembled. Those prices are higher than what I want to charge once I've gotten off the ground; they have to be a bit inflated at this stage so I can manage the setup expenses.

### Electromagnetic compatibility
![board-again](https://i.imgur.com/diupTDp.png)

So, that means another board change. It looks dramatic, but isn't really. Mostly, what I've done is aimed to route traces on the top layer as much as possible, to avoid breaking the ground plane on the bottom in as many places as possible. I think I succeeded pretty well. Now, only the HX711 CLK and DAT lines, the HX711 power line, the battery monitor ADC line, and some USB power lines dip down to the bottom plane, and only then to cross under pads and other traces. You can see all the breaks in the ground plane in the image; anywhere inside the board with a black background has no copper on the back plane.

I also added front ground pours and stitching vias, in part for mechanical stress/flexing reasons, and in part because I was advised it would make for less noise on the various lines and less EMI in general.

Several times now have I said, "I think this is a final design." I think that again this time, but of course you can't trust me on that front. Regardless, I still have some time. The electronic components I need for Pendulum v2 are still in transit, though now they've left China and are making their way to the US postal system. Once they're here, I can start on the next iteration of the software; once that's ongoing, the news here will largely shift in that direction.
