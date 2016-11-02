#Test si linux ou mac
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	CXXFLAGS = -lSDL2
endif
ifeq ($(UNAME_S),Darwin)
	CXXFLAGS = -F/Library/Frameworks -framework SDL2
endif

CXX = g++
LDFLAGS = -I $(INCLDIR)
SRC = src/
INCLDIR = include/
OUTPUT = TrafficRacer

#Génère les .o à partir de tout les .cpp dans $(SRC)
OBJECTS := $(patsubst %.cpp,%.o,$(wildcard $(SRC)*.cpp))

all : $(OBJECTS)
	$(CXX) main.cpp $(OBJECTS) -o $(OUTPUT) $(LDFLAGS) $(CXXFLAGS)

$(SRC)%.o: $(SRC)%.cpp
	$(CXX) -c $< -o $@ $(LDFLAGS) $(CXXFLAGS)

clean :
	rm -f $(SRC)*.o

mrproper : clean
	rm -f $(OUTPUT)

#Affichage des varriables
print-%  : ; @echo $* = $($*)