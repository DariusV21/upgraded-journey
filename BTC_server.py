import serial
import time
import random
import gdax
import os
from time import gmtime, strftime

os.system('cls')

ser = serial.Serial()
ser.baudrate = 9600
ser.port = 'COM4'

ser.open()
public_client = gdax.PublicClient()

os.system('cls')
print("Serial connection opened @", ser.port, ser.baudrate)
print(strftime("%Y-%m-%d %H:%M:%S", time.localtime()))

# Wait for arduino to restart and initialise LCD.
time.sleep(5)




def sendToLCD( stringToSend ):
    #This prints a passed string into this function
    #print("stringToSend: ", str)
    ser.write(b'$')
    ser.write(stringToSend.encode())
    ser.write(b'%')
    return


def sendPercentData ( data ):
    ser.write(b'&')
    ser.write(data.encode())
    ser.write(b'*')
    return

while True:

    
    data = public_client.get_product_24hr_stats('BTC-USD')
    last = float(data["last"])
    btcopen = float(data["open"])
    #print("data: ", data)
    perc = -(100-(last/float(data["open"]))*100)
    print("BTC@ ", last, " USD, ", "{:.2f}".format(perc), "%")
    sendToLCD("{:.2f}".format(last))
    sendPercentData("{:.2f}".format(perc))
    time.sleep(30)






