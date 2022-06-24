#ifndef PROJECT_INCLUDE_UTILS_H_
#define PROJECT_INCLUDE_UTILS_H_

#define NUM_OF_FIELDS 8
#define TRANSACTION_FIELDS 2

struct clientData {
  int number;
  char name[20];
  char surname[20];
  char address[30];
  char telNumber[15];
  double indebtedness;
  double creditLimit;
  double cashPayments;
};

typedef struct clientData clientData_t;

struct transaction {
  int number;
  double cashPayments;
};

typedef struct transaction transaction;

void addClient(const char *filename);

void transactionWrite(const char *filename);

void blackRecord(const char *recordFilename, const char *transactionFilename,
                 const char *blackrecordFilename);

void printMenuOut();

void printFieldsMenu();

int getFields(FILE *stream, clientData_t *client);

void writeFields(FILE *stream, clientData_t *client);

#endif  //  PROJECT_INCLUDE_UTILS_H_
