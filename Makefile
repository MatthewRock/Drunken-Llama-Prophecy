#The relative path to the executable.
TARGET = $(BIN_DIR)/$(EXECUTABLE)
#The compiler that we will be using
CXX ?= g++
#C++ compilation flags
CXXFLAGS = $(INCLUDES) -std=c++11
#Directories for compiler to look for files
INCLUDES = -Iinclude
#Debug flags
DEBUG = -g
#Linker flags
LDFLAGS = -lSDL2 -lSDL2_image -lSDL2_mixer
#Optimization flags
OPTIMIZE = -O3
#Folder where binary will be stored.
BIN_DIR = bin
#Executable name.
EXECUTABLE ?= llama

#Directory of source code
SOURCES_DIR = src
#Source filenames
SOURCES  = $(shell cd $(SOURCES_DIR) && find ./ -type f -name '*.cpp' | sed 's:^\./::')
#Place to store .o files
OBJECTS_DIR = obj
#Object filenames
OBJECTS  = $(SOURCES:%.cpp=$(OBJECTS_DIR)/%.o)

#Target names
.PHONY: all clean debug
#Append optimize flags to C++ flags
all: CXXFLAGS += $(OPTIMIZE)
#Build target
all: $(TARGET)

#Append debug flags to C++ flags
debug: CXXFLAGS += $(DEBUG)
#Build target
debug: $(TARGET)

#Recipe for building target: build all objects
#Here we temporarily go to $OBJECTS_DIR target below
$(TARGET): $(OBJECTS)
	#Create directory for binary file
	mkdir -p $(@D)
	#Link it
	$(CXX) $^ $(LDFLAGS) -o $@

#Create .o file from corresponding .cpp file
$(OBJECTS_DIR)/%.o: $(SOURCES_DIR)/%.cpp
	#Create directory for the file if it doesn't exist
	mkdir -p $(@D)
	#Compile it with C++ flags
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BIN_DIR)/
	rm -rf $(OBJECTS_DIR)/
