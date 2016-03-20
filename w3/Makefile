# wxWindows Template App
# Lukasz Zalewski
# lukas@eecs.qmul.ac.uk
# 2002-2010
# ------------------

# ------------------
EXES = prog1

all  : $(EXES)

full : clean all

clean :
	find -name "*.o" -exec rm {} \;
	rm -f ${EXES} -R

prog1 : ex1.o
	g++ -o ex1 ex1.o

prog1.o : ex1.cpp
	g++ -c ex1.cpp -o ex1.o
