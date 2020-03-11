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
    json.dump(b,f)