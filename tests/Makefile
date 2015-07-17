TARGET = tester.app
CORE_DIR = ../
INCLUDE_DIR = $(CORE_DIR)/includes
SRC_DIR = .
BUILD_DIR = ../builds/tester
OUTPUT_DIR = .
# libraries directories (ex: ../libft)
LIB_DIRS = ../

# libraries (ex: ft, mlx, ...)
LIBS = octo boost_unit_test_framework sfml-system sfml-graphics sfml-window

# sources
SRC = main.cpp						\
	  PackageDetails.cpp			\
	  PackageHeader.cpp				\
	  OptionParser.cpp				\
	  Array2D.cpp					\
	  Array3D.cpp					\
	  Stack.cpp						\
	  Math.cpp						\
	  ByteArray.cpp					\
	  BinaryStream.cpp				\
	  ConsoleCommandParser.cpp		\
	  ExpectChar.cpp				\
	  Options.cpp					\
	  Hsv.cpp						\
	  Palette.cpp					\
	  ColorWheel.cpp				\
	  StringUtils.cpp				\
	  FrameAnimation.cpp			\
	  LexicalTree.cpp				\
	  GenericFactory.cpp			\
	  RingBuffer.cpp

# compiler
CC = $(CXX)
# flags used in both mode
COMMON_FLAGS = -Werror -Wextra -Wall -std=c++11
# flags used in release mode
RELEASE_FLAGS = -O3
# flags used in debug mode
DEBUG_FLAGS = -g
# includes dirs paths
INCLUDE_DIRS = $(addprefix -I, $(INCLUDE_DIR))

OBJS = $(addprefix $(BUILD_DIR)/, $(SRC:.cpp=.o))
SRCS = $(addprefix $(SRC_DIR)/, $(SRC))
CFLAGS = $(COMMON_FLAGS)
CLIBS_FLAGS =  $(addprefix -L, $(LIB_DIRS)) $(addprefix -l, $(LIBS))
COMPLETE_TARGET = $(OUTPUT_DIR)/$(TARGET)
MODE = debug

ifeq ($(MODE), debug)
CFLAGS += $(DEBUG_FLAGS)
COLOR_ACTION = \033[1;32m
else
CFLAGS += $(RELEASE_FLAGS)
COLOR_ACTION = \033[0;34m
endif

COLOR_OFF = \033[0m
COLOR_OBJECT = \033[0m

all: core_library print_summary $(COMPLETE_TARGET)

$(COMPLETE_TARGET): $(BUILD_DIR) $(OBJS)
	@echo " - $(COLOR_ACTION)building$(COLOR_OFF): $(COLOR_OBJECT)$@$(COLOR_OFF)"
	@$(CC) $(CFLAGS) $(OBJS) -o $@ $(CLIBS_FLAGS) 

$(addprefix $(BUILD_DIR)/, %.o) : $(addprefix $(SRC_DIR)/, %.cpp)
	@echo " - $(COLOR_ACTION)compiling$(COLOR_OFF): $(COLOR_OBJECT)$<$(COLOR_OFF)"
	@$(CC) $(INCLUDE_DIRS) $(CFLAGS) -c $< -o $@

re: fclean $(COMPLETE_TARGET)

fclean: clean
	@echo " - $(COLOR_ACTION)removing$(COLOR_OFF): $(COLOR_OBJECT)$(TARGET)$(COLOR_OFF)"
	@rm -f $(COMPLETE_TARGET)
	
clean:
	@echo " - $(COLOR_ACTION)removing$(COLOR_OFF): $(COLOR_OBJECT)$(addprefix "\\n\\t", $(notdir $(OBJS)))$(COLOR_OFF)"
	@rm -f $(OBJS)
	@echo " - $(COLOR_ACTION)removing$(COLOR_OFF): $(COLOR_OBJECT)$(BUILD_DIR)$(COLOR_OFF)"
	@rm -fr $(BUILD_DIR)

$(BUILD_DIR):
	@echo " - $(COLOR_ACTION)creating directory$(COLOR_OFF): $(COLOR_OBJECT)$(BUILD_DIR)$(COLOR_OFF)"
	@mkdir -p $(BUILD_DIR)

print_summary:
ifeq ($(MODE), debug)
	@echo " - Making $(TARGET) [DEBUG]: $(CFLAGS)"
else
	@echo " - Making $(TARGET): $(CFLAGS)"
endif

run:
	$(COMPLETE_TARGET) --log_level=test_suite

core_library: 
	@make -s -C $(CORE_DIR) MODE=$(MODE)

clean_core_library:
	@make -s -C $(CORE_DIR) clean MODE=$(MODE)

fclean_core_library:
	@make -s -C $(CORE_DIR) fclean MODE=$(MODE)
