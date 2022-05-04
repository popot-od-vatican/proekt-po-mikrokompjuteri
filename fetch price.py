import serial
import requests
import json
import time

ard = serial.Serial('COM2', 9600)

url = 'https://api.binance.com/api/v3/ticker/price?symbol=BTCUSDT'
price = None
delay = 5

while True:
  # get data
  res = requests.get(url)
  if res.status_code == 200:
    price = float(res.json()['price'])
    print('OK')
  elif res.status_code == 429:
    print('Increasing delay limit!')
    delay += 5
  elif res.status_code == 418:
    print('Banned')
    exit(0)
  else:
    pass

  price = round(price, 2)
  print(price)
  #ard.write(str(price).encode())
  time.sleep(delay)
