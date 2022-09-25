TOPNAME = example
NXDC_FILES = constr/top.nxdc
INC_PATH ?=

VERILATOR = verilator
VERILATOR_CFLAGS += -MMD --build -cc  \
				-O3 --x-assign fast --x-initial fast --noassert

BUILD_DIR = ./build
OBJ_DIR = $(BUILD_DIR)/obj_dir
BIN = $(BUILD_DIR)/$(TOPNAME)

$(shell mkdir -p $(BUILD_DIR))

# project source
SRC_AUTO_BIND = $(abspath $(BUILD_DIR)/auto_bind.cpp)
VSRCS = $(shell find $(abspath ./vsrc) -name "*.v")
SIM_CSRCS = $(shell find $(abspath ./csrc/sim) -name "*.c" -or -name "*.cc" -or -name "*.cpp")
LIB_CSRCS = $(shell find $(abspath ./csrc/lib) -name "*.c" -or -name "*.cc" -or -name "*.cpp")
NVB_CSRCS = $(shell find $(abspath ./csrc/nvboard) -name "*.c" -or -name "*.cc" -or -name "*.cpp")
NVB_CSRCS += $(SRC_AUTO_BIND)

# constraint file
$(SRC_AUTO_BIND): $(NXDC_FILES)
	python3 $(NVBOARD_HOME)/scripts/auto_pin_bind.py $^ $@

# rules for NVBoard
include $(NVBOARD_HOME)/scripts/nvboard.mk

# rules for verilator
INC_PATH += $(NPC_HOME)/include
INCFLAGS = $(addprefix -I, $(INC_PATH))
CFLAGS=-Wall
CFLAGS += $(INCFLAGS) -DTOP_NAME="\"V$(TOPNAME)\""
LDFLAGS += -lSDL2 -lSDL2_image

all:
	@echo "Write this Makefile by your self."

compile_hw: $(VSRCS)
	@echo "Compiling RTL code..."
	$(VERILATOR) $(addprefix -CFLAGS , $(CFLAGS)) --cc --Mdir $(OBJ_DIR) --trace $^
	@echo "Done."

compile_sim: $(VSRCS) $(SIM_CSRCS) $(LIB_CSRCS)
# $(call git_commit, "sim RTL") # DO NOT REMOVE THIS LINE!!!
	@rm -rf $(OBJ_DIR)
	@echo "Compiling simulation code..."
	$(VERILATOR) --top-module $(TOPNAME) $^ \
		$(addprefix -CFLAGS , $(CFLAGS)) -CFLAGS -DOPEN_WAVE \
		--cc --Mdir $(OBJ_DIR) --exe --build --trace
	@echo "Done."

run_sim: compile_sim
	@build/obj_dir/Vexample

$(BIN): $(VSRCS) $(NVB_CSRCS) $(NVBOARD_ARCHIVE) $(LIB_CSRCS)
	@rm -rf $(OBJ_DIR)
	$(VERILATOR) $(VERILATOR_CFLAGS) \
		--top-module $(TOPNAME) $^ \
		$(addprefix -CFLAGS , $(CFLAGS)) $(addprefix -LDFLAGS , $(LDFLAGS)) \
		--Mdir $(OBJ_DIR) --exe -o $(abspath $(BIN))

run_nvboard: $(BIN)
	@./$(BIN)

clean:
	rm -rf *.vcd build

include ../Makefile
