#------------------------------------------------------------------------------#
# This makefile was generated by 'cbp2make' tool rev.147                       #
#------------------------------------------------------------------------------#


WORKDIR = `pwd`

CC = gcc
CXX = g++
AR = ar
LD = g++
WINDRES = windres

INC = -I../third-party/rapidjson/include
CFLAGS = -Wall -std=c++17
RESINC = 
LIBDIR = 
LIB = 
LDFLAGS = 

INC_RELEASE = $(INC)
CFLAGS_RELEASE = $(CFLAGS) -O3
RESINC_RELEASE = $(RESINC)
RCFLAGS_RELEASE = $(RCFLAGS)
LIBDIR_RELEASE = $(LIBDIR)
LIB_RELEASE = $(LIB)-lpthread
LDFLAGS_RELEASE = $(LDFLAGS) -s
OBJDIR_RELEASE = obj/Release
DEP_RELEASE = 
OUT_RELEASE = bin/Release/gpio-pad

OBJ_RELEASE = $(OBJDIR_RELEASE)/common.o $(OBJDIR_RELEASE)/gpio-pad.o $(OBJDIR_RELEASE)/interfaces/rpi_gpio.o $(OBJDIR_RELEASE)/pad_thread.o

all: release

clean: clean_release

before_release: 
	test -d bin/Release || mkdir -p bin/Release
	test -d $(OBJDIR_RELEASE) || mkdir -p $(OBJDIR_RELEASE)
	test -d $(OBJDIR_RELEASE)/interfaces || mkdir -p $(OBJDIR_RELEASE)/interfaces

after_release: 

release: before_release out_release after_release

out_release: before_release $(OBJ_RELEASE) $(DEP_RELEASE)
	$(LD) $(LIBDIR_RELEASE) -o $(OUT_RELEASE) $(OBJ_RELEASE)  $(LDFLAGS_RELEASE) $(LIB_RELEASE)

$(OBJDIR_RELEASE)/common.o: common.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c common.cpp -o $(OBJDIR_RELEASE)/common.o

$(OBJDIR_RELEASE)/gpio-pad.o: gpio-pad.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c gpio-pad.cpp -o $(OBJDIR_RELEASE)/gpio-pad.o

$(OBJDIR_RELEASE)/interfaces/rpi_gpio.o: interfaces/rpi_gpio.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c interfaces/rpi_gpio.cpp -o $(OBJDIR_RELEASE)/interfaces/rpi_gpio.o

$(OBJDIR_RELEASE)/pad_thread.o: pad_thread.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c pad_thread.cpp -o $(OBJDIR_RELEASE)/pad_thread.o

clean_release: 
	rm -f $(OBJ_RELEASE) $(OUT_RELEASE)
	rm -rf bin/Release
	rm -rf $(OBJDIR_RELEASE)
	rm -rf $(OBJDIR_RELEASE)/interfaces

.PHONY: before_release after_release clean_release
