PREFIX=/vol/back/vbox/netsoft/CoreELEC/build.CoreELEC-S912.arm-9.0-devel/toolchain
STRIP=/vol/back/vbox/netsoft/CoreELEC/build.CoreELEC-S912.arm-9.0-devel/toolchain/lib/gcc-linaro-aarch64-elf/aarch64-elf/bin/strip

CROSS_COMPILE=armv8a-libreelec-linux-gnueabi-

CC = $(PREFIX)/bin/$(CROSS_COMPILE)gcc

HBS658Service: HBS658Service.c
	$(CC) $(CFLAGS) -Wall -w -o $@ $^ -lm 
	$(STRIP) $@
