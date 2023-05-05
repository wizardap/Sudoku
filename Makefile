# Compiler and flags
CXX = g++
CPPFLAGS = -std=c++11 -Wall -Wextra 

ifeq ($(OS),Windows_NT)
	LIBFLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
else 
	LIBFLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
endif

# Source files and objects
SRCDIR = src
BUILDDIR = build
SRCS = $(wildcard $(SRCDIR)/*.cpp)
OBJS = $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.o,$(SRCS))

# Header files directories
INCLUDE_PATHS = SDL/include
LIBRARY_PATHS = SDL/lib

# Binary name
TARGET = Sudoku

$(TARGET): $(OBJS)
	$(CXX) $(CPPFLAGS) $(addprefix -I,$(INCLUDE_PATHS)) $(addprefix -L,$(LIBRARY_PATHS)) $(OBJS) -o $@ $(LIBFLAGS)

$(BUILDDIR)/%.o:$(SRCDIR)/%.cpp
	$(CXX) $(CPPFLAGS) $(addprefix -I,$(INCLUDE_PATHS)) $(addprefix -L,$(LIBRARY_PATHS)) -c $< -o $@




clean:
ifeq ($(OS),Windows_NT)
	del /s /q $(TARGET).exe $(BUILDDIR)\*.o
else 
	rm -rf $(TARGET) $(BUILDDIR)/*.o
endif