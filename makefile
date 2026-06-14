LDFLAGS = -L/usr/local/lib -lm -framework GLUT -framework OpenGL -framework Cocoa -lstdc++
LinuxFLAGS = -lGL -lGLU -lglut -lm -lstdc++
WinCFLAGS = -I./include -DFREEGLUT_STATIC -DGLUT_DISABLE_ATEXIT_HACK
WinFLAGS = -L./lib -lfreeglut_static -lglu32 -lopengl32 -lgdi32 -lwinmm -mwindows -lstdc++

SOURCES = mainAsteroids.cpp ObjectsList.cpp Asteroid.cpp Ship.cpp Bullet.cpp Flame.cpp Shape.cpp Ovni.cpp
TARGET = Asteroids

ifeq ($(OS),Windows_NT)
PLATFORM = windows
else
UNAME_S := $(shell uname -s 2>/dev/null)
ifeq ($(UNAME_S),Darwin)
PLATFORM = osx
else
PLATFORM = linux
endif
endif

.PHONY: all linux osx windows clean

all: $(PLATFORM)

linux:
	g++ -o $(TARGET) $(SOURCES) $(LinuxFLAGS) -Wno-deprecated-declarations

osX:
	g++ -o $(TARGET) $(SOURCES) $(LDFLAGS) -Wno-deprecated-declarations

windows:
	g++ $(WinCFLAGS) -o $(TARGET).exe $(SOURCES) $(WinFLAGS) -Wno-deprecated-declarations

clean:
	rm -f $(TARGET) $(TARGET).exe
	rm -rf bin
