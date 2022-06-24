TARGET = main.out 
TEST_TARGET = tests.out
HDRS_DIR = project/include

SRCS =\
	project/src/main.c\
	project/src/utils.c
SRCS_TEST =\
	test_project/src/main.c\
	project/src/utils.c

.PHONY: all clean

all: main tests 

main:$(SRCS)
	$(CC) -Wall -Wextra -Werror -I $(HDRS_DIR) -o $(TARGET) $(CFLAGS) $(SRCS)

tests:$(SRC)
	$(CC) -Wall -Wextra -Werror -I $(HDRS_DIR) -o $(TEST_TARGET) $(CFLAGS) $(SRCS_TEST)


clean:
	rm -rf $(TARGET)
