# pendulum
Pendulum is a wireless hydrometer powered by the ESP-8266 which fits through the ~30mm neck on a glass carboy. Still in planning.

## Motivation
There are several tilt hydrometer projects already, including the well-supported iSpindel, but none of them are set up out of the box to fit into a glass carboy. The neck on our current primary fermenter, a typical 5-gallon glass model, is 29.75mm wide at the narrowest point of the opening, and for ease of use, we decided on a 27mm-diameter plastic enclosure.

# Usage
Pendulum operates in two modes: hotspot mode, in which live data can be viewed and the configuration changed, and hydrometer mode, in which pendulum spends most of its time in deep sleep, waking at intervals to send data to a web backend. (Currently, [graviton](https://github.com/jslater89/graviton) is supported.)

## Calibration
Like all tilting hydrometers, pendulum requires calibration to correlate tilt angles to specific gravities. Calibration is carried out using the Live Data page when pendulum is in hotspot mode, by measuring specific gravity (_not corrected for temperature_) with a float hydrometer and recording the associated tilts. Pendulum does quadratic regression on the data entered, calculating coefficients without the need for user interaction.

# Repository Structure
Arduino source is in src/pendulum. Source for the web pages delivered by hotspot mode is in src/pendulum/data.

# Shopping List
* [Enclosure](https://www.amazon.com/dp/B0782S6V81/?coliid=I1TOIBPRD6VTA4&colid=13ZBKZWZ204CF&psc=0&ref_=lv_ov_lig_dp_it) (or other 27mm OD plastic cylinder)
* Stopper (size TBD)
* [Microcontroller](https://www.amazon.com/dp/B075H8X7H2/?coliid=I13ZMB7WGBS2O9&colid=13ZBKZWZ204CF&psc=0&ref_=lv_ov_lig_dp_it) [AliExpress](https://www.aliexpress.com/item/Wemos-esp-wroom-02-Pocket-8266-D1-mini-WIFI-Module-ESP8266-18650-Battery/32810063490.html?spm=a2g0s.13010208.99999999.286.307f3c00knVWMJ)
* [Accelerometer](https://www.amazon.com/MPU-6050-MPU6050-Accelerometer-Gyroscope-Converter/dp/B008BOPN40/ref=sr_1_1?ie=UTF8&qid=1527475582&sr=8-1&keywords=gy521&dpID=51dJFuuUXrL&preST=_SY300_QL70_&dpSrc=srch) [AliExpress](https://www.aliexpress.com/item/MPU-6050-3-Axis-gyroscope-acce-lerometer-module-3V-5V-compatible-For-Ar/1858984311.html?spm=a2g0s.13010208.99999999.273.307f3c00knVWMJ)
* [Battery](https://www.amazon.com/Samsung-INR18650-30Q-3000mah-Li-ion-Batteries/dp/B01NCZHSPY/ref=sr_1_2?s=hi&ie=UTF8&qid=1527475727&sr=1-2&keywords=18650+3000mah) (or comparable flat-top 3000mah 3.7V Li-Ion battery)
* Sled (TBD [to be designed]) (Shapeways, or print-it-yourself)
