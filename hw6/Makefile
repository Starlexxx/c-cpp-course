TARGET = main.out

# XXX: Don't forget backslash at the end of any line except the last one
HDRS = \
	   project/include

SRCS = \
       project/src/main.cpp \
       project/src/essence.cpp \
       project/src/enemy.cpp \
       project/src/player.cpp \
       project/src/map.cpp \
       project/src/item.cpp \
       project/src/game.cpp


.PHONY: all clean

all: $(SRCS)
	$(CXX) -std=gnu++17 -Wall -Wextra -Werror $(addprefix -I,$(HDRS)) -o $(TARGET) $(CFLAGS) $(SRCS)

clean:
	rm -rf $(TARGET)
