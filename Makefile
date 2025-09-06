# Makefile simples para projeto CMake (C++/OpenGL)
# Uso:
#   make                # build Debug
#   make run            # build + executa ./build/mine
#   make CONFIG=Release # build Release
#   make clean          # apaga build
#   make rebuild        # clean + build
#   make configure      # só gera files do CMake

# Configurações
TARGET      ?= mine
BUILD_DIR   ?= build
CONFIG      ?= Debug
GEN         ?= $(shell if command -v ninja >/dev/null 2>&1; then echo Ninja; else echo "Unix Makefiles"; fi)
JOBS        ?= $(shell (command -v nproc >/dev/null 2>&1 && nproc) || (command -v sysctl >/dev/null 2>&1 && sysctl -n hw.ncpu) || echo 4)
CMAKE_FLAGS ?=
BUILD_FLAGS ?=

# Caminhos
BIN := $(BUILD_DIR)/$(TARGET)

.PHONY: all configure build run clean rebuild info

all: build

configure: $(BUILD_DIR)/CMakeCache.txt

$(BUILD_DIR)/CMakeCache.txt:
	@mkdir -p $(BUILD_DIR)
	cmake -S . -B $(BUILD_DIR) -G "$(GEN)" -DCMAKE_BUILD_TYPE=$(CONFIG) $(CMAKE_FLAGS)

build: configure
	cmake --build $(BUILD_DIR) --config $(CONFIG) -- -j$(JOBS) $(BUILD_FLAGS)

run: build
	@$(BIN)

clean:
	@rm -rf $(BUILD_DIR)

rebuild: clean all

info:
	@echo "Generator: $(GEN)"
	@echo "Config:    $(CONFIG)"
	@echo "Jobs:      $(JOBS)"
	@echo "Build dir: $(BUILD_DIR)"
	@echo "Target:    $(TARGET)"

