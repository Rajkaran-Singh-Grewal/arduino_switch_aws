from sixth import data_maker as asa
import threading
"""change the port var if arduino is connected to another port"""
port="COM3"
a=asa(port)
t1=threading.Thread(target=a.make)
def get_data():
    
    import requests

    url = "https://7676hssfl5.execute-api.us-east-2.amazonaws.com/beta/arduino-id"

    headers = {
        'cache-control': "no-cache",
        'postman-token': "ce319a08-0710-6581-2d4a-88c6f9c599cf"
        }

    response = requests.request("GET", url, headers=headers)


    s=response.text
    import json
    a=json.loads(s)
    b=json.loads(a)
    with open ('json2.json','w') as f:
        json.dump(a,f)
    with open ('json3.json','w') as f:
        json.dump(b,f)
        
    print('done')
def run():
    while True:
        print("hello world")
        answer=input("Would you like to recieve the data now (y/n)")
        if answer=='y':
            get_data()

try:
    t1.start()
    run()
except:
    print('killing')
    a.running=False