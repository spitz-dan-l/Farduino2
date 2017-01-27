import serial, time, getch

import threading

arduinoSerial = serial.Serial('/dev/cu.wchusbserial1410', 9600, timeout=0.1)
tmpData = 0.0

import struct


def make_instruction(x, y, servo_1, servo_2, pump):
    return struct.pack('bbbbb', x, y, servo_1, servo_2, pump)

def main():
    thread = threading.Thread(target=serial_output, args=())
    thread.daemon = True
    thread.start()

    print("Press [W, A, S, or D]\n")
    while(True):
        rawKey = getch.getch()
        
        key = rawKey.upper()
        print("You pressed: ", key)

        if(key == "A"):
            ins = make_instruction(0, 0, 1, 0, 0)
        elif(key == "Q"):
            ins = make_instruction(0, 0, 2, 0, 0)
        elif(key == "W"):
            ins = make_instruction(0, 0, 0, 1, 0)
        elif(key == "S"):
            ins = make_instruction(0, 0, 0, 2, 0)
        elif(key == 'E'):
            ins = make_instruction(0, 0, 0, 0, 1)
        elif(key == 'D'):
            ins = make_instruction(0, 0, 0, 0, 2)

        arduinoSerial.write(ins)

        if(key == "0"):
            break

        time.sleep(0.1)
            

    arduinoSerial.close()
    print("Program terminated")

def test():
    thread = threading.Thread(target=serial_output, args=())
    thread.daemon = True
    thread.start()

    inss = [
        (-1, 0),
        (1, 0),
        (0, 1),
        (0, -1),
        (0, 0)
    ]

    binss = [make_instruction(*i) for i in inss]

    for i,b in zip(inss, binss):
        print('writing instruction', i)
        arduinoSerial.write(b)
        time.sleep(0.4)
        
    while True: time.sleep(1)

def serial_output():
    while True:
        if arduinoSerial.inWaiting() > 0:
            print(arduinoSerial.readline())
        time.sleep(0.01)


if __name__ == '__main__':
    main()
