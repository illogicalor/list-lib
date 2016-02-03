CC = gcc
CFLAGS = -std=c99 -Wall
OUT = demo

# Project root directory
PROJ_ROOT = .

# Object directory
OBJ_DIR = obj

# Source files root directory
SRC_ROOT = .

# Where to find the source files
VPATH  = $(SRC_ROOT)

# Where to find the header files
IPATH  = $(SRC_ROOT)
INCLUDE_FLAGS := $(foreach NAME,$(IPATH),-I$(NAME))

# Source files
SRCS  = test.c
SRCS += list.c
SRCS_NOPATH := $(foreach NAME,$(SRCS),$(basename $(notdir $(NAME))).c)

# Object files
OBJS_NOPATH := $(SRCS_NOPATH:.c=.o)
OBJS        := $(OBJS_NOPATH:%.o=$(OBJ_DIR)/%.o)

# Create .o output file
$(OBJ_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $< $(INCLUDE_FLAGS)

# Default rule
all: mkdirs
all: $(OUT)

# Rule to create the obj and bin directories
.PHONY: mkdirs
mkdirs:
	@mkdir -p $(OBJ_DIR)

# Rule to create executable
$(OUT): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

# Rule to clean out build products
clean:
	@rm -rf $(OUT) *~ $(OBJ_DIR)

debug:
	@echo OBJ_DIR = $(OBJ_DIR)
	@echo
	@echo SRCS = $(SRCS)
	@echo
	@echo SRCS_NOPATH = $(SRCS_NOPATH)
	@echo
	@echo OBJS_NOPATH = $(OBJS_NOPATH)
	@echo
	@echo OBJS = $(OBJS)

