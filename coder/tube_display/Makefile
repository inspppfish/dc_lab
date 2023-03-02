TOPNAME = tube_display
NXDC_FILES = constr/top.nxdc
INC_PATH ?=
# judge whether Verilator is part of a package install or 
# in the binary relative to $VERILATOR_ROOT
ifeq ($(VERILATOR_ROOT),)
VERILATOR = verilator
VERILATOR_COVERAGE = verilator_coverage
else
export VERILATOR_ROOT
VERILATOR = $(VERILATOR_ROOT)/bin/verilator
VERILATOR_COVERAGE = $(VERILATOR_ROOT)/bin/verilator_coverage
endif

BUILD_DIR = ./build
OBJ_DIR = $(BUILD_DIR)/obj_dir
BIN = $(BUILD_DIR)/$(TOPNAME)
default: $(BIN)

# make /build dir anyway
$(shell mkdir -p $(BUILD_DIR))

# constraint file
SRC_AUTO_BIND = $(abspath $(BUILD_DIR)/auto_bind.cpp)
$(SRC_AUTO_BIND): $(NXDC_FILES)
	python3 $(NVBOARD_HOME)/scripts/auto_pin_bind.py $^ $@

# source file: verilog file in ./vsrc and c++ source file in ./csrc
CSRCS = $(wildcard $(abspath csrc)/*.cpp)
CSRCS += $(SRC_AUTO_BIND)
VSRCS = $(wildcard vsrc/*.v)

# rules for NVBoard
include $(NVBOARD_HOME)/scripts/nvboard.mk

# Verilator flags
VERILATOR_FLAGS += -cc --exe
#VERILATOR_FLAGS += -Wall
VERILATOR_FLAGS += --build
VERILATOR_FLAGS += --trace
INCFLAGS = $(addprefix -I, $(INC_PATH))
CFLAGS += $(INCFLAGS) -DTOP_NAME="\"V$(TOPNAME)\""
LDFLAGS += -lSDL2 -lSDL2_image

# input source file
VERILATOR_INPUT = $(CSRC) $(VSRC)


all: default

$(BIN): $(VSRCS) $(CSRCS) $(NVBOARD_ARCHIVE)
	@echo "---verilate---"
	@rm -rf $(OBJ_DIR)
	$(VERILATOR) $(VERILATOR_FLAGS) \
		--top-module $(TOPNAME) $^ \
		$(addprefix -CFLAGS , $(CFLAGS)) $(addprefix -LDFLAGS , $(LDFLAGS)) \
		--Mdir $(OBJ_DIR) --exe -o $(abspath $(BIN))

sim: $(BIN) 
	@echo "---run---"
	$<
	@echo "---done---"

clean:
	rm -rf $(BUILD_DIR)

