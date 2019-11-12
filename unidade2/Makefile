# sudo apt-get install crossbuild-essential-armhf
CC	=	arm-linux-gnueabihf-g++

BASEDIR = ~/myBlacklib
CPPFLAGS = -Wall	-I ${BASEDIR}/include
LDFLAGS = -L ${BASEDIR}/lib
LDLIBS =	-lBlacklib -lpthread

PROGRAMS = 4trens

all:	${PROGRAMS}

4trens:	4trens.c

testBeagle:	traincrash.cpp

clean:
	rm -f ${PROGRAMS}
