CC := clang++
#CXXFLAGS := -Wall -Werror -pedantic
CXXFLAGS := $(CXXFLAGS) -luser32 -lgdi32 -lopengl32 -lgdiplus -lShlwapi -ldwmapi -static -std=c++20 -mwindows

BUILD_DIR := build

all: $(BUILD_DIR)/reta $(BUILD_DIR)/circulo $(BUILD_DIR)/recorte $(BUILD_DIR)/poligono

$(BUILD_DIR)/reta:	ponto_medio_reta.cpp $(BUILD_DIR)/rasterizacao.o
	$(CC) $^ -o $@.exe $(CXXFLAGS)

$(BUILD_DIR)/circulo:	ponto_medio_circulo.cpp $(BUILD_DIR)/rasterizacao.o
	$(CC) $^ -o $@.exe $(CXXFLAGS)

$(BUILD_DIR)/recorte:	cohen_sutherland.cpp $(BUILD_DIR)/rasterizacao.o
	$(CC) $^ -o $@.exe $(CXXFLAGS)

$(BUILD_DIR)/poligono:	preenchimento.cpp $(BUILD_DIR)/rasterizacao.o
	$(CC) $^ -o $@.exe $(CXXFLAGS)

$(BUILD_DIR)/%.o:	%.cpp %.h build
	$(CC) -c $< -o $@ -std=c++20

clean:
	del $(BUILD_DIR)\*.o
	del $(BUILD_DIR)\*.exe 
	rmdir /s /q $(BUILD_DIR)

build:
	- mkdir $(BUILD_DIR)

.PHONY: build clean