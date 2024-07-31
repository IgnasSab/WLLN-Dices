import serial
import time
import cv2

arduino = serial.Serial(port='COM4', baudrate = 9600, timeout=.1)


def captureFrame():
    print("FRAME CAPTURED") # TODO
    return processFrame()

def processFrame():
    pip_num = 0
    print("PROCESSING FRAME") # TODO
    return pip_num

while True: # Infinite loop
    if arduino.in_waiting > 0:  
        line = sort_ser.readline().decode('utf-8') # Read data from arduino
        if (line.endswith('\n') and line.strip() == "CAPTURE"):  
            # Capture the frame
            pip_num = captureFrame()
            arduino.write(bytes(pip_num,   'utf-8'))


        
