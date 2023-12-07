
#TOOLCHAIN_PATH=/usr/bin/
#TOOLCHAIN_PATH=/opt/rv/bin/
#TOOLCHAIN_PATH=/opt/riscv32imc/bin/
# TOOLCHAIN_PATH=/ef/apps/bin/

# Set the prefix for `riscvXX-unknown-elf-*`
# On installations using `multilib`, this will be `riscv64` even for compiling to 32-bit targets
TOOLCHAIN_PREFIX=riscv32-unknown-elf
#TOOLCHAIN_PREFIX=riscv32

# ---- Test patterns for project raven ----

.SUFFIXES:

PATTERN = uranus_config_loader
VEXRISCV_FILES = ../vexriscv
UTIL_DIR ?= $(HOME)/proj/openmpw/caravel_board/gf180/util

hex:  ${PATTERN:=.hex}

%.elf: %.c $(VEXRISCV_FILES)/sections.lds $(VEXRISCV_FILES)/crt0_vex.S
	$(TOOLCHAIN_PATH)$(TOOLCHAIN_PREFIX)-gcc -I$(VEXRISCV_FILES)/ -I$(VEXRISCV_FILES)/generated/ -O0 -mabi=ilp32 -march=rv32i -D__vexriscv__ -Wl,-Bstatic,-T,$(VEXRISCV_FILES)/sections.lds,--strip-debug -ffreestanding -nostdlib -o $@ $(VEXRISCV_FILES)/crt0_vex.S $(VEXRISCV_FILES)/isr.c $<
	${TOOLCHAIN_PATH}$(TOOLCHAIN_PREFIX)-objdump -D $(PATTERN).elf > $(PATTERN).lst

%.hex: %.elf
	$(TOOLCHAIN_PATH)$(TOOLCHAIN_PREFIX)-objcopy -O verilog $< $@
	sed -ie 's/@1000/@0000/g' $@

%.bin: %.elf
	$(TOOLCHAIN_PATH)$(TOOLCHAIN_PREFIX)-objcopy -O binary $< $@

flash: $(PATTERN).hex
	sudo python3 $(UTIL_DIR)/caravel_hkflash.py $(PATTERN).hex
#	sudo python3 $(UTIL_DIR)/caravel_hkstop.py

flash2: $(PATTERN).hex
	python3 $(UTIL_DIR)/caravel_flash.py $(PATTERN).hex

# ---- Clean ----

clean:
	rm -f *.elf *.hex *.hexe *.bin *.vvp *.vcd *.lst

.PHONY: clean hex all flash

