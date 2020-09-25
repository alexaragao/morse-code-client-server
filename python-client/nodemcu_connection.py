import socket
import time

HOST = '192.168.0.39' # NodeMCU WiFi ipv4
PORT = 8626

def serverConnection(callback):
  with socket.socket() as s:
    s.connect((HOST, PORT))
    message = ""
    while True:
      data = s.recv(44)
      if len(data) != 0:
        try:
          data = data[:5]
          message = data.decode()
          print(message)
          callback(message)
        except:
          print("error")
    s.close()

if __name__ == '__main__':
  serverConnection(print)