# sudo apt-get install crossbuild-essential-armhf
CXX	=	arm-linux-gnueabihf-g++

BASEDIR = ~/myBlacklib
CPPFLAGS = -Wall	-I ${BASEDIR}/include
LDFLAGS = -L ${BASEDIR}/lib
LDLIBS =	-lBlacklib -lpthread

PROGRAMS = sender receiver

all:	${PROGRAMS}

sender:	sender.cpp

receiver: receiver.cpp

clean:
	rm -f ${PROGRAMS}
