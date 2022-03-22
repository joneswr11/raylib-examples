TARGET = graphicsTest
INCLUDES = -I Graphics/include
LIBS = -L Graphics/lib/ -lraylib

# OS Detection for Libs
ifeq ($(OS),Windows_NT)
	 LIBS += -lopengl32 -lgdi32 -lwinmm
else
	OSNAME = $(shell uname)
	ifeq (($OSNAME),Linux)
		LIBS += -lGL -lm -ldl -lrt
	endif
	ifeq ($(OSNAME),Darwin)
		LIBS += -framework OpenGL -framework Cocoa -framework IOKit -framework CoreAudio -framework CoreVideo
	endif
endif

CC = g++
CFLAGS = -g -Wall $(INCLUDES)

.PHONY: default all clean

default: $(TARGET)
all: default

release: LDFLAGS = -Wl,--subsystem,windows
release: clean
release: $(TARGET)

OBJECTS = $(patsubst %.cpp, %.o, $(wildcard *.cpp))

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -g -Wall $(LIBS) -o $@ $(LDFLAGS)

clean:
ifeq ($(OS), Windows_NT)
	-del *.o $(TARGET).exe /q /f 
else
	-rm -r *.o $(TARGET)
endif