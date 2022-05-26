INC += -Isrc -Iinclude
DIR_SRC += src src/core src/core/ui src/core/assets src/scenes
SRC += $(wildcard $(addsuffix /*.cpp, $(DIR_SRC)))
OBJ += $(patsubst src/%.cpp, $(OBJ_DIR)/%.o, $(SRC))

all: create_obj_dir $(OBJ) $(OUT)

$(OBJ_DIR)/%.o: src/%.cpp
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(GDB_FLAGS) $(INC) -c $< -o $@

$(OUT): $(OBJ)
	@mkdir -p $(@D)
	$(CC) $(LIBS) $(OBJ) -o $@

create_obj_dir:
	@mkdir -p $(OBJ_DIR)

clean: rm $(OBJ) $(OUT)
