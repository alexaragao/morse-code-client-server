from flask import Flask, json
from flask_socketio import SocketIO, send

from nodemcu_connection import serverConnection

app = Flask(__name__)

socketIo = SocketIO(app, cors_allowed_origins="*")

app.debug = True

app.host = 'localhost'

text = {
  ".-": "A",
  "-...": "B",
  "-.-.": "C",
  "-..": "D",
  ".": "E",
  "..-.": "F",
  "--.": "G",
  "....": "H",
  "..": "I",
  ".---": "J",
  "-.-": "K",
  ".-..": "L",
  "--": "M",
  "-.": "N",
  "---": "O",
  ".--.": "P",
  "--.-": "Q",
  ".-.": "R",
  "...": "S",
  "-": "T",
  "..-": "U",
  "...-": "V",
  ".--": "X",
  "-..-": "W",
  "-.--": "Y",
  "--..": "Z",
  ".----": "1",
  "..---": "2",
  "...--": "3",
  "....-": "4",
  ".....": "5",
  "-....": "6",
  "--...": "7",
  "---..": "8",
  "----.": "9",
  "-----": "0"
}

@socketIo.on("message")
def sendMessage():
  # send(json.dumps({ "morse": ".", "text": text["."] }))
  serverConnection(lambda msg: send({ "morse": msg, "text": text[msg] }, broadcast=True))
  return None

if __name__ == '__main__':
  socketIo.run(app)