import serial
import time

arduino = serial.Serial(port = 'COM3', baudrate = 9600)
time.sleep(2)


while True:

    print ("Enter '1' to turn 'on' the LED and '0' to turn LED 'off'")

    var = str(input())
    print ("You Entered :", var)

    # 1 is for happy
    if(var == '0'):
        arduino.write(str.encode('0'))
        print("Happy")
        time.sleep(1)

    # 0 is for sad
    if(var == '1'):
        arduino.write(str.encode('1'))
        print("Happy")
    
    if(var == '2'):
        arduino.write(str.encode('2'))
        print("Sad")
    if(var == '3'):
        arduino.write(str.encode('3'))
        print("Sad")