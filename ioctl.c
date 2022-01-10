/* Verify User Read/Write operations using IOCTL functionality.
Write a Simple character driver with Open , Read ,Write , Close and Ioctl Functionality.
Initialize Structure in Kernel space which records kernel buffer data , size of the buffer and Recent activity(Read = 0 /Write = 1).
    	  struct stats
 		{
                                  int size;
                                  char buff[];
                                  int r_w;
                      			};
Write 3 separate user programs for Read, Write and Ioctl in User application.
Check the status of driver using Ioctl program with command GETSTATS, which should return structure(struct stats) from kernel space.
User should run write application first with any string and check stats using Ioctl program and then run Read application and check stats using Ioctl program and verify the string and recent activity(r_w).
 */
#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/kdev_t.h>
#include<linux/types.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<linux/device.h>
#include"ioctl.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("SAURABH SINGH");
//function prototypes
int ioctl_chardevice_open(struct inode *inode, struct file *filp);
int ioctl_chardevice_release(struct inode *inode, struct file *filp);
ssize_t ioctl_chardevice_write(struct file *filp, const char __user *Ubuff, size_t count, loff_t *offp);
ssize_t ioctl__chardevice_read(struct file *filp, char __user *Ubuff, size_t count, loff_t *offp);
ssize_t ioctl_chardevice_write(struct file *filp, const char __user *Ubuff, size_t count, loff_t *offp);

//structure that defines the operation that the driver provides
struct file_operations fops=
{
	.owner = THIS_MODULE,
	.open = ioctl_chardevice_open,
	.read = ioctl_chardevice_read,
	.write = ioctl_chardevice_write,
	.release = ioctl_chardevice_release,
	.ioctl = ioctl_chardevice_ioctl,

};
struct stats{
	int size;
	char buff[];
	int r_w;
};
struct cdev *mycdev;

static int __init prog_init(void)
{
	int result;
	int MAJOR,MINOR;
	result=alloc_chrdev_region(&mydev,0,1,"ioctl_chardevice");
	if(result<0)
	{
		printk(KERN_ALERT"\nThe region requested is not obtainable\n");
		return(-1);
	}
	MAJOR=MAJOR(mydev);
	MINOR=MINOR(mydev);
	printk(KERN_ALERT"\n The major number is:%d\n........The minor number is:%d\n",MAJOR,MINOR);
	mycdev=cdev_alloc();
	mycdev->ops=&fops;

	result=cdev_add(mycdev,mydev,1);
	if(result<0)
	{
		printk(KERN_ALERT"\n The device has not been created...................\n");
		return(-1);
	}
	return 0;
}
//cleanup module
void __exit prog_exit(void)
{
	int MAJOR,MINOR;
	MAJOR=MAJOR(Mydev);
	MINOR=MINOR(Mydev);
	printk("\nThe major number is:%d..........The minor number is:%d\n",MAJOR,MINOR);
	unregister_chrdev_region(Mydev);
	//unregister the device number and the device created
        cdev_del(mycdev);
	printk(KERN_ALERT"\n Ihave unregistered the stuff that was allocated.......goodbye\n");
	return;
}
//open sysem call
int ioctl_chardevice_open(struct inode *inode, struct file *filp);
{
	printk(KERN_ALERT"\n This is system open call\n");
	return 0;
}
//close syste call
int ioctl_chardevice_release(struct inode *inode, struct file *filp);
{
	printk(KERN_ALERT"\n This is system close call\n");
}
//write functionality
ssize_t ioctl_chardevice_write(struct file *filp, const char __user *Ubuff, size_t count, loff_t *offp);
{
	char kbuff[100];
	unsigned long result;
	ssize_t retval;
	result=copy_from_user((char*)kbuff,(char*)ubuff,count);
	if(result==0)
	{
		printk(KERN_ALERT"\nMessage from he user ......\n>>>>>>%s<<<<<<<<\n",kbuff);
		printk(KERN_ALERT"\n DATA SUCCESSFULLY WRITTEN...........\n");
		retval=count;
		return retval;
	}
	else
	{
		printk(KERN_ALERT"\n Error in writting data\n");
		retval =-EFAULT;
		return retval;
	}
//read functionality
ssize_t ioctl_chardevice_read(struct file *filp, char __user *Ubuff, size_t count, loff_t *offp);
{
	char kbuff[]="THIS IS SOME DATA FROM KERNEL TO USER......../ENJOY";
	unsigned long result;
	ssize_t retval;
	result=copy_to_user((char*)ubuff,(char*)kbuff,sizeof(kbuff));
	if(result==0)
	{
	printk(KERN_ALERT"\n DATA SUCCESFULLY READ...........\n");
	retval =count;
	return retval;
	}
	else
	{
	printk(KERN_ALERT"\n ERROR in writting data to user \n");
	retval =-EFAULT;
	return retval;
	}
}
long ioctl_chardevice_ioctl(struct file *filp,unsigned int cmd,unsigned long arg)
{
	unsigned int temp,size;
	char buff;
	size_t retval=success;
	char ubuff[20];
	struct stats *ToSend;
	printk("\nIOCTL FUNCTION");
	switch(cmd)
	{
		case size:
			get_user(temp,(int __user*)arg);
			printk("\ngetting size in temp\n");
			temp=sizeof(kbuff);
			put_user(temp(int __user*)arg);
			break;
	}
module_init(CharDevice_init);
module_exit(CharDevice_exit);


