TARGET_EXEC ?= jstwin

BUILD_DIR ?= ./build
SRC_DIRS ?= ./.

SRCS := $(shell find $(SRC_DIRS) -name "*.cpp")
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

CPPFLAGS ?= $(INC_FLAGS) -MMD -MP `pkg-config gtkmm-3.0 --cflags --libs`
LDFLAGS  ?= `pkg-config gtkmm-3.0 --cflags --libs`

$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CXX) $(OBJS) $(LDFLAGS) -o $@ 

# c++ source
$(BUILD_DIR)/%.cpp.o: %.cpp
	$(MKDIR_P) $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@


.PHONY: clean

clean:
	$(RM) -r $(BUILD_DIR)

-include $(DEPS)

MKDIR_P ?= mkdir -p

