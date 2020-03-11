import requests
import json
url = "https://7676hssfl5.execute-api.us-east-2.amazonaws.com/beta/arduino-id"

payload = {"id":"799",    "time":"78787878"}
headers = {
    'content-type': "application/json",
    'cache-control': "no-cache",
    'postman-token': "695f3c99-0233-fcce-27a1-62d64b0006d1"
    }
payload=json.dumps(payload)
response = requests.request("POST", url, data=payload, headers=headers)
#response=requests.request("GET",url)
