import eventlet
eventlet.monkey_patch()

import serial
from time import sleep
from flask import Flask, request, send_from_directory
from flask_socketio import SocketIO

app = Flask(__name__)
socketio = SocketIO(app)

"""
This is the path to your serial port. In my case, COM3 is where the arduino
is connected to on my Windows computer.  You can get this by plugging your
arduino in, opening the arduino ide and then navigating to Tools -> Port.
"""
path_to_serial = 'COM3'

"""
The variable is used to specify the port that the server use.
"""
server_port = 8080

"""
This end point basically says to interpret anything after / in the URL as
a path, ie, an address to a file.  We then return the file at that path
inside the templates directory.
"""
@app.route('/<path:path>')
def templates(path):
    return send_from_directory('templates', path)


"""
We are going to use sockets instead of traditional URLs so that our
little server runs a bit faster.  What we define are basically event
listeners. If the forward event is triggered (emited from the browser)
then we write an int 8 to the serial port.  
"""
@socketio.on('forward')
def handle_my_custom_event():
    print "forward"
    ser.write('8')

@socketio.on('stop')
def handle_my_custom_event():
    ser.write('5')
    print "stop"

@socketio.on('backward')
def handle_my_custom_event():
    ser.write('2')
    print "backward"

@socketio.on('left')
def handle_my_custom_event():
    ser.write('4')
    print "left"

@socketio.on('straight')
def handle_my_custom_event():
    ser.write('0')
    print "straight"

@socketio.on('right')
def handle_my_custom_event():
    ser.write('6')
    print "right"

if __name__ == "__main__":
    """
    Start up the server!

    By setting the host to 0.0.0.0, we should be able to connec to the server
    over any interface.
    """
    with app.app_context():
        ser = serial.Serial(path_to_serial, 115200)
    socketio.run(app, host='0.0.0.0', server_port=server_port)
