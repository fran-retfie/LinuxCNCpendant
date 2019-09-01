import tkinter as tk
import tk_tools
import serial

import decodeData as dD

LedNum = 18
GaugesNum = 8

PORT = "/dev/ttyACM0"
ser = serial.Serial(PORT, 9600, timeout=2)


window = tk.Tk()
window.title("Arduino I/0")
window.geometry('450x450')


leds = [None] * LedNum
for ii in range(LedNum):
    leds[ii] = tk_tools.Led(window, size=25)
    leds[ii].grid(row=ii//4+2, column=ii%4)

gauges = [None] * GaugesNum
for ii in range(GaugesNum):
    gauges[ii] = tk_tools.RotaryScale(window, max_value=100.0, size=100, unit='%')
    gauges[ii].grid(row=ii//4, column=ii%4)


readFlag = True;
cnt = 1

while 1:

    if (readFlag == True):
        readFlag = False
        ser.write('A'.encode())

    if (ser.inWaiting() >= 20):
        readFlag = True

        rawData = ser.read(size=20)
        if rawData[0] == 0x55:
            Data = dD.decodeData(rawData)
        else:
            print("Broken packet")
            ser.flush()

        if Data:
            for ii in range(LedNum-2):
                leds[ii].to_green(on=(Data['Buttons'] & (0x01<<ii)))
            leds[16].to_green(on=(Data['jogButtons'] & 0x01))
            leds[17].to_green(on=(Data['jogButtons'] & 0x02))

            gauges[0].set_value(Data['Pot0'])
            gauges[1].set_value(Data['Pot1'])
            gauges[2].set_value(Data['Pot2'])
            gauges[3].set_value(Data['Pot3'])
            gauges[4].set_value(Data['JogX'])
            gauges[5].set_value(Data['JogY'])
            gauges[6].set_value(Data['JogZ'])
            gauges[7].set_value(Data['JogA'])



    window.update_idletasks()
    window.update()
