#!/bin/bash

/sbin/ifconfig usb0 192.168.137.10 netmask 255.255.255.0 || true
/sbin/ifconfig eth0 192.168.0.10 netmask 255.255.255.0 || true
/sbin/route add default gw 192.168.137.1 usb0
