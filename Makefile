EXE = CAENdaq

SRC_DIR = src
OBJ_DIR = obj

SRC = $(wildcard $(SRC_DIR)/*.cc)
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

ROOTCFLAGS   := $(shell root-config --cflags) -Wl,--no-as-needed
ROOTLIBS     := $(shell root-config --glibs) -lTreePlayer 

CPPFLAGS += -Iinclude
CPPFLAGS +=  -Wall -O2 $(ROOTCFLAGS)
CPPFLAGS += -lCAENDigitizer
CPPFLAGS += -DLINUX

CFLAGS += -Wall
LDFLAGS += -Llib
LDLIBS += -lm
LDLIBS += $(ROOTLIBS) 

.PHONY: all clean

all: $(EXE)

$(EXE): $(OBJ)
	$(CXX) $(LDFLAGS) $^ $(LDLIBS) -o $@ $(CPPFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CXX) $(CPPFLAGS) $(CFLAGS) -c $< -o $@ 

