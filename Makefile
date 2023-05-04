# Compiler and flags
CXX = g++
CPPFLAGS = -std=c++11 -Wall -Wextra 
LIBFLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

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

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CPPFLAGS) $(addprefix -I,$(INCLUDE_PATHS)) $(addprefix -L,$(LIBRARY_PATHS)) -c $< -o $@



# debug: $(BUILDDIR)/Level.o

# $(BUILDDIR)/Level.o: $(SRCDIR)/Level.cpp
# 	$(CXX) $(CPPFLAGS) $(addprefix -I,$(INCLUDE_PATHS)) $(addprefix -L,$(LIBRARY_PATHS)) -c $< -o $@
clean:
# if WINDOWS, use the below line
	del /s /q $(TARGET).exe $(BUILDDIR) 
# if LINUX, use the below line
#  rm -rf $(TARGET) $(BUILDDIR)