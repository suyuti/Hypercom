##############################################################################
# Makefile for creating downloadable file and updating the packing list for
# Hyperware reference application and applications based on the
# reference application
#
# Command Line Definitions
#
# VSECONFIG  configuration to make, usually Debug or Release
# APPNAME    name of application
# DEVTYPE    terminal type, T4100 or M4100
# GNU_TOOLS  path to gnu tools
# PACKINGLISTBUILDER path to packing List Builder
# BINFORMAT  type of binary output format
#
# typical usage
# make -f app.mak VSECONFIG=Release APPNAME=Hyperware DEVTYPE=T4100 GNU_TOOLS=<gnu_tools_location> PACKINGLISTBUILDER=<packing_list_builder_location> BINFORMAT=bin|srec
#
##############################################################################

GNU_TOOLS_POSIX := $(shell $(GNU_TOOLS)\bin\cygpath -dm "$(GNU_TOOLS)")

VSECONFIG ?= Release

BASE_PACKINGLIST = Resources/hxp-files.xml

ifeq ($(VSECONFIG),Debug)
OBJDIR = Debug/$(DEVTYPE)
else
OBJDIR = Release/$(DEVTYPE)
endif

# Application name
_APPNAME = $(OBJDIR)/$(APPNAME)

# Packing list xml file
PACKINGLIST = $(OBJDIR)/PackingList.xml

OBJCOPY = $(GNU_TOOLS_POSIX)/bin/xscale-elf-objcopy
FIXUP = $(GNU_TOOLS_POSIX)/bin/fixup
FIXJMP = $(GNU_TOOLS_POSIX)/bin/fixjmp
DDLCOMPRESS = $(GNU_TOOLS_POSIX)/bin/DDLCompress 
AWKPATH := $(shell $(GNU_TOOLS)\bin\cygpath -d "$(GNU_TOOLS)")
#AWK = $(GNU_TOOLS_POSIX)/bin/awk
AWK = $(AWKPATH)\bin\awk
ZIP = $(GNU_TOOLS_POSIX)/bin/zip
RM = $(GNU_TOOLS_POSIX)/bin/rm


all : $(PACKINGLIST) $(_APPNAME).app $(_APPNAME).hxp

$(PACKINGLIST) : $(BASE_PACKINGLIST) FORCE
        # filter out File nodes with non-matching Target attribute
        # append SVN revision to application Version attribute
        # fill in ReleaseDate attribute if its empty
	@$(AWK) '/Target\s*=\s*"($(DEVTYPE)|[*])\/($(VSECONFIG)|[*])"/ { print }\
             /Target\s*=\s*/ { }\
             !/Target\s*=\s*/ { print }' $(BASE_PACKINGLIST)\
             > $(PACKINGLIST)
FORCE:

########################################################
# Sections to remove from OBJ file

NOSECTIONS  = .interp .hash .dynsym .dynstr .rel.init
NOSECTIONS += .rela.init .rel.text .rela.text .rel.fini
NOSECTIONS += .rela.fini .rel.rodata .rela.rodata .rel.dyn .rela.dyn
NOSECTIONS += .rel.data .rela.data .rel.tdata .rela.tdata
NOSECTIONS += .rel.tbss .rela.tbss .rel.ctors .rela.ctors
NOSECTIONS += .rel.dtors .rela.dtors .rel.got .rela.got
NOSECTIONS += .rel.sdata .rela.sdata .rel.sbss .rela.sbss
NOSECTIONS += .rel.sdata2 .rela.sdata2 .rel.sbss2
NOSECTIONS += .rela.sbss2 .rel.bss .rela.bss .rel.plt
NOSECTIONS += .rela.plt .dynamic

SRECFORMAT = --srec-len=255


$(_APPNAME).app: $(_APPNAME).elf
	$(FIXJMP) $< $(basename $@).rel
	$(OBJCOPY)  $(foreach sec,$(NOSECTIONS),-R $(sec) ) $(SRECFORMAT) -O srec $< $(basename $@).src
	- $(FIXUP) $(basename $@).src $(basename $@).txt $(basename $@).map \
	$(basename $@).rel $(BINFORMAT)
	- $(RM) -f $(basename $@).rel
	$(DDLCOMPRESS) $(basename $@).txt $(basename $@).app $(BINFORMAT)


################## Create the Packing List #######################

# Create the Packing List

# This rule creates/updates HXP packing list file. PackingListBuilder 1.0.8 or later required.
# List of files, which goes into HXP package are taken from PackingList.xml ("hidden" file in HXP).
# In order to add new file(s) to HXP, add new entry to PackingList.xml and if required to dependencies list.
# NOTE: PackingListBuilder only works with xml files with line end character LF, and nothing more! 
# If there will be CRLF, you will receive error with description "Failed to load PackingList.xml file" 
# and "Update failed". Please, take it into account, when adding new files.
$(_APPNAME).hxp: $(_APPNAME).app
	@echo
	@echo Creating HXP packing list...
	@$(ZIP) -j $(_APPNAME).hxp $(PACKINGLIST) > nul
	"$(PACKINGLISTBUILDER)" /update $@
	@echo