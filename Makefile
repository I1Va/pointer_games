CC = g++

CC_FLAGS = -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal \
	-Winline -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch \
	-Wswitch-default -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions \
	-Wcast-qual -Wconversion -Wctor-dtor-privacy -Wempty-body -Wformat-security -Wformat=2 \
	-Wignored-qualifiers -Wlogical-op -Wno-missing-field-initializers -Wnon-virtual-dtor \
	-Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing \
	-Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -Werror

INCLUDE_FLAGS = -Iinc

DEFINE_FLAGS = -D_DEBUG

BUILD_DIR = build

SRC_DIR = src
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
SRC_OUTPUTFILE = $(BUILD_DIR)/pointers.out

# LD_FLAGS = 

.PHONY: build

all: build launch

build:
	$(CC) $(SRC_FILES) -O0 -o $(SRC_OUTPUTFILE) $(INCLUDE_FLAGS) $(CC_FLAGS)

debug:
	$(CC) $(SRC_FILES) -O0 -o $(SRC_OUTPUTFILE) $(DEFINE_FLAGS) $(INCLUDE_FLAGS) $(CC_FLAGS)
	./$(SRC_OUTPUTFILE) < matrix.txt;

launch:
	./$(SRC_OUTPUTFILE)