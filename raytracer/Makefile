CC := clang++
CXXFLAGS := $(CXXFLAGS) -luser32 -lgdi32 -lopengl32 -lgdiplus -lShlwapi -ldwmapi -static -std=c++20 -mwindows
BUILD_DIR := build
LIB_DIR := lib

src_files := main.cpp $(LIB_DIR)/Shape.cpp $(LIB_DIR)/Sphere.cpp
obj_files := $(BUILD_DIR)/Shape.o $(BUILD_DIR)/Sphere.o

all: $(BUILD_DIR)/app

$(BUILD_DIR)/app:	main.cpp ${obj_files}
	$(CC) $^ -o $@.exe $(CXXFLAGS)

$(BUILD_DIR)/%.o:	$(LIB_DIR)/%.cpp $(LIB_DIR)/%.h build
	$(CC) -c $< -o $@ -std=c++20

clean:
	rmdir /s /q $(BUILD_DIR)

build:
	- mkdir $(BUILD_DIR)

.PHONY: build clean