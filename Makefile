CXX = g++
CXXFLAGS = -O2 -std=c++17
TARGET = brain_tester_sfml
SRC = main.cpp
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $@ $< $(LDFLAGS)

run: $(TARGET)
	.\$(TARGET).exe

clean:
	del $(TARGET).exe