# wxWindows Template App
# Lukasz Zalewski 
# lukas@eecs.qmul.ac.uk
# 2002-2010
# ------------------

###################### linux #################################
INCS =
LIBP = 

ARCH_CFLAGS =
#The code below should be used rather than the
#specific 2.4 version one. With this one we ensure
#that we run the latest release of wxGTK rather
#than a specific one:

WX_LIBS = `wx-config --libs --gl-libs`
WX_FLAGS = `wx-config --cxxflags`

LIBS = $(WX_LIBS)
ARCH_CFLAGS =
EXES = window

CFLAGS	= $(ARCH_CFLAGS) $(WX_FLAGS) -Wall -Wno-unused -Wno-reorder \
	-O3  -fomit-frame-pointer -fforce-addr 


# ------------------

all : clean $(EXES)

clean :
	find . -name "*.o" -exec rm {} \;
	rm -f ${EXES} -R

# ------------------

window : window.o
	g++ window.o -o window $(ARCH_CFLAGS) $(LIBS) $(CFLAGS)

window.o : window.cpp
	g++ -c window.cpp $(ARCH_CFLAGS) $(INCS) $(WX_FLAGS)

# ------------------
