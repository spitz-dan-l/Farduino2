import serial, time, msvcrt

arduinoSerial = serial.Serial('com3', 9600, timeout=0.1);
time.sleep(2);
tmpData = 0.0;

while(1):
	print("Press [W, A, S, or D]\n");
	
	rawKey = msvcrt.getch();
	
	key = rawKey.decode();
	print("You pressed: " + key);

	if(key == "A"):
		arduinoSerial.write('1'.encode());
	elif(key == "D"):
		arduinoSerial.write('2'.encode());
	elif(key == "W"):
		arduinoSerial.write('3'.encode());
	elif(key == "S"):
		arduinoSerial.write('4'.encode());
	else:
		arduinoSerial.write('0'.encode());
		
	if(key == "0"):
		break;
		
	if(arduinoSerial.inWaiting() > 0):
		tmpData = arduinoSerial.readline();
		print(float (tmpData));

arduinoSerial.close();
print("Program terminated");