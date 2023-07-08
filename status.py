#!/usr/bin/env python3
import psutil
import time
import datetime
import os

file = open(os.path.expanduser("~/.config/statusModules"), "r")
args = []
arg = -1
mod = 0
WIFI = 0
CPU = 1
RAM = 2
SWAP = 3
STORAGE = 4
BATTERY = 5
TEMP = 6
DATE = 7
for i in file.read():
    if i == "{":
        arg += 1
        args.append("")
    elif i == "\\":
        mod = 1
    elif i == "/":
        if mod == 1:
            mod = 0
            if type(args[arg]) != type([]):
                args[arg] += i
            else:
                args[arg][-1] += i
        else:
            args[arg] = [args[arg]]
            args[arg].append("")
    elif i != "}":
        if type(args[arg]) != type([]):
            args[arg] += i
        else:
            args[arg][-1] += i

def getI(i):
    if i == "WIFI":
        return(WIFI)
    elif i == "CPU":
        return(CPU)
    elif i == "RAM":
        return(RAM)
    elif i == "SWAP":
        return(SWAP)
    elif i[:7] == "STORAGE":
        return([STORAGE, i[8:-1]])
    elif i == "BATTERY":
        return(BATTERY)
    elif i == "TEMP":
        return(TEMP)
    elif i[:4] == "DATE":
        ret = i[6:-2].split("\"")
        if len(ret) == 2 and ret[1] != "":
            print(ret)
            return([DATE, ret[0], int(ret[1][1:])])
        else:
            return([DATE, ret[0]])


def decArg(a):
    if type(a) != type([]):
        return getI(a)
    else:
        c = []
        for z in a:
            c.append(decArg(z))
        return c

for i in range(len(args)):
    args[i] = decArg(args[i])


def get_bytes(t, iface='wlp3s0'):
    try:
        with open('/sys/class/net/' + iface + '/statistics/' + t + '_bytes', 'r') as f:
            data = f.read();
            return int(data)
    except Exception:
        return 0


def getCpu():
    rx1 = get_bytes('rx')
    cpu = psutil.cpu_percent(interval=1)
    rx2 = get_bytes('rx')
    return [cpu, doWifi(round((rx2 - rx1), 4))]

def doWifi(speeeeed):
    if speeeeed < 1000:
        return speeeeed
    elif speeeeed < 1000000:
        return str(speeeeed // 1000) + " Kb"
    else:
        return str(speeeeed // 1000000) + " Mb"

out = "  "

def outArg(b, c=None, d=None):
    if b == WIFI:
        return(":{} | ".format(cpuOut[1]))
    elif b == CPU:
        return(" :{} | ".format(cpuOut[0]))
    elif b == RAM:
        return(":{} | ".format(str(psutil.virtual_memory()[3] / 1000000000)[:4]))
    elif b == SWAP:
        return(":{} | ".format(str(psutil.swap_memory()[1] / 1000000)[:4]))
    elif b == BATTERY:
        return(" {} | ".format(str(psutil.sensors_battery().percent)[:4]))
    elif b == TEMP:
        return(":{} | ".format(psutil.sensors_temperatures().get("coretemp")[0][1]))
    elif b == STORAGE:
        return(": {} | ".format(psutil.disk_usage(c)[3]))
    elif b == DATE:
        if d == None:
            return("{} | ".format(datetime.datetime.now().strftime(c)))
        else:
            return("{} | ".format(datetime.datetime.now(datetime.timezone(datetime.timedelta(hours=-4))).strftime("%d, %X, %s")))

def doArg(l, a):
    if type(l) != type([]):
        return outArg(l)
    elif l[0] == STORAGE or l[0] == DATE:
        if len(l) == 2:
            return outArg(l[0], l[1])
        else:
            return outArg(l[0], l[1], l[2])
    else:
        return doArg(l[a], a)


a = 0
while(True):
    cpuOut = getCpu()
    if a == 0:
        a = 1
    else:
        a = 0

    for i in args:
        out += doArg(i, a)
    out += " "
    os.system("xsetroot -name '{}'".format(out))
    out = "  "
