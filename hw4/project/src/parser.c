#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parser.h"

#define START_SIZE 50
#define FROM "From:"
#define TO "To:"
#define DATE "Date:"
#define CONTENT_TYPE "Content-Type: "
#define MULTIPART "multipart"
#define BOUNDARY "boundary"
#define RATIO 1.6
#define END_LINE_BYTES 2
#define BYTE 1

char *find_data(const char *message_from_email, const char *search_key) {
  const char *str = search_key;

  if (!strstr(message_from_email, str)) {
    return NULL;
  }

  char *data_str = strstr(message_from_email, str);

  data_str = skip_spaces(data_str);

  if (data_str == message_from_email) {
    data_str += strlen(str);
  } else {
    char *prev_data_str = data_str - BYTE;
    while (*prev_data_str != '\n') {
      data_str += strlen(str);
      data_str = strstr(data_str, str);
      prev_data_str = data_str - BYTE;
    }
    data_str += strlen(str);
  }

  data_str = skip_spaces(data_str);

  size_t cur_size_data = START_SIZE;
  char *data = calloc(cur_size_data, sizeof(char));

  if (!data) {
    return NULL;
  }

  size_t i = 0;
  while (1) {
    if ((((*data_str == '\r') && (*(data_str + BYTE) == '\n')) &&
         *(data_str + END_LINE_BYTES) != ' ') ||
        (*data_str == '\n' && *(data_str + BYTE) != ' ')) {
      break;
    }

    if (*data_str == '\r') {
      data_str += END_LINE_BYTES;
      continue;
    }

    if (*data_str == '\n') {
      data_str += BYTE;
      continue;
    }

    if (i + BYTE >= cur_size_data) {
      cur_size_data *= RATIO;
      char *new_data = realloc(data, cur_size_data * sizeof(char));
      if (!new_data) {
        free(data);
        return NULL;
      }
      data = new_data;
      size_t n = cur_size_data - i;
      char *end_of_str = data;
      end_of_str += i;
      memset(end_of_str, 0, n);
    }
    data[i] = *data_str;

    i++;
    data_str++;
  }
  return data;
}

int find_parts(const char *message_from_email) {
  char *check_multipart = strstr(message_from_email, CONTENT_TYPE);

  if (!check_multipart) {
    return 1;
  }

  if (check_multipart == message_from_email) {
    check_multipart += strlen(CONTENT_TYPE);
  } else {
    char *prev_date_str = check_multipart - BYTE;
    while (*prev_date_str != '\n') {
      check_multipart += strlen(CONTENT_TYPE);
      check_multipart = strstr(check_multipart, CONTENT_TYPE);
      if (!check_multipart) {
        return 1;
      }
      prev_date_str = check_multipart - BYTE;
    }
    check_multipart += strlen(CONTENT_TYPE);
  }

  char *multipart = calloc(START_SIZE, sizeof(char));

  if (!multipart) {
    return 0;
  }

  multipart = write_in_multipart(multipart, check_multipart);

  const char *multipart_compare = MULTIPART;
  if (strcasecmp(multipart, multipart_compare) != 0) {
    free(multipart);
    return 1;
  }

  const char *boundary = BOUNDARY;
  char *start_separator = strcasestr(message_from_email, boundary);
  if (!start_separator) {
    free(multipart);
    return -1;
  }

  if (*(start_separator - BYTE) != '\n' && *(start_separator - BYTE) != ' ' &&
      *(start_separator - BYTE) != '\t' && *(start_separator - BYTE) != ';') {
    free(multipart);
    return 1;
  }
  start_separator += strlen(boundary);

  start_separator = skip_symbols(start_separator);

  size_t cur_size_separator = START_SIZE;
  char *separator = calloc(cur_size_separator, sizeof(char));

  size_t k = 0;
  while (1) {
    if ((*start_separator == '\r') || (*start_separator == '\n')) {
      separator[k] = '\0';
      break;
    }

    if (*start_separator == '\"' || *start_separator == ' ') {
      separator[k] = '\0';
      break;
    }

    if (k + BYTE >= cur_size_separator) {
      cur_size_separator *= RATIO;
      char *new_separator =
          realloc(separator, cur_size_separator * sizeof(char));
      if (!new_separator) {
        free(multipart);
        free(separator);
        return 0;
      }
      separator = new_separator;
    }
    separator[k] = *start_separator;

    k++;
    start_separator++;
  }

  int parts = num_of_parts(start_separator, separator);

  if (parts < 1) {
    free(separator);
    free(multipart);
    return 0;
  }

  free(separator);
  free(multipart);

  return parts;
}

char *skip_symbols(char *str) {
  while (*str == '\"' || *str == ' ' || *str == '=') {
    str++;
  }
  return str;
}

char *write_in_multipart(char *str, char *check_str) {
  size_t i = 0;
  while (1) {
    if (*check_str == '/') {
      break;
    }
    str[i] = *check_str;

    i++;
    check_str++;
  }

  return str;
}

int num_of_parts(char *start_str, char *str) {
  int counter = 0;
  while (1) {
    start_str = strstr(start_str, str);
    if (start_str == NULL) {
      break;
    }
    char *check_end_boundary = start_str + strlen(str);
    if (*check_end_boundary == '-') {
      break;
    }
    start_str += strlen(str);
    counter++;
  }
  return counter;
}

char *skip_spaces(char *str) {
  while (*str == ' ') {
    str++;
  }
  return str;
}

Data *parse(const char *message_from_email) {
  Data *data = calloc(1, sizeof(Data));

  if (!data) {
    free(data);
    return NULL;
  }

  data->from = find_data(message_from_email, FROM);
  data->to = find_data(message_from_email, TO);
  data->date = find_data(message_from_email, DATE);
  data->parts = find_parts(message_from_email);

  return data;
}

void check_and_print_data(Data *data) {
  if (data->from) {
    printf("%s", data->from);
    free(data->from);
  }

  printf("|");

  if (data->to) {
    printf("%s", data->to);
    free(data->to);
  }

  printf("|");

  if (data->date) {
    printf("%s", data->date);
    free(data->date);
  }

  printf("|");
  printf("%d", data->parts);

  free(data);
}
