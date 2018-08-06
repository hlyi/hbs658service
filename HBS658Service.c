#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/select.h>
#include <time.h>
#include <sys/ioctl.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/ipc.h>
#include <dirent.h>
#include <stdint.h>
#include <signal.h>

#include <time.h>

#include "../linux/drivers/amlogic/led/led_hbs658.h"

#define DEV_NAME	"/sys/class/leds/led-hbs658/data_cmd"
#define COL_BIT		4


int main(int argc, char *argv[])
{
	int		fd;
	struct tm *	curtime;
	time_t		rawtime;
	int		last_hour =-1;
	int		last_min = -1;
	char		buf[5];

	fd = open(DEV_NAME, O_WRONLY);
	if (fd < 0) {
		printf("Error: Open device failed %s.\n", DEV_NAME);
		exit(1);
	}

	do {
		rawtime = time(NULL);
		curtime = localtime(&rawtime);
		buf[0] = HBS658_DEV_MAGIC;
		buf[1] = HBS658_DEV_CMD_ICON | HBS658_DEV_SUBCMD_ICON_TOGGLE | COL_BIT;
		write ( fd, buf, 2);
		if ( last_hour != curtime->tm_hour || last_min != curtime->tm_min) {
			buf[1] = HBS658_DEV_CMD_DATA;
			last_hour = curtime->tm_hour;
			last_min = curtime->tm_min;
			if ( last_hour > 9 ) {
				buf[2] = (last_hour/10)<<4; 
			}else{
				buf[2] = 0xf0;
			}
			buf[2] += last_hour %10;
			buf[3] =  (last_min /10) << 4;
			buf[3] += last_min % 10;
			write(fd, buf, 4 );
		}	
		usleep(500000);
	} while (1);
	
	close(fd);
}
