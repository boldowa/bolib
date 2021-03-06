# Enable gcov
CPPUTEST_USE_GCOV = Y

# Execute flags
CPPUTEST_EXE_FLAGS = -c

#Set this to @ to keep the makefile quiet
SILENCE = @

#---- Outputs ----#
COMPONENT_NAME = bolib
#Set this to @ to keep the makefile quiet
SILENCE = @

#--- Inputs ----#
PROJECT_HOME_DIR = .
ifeq "$(CPPUTEST_HOME)" ""
    CPPUTEST_HOME = ../CppUTest
endif
CPP_PLATFORM = Gcc

SRC_DIRS = \
    src\
    src/*

# to pick specific files (rather than directories) use this:    
SRC_FILES = 

TEST_SRC_DIRS = \
    tests \
    tests/*

MOCKS_SRC_DIRS = \
    mocks \

INCLUDE_DIRS =\
  .\
  include \
  include/common \
  include/file \
  include/util \
  $(CPPUTEST_HOME)/include/ \
  $(CPPUTEST_HOME)/include/Platforms/Gcc\
  mocks

CPPUTEST_WARNINGFLAGS = -Wall -Werror -Wswitch-default 
#CPPUTEST_WARNINGFLAGS += -Wconversion -Wswitch-enum 
CPPUTEST_WARNINGFLAGS += -Wconversion

include $(CPPUTEST_HOME)/build/MakefileWorker.mk

