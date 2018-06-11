# pendulum
Pendulum is a wireless hydrometer powered by the ESP-8266 which fits through the ~30mm neck on a glass carboy. Still in planning.

## Motivation
There are several tilt hydrometer projects already, including the well-supported iSpindel, but none of them are set up out of the box to fit into a glass carboy. The neck on our current primary fermenter, a typical 5-gallon glass model, is 29.75mm wide at the narrowest point of the opening, and for ease of use, we decided on a 27mm-diameter plastic enclosure.

# Assembly

## Cylinder

## Electronics
Connect D1 and D2 to MPU6050 SDA, SCL. Connect D5 to MPU6050 V+. Connect MPU6050 GND and ADO to WeMos GND.

Connect battery V+ to a 100kohm resistor, then to the WeMos analog input pin.

## Final Assembly
Print the sled, mount the various bits and bobs, and put it in the cylinder.

# Usage
Pendulum operates in two modes: hotspot mode, in which live data can be viewed and the configuration changed, and hydrometer mode, in which pendulum spends most of its time in deep sleep, waking at intervals to send data to a web backend. (Currently, [graviton](https://github.com/jslater89/graviton) is supported.)

## Mode Selection
Enter hotspot mode by double-pressing the reset button, with both presses occuring at least half a second apart within two seconds in total.

## Configuration

## Calibration
Like all tilting hydrometers, pendulum requires calibration to correlate tilt angles to specific gravities. Calibration is carried out using the Live Data page when pendulum is in hotspot mode, by measuring specific gravity (_not corrected for temperature_) with a float hydrometer and recording the associated tilts. Pendulum does quadratic regression on the data entered, calculating coefficients without the need for user interaction.

## Fermentation
When not in hotspot mode, pendulum runs in hydrometer mode. In hydrometer mode, pendulum remains in deep sleep mode at almost all times, waking only to take a measurement and send it to graviton.

Pendulum takes a reading immediately when starting in hydrometer mode. To avoid corrupting data in graviton, wait until you have placed the hydrometer in the fermentation vessel before connecting the batch and hydrometer in gravity.

# Repository Structure
Arduino source is in src/pendulum. Source for the web pages delivered by hotspot mode is in src/pendulum/data.

# Shopping List
* Enclosure: a 27mm cylinder of some kind, exact specifications to be determined. Those listed below are the ones I'm experimenting with.
   * [Plastic 27mm OD test tube](https://www.amazon.com/dp/B0782S6V81/?coliid=I1TOIBPRD6VTA4&colid=13ZBKZWZ204CF&psc=0&ref_=lv_ov_lig_dp_it)
   * [27mm ID coin collector's cylinder](https://www.amazon.com/gp/product/B07D7496CS/)
* Stopper (size TBD) or screw cap (depending on above)
* WeMos D1 Mini ESP WROOM 02 w/ 18650 battery slot
   * [Amazon](https://www.amazon.com/dp/B075H8X7H2/?coliid=I13ZMB7WGBS2O9&colid=13ZBKZWZ204CF&psc=0&ref_=lv_ov_lig_dp_it)
   * [AliExpress](https://www.aliexpress.com/item/Wemos-esp-wroom-02-Pocket-8266-D1-mini-WIFI-Module-ESP8266-18650-Battery/32810063490.html?spm=a2g0s.13010208.99999999.286.307f3c00knVWMJ)
* GY-521 MPU-6050 gyro/accelerometer board
   * [Amazon](https://www.amazon.com/MPU-6050-MPU6050-Accelerometer-Gyroscope-Converter/dp/B008BOPN40/ref=sr_1_1?ie=UTF8&qid=1527475582&sr=8-1&keywords=gy521&dpID=51dJFuuUXrL&preST=_SY300_QL70_&dpSrc=srch) 
   * [AliExpress](https://www.aliexpress.com/item/MPU-6050-3-Axis-gyroscope-acce-lerometer-module-3V-5V-compatible-For-Ar/1858984311.html?spm=a2g0s.13010208.99999999.273.307f3c00knVWMJ)
* 3.7v ~3000mAh lithium-ion battery
   * [Amazon](https://www.amazon.com/Samsung-INR18650-30Q-3000mah-Li-ion-Batteries/dp/B01NCZHSPY/ref=sr_1_2?s=hi&ie=UTF8&qid=1527475727&sr=1-2&keywords=18650+3000mah)
* Sled (TBD [to be designed]) (Shapeways, or print-it-yourself)
