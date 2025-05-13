BUILD_DIR        ?= build
CMAKE_BUILD_TYPE ?= Release

CMAKE_CONFIGURE  = cmake -S . -B $(BUILD_DIR) -DCMAKE_BUILD_TYPE=$(CMAKE_BUILD_TYPE)

COPY_FILES = $(wildcard file_to_copy/*)

.PHONY: all configure clean fclean re

copy_files:
	@mkdir -p $(BUILD_DIR)
	@cp -r file_to_copy/* $(BUILD_DIR)/

all: $(BUILD_DIR)/CMakeCache.txt copy_files
	@cmake --build $(BUILD_DIR) --parallel

run: all
	chmod +x $(BUILD_DIR)/MonProjetQt
	@./$(BUILD_DIR)/MonProjetQt

$(BUILD_DIR)/CMakeCache.txt:
	@echo "==> [CMake] configure ($(CMAKE_BUILD_TYPE))"
	@mkdir -p $(BUILD_DIR)
	@$(CMAKE_CONFIGURE)

clean:
	@if [ -d $(BUILD_DIR) ]; then \
		echo "==> [CMake] clean"; \
		cmake --build $(BUILD_DIR) --target clean; \
	fi

fclean: clean
	@echo "==> Removing $(BUILD_DIR)/"
	@rm -rf $(BUILD_DIR)

re: fclean all