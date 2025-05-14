BUILD_DIR        ?= build
CMAKE_BUILD_TYPE ?= Release

CMAKE_CONFIGURE  = cmake -S . -B $(BUILD_DIR) -DCMAKE_BUILD_TYPE=$(CMAKE_BUILD_TYPE)

.PHONY: all configure clean fclean re copy_files

all: $(BUILD_DIR)/CMakeCache.txt
	@cmake --build $(BUILD_DIR) --parallel
	@$(MAKE) copy_files

run: all
	@chmod +x $(BUILD_DIR)/N-Puzzle
	@./$(BUILD_DIR)/N-Puzzle

$(BUILD_DIR)/CMakeCache.txt:
	@echo "==> [CMake] configure ($(CMAKE_BUILD_TYPE))"
	@mkdir -p $(BUILD_DIR)
	@$(CMAKE_CONFIGURE)

copy_files: $(BUILD_DIR)/.copied

$(BUILD_DIR)/.copied: file_to_copy/*
	@mkdir -p $(BUILD_DIR)
	@cp -r file_to_copy/* $(BUILD_DIR)/
	@touch $(BUILD_DIR)/.copied

clean:
	@if [ -d $(BUILD_DIR) ]; then \
		echo "==> [CMake] clean"; \
		cmake --build $(BUILD_DIR) --target clean; \
	fi
	@rm -f $(BUILD_DIR)/.copied

fclean: clean
	@echo "==> Removing $(BUILD_DIR)/"
	@rm -rf $(BUILD_DIR)

re: fclean all