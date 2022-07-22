CC 			= gcc
CFLAGS 		= -Wall -Werror -Wextra -pedantic -std=c11 -fsanitize=address -fanalyzer
LIBS 		= -lncurses

BUILDDIR 	= ../build
TARGET 		= s21_pong

SRC 	 	:= $(shell find . -name "*.c")
INC 	 	:= $(shell find . -name "*.h")

all: 		$(TARGET)

$(TARGET): 	$(SRC) $(INC)
				mkdir -p $(BUILDDIR)
				$(CC) $(CFLAGS) $(SRC) -o $(BUILDDIR)/$(TARGET) $(LIBS)

clean:
				rm -rf *.o $(BUILDDIR)

