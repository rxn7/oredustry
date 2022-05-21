OUT := bin/oredustry
CC := clang++
INC := -Isrc
CFLAGS := -std=c++17 -O3
DIR_SRC := src src/core src/core/ui src/scenes
SRC := $(wildcard $(addsuffix /*.cpp, $(DIR_SRC)))
OBJ := $(patsubst src/%.cpp, obj/%.o, $(SRC))
LIBS := -lSDL2 -lSDLmain -lSDL2_ttf -lSDL2_image

.PHONY: all clean

all: create_obj_dir $(OBJ) $(OUT)

obj/%.o: src/%.cpp
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(GDB_FLAGS) $(INC) -c $< -o $@

$(OUT): $(OBJ)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(LIBS) $(OBJ) -o $@

create_obj_dir:
	@mkdir -p obj

clean:
	rm $(OBJ) $(OUT)
