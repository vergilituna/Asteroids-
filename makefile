LDFLAGS = -L/usr/local/lib -lm -framework GLUT -framework OpenGL -framework Cocoa -lstdc++
LinuxFLAGS = -lGL -lGLU -lglut -lm -lstdc++
WinFLAGS = -lfreeglut -lglu32 -lopengl32 -mwindows -lstdc++

SOURCES = mainAsteroids.cpp ObjectsList.cpp Asteroid.cpp Ship.cpp Bullet.cpp Flame.cpp Shape.cpp
TARGET = Asteroids

linux:
	g++ -o $(TARGET) $(SOURCES) $(LinuxFLAGS) -Wno-deprecated-declarations

osX:
	g++ -o $(TARGET) $(SOURCES) $(LDFLAGS) -Wno-deprecated-declarations

windows:
	g++ -o $(TARGET).exe $(SOURCES) $(WinFLAGS) -Wno-deprecated-declarations
