#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "parser.h"

int main(int argc, const char **argv) {
  if (argc != 2) {
    return -1;
  }

  const char *path_to_eml = argv[1];

  int fd = open(path_to_eml, O_RDWR);
  if (fd == -1) {
    return -1;
  }

  struct stat statbuf = {0};
  if (fstat(fd, &statbuf) == -1) {
    return -1;
  }

  char *email =
      (char *)mmap(NULL, statbuf.st_size, PROT_READ, MAP_SHARED, fd, 0);
  if (email == NULL) {
    return -1;
  }

  Data *data = parse(email);
  check_and_print_data(data);

  close(fd);

  return 0;
}
