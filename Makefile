# Compilation & Execution Happen On Windows
CC=x86_64-w64-mingw32-g++
DIRNAME=opengl
RUNPATH=exec

# Link Paths
GLFW_SRC_PATH=include/glfw-3.4/build-windows/src

# opengl32 and gdi32 are default while glfw3dll must be dynamically linked
LINKS= -lopengl32 -lgdi32 \
			 -L$(GLFW_SRC_PATH) -lglfw3dll

# Include Paths 
GLFW_INC_PATH=include/glfw-3.4/include
GLAD_INC_PATH=include

# Defining Inclusions
INCLUDE= -I$(GLFW_INC_PATH) -I$(GLAD_INC_PATH)

# Rules 

all: clean

build-ch%:
	$(CC) -std=c++17 src/glad.c src/ch$*.cpp src/classes/* src/shapes/* \
	$(LINKS) $(INCLUDE) -o exec/program.exe

test:
	./$(RUNPATH)/program.exe

clean:
	rm $(RUNPATH)/program.exe
