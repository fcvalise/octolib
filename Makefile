LIB_NAME = octo
INCLUDE_DIR = ./includes
SRC_DIR = ./src
BUILD_DIR = ./builds
OUTPUT_DIR = .

# sources
SRC = 	$(RESOURCE_SRC)						\
		$(STATE_SYSTEM_SRC)					\
		$(PACKAGE_SRC)						\
		$(MATH_SRC)							\
		$(CORE_SRC)							\
		$(CONSOLE_SRC)

CORE_SRC =	Application.cpp					\
			PausableClock.cpp				\
			GraphicsManager.cpp				\
			OptionParser.cpp				\
			Options.cpp						\
			ByteArray.cpp					\
			BinaryInputStream.cpp			\
			BinaryOutputStream.cpp			\
			PrintSFML.cpp

MATH_SRC = 	Interpolations.cpp				\
	 		Math.cpp

RESOURCE_SRC = ResourceManager.cpp

PACKAGE_SRC = PackageReader.cpp				\
			  PackageHeader.cpp				\
			  PackageCompiler.cpp

STATE_SYSTEM_SRC =	AbstractState.cpp		\
					AbstractTransition.cpp	\
					StateManager.cpp		\
					DefaultTransition.cpp

CONSOLE_SRC = ConsoleCommandParser.cpp		\
			  ConsoleInterpreter.cpp		\
			  ConsoleCore.cpp				\
			  Console.cpp

# compiler
CC = g++
# archiver
AR = ar
# flags used in both mode
COMMON_FLAGS = -Werror -Wextra -Wall -std=c++11
# flags used with archiver
AR_FLAGS = -rs
# flags used in release mode
RELEASE_FLAGS = -O3
# flags used in debug mode
DEBUG_FLAGS = -g
# includes dirs paths
INCLUDE_DIRS = $(addprefix -I, $(INCLUDE_DIR))


OBJS = $(addprefix $(BUILD_DIR)/, $(SRC:.cpp=.o))
SRCS = $(addprefix $(SRC_DIR)/, $(SRC))
CFLAGS = $(COMMON_FLAGS)
TARGET = lib$(LIB_NAME).a
COMPLETE_TARGET = $(OUTPUT_DIR)/$(TARGET)
MODE = release

ifeq ($(MODE), debug)
CFLAGS += $(DEBUG_FLAGS)
COLOR_ACTION = \033[1;32m
else
CFLAGS += $(RELEASE_FLAGS)
COLOR_ACTION = \033[0;34m
endif

COLOR_OFF = \033[0m
COLOR_OBJECT = \033[0m

all: print_summary $(COMPLETE_TARGET)

$(COMPLETE_TARGET): $(BUILD_DIR) $(OBJS)
	@echo " - $(COLOR_ACTION)building$(COLOR_OFF): $(COLOR_OBJECT)$@$(COLOR_OFF)"
	@$(AR) $(AR_FLAGS) $(COMPLETE_TARGET) $(OBJS)

$(addprefix $(BUILD_DIR)/, %.o) : $(addprefix $(SRC_DIR)/, %.cpp)
	@echo " - $(COLOR_ACTION)compiling$(COLOR_OFF): $(COLOR_OBJECT)$<$(COLOR_OFF)"
	@$(CC) $(INCLUDE_DIRS) $(CFLAGS) -c $< -o $@

re: print_summary fclean $(COMPLETE_TARGET)

fclean: clean
	@echo " - $(COLOR_ACTION)removing$(COLOR_OFF): $(COLOR_OBJECT)$(TARGET)$(COLOR_OFF)"
	@rm -f $(COMPLETE_TARGET)
	
clean:
	@echo " - $(COLOR_ACTION)removing$(COLOR_OFF): $(COLOR_OBJECT)$(addprefix "\\n\\t", $(notdir $(OBJS)))$(COLOR_OFF)"
	@rm -f $(OBJS)

$(BUILD_DIR):
	@echo " - $(COLOR_ACTION)creating directory$(COLOR_OFF): $(COLOR_OBJECT)$(BUILD_DIR)$(COLOR_OFF)"
	@mkdir -p $(BUILD_DIR)

print_summary:
ifeq ($(MODE), debug)
	@echo " - Making library $(LIB_NAME) [DEBUG]: $(CFLAGS)"
else
	@echo " - Making library $(LIB_NAME): $(CFLAGS)"
endif

dox:
	@doxygen ./doc/octolib.dox

open_dox:
	@open ./doc/generated/html/index.html

complete: re
	@make re -C tests
	@tests/tester.app
	@make re -C tools/packager
	@make re -C tools/package_reader
	@make re -C benchmarks
	@make re -C interactive_tests/application
	@make re -C interactive_tests/options
	@make re -C interactive_tests/resource_test
	@make re -C interactive_tests/state_manager
	
benchmarks:
	@make -C benchmarks
	@./benchmarks/benchmark.app
