# File         : GPS_ACC_integration                                                                               # 
# author       : Nariman Alaa - Dalia Abdullah                                                                     #
# Description  : This file gets the accelerometr and GPS readings and parse it                                     #
#                Then send their data to the stm32 microcontroller to take action depend on accelerometr status    #
# version      : 1.0.0                                                                                             #
# date         : 2-15-2023                                                                                         #
####################################################################################################################

import time
import string

#GPS used libraries
import serial
import string
import pynmea2
import sys

# ADXL345 module used libraries
import Adafruit_ADXL345


# Create an ADXL345 instance.
accel = Adafruit_ADXL345.ADXL345()

#Intialization of UART for recieving data from GPS module and send data to stm32 microcontroller
port="/dev/ttyAMA0"
ser = serial.Serial(port,baudrate = 9600,parity=serial.PARITY_NONE,stopbits=serial.STOPBITS_ONE,bytesize=serial.EIGHTBITS,timeout=0.5)


while True:

    #Getting the data from the GPS module and store it in a variable
    dataout = pynmea2.NMEAStreamReader()
    newdata=ser.readline()
    if sys.version_info[0] == 3: 
        newdata = newdata.decode("utf-8","ignore")
		
    # Read the X, Y, Z axis acceleration values and print them.
    x, y, z = accel.read()
	
    #Parsing the output data from GPS to get latitude and longitude
    if newdata[0:6] == "$GPRMC":
        newmsg=pynmea2.parse(newdata)
        lat=newmsg.latitude
        lng=newmsg.longitude
		
		#the string that will sent to the stm32 microcontroller
		#the first thing in the string is the status of the accelerometer that indicates that accident happened
		#then the latitude and longitude of the vehicle's location 
		#the latitude and the longitude are seprated by * and end by # for making parsing easier when string recieved by stm32 microcontroller
        gps="1"+str(lat)+"*"+ str(lng)+"#"
		
		#check on the readings of the Acceleromter to detect the vehicle's behaviour
        if -200>x>-300 or 300>x>250 or 300>y>200 or -200>y>-300:
            ser.write(gps.encode())
            time.sleep(0.5)
      