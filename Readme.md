# Plant Moisture Sensor

This is a NodeMCU based plant moisture sensor, adapted from [GardenBot's soil moisture sensor](http://www.gardenbot.org/howTo/soilMoisture/). You can find the scematics to building the actual sensor (it's really simple) and voltage flip-flop from there. I've also used a two-color led as an indicator.

## What it does

The sensor monitors plant soil moisture and reports it with led. I'm still experimenting with the thresholds, but the idea is to have a dim yellow light on when the plant has plenty of water, and have bright yellow and red when the soil is drying and is really dry, respectively.

## Connections

I've connected the moisture sensor voltage flip-flop to NodeMCU ports D1 (goes to the 100ohm connection) and D2 (100komh connection). The analog in is connected to NodeMCU's ADC0 input (A0 or AD0).

For the leds, I've used pins D5 (red) and D6 (yellow).
