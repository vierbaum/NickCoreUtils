#!/usr/bin/env python3
import psutil
import time
import datetime
import os

def get_bytes(t, iface='wlp3s0'):
    with open('/sys/class/net/' + iface + '/statistics/' + t + '_bytes', 'r') as f:
        data = f.read();
        return int(data)

swapram = 1

while(True):

    rx1 = get_bytes('rx')

    cpu = psutil.cpu_percent(interval=1)
    ram = str(psutil.virtual_memory()[3] / 1000000000)[:4]
    swap = str(psutil.swap_memory()[1] / 1000000)[:4]
    root_dir = psutil.disk_usage('/')[3]
    home_dir = psutil.disk_usage('/home')[3]
    temp = psutil.sensors_temperatures().get("coretemp")[0][1]

    battery = psutil.sensors_battery()
    bat_perc = str(battery.percent)[:4]
    rx2 = get_bytes('rx')
    rx_speed = round((rx2 - rx1), 4)
    now = datetime.datetime.now().strftime("%d, %X")

    if swapram == 1:
        swapram = 0
        status = "  :{} |  :{}% | :{} Gi | [/]:{} |  {}% | :{} | {} |  ".format(rx_speed, cpu, ram, root_dir, bat_perc, temp, now)
    else:
        swapram = 1
        status = "  :{} |  :{}% | :{} Mb | [h]:{} |  {}% | :{} | {} |  ".format(rx_speed, cpu, swap, home_dir, bat_perc, temp, now)

    os.system("xsetroot -name '{}'".format(status))
