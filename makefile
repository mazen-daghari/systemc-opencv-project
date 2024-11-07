CXX = g++
CXXFLAGS = -I/usr/local/include/opencv4 -I$(SYSTEMC_HOME)/include -Wno-unused-variable -Wno-sign-compare -Wno-maybe-uninitialized
LDFLAGS = -L/usr/local/lib -lopencv_core -lopencv_imgcodecs -lopencv_imgproc -lopencv_highgui -L$(SYSTEMC_HOME)/lib-linux64 -lsystemc

all: main

main: main.o image_processor.o
    $(CXX) -o main main.o image_processor.o $(LDFLAGS)

main.o: main.cpp
    $(CXX) $(CXXFLAGS) -c main.cpp

image_processor.o: image_processor.cpp
    $(CXX) $(CXXFLAGS) -c image_processor.cpp

clean:
    rm -f *.o main
