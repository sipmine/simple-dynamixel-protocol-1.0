# Путь к ARM GCC Toolchain
CC = arm-none-eabi-gcc
AR = arm-none-eabi-ar
INCLUDES = -I.
CFLAGS = -mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard \
         -Wall -Os -ffunction-sections -fdata-sections -nostdlib \
         -DSTM32F401xE  $(INCLUDES)

# Исходные файлы
SRC = dynamixel.c# Добавьте сюда ваши файлы

# Выходная библиотека
LIB = libdynamixel.a

# Компиляция объектных файлов
OBJS = $(SRC:.c=.o)

all: $(LIB)

$(LIB): $(OBJS)
	$(AR) rcs $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(LIB)
