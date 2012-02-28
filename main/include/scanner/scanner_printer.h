#ifndef SCANNER_PRINTER_H_JHV9902116
#define SCANNER_PRINTER_H_JHV9902116

#include "model/node.h"

void sp_print_error(const enum error_type error_type);
void sp_print_input(const int line_number, const char* input_string, const int input_length);
void sp_print_node(const struct node *node);

#endif /*SCANNER_PRINTER_H_JHV9902116*/