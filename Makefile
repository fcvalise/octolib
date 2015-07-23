LIB_NAME = octo
INCLUDE_DIR = ./includes
SRC_DIR = ./src
BUILD_DIR = ./builds
OUTPUT_DIR = .

TARGET_VERSION = $(shell git describe --abbrev=0 --tags)
GIT_BRANCH = $(shell git rev-parse --abbrev-ref HEAD)
GIT_SHORT_COMMIT = $(shell git rev-parse --short HEAD)

# sources
SRC = 	$(RESOURCE_SRC)								\
		$(STATE_SYSTEM_SRC)							\
		$(PACKAGE_SRC)								\
		$(MATH_SRC)									\
		$(CORE_SRC)									\
		$(CONSOLE_SRC)								\
		$(GRAPHICS_SRC)								\
		$(LEVELMAP_SRC)								\
		$(ANIMATION_SRC)							\
		$(AUDIO_SRC)								\
		$(DEBUG_SRC)

CORE_SRC =	Application.cpp							\
			PausableClock.cpp						\
			OptionParser.cpp						\
			Options.cpp								\
			ByteArray.cpp							\
			BinaryInputStream.cpp					\
			BinaryOutputStream.cpp					\
			PrintSFML.cpp							\
			WPrintSFML.cpp							\
			StringUtils.cpp

GRAPHICS_SRC =	GraphicsManager.cpp					\
				GraphicsListeners.cpp				\
				DefaultGraphicsListeners.cpp		\
				Camera.cpp							\
				Hsv.cpp								\
				Palette.cpp							\
				ColorWheel.cpp						\
				OneColor.cpp						\
				SpriteSheet.cpp						\
				AnimatedSprite.cpp					\
				VertexBuilder.cpp

LEVELMAP_SRC =	LevelMap.cpp

AUDIO_SRC =	AudioManager.cpp

ANIMATION_SRC =	SpriteAnimation.cpp					\
				CharacterFrame.cpp					\
				CharacterAnimation.cpp				\
				CharacterSprite.cpp					\
				FiniteStateMachine.cpp

MATH_SRC = 	Interpolations.cpp						\
	 		Math.cpp

RESOURCE_SRC = ResourceManager.cpp					\
			   ResourceLoading.cpp

PACKAGE_SRC = PackageReader.cpp						\
			  PackageHeader.cpp						\
			  PackageCompiler.cpp

STATE_SYSTEM_SRC =	AbstractState.cpp				\
					AbstractTransition.cpp			\
					StateManager.cpp				\
					DefaultTransition.cpp			\
					AbstractResourceLoadingState.cpp

CONSOLE_SRC = ConsoleCommandParser.cpp				\
			  ConsoleInterpreter.cpp				\
			  ConsoleCore.cpp						\
			  Console.cpp							\
			  ConsoleHistory.cpp					\
			  ConsoleCompletion.cpp

DEBUG_SRC = FpsCounter.cpp							\
			AbstractFpsDisplayer.cpp				\
			FpsDisplayer.cpp

.PHONY: doc tools tests

# compiler
CC = $(CXX)
# archiver
AR = ar
# flags used in both mode
COMMON_FLAGS = -Werror -Wextra -Wall -std=c++11
# flags used with archiver
AR_FLAGS = -rs
# flags used in release mode
RELEASE_FLAGS = -O3 -DNDEBUG
# flags used in debug mode
DEBUG_FLAGS = -g
# includes dirs paths
INCLUDE_DIRS = $(addprefix -I, $(INCLUDE_DIR))
# defines
DEFINES = -DLIBOCTO_GIT_BRANCH="\"$(GIT_BRANCH)\"" 				\
		  -DLIBOCTO_GIT_SHORT_COMMIT="\"$(GIT_SHORT_COMMIT)\""

OBJS = $(addprefix $(BUILD_DIR)/, $(SRC:.cpp=.o))
SRCS = $(addprefix $(SRC_DIR)/, $(SRC))
CFLAGS = $(COMMON_FLAGS)
TARGET = lib$(LIB_NAME).a
COMPLETE_TARGET = $(OUTPUT_DIR)/$(TARGET)
MODE = release
RUN_DEPEND = "1"

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

$(COMPLETE_TARGET): $(BUILD_DIR) depend $(OBJS)
	@echo " - $(COLOR_ACTION)building$(COLOR_OFF): $(COLOR_OBJECT)$@$(COLOR_OFF)"
	@$(AR) $(AR_FLAGS) $(COMPLETE_TARGET) $(OBJS)

$(addprefix $(BUILD_DIR)/, %.o) : $(addprefix $(SRC_DIR)/, %.cpp)
	@echo " - $(COLOR_ACTION)compiling$(COLOR_OFF): $(COLOR_OBJECT)$<$(COLOR_OFF)"
	@$(CC) $(DEFINES) $(INCLUDE_DIRS) $(CFLAGS) -c $< -o $@

re: fclean print_summary $(COMPLETE_TARGET)

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
	@echo " - Making library $(LIB_NAME) [DEBUG]: $(CFLAGS) - $(CXX)"
else
	@echo " - Making library $(LIB_NAME): $(CFLAGS)"
endif

tools:
	@make re -C tools/packager MODE=$(MODE)
	@make re -C tools/package_reader MODE=$(MODE)

tests:
	@make -C tests MODE=$(MODE)

run_tests: tests
	@make run -C tests

complete: re
	@make re -C tools/packager MODE=$(MODE)
	@make re -C tools/package_reader MODE=$(MODE)

doc:
	@doxygen ./doc/octolib.dox

open_doc:
	@open ./builds/doc/html/index.html

application_tests:
	@make re -C benchmarks MODE=$(MODE)
	@make re -C interactive_tests/application MODE=$(MODE)
	@make re -C interactive_tests/options MODE=$(MODE)
	@make re -C interactive_tests/resource_test MODE=$(MODE)
	@make re -C interactive_tests/state_manager MODE=$(MODE)
	@make re -C interactive_tests/bspline_test MODE=$(MODE)
	@make re -C interactive_tests/in_game_console MODE=$(MODE)
	@make re -C interactive_tests/firefly MODE=$(MODE)

gource:
	@gource --load-config doc/gource.conf

depend:
ifeq ($(RUN_DEPEND), "1")
	@echo " - $(COLOR_ACTION)Running hatedepend...$(COLOR_OFF)"
	@hatedepend -r -I $(INCLUDE_DIR) -S $(SRC_DIR) -O $(BUILD_DIR)
endif
