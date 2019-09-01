
import linuxcnc

jogFree = True;
jogStat = False;
jogSpeed = 0.1;
rapidSpeed = 100;
feedSpeed = 100;
maxSpeed = 3200;

def Start(c,s,d):
    print("START")
    c.auto(linuxcnc.AUTO_RUN, 0)

def Stop(c,s,d):
    print("Stop")
    jogStat = False;
    c.abort()

def MDImode(c,s,d):
    print("MDI")
    global jogStat
    jogStat = False;
    c.mode(linuxcnc.MODE_MDI)

def AUTOmode(c,s,d):
    print("AUTO")
    global jogStat
    jogStat = False;
    c.mode(linuxcnc.MODE_AUTO)

def JOGmode(c,s,d):
    print("JOG")
    c.mode(linuxcnc.MODE_MANUAL)

def Step(c,s,d):
    print("Step")
    c.auto(linuxcnc.AUTO_STEP)

def Pause(c,s,d):
    print("Pause")
    if(d.task_paused):
        c.auto(linuxcnc.AUTO_RESUME)
    else:
        c.auto(linuxcnc.AUTO_PAUSE)

def FloodON(c,s,d):
    print("FloodON")
    c.flood(linuxcnc.FLOOD_ON)

def FloodOFF(c,s,d):
    print("FloodOFF")
    c.flood(linuxcnc.FLOOD_OFF)

def ON(c,s,d):
    c.state(linuxcnc.STATE_ON)

def OFF(c,s,d):
    c.state(linuxcnc.STATE_OFF)
    global jogStat
    jogStat = False

def JOGoff(c,s,d):
    global jogStat
    jogStat = False
    haltJog(c)

def JOGon(c,s,d):
    global jogStat
    jogStat = True

def JOGinputRequest(s):
    if((jogStat == True) and (jogFree == True)):
        s.write('R'.encode())
        global jogFree
        jogFree = False

def JOGspeedSet(c,s,d):
    while (s.inWaiting < 2):
        pass
    data = s.read(size = 2)
    global jogSpeed
    jogSpeed = (ord(data[0]) + ord(data[1])*256)*200/4096.0
    sendInfo(s,"Jog:" + str("{:4.1f}".format(jogSpeed)) + "mm/min")

def RapidSpeedSet(c,s,d):
    while (s.inWaiting < 2):
        pass
    data = s.read(size = 2)
    global rapidSpeed
    rapidSpeed = (ord(data[0]) + ord(data[1])*256)*100/4096
    sendInfo(s,"Rapid speed:" + str(rapidSpeed) + "%")

def FeedSpeedSet(c,s,d):
    while (s.inWaiting < 2):
        pass
    data = s.read(size = 2)
    global feedSpeed
    feedSpeed = (ord(data[0]) + ord(data[1])*256)*120/4096
    sendInfo(s,"Feed speed:" + str(feedSpeed) + "%")
    c.feedrate(feedSpeed / 100.0)

def MaxSpeedSet(c,s,d):
    while (s.inWaiting < 2):
        pass
    data = s.read(size = 2)
    global jogSpeed
    maxSpeed = 150 - (ord(data[0]) + ord(data[1])*256)*150/4096
    sendInfo(s,"Max Speed:" + str(maxSpeed) + "%")
    c.maxvel(maxSpeed / 100.0)

def JOG(c,s,d):
    global jogFree
    jogFree = True

    while (s.inWaiting < 8):
        pass
    data = s.read(size = 8)

    jogVel = [None] * 4
    jogVel[0] = (1 - (ord(data[0]) + ord(data[1])*256)/2048.0)
    jogVel[1] = ((ord(data[2]) + ord(data[3])*256)/2048.0 -1)
    jogVel[3] = ((ord(data[4]) + ord(data[5])*256)/2048.0 -1)
    jogVel[2] = ((ord(data[6]) + ord(data[7])*256)/2048.0 -1)

    for ii in range(len(jogVel)):
        if ((jogVel[ii] < -0.07) or (jogVel[ii] > 0.07)):
            c.jog(linuxcnc.JOG_CONTINUOUS, 0, ii, jogVel[ii] * jogSpeed)
        else:
            c.jog(linuxcnc.JOG_STOP, 0, ii)


def sendInfo(s,str):
    encStr = ('{:<21}'.format('I' + str)).encode()
    s.write(encStr)

def haltJog(c):
    if(jogStat):
        c.jog(linuxcnc.JOG_STOP, 0, 0)
        c.jog(linuxcnc.JOG_STOP, 0, 1)
        c.jog(linuxcnc.JOG_STOP, 0, 2)
