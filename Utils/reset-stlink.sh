#!/bin/bash
deviceNameRegex='.*ST-LINK.*'

bus=$(lsusb | grep -P -o "(?<=Bus )\d{3}(?= Device \d{3}: ID [[:xdigit:]]{4}:[[:xdigit:]]{4} $deviceNameRegex)")
device=$(lsusb | grep -P -o "(?<= Device )\d{3}(?=: ID [[:xdigit:]]{4}:[[:xdigit:]]{4} $deviceNameRegex)")

devicePath="/dev/bus/usb/$bus/$device"

[[ $bus == "" || $device == "" ]] && printf "not found\n" || Utils/usbreset/usbreset $devicePath

