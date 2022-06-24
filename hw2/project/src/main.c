#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

#define ACTION 1

int main(void) {
  char recordFilename[] = "record.dat";
  char transactionFilename[] = "transaction.dat";
  char blackrecordFilename[] = "blackrecord.dat";
  printMenuOut();
  int choice = 0;
  while (scanf("%d", &choice) == ACTION) {
    switch (choice) {
    case 1:
      addClient(recordFilename);
      break;
    case 2:
      transactionWrite(transactionFilename);
      break;
    case 3:
      blackRecord(recordFilename, transactionFilename, blackrecordFilename);
      break;
    default:
      puts("error");
      break;
    }
    printMenuOut();
  }
  return 0;
}
