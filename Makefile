obj-m :=ques2.o
KERNELDIR = /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)
default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
	 gcc -o read read.c
	 gcc -o write write.c
clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean
	rm -rf read
	rm -rf write
install:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules_install
	depmod -a
