#!/bin/bash

n=0
for arg in $(cat /proc/cmdline); do
	case $arg in
		host2scan=*)
			host2scan_value="${arg#*=}"
			n=$((n+1))
			;;
		channel2scan=*)
			channel2scan_value="${arg#*=}"
			n=$((n+1))
			;;
		target2scan=*)
			target2scan_value="${arg#*=}"
			n=$((n+1))
			;;
		lun2scan=*)
			lun2scan_value="${arg#*=}"
			n=$((n+1))
			;;
	esac
done

if [ $n -ge 5 ]; then
	echo "scsi scan target LUN"
	echo "${channel2scan_value} ${target2scan_value} ${lun2scan_value}" > /sys/class/scsi_host/host${host2scan_value}/scan
	fi
