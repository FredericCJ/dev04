#include "config.h"
#include "csv.h"
#include "validip.h"
#include <assert.h>
#include <errno.h>
#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool findIP (unsigned long int ip_decimal);
unsigned long int cast_ip_to (csv_file *csv);
unsigned long int cast_ip_from (csv_file *csv);

int
main (int argc, char **argv)
{
  unsigned long int ip_decimal;

  if (argc == 2)
    {
      // Affectation et test en une seule fois
      if (convertIP2int (argv[1], &ip_decimal))
        {
          printf ("ip_decimal=%lu\n", ip_decimal);
          if (findIP (ip_decimal))
            {
              ;
            }
          else
            {
              printf ("Non trouvé\n");
            }
        }
      else
        {
          fprintf (stderr, "Erreur adresse IP\n");
          exit (EXIT_FAILURE);
        }
    }
  else
    {
      printf ("Usage:\n");
      printf ("\t%s <adresse_ip>\n", argv[0]);
      exit (EXIT_FAILURE);
    }

  return (EXIT_SUCCESS);
}

bool
findIP (unsigned long int ip_decimal)
{
  unsigned long int ip_from;
  unsigned long int ip_to;
  csv_file csv;
  int err;

  err = openCSV (&csv);
  assert (err == EXIT_SUCCESS
          || fprintf (stderr, "Couldn't open %s: %s\n", CSV_FILENAME,
                      strerror (err)));
  csv.read_header = false;

  if (csv.is_open)
    {
      while (getRecordCSV (&csv) == 0)
        {

          ip_from = cast_ip_from (&csv);
          ip_to = cast_ip_to (&csv);

          if (ip_decimal >= ip_from && ip_decimal <= ip_to)
            {
              printf ("Trouvé\n%s, %s\n", csv.record[2], csv.record[3]);
              closeCSV (&csv);
              return (true);
            }
        }
      closeCSV (&csv);
    }
  return (false);
}

unsigned long int
cast_ip_from (csv_file *csv)
{
  int i = 0;
  char iptemp[11];
  char *ptr;
  while (csv->record[0][i] != '\0')
    {
      iptemp[i] = csv->record[0][i];
      i++;
    }
  iptemp[i] = '\0';
  return strtoul (iptemp, &ptr, 10);
}

unsigned long int
cast_ip_to (csv_file *csv)
{
  int i = 0;
  char iptemp[11];
  char *ptr;
  while (csv->record[1][i] != '\0')
    {
      iptemp[i] = csv->record[1][i];
      i++;
    }
  iptemp[i] = '\0';
  return strtoul (iptemp, &ptr, 10);
}
