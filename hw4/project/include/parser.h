#ifndef PROJECT_INCLUDE_PARSER_H_
#define PROJECT_INCLUDE_PARSER_H_

typedef struct {
  char *from;
  char *to;
  char *date;
  int parts;
} Data;

char *find_data(const char *message_from_email, const char *search_key);
int find_parts(const char *message_from_email);
char *skip_symbols(char *str);
char *write_in_multipart(char *str, char *check_str);
int num_of_parts(char *start_str, char *str);
char *skip_spaces(char *str);
Data *parse(const char *message_from_email);
void check_and_print_data(Data *data);

#endif  // PROJECT_INCLUDE_PARSER_H_
