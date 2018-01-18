import serial
import time
import random
import gdax

ser = serial.Serial()
ser.baudrate = 9600
ser.port = 'COM4'

ser.open()



curPrice = 0

class myWebsocketClient(gdax.WebsocketClient):
    def on_open(self):
        self.url = "wss://ws-feed.gdax.com/"
        self.products = ["BTC-USD"]
        print("WebSocket is oppened")
    def on_message(self, msg):
        if 'price' in msg and 'type' in msg:
            #print ("Message type:", msg["type"],
                   #\t@ {:.3f}".format(float(msg["price"])))'''
            curPrice = "{:.2f}".format(float(msg["price"]))
            sendToLCD(curPrice)
        time.sleep(1)
    def on_close(self):
        print("-- Goodbye! --")

wsClient = myWebsocketClient()
wsClient.start()
print(wsClient.url, wsClient.products)
#wsClient.close()

print("It works and i don't know why...")



def sendToLCD( str ):
   #"This prints a passed string into this function"
    #print("string: ", str)
    ser.write(b'$')
    ser.write(str.encode())
    ser.write(b'%')
    time.sleep(1)
    return



