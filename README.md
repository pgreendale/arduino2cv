# arduino2cv aka Electric - HnnH
## Introduction
Electric HnnH is a simple Midi2CV converter based on Arduino nano (or its clones), namely Atmega328p and just basic stuff to keep the Project cheap and as simple as possible. 

It is based on work from these people: 
* the simplicity of Emilié Gillets (Mutable Instruments) CVpal Module, now obsolete? https://github.com/pichenettes/cvpal
* the useful 4822 DAC implementation of Kerry D Wong http://www.kerrywong.com/2012/07/25/code-for-mcp4821-mcp4822/ 
* the easy-to-use Midi Library from Francois Best https://github.com/FortySevenEffects/arduino_midi_library

This project is on an early stage and just provides basic functionality, it is not professional, has no linearity V/oct control etc.
I wish to share it because I felt that buying expensive interfaces or a lot of components to build one is over the top in many cases, this thing is built in 1h and does the basic stuff I needed for sequencing my modular from either ableton or a variety of old sequencers. 

## Requirements
* Arduino Nano
* 6N138 based Midi coupler
* MCP4822 DAC http://ww1.microchip.com/downloads/en/devicedoc/20002249b.pdf

## Wiring 
Actually I am too lazy to draw schematics. Put some protection resistors on the Gate Outs (1k) and on the CV outs of the DAC (200R)
 
(Pin Name | Atmel Pin | Function)
* i2S DAC
  * D11		|	PB3		| MOSI -> Data out
  * D13		|	PB5		|	SCK  -> Clock
  * D9 		|	PB1		|	DAC Latch	(active low)
  * D10		|	PD6		|	CS Pin 		(active low)
* Direct Outs (Gate Outs)
  * D3 		|	PD3		|	Gate 1, SQR out by OC2B
  * D5 		|	PD5		|	Gate 2, SQR out by OB0B, freq. meas in
* Periphery 
  * D2 		|	PD2		|	LED control
  * D7 		|	PD7		|	Mode Switch (learn/run)

MCP4822 Outputs
* CV Outs for VCO freq and Velocity out
  * VoutA  |  8  |  CV Out for VCO 1V/oct
  * VoutB  |  6  | CV Out for Velocity (use at Filter, VCA, whatever you want)
  
 ## License
 GPL v3 
