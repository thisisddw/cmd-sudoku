TARGET_EXEC := shudu

BUILD_DIR := ./build
SRC_DIR := ./src
INCLUDE_DIR := ./include

SRCS := $(wildcard $(SRC_DIR)/*.cpp)
SRCS := $(SRCS:$(SRC_DIR)/%=%)
OBJS := $(SRCS:%.cpp=$(BUILD_DIR)/%.o)

CXX := g++
CPPFLAGS += -I$(INCLUDE_DIR)
CXXFLAGS += -O2 -g -Wall

$(BUILD_DIR)/$(TARGET_EXEC):$(OBJS)
	@$(CXX) $(LDFLAGS) $(OBJS) -o $@

$(BUILD_DIR)/%.o:$(SRC_DIR)/%.cpp
	@$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

test: $(BUILD_DIR)/$(TARGET_EXEC)
	@$(BUILD_DIR)/$(TARGET_EXEC) $(ARGS)

clean:
	-@rm $(BUILD_DIR)/*.o $(BUILD_DIR)/$(TARGET_EXEC)
	@cd test && make clean

.PHONY: clean test
