CURRENT = $(shell uname -r)
KDIR = /lib/modules/$(CURRENT)/build
PWD = $(shell pwd)

TARGET = pagetracer
obj-m := $(TARGET).o

default:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

clean:
	@rm -f *.o .*.cmd .*.flags *.mod.c *.order
	@rm -f .*.*.cmd *~ *.*~
	@rm -fR .tmp*
	@rm -rf .tmp_versions

distclean: clean
	@rm -f *.ko *.symvers *.mod

load:
	sudo insmod $(TARGET).ko process_id=$(pid)

info:
	sudo lsmod | grep $(TARGET)

log:
	sudo dmesg | grep "$(TARGET): $(pid):"

unload:
	sudo rmmod $(TARGET).ko
