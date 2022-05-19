OUT := bin/oredustry
CC := g++
DIR_SRC := src
INC := -Isrc
CFLAGS := -std=c++17
SRC := $(wildcard $(addsuffix /*.cpp, $(DIR_SRC)))
OBJ := $(patsubst %.cpp, %.o, $(SRC))
LIBS := -lallegro -lallegro_ttf -lallegro_font

.PHONY: all clean

all: $(OBJ) $(OUT)

%.o: %.cpp
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OUT): $(OBJ)
	$(CC) $(CFLAGS) $(LIBS) $(OBJ) -o $@

clean:
	rm $(OBJ) $(OUT)
