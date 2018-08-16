---
layout: post
title: Test results and more
---

Test results are in; I'm just going to link to [the reddit post]() to save myself some time.

The short version is this: on a fermentation from about 1.042 to 0.996, the scale ended up reading 0.9935, and the difference may well be in my refractometer rather than in actuality. There's much (much) more at the link.

In other news, I've been taking a bit of a breather. The second-revision PCBs are on their way, and I plan to wait for them to arrive before I do more hardware work. Over the past day or two, I've tried a few things to get direct Google Drive output working, to no avail. There isn't enough room in the heap to do HTTPS, and there aren't many third-party services left which accept HTTP requests to send to Google Drive.

Instead, I may expand the groovyLogger script. A very easy change would be to add Google Drive output via a Google Script web app; all I have to do is make one more web request. A slightly more involved option would be to make groovyLogger a webserver, too; then, Librae Cervisiarum could still deep sleep and be assured someone is listening when they wake.
