TARGET = graphicsTest
INCLUDES = -I Graphics/include

LIBS = -L Graphics/lib/ -lraylib -lopengl32 -lgdi32 -lwinmm
CC = g++
CFLAGS = -g -Wall $(INCLUDES)
LDFLAGS = 

.PHONY: default all clean

default: $(TARGET)
all: default

release: LDFLAGS = -Wl,--subsystem,windows
release: clean
release: $(TARGET)

OBJECTS = $(patsubst %.cpp, %.o, $(wildcard *.cpp))
HEADERS = $(wildcard *.h $(INCLUDES)*.h)

%.o: %.cpp $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -g -Wall $(LIBS) -o $@ $(LDFLAGS)

clean:
	-del /f /q *.o
	-del /f /q $(TARGET).exe