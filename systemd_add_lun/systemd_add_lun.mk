SYSTEMD_ADD_LUN_VERSION = 1.0
SYSTEMD_ADD_LUN_SITE = file://$(TOPDIR)/package/systemd_add_lun/src
SYSTEMD_ADD_LUN_LICENSE = MIT
SYSTEMD_ADD_LUN_LICENSE_FILES = LICENSE

define UDEVTHING_BUILD_CMDS
    echo;
endef

define SYSTEMD_ADD_LUN_INSTALL_TARGET_CMDS
    $(INSTALL) -D -m 644 $(@D)/scsi_scan_target.target $(TARGET_DIR)/etc/systemd/system/scsi_scan_target.target
    $(INSTALL) -D -m 644 $(@D)/scsi_scan_target.service $(TARGET_DIR)/etc/systemd/system/scsi_scan_target.service
    $(INSTALL) -D -m 755 $(@D)/scsi_scan_target.sh $(TARGET_DIR)/usr/bin/scsi_scan_target.sh
endef

$(eval $(generic-package))
