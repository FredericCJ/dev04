#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <regex.h>
#include <assert.h>

bool convertIP2int( char *adresse_ip, unsigned long int *ip_int );
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

// Version avec expression reguliere
// Si retourne false si adresse invalide
bool convertIP2int( char *adresse_ip, unsigned long int *ip_int )
{
    char *IPpattern = "([[:digit:]]{1,3})\\.([[:digit:]]{1,3})\\.([[:digit:]]{1,3})\\.([[:digit:]]{1,3})";
    regex_t regex; 
    int err;
    regmatch_t pmatch[5];
    unsigned long int ip[4];
    bool ip_valid = false;

//    printf("adresse IP: %s\n", adresse_ip );

    // Compilation expression reguliere et verification 4 subexpressions pour detecter une IP
    err = regcomp(&regex, IPpattern, REG_EXTENDED);
    assert( err==0 );
    assert( regex.re_nsub==4 );

    // Execution regex
    err = regexec(&regex, adresse_ip, 5, pmatch, 0);

    if ( (err==0) &&                                // L'expression a ete trouvee (match)
        (pmatch[0].rm_so == 0) &&                   // Aucun caractere avant le "match"
        ( pmatch[0].rm_eo == strlen(adresse_ip) )   // Aucun caractere apres le "match"
        ){

        ip_valid = true;

        // Pour chaque octet trouve de l'adresse IP
        for(int octet_num=1; octet_num<=4; octet_num++) {
            // Copier du debut de la zone trouvee, jusqu'à la fin
            // pmatch[octet_num].rm_so : debut zone trouvee
            // pmatch[octet_num].rm_eo caractere suivant la zone trouvee
            char octet_str[4] = {'\0'};
            for(int pos=pmatch[octet_num].rm_so, i=0; pos<pmatch[octet_num].rm_eo; pos++, i++) {
                octet_str[i] = adresse_ip[pos];
            }

            int octet = atoi(octet_str);
            if ( (octet>=0) && (octet <=255) ) 
                ip[octet_num-1] = octet;
            else
                ip_valid = false;
        }

        if (ip_valid) {
            *ip_int = (ip[0]<<24) | (ip[1] << 16) | (ip[2] << 8) | ip[3];
        }
    }

    return(ip_valid);
}

