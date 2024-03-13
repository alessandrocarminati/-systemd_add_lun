#!/bin/sh
cd ./systemd_add_lun
tar zcvf src/systemd_add_lun-1.0.tar.gz src/scsi_scan_target.target src/scsi_scan_target.sh src/scsi_scan_target.service
cd ../systemd_add_lun_q
tar zcvf src/systemd_add_lun_q-1.0.tar.gz src/scsi_scan_target.service src/scsi_scan_target.target src/scsi_scan_target.c
cd ..
