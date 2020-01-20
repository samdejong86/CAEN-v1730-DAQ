EXE = CAENdaq
WHICHMAKE = $(shell which make)
INSTALLOC = $(WHICHMAKE:/make=)

SRC_DIR = src
OBJ_DIR = include

SRC = $(wildcard $(SRC_DIR)/*.cc)
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

ROOTCFLAGS   := ""
ROOTLIBS     := ""

ifneq (, $(shell which root-config))
	ROOTCFLAGS   := $(shell root-config --cflags) -Wl,--no-as-needed
	ROOTLIBS     := $(shell root-config --glibs) -lTreePlayer
endif

CPPFLAGS += -Iinclude
CPPFLAGS +=  -Wall -O2 $(ROOTCFLAGS)
CPPFLAGS += -lCAENDigitizer
CPPFLAGS += -DLINUX
CPPFLAGS += -DNOTIFY

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


.PHONY: install

install:
	@cp $(EXE) $(INSTALLOC)
