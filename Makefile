BUILD_DIR:=build-makefile

.PHONY: build
build-debug:
	mkdir -p $(BUILD_DIR) && cd $(BUILD_DIR) && cmake .. -DCMAKE_BUILD_TYPE=Debug && make && cd -

build-release:
	mkdir -p $(BUILD_DIR) && cd $(BUILD_DIR) && cmake .. -DCMAKE_BUILD_TYPE=Release && make && cd -

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)

.PHONY: run_cache_miss
run_cache_miss:
	@./$(BUILD_DIR)/bin/cache_miss --storage heap --traversal breadth-first
	@./$(BUILD_DIR)/bin/cache_miss --storage stack --traversal breadth-first
	@./$(BUILD_DIR)/bin/cache_miss --storage static --traversal breadth-first
	@./$(BUILD_DIR)/bin/cache_miss --storage heap --traversal depth-first
	@./$(BUILD_DIR)/bin/cache_miss --storage stack --traversal depth-first
	@./$(BUILD_DIR)/bin/cache_miss --storage static --traversal depth-first

.PHONY: run_locality
run_locality:
	@./$(BUILD_DIR)/bin/locality --storage heap
	@./$(BUILD_DIR)/bin/locality --storage static


.PHONY: run_all
run_all: run_cache_miss run_locality
