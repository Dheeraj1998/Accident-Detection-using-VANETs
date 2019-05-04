# Accident detection using VANETs
<p align = "center"><img src="Screenshots/Project Icon.png" width = 10%"></img></p>
This project builds an accident detection system based on the concept of VANETs. An ad-hoc network is build on the highway with the use of RF transmitters and receivers. These can help transmit the messages containing the location of the affected vehicle and other identifying details for the vehicle. 

## Architecture diagram
<p align = "center"><img src="Screenshots/Architecture.png" align = "center"></img></p>

## Working of hardware
<p align = "center"><img src="Screenshots/Hardware Working.gif"></img></p>

The **key insights** from this GIF visualisation are:
1. The receivers of the vehicles are kept on at all durations.
2. In an event of an accident, the data is recorded by the MPU6050 sensor (accelerometer + gyroscope).
3. The data is transmitted to the on-board processor - Arduino development board.
4. Using pre-trained algorithms, we determine whether the recorded data is an accident or not.
5. In case of a detected accident, the receivers are turned off and the transmitter is switched on.
6. The data would consists of VIN (Vehicle Identification Number) along with the location of the accident.

## Demostration
<img src="Screenshots/Arduino Working.png"></img>
<img src="Screenshots/Website Working.png"></img>

## Project files
The files in [Arduino-Code](https://github.com/Dheeraj1998/Accident-Detection-using-VANETs/tree/master/Arduino-Code) folder contains the code for different stages of the project. The **[LCD_MPU_TR](https://github.com/Dheeraj1998/Accident-Detection-using-VANETs/tree/master/Arduino-Code/LCD_MPU_TR)** is the final Arduino code for *LCD screen + MPU sensor + RF transmitter + RF receiver*. **[Website-Code](https://github.com/Dheeraj1998/Accident-Detection-using-VANETs/tree/master/Website-Code)** has the Firebase hosted website to display the locations of the accidents.

## Project details
This project was developed during the summer vacations of 2017 as part of the **Summer Research Grant Programme - 2017** conducted by the SENSE school, VIT University.
