# Путь к ARM GCC Toolchain
PLATFORM ?= stm

MCPU = cortex-m4

MFPU = fpv4-sp-d16

BOARD = STM32F401xE

INCLUDES = -I.

# source files
SRC = dynamixel.c

# library name
LIB = libdynamixel.a

# object files
OBJS = $(SRC:.c=.o)


ifeq ($(PLATFORM), stm)
    CC = arm-none-eabi-gcc
    AR = arm-none-eabi-ar
    CFLAGS = -mcpu=$(MCPU) -mthumb -mfpu=$(MFPU) -mfloat-abi=hard \
             -Wall -Os -ffunction-sections -fdata-sections -nostdlib \
             -D$(BOARD) -I.
else ifeq ($(PLATFORM), unix)
    CC = gcc
    AR = ar
    CFLAGS = -Wall -Os -ffunction-sections -fdata-sections -nostdlib -I.
endif


all: $(LIB)

$(LIB): $(OBJS)
	$(AR) rcs $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(LIB)
