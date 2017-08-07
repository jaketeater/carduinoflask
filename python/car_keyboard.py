import serial
from time import sleep
from pynput import keyboard

def on_press(key):
    if key == keyboard.Key.up:
        ser.write('8')
    if key == keyboard.Key.left:
        ser.write('4')
    if key == keyboard.Key.right:
        ser.write('6')
    if key == keyboard.Key.down:
        ser.write('2')

def on_release(key):
    print key
    if key == keyboard.Key.up:
        ser.write('5')
    if key == keyboard.Key.left:
        ser.write('0')
    if key == keyboard.Key.right:
        ser.write('0')
    if key == keyboard.Key.down:
        ser.write('5')

ser = serial.Serial('COM3', 115200)
sleep(1)

with keyboard.Listener(
        on_press=on_press,
        on_release=on_release) as listener:
    listener.join()
