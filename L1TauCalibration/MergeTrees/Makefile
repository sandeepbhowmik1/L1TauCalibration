#makefile 


CC   =   g++

#UCFLAGS = -O0 -g3 -Wall -gstabs+  
UCFLAGS = -O3 -Wall -gstabs+ -std=c++0x


RUCFLAGS := $(shell root-config --cflags) -I./include/
LIBS :=  $(shell root-config --libs) -lTreePlayer
GLIBS := $(shell root-config --glibs)

VPATH = ./src/

SRCPP = main.cpp\
	Utilities.cpp\
	IFactory.cpp\
	ITrees.cpp\
	EgammaStage2Trees.cpp\
	TauStage2Trees.cpp\
	EgammaStage1Stage2Trees.cpp\
	Manager.cpp

	
         
#OBJCPP = $(SRCPP:.cpp=.o)
OBJCPP = $(patsubst %.cpp,obj/%.o,$(SRCPP))


all : merge.exe obj/libDictionary_C.so

obj/%.o : %.cpp
	@mkdir -p obj/
	@echo compiling $*
	@$(CC) -c $< $(UCFLAGS) $(RUCFLAGS) -o $@

merge.exe : $(OBJCPP) 
	@echo linking...
	@$(CC) $^ $(ACLIBS) $(LIBS) $(GLIBS)  -o $@

clean:
	@echo "> Cleaning dictionary"
	@rm -f obj/libDictionary_C.so
	@echo "> Cleaning executable"
	@rm -f obj/*.o
	@rm -f merge.exe

obj/libDictionary_C.so: ./include/libDictionary.C
	@echo "> Generating dictionary"
	@cd include && root -b -q libDictionary.C++
	@mv ./include/libDictionary_C.so ./obj/
