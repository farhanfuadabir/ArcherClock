<p align="right"><img src="https://img.shields.io/github/license/farhanfuadabir/ArcherClock"></p>

# ArcherClock

This is a timer system for archery competition developed by Quanfield Technologies. This repository contains the initial functionality demo and the main project codes and designs. 

There are two modes of the timer system: 
- Normal Mode 
- Alternate mode

The project used two `Raspberry Pi`s as the controller of the segments. The display controller has been designed with `Proteus Design Suite`. An `MQTT` server was used for maintaining the time-sync among the terminals. The connection to the display are maintained by LAN wires via router. Also, an `Android App` was developed as a wireless control interface.

 - <a href="https://github.com/farhanfuadabir/ArcherClock/tree/main/PCB%20Designs">PCB Design Files</a>
 - <a href="https://github.com/atick-faisal/Archer-Clock">Android App</a>

## Developer

Farhan Fuad Abir, Md. Ahasan Atick Faisal


## Display Drive Schematic
<p align="center">
<img src="PCB Designs/V2/schematic.SVG" width="1100"/>
</p>

## Display Drive PCB Layout
<p align="center">
<img src="PCB Designs/V2/pcb_layout.SVG" width="600"/>
</p>

## Android App Interface

### Normal Mode

<p align="center">
<img src="https://github.com/atick-faisal/Archer-Clock/blob/master/Screenshot_2018-04-03-20-04-53.png" height="400"> 
</p>

### Alternate Mode 
<p align="center">
<img src="https://github.com/atick-faisal/Archer-Clock/blob/master/Screenshot_2018-04-03-20-05-36.png" height="400">
<img src="https://github.com/atick-faisal/Archer-Clock/blob/master/Screenshot_2018-04-03-20-05-29.png" height="400"> 
</p>

### Settings
<p align="center">
<img src="https://github.com/atick-faisal/Archer-Clock/blob/master/Screenshot_2018-04-03-20-05-43.png" height="400"/> 
</p>


## System Diagrams

<p align="center">
<img src="archerClock_connectivity.svg" width="450"> 
</p>



## Video Demonstration

### Normal Mode

<p align="center">
  <a href="https://www.youtube.com/watch?v=_82nGCiF96M">
    <img src="thumbnail_1.png" width="450"/>
  </a>
</p>


### Alternate Mode

<p align="center">
  <a href="https://www.youtube.com/watch?v=EWotnfpleiI">
    <img src="thumbnail_2.png" width="450"/>
  </a>
</p>


## Project Reference

<a href="http://www.archeryclock.com/">Click Here</a>
