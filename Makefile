CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I./src
LDFLAGS = -lsqlite3

TARGET = petfinder
SOURCES = src/main.cpp src/database/Database.cpp

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
