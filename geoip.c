#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <regex.h>
#include <assert.h>
#include "validip.h"

bool findIP( int ip_decimal );

int main( int argc, char **argv )
{
    unsigned long int ip_decimal;

    if (argc == 2) {
        // Affectation et test en une seule fois
        if ( convertIP2int( argv[1], &ip_decimal ) ) {
            printf( "ip_decimal=%lu\n", ip_decimal);
            if ( findIP( ip_decimal ) ) {
                printf("Trouvé");
            } else {
                printf("Non trouvé\n");
            }
        } else {
            fprintf( stderr, "Erreur adresse IP\n");
            exit(EXIT_FAILURE);
        }
    } else {
        printf("Usage:\n");
        printf("\t%s <adresse_ip>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    return(EXIT_SUCCESS);
}


bool findIP( int ip_decimal )
{
    return(false);
}
