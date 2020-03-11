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
        self.running=True
        #self.fieldnames=["classifier", "time"]
        self.d={}
        self.i=0
        with open('js2.json','w+') as f:
            json.dump(self.d,f,indent=2)
        self.kk={}
    def make(self):
        """with open('data.csv', 'w') as csv_file:
            csv_writer = csv.DictWriter(csv_file, fieldnames=self.fieldnames)
            csv_writer.writeheader()
        """
        while self.running:
            try:
                ser_bytes = self.ser.readline()
                decoded_bytes = ser_bytes[0:len(ser_bytes)-2].decode("utf-8")
                a=decoded_bytes.split(",")
                try:
                    b=a[0]
                    c=a[1]
                    e=a[2]
                except:
                    continue
                
                e=float(e)
                #print(e)
                e=e/(10**6)
                
                
                print(b+","+c+","+str(e))
                
                """with open("data.csv","a") as f:
                    csv_writer = csv.DictWriter(f, fieldnames=self.fieldnames)
            
                    info = {
                        
                        
                        "classifier": c
                    }
                    
                    csv_writer.writerow(info)
                """
                #self.d[str(c)]=[next(self.index)]
                
                self.d.update({str(self.i):{"id":b,"status":c,"time in seconds":e}})
                with open ('js2.json','w+') as f:
                    json.dump(self.d,f,indent=2)
                    
                with open('js2.json','r') as f:
                    d=json.load(f)
                self.i=len(d)
                import requests
               
                url = "https://7676hssfl5.execute-api.us-east-2.amazonaws.com/beta/arduino-id"

                
                payload = {"id":str(b),"status":str(c),"time in seconds":str(e)}
                print(payload)
                headers = {
                    'content-type': "application/json",
                    'cache-control': "no-cache",
                    'postman-token': "695f3c99-0233-fcce-27a1-62d64b0006d1"
                    }
                payload=json.dumps(payload)
                print(payload)
                response = requests.request("POST", url, data=payload, headers=headers)
                print('done')
                #print(response.write)
            except:
                print("Keyboard Interrupt")
                break
            
#Enter the port in which the arduino is connected to
