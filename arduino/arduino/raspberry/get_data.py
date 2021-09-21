import time
import serial
import json

ser = serial.Serial(port='COM10', baudrate=9600, timeout=.1)

def get_data():
    while True:
        data = ser.readline()
        data = data.decode("utf-8")
        print(data)
        if data != "":
            return json.loads(data)
            

