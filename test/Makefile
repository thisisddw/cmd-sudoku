TARGET_EXEC := shudu

ORIGIN_DIR := ..
BUILD_DIR := ./build
SRC_DIR := ./src
INCLUDE_DIR := ./include

SRCS := $(wildcard $(SRC_DIR)/*.cpp)
SRCS := $(SRCS:$(SRC_DIR)/%=%)
OBJS := $(SRCS:%.cpp=$(BUILD_DIR)/%.o)

CXX := g++
CPPFLAGS += -I$(INCLUDE_DIR)
CXXFLAGS += -O2 -g -Wall
CXXFLAGS += -fprofile-arcs -ftest-coverage
LDFLAGS += -lgtest -lgtest_main -pthread -lgcov --coverage

$(BUILD_DIR)/$(TARGET_EXEC):$(OBJS)
	@$(CXX) $(OBJS) $(LDFLAGS) -o $@

$(BUILD_DIR)/%.o:$(SRC_DIR)/%.cpp
	@$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

test: $(BUILD_DIR)/$(TARGET_EXEC)
	@$(BUILD_DIR)/$(TARGET_EXEC) $(ARGS)

gcov:
	@gcov $(OBJS)
	@mv ./*.gcov $(BUILD_DIR)/ 
# @lcov --no-external --capture --initial --directory $(BUILD_DIR) --output-file coverage.info
# genhtml coverage.info -o r.html

clean:
	-@rm -r $(BUILD_DIR) $(SRC_DIR) $(INCLUDE_DIR)

sync:
	-@rm -r $(BUILD_DIR) $(SRC_DIR) $(INCLUDE_DIR)
	@mkdir $(BUILD_DIR)
	@cp -r $(ORIGIN_DIR)/src $(SRC_DIR)
	@cp -r $(ORIGIN_DIR)/include $(INCLUDE_DIR)
	@cp test_main.cpp $(SRC_DIR)/main.cpp
	
.PHONY: sync clean test gcov
