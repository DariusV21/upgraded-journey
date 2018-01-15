import serial
from forex_python.bitcoin import BtcConverter
import time
import random

ser = serial.Serial()
ser.baudrate = 9600
ser.port = 'COM4'
ser.open()

b = BtcConverter()



demo = True

time.sleep(5)

print("Demo is: ", demo)

while True:
    

    ser.write(b'$')
    
    bitcoinValue = b.get_latest_price('USD')

    rnd = random.randint(13500, 14500);


    if not demo:
       stringToSend = str(round(bitcoinValue, 3))
    else:
       stringToSend = str(round(rnd, 3))
    
    
    ser.write(stringToSend.encode())

    ser.write(b'%')



if not demo:
    time.sleep(30)
else:
    time.sleep(3)
    
    
