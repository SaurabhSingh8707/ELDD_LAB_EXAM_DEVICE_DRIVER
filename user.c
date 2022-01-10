#include<stdio.h>
#include<sys/types.h>
#include<fcntl.h>
#include<stdlib.h>
#include<asm/ioctl.h>
#include "ioctl.h"
struct stats{
	int size;
	char buff[];
	int r_w;
};
int main()
{
	int fd,result,size=sizeof(kbuff);
	char buff[];
	struct statsdata ToSend={50,"mychar"};
	char ubuff[]="This is user buffer sending data to the kernel........";
	char kbuff[100];
	file fd=open("/dev/ioctl_chardevice",O_RDWR,0777);
	if(fd<0)
	{
		printf("\nError in opening device\n");
		exit(EXIT);
	}
	result=ioctl(fd,sizeof(kbuff));
	if(result<0)
	{
		printf("\nIOCTL error");
		return(-1);
	}
	write(fd,ubuff,sizeof(ubuff));
	read(fd,kbuff,sizeof((ubuff));
	printf("The data read from the kernel is\bn>>>>%s<<<<<\n"kbff);
	close(fd);
	}


