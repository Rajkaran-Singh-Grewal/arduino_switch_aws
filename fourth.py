import serial
import time
import csv
from itertools import count
import json
class data_maker:
    def __init__(self,port):
        self.index=count()
        self.ser = serial.Serial(port)
        self.ser.flushInput()
        self.fieldnames=["Time", "analog signal", "classifier"]
        self.d={
           "0":[0],"1":[0]
           }
        with open ('js2.json','w+') as f:
                json.dump(self.d,f,indent=2,sort_keys=True)
    def make(self):
        with open('data.csv', 'w') as csv_file:
            csv_writer = csv.DictWriter(csv_file, fieldnames=self.fieldnames)
            csv_writer.writeheader()
        while True:
            #try:
            ser_bytes = self.ser.readline()
            decoded_bytes = ser_bytes[0:len(ser_bytes)-2].decode("utf-8")
            a=decoded_bytes.split(",")
            try:
                b=a[0]
                c=a[1]
            except:
                continue
            print(b+","+c)
            with open("data.csv","a") as f:
                csv_writer = csv.DictWriter(f, fieldnames=self.fieldnames)
        
                info = {
                    "Time": time.time(),
                    "analog signal": b,
                    "classifier": c
                }
                
                csv_writer.writerow(info)
            self.d[str(c)]=[next(self.index)]
            with open ('js2.json','w+') as f:
                json.dump(self.d,f,indent=2)
            #except:
             #   print("Keyboard Interrupt")
              #  break
#a=data_maker()
#a.make()