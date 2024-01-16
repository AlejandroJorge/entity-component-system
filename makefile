SOURCE_DIR := ./src
INCLUDE_DIR := ./include
BUILD_DIR := ./build
LIBS := -lraylib -lm -lX11

run: executable
	$(BUILD_DIR)/executable

executable: $(SOURCE_DIR) $(BUILD_DIR)
	echo "I'm compiling the project again"
	gcc -Wall -g $(SOURCE_DIR)/*.c -I$(INCLUDE_DIR) $(LIBS) -o $(BUILD_DIR)/executable

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)
