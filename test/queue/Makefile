CC_ ?= gcc
CCP ?= g++
TOOLCHAIN ?= gcc
PLATFORM = linux
ECHO = echo
BUILD_OUTPUT := output 
GOAL = queue_test.exe
PL_DIR = ../../pl
UTIL_DIR = ../../util



#---------------------------------------------------------------------------
# Include section
#---------------------------------------------------------------------------
INCLUDE_DIR	+= -I$(PL_DIR)/memory/include  -I$(PL_DIR)/logger/include  -I$(PL_DIR)/lock/include -I$(UTIL_DIR)/queue \

#---------------------------------------------------------------------------
# Source section
#---------------------------------------------------------------------------
#C_SRC_CPP   += engine_app.cpp

#---------------------------------------------------------------------------
# C source files
#---------------------------------------------------------------------------
C_SRC       += $(PL_DIR)/memory/$(PLATFORM)/memory_pl.c
C_SRC       += $(PL_DIR)/logger/$(PLATFORM)/logger_pl.c
C_SRC       += $(PL_DIR)/lock/$(PLATFORM)/lock_pl.c
C_SRC       += $(UTIL_DIR)/queue/queue.c

#---------------------------------------------------------------------------
# C test source
#---------------------------------------------------------------------------

C_SRC       += queue_test.c

#---------------------------------------------------------------------------
# Library section
#---------------------------------------------------------------------------
#LIB_PATH=-L$(BUILD_OUTPUT)/$(TOOLCHAIN)/$(PLATFORM)/rls_dbginfo/ -L$(BUILD_OUTPUT)/external/minizip/lib/$(TOOLCHAIN)/$(PLATFORM)/ -L$(BUILD_OUTPUT)/external/zlib/lib/$(TOOLCHAIN)/$(PLATFORM)/

LIB_FILES       += 
#---------------------------------------------------------------------------
# Complier options
#---------------------------------------------------------------------------
CCFLAGS    += -Wall -g -Werror -Wdeclaration-after-statement -Wconversion
CCPFLAGS   += -Wall -g #-Werror
DEFINES    += 
LDFLAGS    +=
LDLIBS     += -lpthread -lresolv -lc -lrt -lssl -lcrypto

#---------------------------------------------------------------------------
# Implicit rules
#---------------------------------------------------------------------------
.c.o:
	@$(ECHO) "Compiling $<..." $(CC_) -c $(CCFLAGS) $(DEFINES) -o $*.o $< $(INCLUDE_DIR)
	@$(CC_) -c $(CCFLAGS) $(DEFINES) -o $*.o $< $(INCLUDE_DIR)

.cpp.o:
	@$(ECHO) "Compiling $<..." $(CCP) -c $(CCPFLAGS) $(DEFINES) -o $*.o $< $(INCLUDE_DIR)
	@$(CCP) -c $(CCPFLAGS) $(DEFINES) -o $*.o $< $(INCLUDE_DIR)

#---------------------------------------------------------------------------
# Explicit ruls
#---------------------------------------------------------------------------
OBJ_FILES_C	  = $(C_SRC:%.c=%.o)
OBJ_FILES_CPP = $(C_SRC_CPP:%.cpp=%.o)
OBJ_FILES	= $(OBJ_FILES_C) $(OBJ_FILES_CPP)

all: $(GOAL)

$(GOAL): build_all 


build_all: build_objects
	@$(ECHO) "###################"
	@$(ECHO) $(CC) -o $@ $(OBJ_FILES) $(LIB_PATH) $(LIB_FILES) $(LDLIBS) $(LDFLAGS)
	@$(CC) -o $(GOAL) $(OBJ_FILES) $(LIB_PATH) $(LIB_FILES) $(LDLIBS) $(LDFLAGS)
	@$(ECHO) "*** $(GOAL) is built successfully! ***"


build_objects: $(OBJ_FILES)

.PHONY: clean
clean: clean_obj
	rm -f $(GOAL)

clean_obj:
	rm -f $(OBJ_FILES)
	
