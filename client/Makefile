CC        := g++
LD        := g++
CFLAGS	  := -g -Wall \
	     `sdl-config --cflags` \
	     `pkg-config --cflags gl glu`
LIBS	  := `sdl-config --libs` -lSDL_image -lSDL_mixer \
	     `pkg-config --libs gl glu` -lglut
MODULES   := 
SRC_DIRS  := $(addprefix src/, $(MODULES)) src
OBJ_DIRS  := $(addprefix obj/, $(MODULES)) obj
SRC       := $(foreach sdir, $(SRC_DIRS), $(wildcard $(sdir)/*.cpp))
OBJ       := $(patsubst src/%.cpp, obj/%.o, $(SRC))
INCLUDES  := $(addprefix -I, $(SRC_DIRS))
PROGNAME  := destination-client

.SUFFIXES:
.SUFFIXES: .o .cpp .hpp

vpath %.cpp $(SRC_DIRS)

define make-goal
$1/%.o: %.cpp
	$(CC) $(CFLAGS) $(LIBS) $(INCLUDES) -c $$< -o $$@
endef

.PHONY: all
all: dirs $(PROGNAME)

$(PROGNAME): $(OBJ)
	$(LD) $(CFLAGS) $(LIBS) $^ -o $@
 
.PHONY: dirs
dirs: $(OBJ_DIRS)

.PHONY: clean
clean:
	@-rm -rf $(OBJ_DIRS)

$(OBJ_DIRS):
	@mkdir -p $@

%.o: %.cpp %.hpp
	$(make-goal)

$(foreach bdir,$(OBJ_DIRS), \
  $(eval $(call make-goal,$(bdir))))
