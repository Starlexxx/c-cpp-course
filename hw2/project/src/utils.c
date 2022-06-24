#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

#define ERR -1
#define OK 0
#define RECORD_FILENAME recordFilename
#define TRANSACTION_FILENAME transactionFilename
#define BLACK_RECORD_FILENAME blackrecordFilename

void printMenuOut() {
  printf("please enter action\n1 enter data client:\n2 enter data "
         "transaction:\n3 update base\n");
}

void printFieldsMenu() {
  printf("1 Number account:\n"
         "2 Client name: \n"
         "3 Surname:\n"
         "4 address client:\n"
         "5 Client telNum:\n"
         "6 Client indebtedness:\n"
         "7 Client credit limit:\n"
         "8 Client cash payments:\n");
}

int getFields(FILE *stream, clientData_t *client) {
  int rc = 0;
  rc = fscanf(stream, "%d %20s %20s %30s", &client->number, client->name,
              client->surname, client->address);
  if (rc != 4 || fscanf(stream, "%15s %lf %lf %lf", client->telNumber,
                        &client->indebtedness, &client->creditLimit,
                        &client->cashPayments) != 4) {
    rc = ERR;
  } else {
    rc = OK;
  }
  return rc;
}

void writeFields(FILE *stream, clientData_t *client) {
  fprintf(stream, "%-12d%-11s%-11s%-16s%20s%12.2f%12.2f%12.2f\n",
          client->number, client->name, client->surname, client->address,
          client->telNumber, client->indebtedness, client->creditLimit,
          client->cashPayments);
}

void printTransactionMenu() {
  printf("1 Number account:\n2 Client cash payments:\n");
}

void writeTransaction(FILE *stream, transaction *transfer) {
  fprintf(stream, "%-3d%-6.2f\n", transfer->number, transfer->cashPayments);
}

int getTransaction(FILE *stream, transaction *transfer) {
  int resultOfFscanf =
      fscanf(stream, "%d %lf", &transfer->number, &transfer->cashPayments);
  if ((resultOfFscanf != TRANSACTION_FIELDS && resultOfFscanf != EOF) ||
      resultOfFscanf == EOF) {
    return -1;
  } else {
    return 0;
  }
}

void addClient(const char *filename) {
  clientData_t client = {};
  FILE *recordStream = fopen(filename, "r+");
  if (recordStream == NULL) {
    puts("Not acess");
    return;
  }
  printFieldsMenu();
  while (getFields(stdin, &client) == 0) {
    writeFields(recordStream, &client);
    printFieldsMenu();
  }
  fclose(recordStream);
}

void transactionWrite(const char *filename) {
  transaction transfer = {};
  FILE *transactionStream = fopen(filename, "r+");
  if (transactionStream == NULL) {
    puts("Not access");
    return;
  }

  printTransactionMenu();
  while (getTransaction(stdin, &transfer) == 0) {
    writeTransaction(transactionStream, &transfer);
  }
  printTransactionMenu();
  fclose(transactionStream);
}

void blackRecord(const char *RECORD_FILENAME, const char *TRANSACTION_FILENAME,
                 const char *BLACK_RECORD_FILENAME) {
  clientData_t clientData = {};
  transaction transfer = {};
  FILE *recordStream = fopen(RECORD_FILENAME, "r+");
  if (recordStream == NULL) {
    puts("Not access to record.dat");
    return;
  }
  FILE *transactionStream = fopen(TRANSACTION_FILENAME, "r+");
  if (transactionStream == NULL) {
    puts("Not access to transaction.dat");
    fclose(recordStream);
    return;
  }
  FILE *blackrecordStream = fopen(BLACK_RECORD_FILENAME, "r+");
  if (blackrecordStream == NULL) {
    puts("Not access to blackrecord.dat");
    fclose(recordStream);
    fclose(transactionStream);
    return;
  }
  while (getFields(recordStream, &clientData) == 0) {
    while (getTransaction(transactionStream, &transfer) == 0) {
      if (clientData.number == transfer.number && transfer.cashPayments != 0) {
        clientData.creditLimit += transfer.cashPayments;
      }
    }
    writeFields(blackrecordStream, &clientData);
    rewind(transactionStream);
  }
  fclose(recordStream);
  fclose(transactionStream);
  fclose(blackrecordStream);
}
