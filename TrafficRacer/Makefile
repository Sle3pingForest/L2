#Test si linux ou mac
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	LDFLAGS = -lSDL2
endif
ifeq ($(UNAME_S),Darwin)
	LDFLAGS = -F/Library/Frameworks -framework SDL2
endif

CXX = g++
CXXFLAGS = -Wall
LDFLAGS += -I $(INCLDIR)
SRC = src/
INCLDIR = include/
OUTPUT = TrafficRacer

#Génère les .o à partir de tout les .cpp dans $(SRC)
OBJECTS := $(patsubst %.cpp,%.o,$(wildcard $(SRC)*.cpp))

all : $(OBJECTS)
	$(CXX) $(CXXFLAGS) main.cpp $(OBJECTS) -o $(OUTPUT) $(LDFLAGS)

$(SRC)%.o: $(SRC)%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(LDFLAGS)

clean :
	rm -f $(SRC)*.o

mrproper : clean
	rm -f $(OUTPUT)

#Affichage des varriables
print-%  : ; @echo $* = $($*)