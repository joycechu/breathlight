#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <fcntl.h>
#include <math.h>

#define _USE_MATH_DEFINES

void initpwm(int frequency) //config and init pwm, only need to do once, max frequency 1Mhz
{
	system("modprobe pwm-meson");
	system("modprobe pwm-ctrl");
	system("cd /sys/devices/platform/pwm-ctrl/; echo 1 > enable0");
	char buffer1[100];
	sprintf(buffer1, "cd /sys/devices/platform/pwm-ctrl/; echo %d > freq0", frequency);
	system (buffer1);
	system("cd /sys/devices/platform/pwm-ctrl/; echo 0 > duty0");
}

void gpiowrite(int state)
{
char exbuf[64];
char valbuf[5];
int ret;
int bytesread = 0;
int writedata = 1;
int fdg;
int fdr;

    sprintf(exbuf, "/sys/devices/platform/pwm-ctrl/duty0");

    fdr = open(exbuf, O_RDONLY);
      bytesread = read(fdr,&valbuf,sizeof(valbuf)-1);
      if(!bytesread)
      {
         fprintf(stderr,"could not read from gpio at %s \n", exbuf);
      }
      if(atoi(valbuf) == state)
      {
         writedata = 0;
      }
    close(fdr);
	  
   if(writedata)
   {
      fdg = open(exbuf, O_WRONLY || O_TRUNC);
      snprintf(valbuf,sizeof(valbuf),"%d",state);
      ret = write(fdg, valbuf, sizeof(valbuf)-1);
      if(!ret || ret == -1)
      {
         fprintf(stderr,"could not write to gpio at %s \n", exbuf);
      }
      close(fdg);
   }
}


int main(void)
{
	int i;
	float j;
	initpwm(120);
	while(1) {
		for(i=0;i<=1000;i++) {
			j=floor(1000*sin(M_PI/2000*i-M_PI/2)+1000);
			gpiowrite(j);
			usleep(1500);
		}

		for(i=1000-1;i>=0;i--) {
			j=floor(1000*sin(M_PI/2000*i-M_PI/2)+1000);
			gpiowrite(j);
			usleep(1500);
		}

		sleep(2);
	}

	return 0;
}
