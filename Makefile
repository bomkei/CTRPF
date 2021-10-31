.PRECIOUS: %.elf

TARGET		= acnl_power

BASE			= /opt/devkitpro/devkitARM/bin/

AS				= $(BASE)/arm-none-eabi-gcc
CC				= $(BASE)/arm-none-eabi-gcc
CXX				= $(BASE)/arm-none-eabi-g++
LD				= $(BASE)/arm-none-eabi-g++
NM				= $(BASE)/arm-none-eabi-nm

HEADER		= plugin.h
SFILES		= $(wildcard *.s)
CFILES		= $(wildcard *.c)
CXXFILES	= $(wildcard *.cc)

INCLUDES	= \
	/opt/devkitpro/libctrpf/include \
	/opt/devkitpro/libctru/include \
	/opt/devkitpro/libctru/include/3ds

PLGINFO		= plginfo.txt

ARCH			= -march=armv6k -mtune=mpcore -mfloat-abi=hard -mtp=soft -DARM11 -D_3DS
SFLAGS		= -Os $(ARCH)
CFLAGS		= -Os $(ARCH) $(foreach dir,$(INCLUDES),-I $(dir))
CXXFLAGS	= $(CFLAGS) -std=gnu++20 -fno-rtti -fomit-frame-pointer -ffunction-sections -fno-strict-aliasing -Wno-psabi

LDFLAGS		= -T ./3gx.ld -Wl,--gc-sections,--strip-discarded,--strip-debug \
	-Os -L /opt/devkitpro/libctru/lib/ -L /opt/devkitpro/libctrpf/lib/ \
	-lctrpf -lctru

OFILES		= \
	$(SFILES:.s=.o) \
	$(CFILES:.c=.o) \
	$(CXXFILES:.cc=.o)

all: $(TARGET).3gx

clean:
	@rm -rf *.o
	@rm -rf $(TARGET).3gx
	@rm -rf $(TARGET).elf
	@rm -rf $(TARGET).lst

re: clean all

%.o: %.s $(HEADER)
	@echo $<
	@$(AS) $(SFLAGS) -c -o $@ $<

%.o: %.c $(HEADER)
	@echo $<
	@$(CC) $(CFLAGS) -c -o $@ $<

%.o: %.cc $(HEADER)
	@echo $<
	@$(CXX) $(CXXFLAGS) -c -o $@ $<

%.3gx: %.elf
	@echo creating $@ ...
	@/opt/devkitpro/tools/bin/3gxtool -d -s $< $(PLGINFO) $@

%.elf: $(OFILES)
	@echo linking...
	@$(LD) $(LDFLAGS) $(ARCH) -o $@ $^
	@$(NM) -CSn $@ > $*.lst