#ifndef CSV_H
#define CSV_H

#include "config.h"
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct csv_file
{
  FILE *fcsv;
  bool is_open;
  bool read_header;
  int line_counter;
  int max_len; // inclu '\n'

  char fields_maxlen[CSV_FIELDCNT];
  char header[CSV_FIELDCNT][256];
  char record[CSV_FIELDCNT][256];
} csv_file;

int openCSV (csv_file *csv);
int getRecordCSV (csv_file *csv);
int printRecordCSV (csv_file *csv);
int printFieldmaxCSV (csv_file *csv);
int closeCSV (csv_file *csv);
int getHeader (csv_file *csv);

#endif
