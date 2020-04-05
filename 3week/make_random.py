import requests
import random

value = random.randrange(10,20)
r= requests.get("http://ec2-34-229-114-134.compute-1.amazonaws.com:8080/sensor?value="+str(value))
r.encoding = 'utf8'
print(value);
