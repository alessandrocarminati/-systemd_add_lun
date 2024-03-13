# systemd Add-in for Buildroot

## Introduction
This project aims to optimize the boot time within a system by providing
a systemd add-in for Buildroot. 
The specific focus of this module is to enumerate a particular LUN 
within a SCSI chain containing multiple devices. 
By leveraging systemd capabilities and configuring the kernel arguments
appropriately, this module efficiently scans the intended LUN, reducing 
boot time by avoiding unnecessary device scans.

## Purpose
In systems, especially embedded environments utilizing Buildroot, optimizing
boot time is critical for efficient operation.
Default method involve the Linux kernel scanning all devices within a SCSI 
chain during boot, which can lead to significant delays.
This project addresses this issue by introducing a systemd add-in that
intelligently scans only the intended LUN, leaving other devices for
later enumeration.

## Functionality
The key functionalities of this systemd add-in include:

* Enumerating a specific LUN within a SCSI chain.
* Utilizing the `scsi_mod.scan=manual` kernel argument to prevent automatic 
scanning of all devices in the chain.
* Use fake kernel arguments (`host2scan`, `channel2scan`, `target2scan`, 
`lun2scan`) to specify the controller, channel, target, and intended LUN for
scanning.

## Usage
To use this systemd add-in effectively, follow these steps:

* Ensure that the `scsi_mod.scan=manual` kernel argument is used to prevent
the kernel from scanning all devices in the SCSI chain.
* Pass the following fake kernel arguments:
    * host2scan: Specify the controller where the scan will be performed.
    * channel2scan: Specify the channel for scanning.
    * target2scan: Specify the SCSI target for scanning.
    * lun2scan: Specify the intended LUN for scanning.
* Integrate the provided systemd add-in into your Buildroot project.
* Configure systemd to execute the add-in during boot.
* Use `init.sh` to initialize the two buildroot packages

## Directories
The project contain two directories:
* `systemd_add_lun` is the prototype directory where the actual scan is 
performed by a bash script
* `systemd_add_lun_q` is the directory containing the c version of the 
script for quicker activation.

