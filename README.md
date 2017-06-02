# CBM - The Bicho
A hardware-backdoor for CAN bus - by @UnaPibaGeek &amp; @holesec

For the first time, a hardware backdoor tool is presented having several advanced features, such as: remote control via SMS commands, automated launch of attack payloads at a GPS location or when a specific car status is reached; and a configuration interface that allows users to create attack payloads in an easy manner.
Have you ever imagined the possibility of your car being automatically attacked based on its GPS coordinates, its current speed or any other set of parameters? Now it's possible :-)

Our project is divided in two parts: the "Car Backdoor Maker" (PC software) and "The Bicho" (hardware-backdoor for CAN bus).

## Car Backdoor Maker

The "car backdoor maker" is a PC software that allows payload customization for using with the hardware-backdoor. 
It has an intuitive graphical interface:

<p align="center">
  <img src="http://www.semecayounexploit.com/CMB/car-backdoor-maker-1.png" />
</p>

Under "car backdoor maker" folder, you'll find the source code to compile it using Qt C++ 5.6.

## The Bicho

The Bicho is a hardware-backdoor that must be connected to the car's OBD-II port.
It supports multiple attack payloads (pre-configured using Car Backdoor Maker) and it can be used against any vehicle that supports CAN, without limitations regarding manufacturer or model. Each one of the payloads is associated to a command that can be delivered via SMS, allowing remote execution from any geographical point.
Furthermore, as an advanced feature, the attack payload can be configured to be automatically executed once the victim's vehicle is proximate to a given GPS location. The execution can also be triggered by detecting the transmission of a particular CAN frame, which can be associated with the speed of the vehicle, its fuel level, and some other factors, providing the means to design highly sophisticated attacks and execute them remotely.


<p align="center">
  <img src="http://www.semecayounexploit.com/CMB/the-bicho.jpg" />
</p>

Under "hardware-schematics" and "firmware" folders you'll find all you need to build our hardware-backdoor in your own lab.

## IMPORTANT DATES

<ul>
<li> Hardware schematics release date: May 20th (2017).</li>
<li> Firware release date: July 10th (2017). </li>
<li> Car backdoor maker release date: July 10th (2017).</li>
</ul>


