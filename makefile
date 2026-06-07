
  
LDFLAGS= -L/usr/local/lib    -lm   -framework GLUT -framework OpenGL -framework Cocoa -lstdc++

LinuxFLAGS= -lGL -lGLU -lglut -lm -lstdc++



linux:
	gcc Trabajo2.cpp GLstuff.cpp Cube.cpp Man.cpp $(LinuxFLAGS)  -o Trabajo2  -Wno-deprecated-declarations



osX:
	gcc Trabajo2.cpp GLstuff.cpp Cube.cpp Man.cpp  $(LDFLAGS)  -o Trabajo2  -Wno-deprecated-declarations

