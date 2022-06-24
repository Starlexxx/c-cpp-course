#include <stdio.h>
#include <string.h>

#include "utils.h"

int compareFields(clientData_t *expectedData, clientData_t *gotData) {
  if (expectedData->number != gotData->number) {
    printf("Mistake in number field! Expected: %d Got: %d\n",
           expectedData->number, gotData->number);
    return 1;
  }
  if (strcmp(expectedData->name, gotData->name) != 0) {
    printf("Mistake in name field! Expected: %s Got: %s\n", expectedData->name,
           gotData->name);
    return 1;
  }
  if (strcmp(expectedData->surname, gotData->surname) != 0) {
    printf("Mistake in surname field! Expected: %s Got: %s\n",
           expectedData->surname, gotData->surname);
    return 1;
  }
  if (strcmp(expectedData->address, gotData->address) != 0) {
    printf("Mistake in address field! Expected: %s Got: %s\n",
           expectedData->address, gotData->address);
    return 1;
  }
  if (strcmp(expectedData->telNumber, gotData->telNumber) != 0) {
    printf("Mistake in telNumber field! Expected: %s Got: %s\n",
           expectedData->telNumber, gotData->telNumber);
    return 1;
  }
  if (expectedData->indebtedness != gotData->indebtedness) {
    printf("Mistake in indebtedness field! Expected: %lf Got: %lf\n",
           expectedData->indebtedness, gotData->indebtedness);
    return 1;
  }
  if (expectedData->creditLimit != gotData->creditLimit) {
    printf("Mistake in creditLimit field! Expected: %lf Got: %lf\n",
           expectedData->creditLimit, gotData->creditLimit);
    return 1;
  }
  if (expectedData->cashPayments != gotData->cashPayments) {
    printf("Mistake in cashPayments field! Expected: %lf Got: %lf\n",
           expectedData->cashPayments, gotData->cashPayments);
    return 1;
  }
  return 0;
}

int main() {
  FILE *testStream = NULL;
  testStream = fopen("test_project/test_files/test.dat", "r+");
  clientData_t expectedData = {1,   "Andrew", "Pavlovskiy", "Moscow", "88005553535",
                       400, 300,      200};
  writeFields(testStream, &expectedData);
  fclose(testStream);

  testStream = fopen("test_project/test_files/test.dat", "r+");
  clientData_t gotData = {};
  getFields(testStream, &gotData);
  printf("%d\n", compareFields(&expectedData, &gotData));
  fclose(testStream);

  return 0;
}
