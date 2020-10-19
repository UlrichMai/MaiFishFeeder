# Smart Fish Feeder

This fish feeder is for a small cylindric aquarium 30x30cm.
The fish need only small amount of food, and most other solution are just to big of unprecise.
This feeder has 14 chambers for food portions.
A 180 degree servo rotates the hole to drop the food.
Once the software is ready, there will be 2 actions that can be controlled
1. feed 1 portion: The disc will rotate to drop the next portion.
2. refill: the disc will rotate to the beginning an you can refill the disc holes.

## Part List
- SG90 servo
- ESP8266 D1 mini
- USB panel jack
- 3D printed parts [top](doc/fishfeeder_top.stl), [body](doc/fishfeeder_body.stl), [bottom](doc/fishfeeder_bottom.stl)

## todo
- improve 3D parts
- decide wether to build my own firmware or to use Tasmota.
  - Tasmota PWM feature is able to control the servo. pwm 38..140 results in the neccessary servo movement
  - the servo its self needs pulses ranging from 750..2600 microseconds for the 180 range
- requirements
  - the current servo position must be persisted
  - a reset or power cycle must not move the servo, so not unwanted food is dropped.


## Whishlist
- add a ESP32 cam as a webcam for the aquarium
- add a water temperatur sensor