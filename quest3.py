import requests
import random
import time

for i in range(10):
    value = random.randrange(0,50)
    r = requests.get("https://api.thingspeak.com/update?api_key=KVFLJ8EI8L9HBJYK&field1="+str(value))
    r.encoding = 'utf8'
    print(value)
    time.sleep(20)

