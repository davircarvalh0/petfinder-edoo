CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I./src
LDFLAGS = -lsqlite3 -lws2_32

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
