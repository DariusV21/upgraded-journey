import serial
from forex_python.bitcoin import BtcConverter
import time

ser = serial.Serial()
ser.baudrate = 9600
ser.port = 'COM4'
ser.open()

b = BtcConverter()


time.sleep(5)

while True:
    

    ser.write(b'$')
    
    l = b.get_latest_price('USD')

    s = str(round(l, 3))
    
    ser.write(s.encode())

    ser.write(b'%')




    time.sleep(5)
