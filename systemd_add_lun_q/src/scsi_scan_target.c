//#define DEBUG
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define MAX_ARGS 100
#define MAX_BUF 128

#ifndef DEBUG
#define CMDLINE "/proc/cmdline"
#define SCSI_SYS_TMPL "/sys/class/scsi_host/host%d/scan"
#else
#define CMDLINE "cmdline"
#define SCSI_SYS_TMPL "host%dscan"
#endif

#define SCSI_SYS_SCAN_STR "%d %d %d\n"
#define SUCCESS_STR "scsi scan target LUN [\e[0;32mOK\e[0m]\n"
#define FAIL_STR "scsi scan target LUN [\e[0;31mFAILED\e[0m]\n"



#ifdef DEBUG
#define DBG_PRINT(...) do{ fprintf( stderr, __VA_ARGS__ ); } while( 0 )
#else
#define DBG_PRINT(...) do {} while (0)
#endif

static int c2i(char *str){
	char *endptr;
	int num;

	errno = 0;
	num = strtol(str, &endptr, 10);
	if ((errno != 0 && num == 0) || (num > 99)) return -1;
	if (endptr == str) return -1;
	return num;
}

__attribute__((noreturn))
static void die() {
	printf(FAIL_STR);
	exit(1);
}

int main() {
	int host2scan_value, channel2scan_value, target2scan_value, lun2scan_value;
	char cmdline[MAX_BUF];
	char buf[MAX_BUF];
	FILE *file;
	int n = 0;

	file = fopen(CMDLINE, "r");
	if (file == NULL) die();

	while (fgets(cmdline, sizeof(cmdline), file)) {
		char *token = strtok(cmdline, " ");
		while (token != NULL) {
			if (strncmp(token, "host2scan=", strlen("host2scan=")) == 0) {
				char *value = strchr(token, '=') + 1;
				host2scan_value = c2i(value);
				if (host2scan_value < 0) die();
				DBG_PRINT("host2scan_value=%d\n", host2scan_value);
				n++;
			}
			if (strncmp(token, "channel2scan=", strlen("channel2scan=")) == 0) {
				char *value = strchr(token, '=') + 1;
				channel2scan_value = c2i(value);
				if (channel2scan_value < 0) die();
				DBG_PRINT("channel2scan_value=%d\n", channel2scan_value);
				n++;
			}
			if (strncmp(token, "target2scan=", strlen("target2scan=")) == 0) {
				char *value = strchr(token, '=') + 1;
				target2scan_value = c2i(value);
				if (target2scan_value < 0) die();
				DBG_PRINT("target2scan_value=%d\n", target2scan_value);
				n++;
			}
			if (strncmp(token, "lun2scan=", strlen("lun2scan=")) == 0) {
				char *value = strchr(token, '=') + 1;
				lun2scan_value = c2i(value);
				if (lun2scan_value < 0) die();
				DBG_PRINT("lun2scan_value=%d\n", lun2scan_value);
				n++;
			}
			token = strtok(NULL, " ");
		}
	}

	fclose(file);

	if (n == 4) {
		sprintf(buf, SCSI_SYS_TMPL, host2scan_value);
		DBG_PRINT("Filename=%s\n", buf);
		file = fopen(buf, "w");
		if (file == NULL) die();
		n = snprintf(buf, MAX_BUF, SCSI_SYS_SCAN_STR, channel2scan_value, target2scan_value, lun2scan_value);
		DBG_PRINT("buffer=\"%s\", size=%d\n", buf, n);
		fwrite(buf, n, 1, file);
		fclose(file);
		printf(SUCCESS_STR);
		exit(0);
	}
	die();

}
