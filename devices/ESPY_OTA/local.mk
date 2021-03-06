ifdef ESPY_INSTALLER
	PROGRAM = espy_installer
	EXTRA_CFLAGS += -DESPY_INSTALLER
else
	PROGRAM = espy_ota
	LINKER_SCRIPTS = $(ROOT)ld/program1.ld
endif

#==================================================
# for this to work, we need to copy $(ROOT)ld/program.ld
# to $(ROOT)ld/program1.ld and in the copy change this:
# irom0_0_seg :                       org = 0x40202010, len = (1M - 0x2010)
# to this:
# irom0_0_seg :                       org = 0x40290010, len = (0xf2000 - 0x90010)
# 
# note that the previous len is forgetting about the system settings area which
# is 9 sectors for esp-open-rtos, and then it is ignored as well...
#
# also we need to change parameters.mk like this:
# LINKER_SCRIPTS += $(ROOT)ld/program.ld $(ROOT)ld/rom.ld
# becomes:
# LINKER_SCRIPTS ?= $(ROOT)ld/program.ld
# LINKER_SCRIPTS += $(ROOT)ld/rom.ld
#==
# if you know a more elegant way, I am all open for it ;-)
