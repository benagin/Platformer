# Configuration Options ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#

# Set debug mode.
debug ?= 0

# Replace with the directory that contains ft2build.h.
# if the new Font implementation words, this isnt needed anymore.
FTYPE_INC_DIR  ?= /usr/local/Cellar/freetype/2.7/include/freetype2/

# Replace with the directory that contains freetype.a.
FTYPE_LINK_DIR ?= /usr/local/Cellar/freetype/2.7/lib/

# Directory Layout ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#

SRC_DIR ?= .

# Compiler Configuration ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#

CXX 	 = g++
CXXFLAGS = -std=c++11 -Wall -Werror -pedantic

ifeq ($(debug), 1)
	CXXFLAGS += -g
endif

FRMWRKS  = -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo
LIBS     = -lglfw -lglew -lfreetype

INC_DIRS = -I$(FTYPE_INC_DIR) -I./
LIB_DIRS = -L$(FTYPE_LINK_DIR)

DEPS = -MMD -MF $*.d

# File Configuration ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#

SRCS := $(shell find . -path "*.cpp")
OBJS := $(SRCS:.cpp=.o)

# Executable Recipes ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#


# Build the game executable.
game: $(OBJS)
	@echo Linking $@...
	@$(CXX) $(CXXFLAGS) $(LIBS) $(FRMWRKS) $(LIB_DIRS) $(FRMWRKS) $(LIBS) $(OBJS) -o $@
	@rm -f *.o

# Object File Recipes ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#

.cpp.o: $(SRCS)
	@echo Compiling $<...
	@$(CXX) -c $(CXXFLAGS) $(DEPS) $(INC_DIRS) $< -o $@
	@cat $*.d >> Dependencies
	@rm -f $*.d

# Cleanup ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#

.PHONY: clean
clean:
	@echo Cleaning game and executables...
	@rm -f $(OBJS) game
	@rm Dependencies

# Other Stuff ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#

# include automatically generated dependencies
-include Dependencies

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#
