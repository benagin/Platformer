# Configuration Options ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#

# Set debug mode.
debug ?= 0

CELLAR ?= /usr/local/Cellar

# Replace with the directory that contains your freetype libraries.
# if the new Font implementation words, this isnt needed anymore.
FTYPE_INC_DIR  ?= $(CELLAR)/freetype/2.7/include/freetype2/

# Replace with the directory that contains freetype.a.
FTYPE_LINK_DIR ?= $(CELLAR)/freetype/2.7/lib/

# Replace with the directory that contains tinyxml2.h and libtinyxml2.dylib
TINYXML_INC_DIR ?= $(CELLAR)/tinyxml2/4.0.1/include/
TINYXML_LINK_DIR ?= $(CELLAR)/tinyxml2/4.0.1/lib/

# Directory Layout ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#

SRC_DIR ?= .

# Compiler Configuration ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#

CXX 	 = g++
CXXFLAGS = -std=c++11 -Wall -Werror -pedantic

ifeq ($(debug), 1)
	CXXFLAGS += -g -DPLAT_DEBUG
endif

FRMWRKS  = -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo
LIBS     = -lglfw -lglew -lfreetype -ltinyxml2

INC_DIRS = -I$(FTYPE_INC_DIR) -I$(TINYXML_INC_DIR) -I./
LIB_DIRS = -L$(FTYPE_LINK_DIR) -L$(TINYXML_LINK_DIR)

DEPS = -MMD -MF $*.d

# File Configuration ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#

SRCS := $(shell find . -path "*.cpp")
OBJS := $(SRCS:.cpp=.o)

# Executable Recipes ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#


# Build the game executable.
game: $(OBJS)
	@echo Linking $@...
	@$(CXX) $(CXXFLAGS) $(LIBS) $(INC_DIRS) $(FRMWRKS) $(LIB_DIRS) $(FRMWRKS) $(LIBS) $(OBJS) -o $@
	@rm -f *.o

# Object File Recipes ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#

.cpp.o: $(SRCS)
	@echo Compiling $<...
	@$(CXX) -c $(CXXFLAGS) $(DEPS) $(INC_DIRS) $< -o $@
	@cat $*.d >> Dependencies

# Cleanup ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#

.PHONY: clean
clean:
	@echo Cleaning game and executables...
	@rm -f $(OBJS) game
	@rm $(shell find . -path "*.d")
	@rm Dependencies

# Other Stuff ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#

# include automatically generated dependencies
-include Dependencies

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#
