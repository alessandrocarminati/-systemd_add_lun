SYSTEMD_ADD_LUN_Q_VERSION = 1.0
SYSTEMD_ADD_LUN_Q_SITE = file://$(TOPDIR)/package/systemd_add_lun_q/src
SYSTEMD_ADD_LUN_Q_LICENSE = MIT
SYSTEMD_ADD_LUN_Q_LICENSE_FILES = LICENSE

define SYSTEMD_ADD_LUN_Q_BUILD_CMDS
    $(TARGET_CC) $(TARGET_CFLAGS) -static -o $(@D)/scsi_scan_target $(@D)/scsi_scan_target.c
endef

define SYSTEMD_ADD_LUN_Q_INSTALL_TARGET_CMDS
    $(INSTALL) -D -m 644 $(@D)/scsi_scan_target.target $(TARGET_DIR)/etc/systemd/system/scsi_scan_target.target
    $(INSTALL) -D -m 644 $(@D)/scsi_scan_target.service $(TARGET_DIR)/etc/systemd/system/scsi_scan_target.service
    $(INSTALL) -D -m 755 $(@D)/scsi_scan_target $(TARGET_DIR)/usr/bin/scsi_scan_target
endef

$(eval $(generic-package))
