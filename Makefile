CXX = g++
UNAME_S := $(shell uname -s)

CXXFLAGS = -std=c++17 -Wall -Wextra -I./src
LDFLAGS = -lsqlite3

ifeq ($(OS),Windows_NT)
    CXXFLAGS += -D_WIN32_WINNT=0x0A00
    LDFLAGS += -lws2_32
endif

TARGET = petfinder
SOURCES = src/main.cpp src/database/Database.cpp $(wildcard src/models/*.cpp) $(wildcard src/services/*.cpp)
.PHONY: all run clean db-reset db-schema

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET) $(LDFLAGS)

run: $(TARGET)
	./$(TARGET)

db-schema:
	sqlite3 petfinder.db < src/database/schema.sql

db-reset:
	rm -f petfinder.db
	sqlite3 petfinder.db < src/database/schema.sql

clean:
	rm -f $(TARGET)
