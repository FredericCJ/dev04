#ifndef VALIDIP_H
#define VALIDIP_H
#include <stdbool.h>
#include <regex.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

bool convertIP2int( char *adresse_ip, unsigned long int *ip_int );

#endif
