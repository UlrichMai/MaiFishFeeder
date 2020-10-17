Modified version of Servo(esp8266) library.
I removed the `write(_valueUs);` from `attach` method, because I need to have control of the intial servo position.