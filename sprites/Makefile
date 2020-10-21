include $(DEVKITARM)/base_tools

TARGET  := $(notdir $(CURDIR))
ARCH	:=	-mthumb -mthumb-interwork
ASFLAGS	:=	-g $(ARCH)

SOURCES := $(wildcard *.png)
BMPS    := $(patsubst %.png, %.bmp, $(SOURCES))
OBJECTS := $(patsubst %.png, %.o, $(SOURCES))
SFILES  := $(patsubst %.png, %.s, $(SOURCES))

export LD   :=  $(CC)

%.bmp: %.png
	$(SILENTCMD)sips -s format bmp $< --out $@

%.s %.h: %.bmp
	grit $< -gB4 -pn2 -Mh 1 -Mw 1

%.o: %.s
	$(SILENTCMD)$(CC) -MMD -MP -MF assembler-with-cpp $(ASFLAGS) -c $< -o $@ $(ERROR_FILTER)

all: $(SFILES)

# clean:
# 	rm -f *.bmp


.SECONDARY: $(SFILES) $(BMPS)
