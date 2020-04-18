import random
import time
import serial

ser = serial.Serial('com11', 115200)
time.sleep(1)


while(1):
	x = float(random.uniform(500,501))
	y = float(random.uniform(499,502))
	
	time.sleep(.1)
	
	
	command = str(x)
	command+=","
	command+=str(y)
	command+='\n'
	
	ser.write(command)
	
	print(x,y,"\n")
	