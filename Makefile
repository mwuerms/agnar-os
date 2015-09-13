# Martin Wuerms
# 2015-07-23
# cooperative operating system for MCU

TARGET = coop

DEP_DIR = .dep
#VERSION_FILE = version.h

CC = gcc
CFLAGS  = -c -g -Wall -rdynamic
CFLAGS += -MD -MP -MT $(*F).o -MF $(DEP_DIR)/$(@F).d
#CFLAGS += $(shell pkg-config --cflags glib-2.0)
# preprocessor output
#CFLAGS += -E > preproc_output.c

#LDFLAGS = $(shell pkg-config --libs glib-2.0)

# Versionfile
#VERSION_STRING_NAME = cVERSION
#STORED_VERSION_STRING = $(subst ",,$(shell [ ! -r $(VERSION_FILE) ] || \
                                                read ignore ignore v <$(VERSION_FILE) && echo $$v))                                                              
#VERSION_STRING := $(shell git describe --dirty --always || echo $(VERSION))
#ifneq ($(STORED_VERSION_STRING),$(VERSION_STRING))
#$(info updating $(VERSION_FILE) to $(VERSION_STRING))
#$(shell echo // this file was automatically created by the Makefile, do not edit >$(VERSION_FILE))
#$(shell echo \#define $(VERSION_STRING_NAME) \"$(VERSION_STRING)\" >>$(VERSION_FILE))
#endif

#INSTDIR = ${TARGET}-$(VERSION_STRING)


SRC=test.c\
process.c

OBJ = $(SRC:.c=.o)

all: $(OBJ) $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o $(TARGET) 

%.o: %.c
	$(CC) -c $(CFLAGS) $<

#doc: 
#        doxygen setup.dox

clean:
	rm -v $(OBJ) $(TARGET)

#package: all
#        echo "make package: ${INSTDIR}.tar"
#        mkdir ${INSTDIR}
#        cp ../install/install.sh ./${INSTDIR}
#        cp ${TARGET} ./${INSTDIR}
#        cp msrblebssupervisor ./${INSTDIR}
#        cp ../initskripts/bbbuart ./${INSTDIR}
#        cp ../initskripts/bbbmsrblebs ./${INSTDIR}
#        cp ../initskripts/bbbgpioreset1 ./${INSTDIR}
#        cp ../initskripts/bbbgpioled ./${INSTDIR}
#        cp ../initskripts/bbbsupervisor ./${INSTDIR}
#        tar -cf ${INSTDIR}.tar ./${INSTDIR}/*
#        rm -r ${INSTDIR}

-include $(shell mkdir $(DEP_DIR) 2>/dev/null) $(wildcard $(DEP_DIR)/*)
