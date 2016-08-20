import serial, time, msvcrt

arduinoSerial = serial.Serial('com3', 9600, timeout=0.1)
time.sleep(2)
tmpData = 0.0

import struct


def make_instruction(x, y):
    return struct.pack('Bbb', 2, x, y)

def main():
    while(True):
        print("Press [W, A, S, or D]\n")
        
        rawKey = msvcrt.getch()
        
        key = rawKey.decode()
        print "You pressed: " + key

        if(key == "A"):
            ins = make_instruction(-1, 0)
        elif(key == "D"):
            ins = make_instruction(1, 0)
        elif(key == "W"):
            ins = make_instruction(0, 1)
        elif(key == "S"):
            ins = make_instruction(0, -1)
        else:
            ins = make_instruction(0, 0)

        arduinoSerial.write(ins)

        if(key == "0"):
            break
            
        if(arduinoSerial.inWaiting() > 0):
            tmpData = arduinoSerial.readline()
                print float(tmpData)

    arduinoSerial.close()
    print("Program terminated")

if __name__ == '__main__':
    main()
