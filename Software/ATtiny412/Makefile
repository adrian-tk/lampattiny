# makefile for lampattiny avr412 
#
# 2024-07-13
# Adrian Tomczyk
# adrian.tk@gmail.com
#
# 2024-07-05 initial version
# 2024-07-13 create directories for project

# directories
SRC_DIR := src
OBJ_DIR := build
INC_DIR := include
# or . intead of bin if want to build in current dir
BIN_DIR := bin

# uc name for gcc CFLAGS
MCU = attiny412
# uc name for programming device
MCU_DEV = $(MCU)

#toolchain placement
TOOLCHAIN = /opt/avr/avr8-gnu-toolchain-linux_x86_64/bin/


# phony don't create file
.PHONY: clean all compile-all

#name of output file
PROG := $(BIN_DIR)/main.elf

#CC = avr-gcc
CC = $(TOOLCHAIN)avr-gcc

#OC = avr-objcopy
OC = $(TOOLCHAIN)avr-objcopy

CFLAGS=-x c \
	   -funsigned-char \
	   -funsigned-bitfields \
	   -DDEBUG  \
	   -O1 \
	   -ffunction-sections \
	   -fdata-sections \
	   -fpack-struct \
	   -fshort-enums \
	   -g2 \
	   -Wall \
	   -mmcu=$(MCU) \
	   -c \
	   -std=gnu99 #\
#	   -I$(INC_DIR)
#	   -MD \
	   -MP \
	   -MF $*.d \
	   -MT $*.d \
	   -MT $*.o

# C PreProcessor flags
# 
CPPFLAGS := -Iinclude/ -MMD -MP

# Llib from c makefile
LDFLAGS = -mmcu=$(MCU) \
		  -Llib
		  -Wl,-Map=$(PROG:.elf=.map) \
		  -Wl,--start-group \
		  -Wl,-lm \
		  -Wl,--end-group \
		  -Wl,--gc-sections

LDLIBS =

OCFLAGS = -O ihex \
		  -R .eeprom \
		  -R .fuse \
		  -R .lock \
		  -R .signature \
		  -R .user_signatures

SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
HEX := $(PROG:.elf=.hex)

# add program to use, might be in env
#DEVICE = $(MAKEFILE_DIRECTORY)../env/bin/pymcuprog
# for pyver and other just
DEVICE = pymcuprog

# port for serial programming
SERIAL_PORT = /dev/ttyACM0

# flags for DEVICE 
DEV_FLAGS = -t uart \
		  -u $(SERIAL_PORT) \
		  -d $(MCU_DEV) \

# targets

# default target
#all: $(OBJS)
#	$(CC) $(OBJS) $(LDFLAGS) -o $(PROG)
all: $(PROG)

# LDFLAGS shall be before objects, LDLIBS after.
$(PROG): $(OBJS)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

hex: all 
	$(OC) $(OCFLAGS) $(PROG) $(HEX)

erase: 
	$(DEVICE) erase $(DEV_FLAGS)

write: hex
#	$(DEVICE) write -f $(PROG:.elf=.hex) $(DEV_FLAGS)
	$(DEVICE) write --erase -f $(PROG:.elf=.hex) $(DEV_FLAGS)


#program: upload clean
program: write clean

#compile-all: $(SRCS)
#	$(CC) $(CFLAGS) $(INCLUDES) $(SRCS)
#
#%.i: %.c
#	$(CC) $(CFLAGS) $(INCLUDES) -E $< -o $@
#
#%.asm: %.c
#	$(CC) $(CFLAGS) $(INCLUDES) -S $< -o $@

#clean: 
#	rm -f $(PROG)	\
#		$(PROG:.elf=.hex)	\
#		$(PROG:.elf=.map)	\
#	   	$(SRCS:.c=.o) \
#	   	$(SRCS:.c=.d) \
#	   	$(SRCS:.c=.asm) \
#	   	$(SRCS:.c=.i) 

#clean:
#	@$(RM) -rv $(BIN_DIR) $(OBJ_DIR)
clean:
	@$(RM) -rv $(BIN_DIR)/* $(OBJ_DIR)/*

# GCC, Cland, or other dependency generator
# might create .d file with Makefile rules,
# include it here
-include $(OBJS:.o=.d)

