
import sys
sys.path.append('/home/retfie/linuxcnc-dev/lib/python/')


import serial
import time
import struct
import linuxcnc
import decodeData as dD
import CNCcommands as Cc

PORT = "/dev/ttyACM0"
ser = serial.Serial(PORT, baudrate = 115200, parity = serial.PARITY_EVEN, stopbits = serial.STOPBITS_ONE, timeout=0.5, write_timeout = 0)

try:
        s = linuxcnc.stat() # create a connection to the status channel
        s.poll() # get current values
        c = linuxcnc.command()
        print("connected to linuxcnc")
except (linuxcnc.error):
        print("unable to connect to linuxcnc")
        sys.exit(1)

Cc.sendInfo(ser,"connected to CNC")

actions = {'S' : Cc.Start, 'T' : Cc.Stop, 'A' : Cc.AUTOmode, 'M' : Cc.MDImode, 'G' : Cc.JOGmode, 'P' : Cc.Step, 'E' : Cc.Pause, 'F' : Cc.FloodON, 'f' : Cc.FloodOFF, 'O' : Cc.ON, 'o' : Cc.OFF, 'J' : Cc.JOGon,  'j' : Cc.JOGoff, 'R' : Cc.JOG, '1' : Cc.FeedSpeedSet, '0' : Cc.RapidSpeedSet, '2' : Cc.MaxSpeedSet, '3' : Cc.JOGspeedSet}

def dummyEvent(s,c,d):
    pass

t = time.time()

while 1:

    if (ser.inWaiting() > 0):
        InCMD = (ser.read(size = 1)).decode()
        if (InCMD != 'J'):
            Cc.haltJog(c);
        actions.get(InCMD,dummyEvent)(c,ser,s)

    if(time.time() - t > 0.2):
        s.poll()
        pos = s.actual_position
        mode = s.task_mode
        state = s.enabled
        #state = s.task_state

        modeChar = { linuxcnc.MODE_MDI : 'M', linuxcnc.MODE_AUTO : 'A', linuxcnc.MODE_MANUAL : 'J'}
        #stateChar = { linuxcnc.STATE_ESTOP : 'E', linuxcnc.STATE_ESTOP_RESET : 'R', linuxcnc.STATE_ON : 'O', linuxcnc.STATE_OFF : 'F'}

        if state:
            stateChar = 'O'
        else:
            stateChar = 'F'

        posX = "{:6.3f}".format(pos[0])
        posY = "{:6.3f}".format(pos[1])
        posZ = "{:6.3f}".format(pos[2])
        posStr = modeChar[mode] + stateChar + "X:" + posX + " "*(18-len(posX)) + "Y:" + posY + " "*(18-len(posY)) + "Z:" + posZ + " "*(18-len(posZ)) + "e"
        ser.write(posStr.encode())
        t = time.time()

    Cc.JOGinputRequest(ser)
