#include <stdio.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include "config.h"
#include "csv.h"

int openCSV(csv_file *csv){
    if(csv->is_open == true)
        return EXIT_FAILURE;
    if((csv->fcsv = fopen(CSV_FILENAME,"r")) == NULL){
        fprintf(stderr, "Couldn't open %s: %s\n", CSV_FILENAME, strerror(errno));
        return EXIT_FAILURE;
    }
    csv->is_open = true;
    csv->line_counter = 0;
    csv->max_len = 0;
    for(int i=0 ; i<CSV_FIELDCNT ; i++)
        csv->fields_maxlen[i] = 0;
    for(int i=0 ; i<CSV_FIELDCNT ; i++)
        csv->header[i][0] = '\0';
    for(int i=0 ; i<CSV_FIELDCNT ; i++)
        csv->record[i][0] = '\0';
    return EXIT_SUCCESS;
}

int getRecordCSV(csv_file *csv){
    char c = '\0';
    int line_len = 0;
    int field_len = 0;
    int field_num = 0;
    int field_pos = 0;
    
    if(csv->read_header == true)
        getHeader(csv);
    
    while(c != EOF){
        c = fgetc(csv->fcsv);
        line_len++;
        field_len++;

        switch(c){
            case '\n':
                if(field_len-1 >= csv->fields_maxlen[field_num])
                    csv->fields_maxlen[field_num] = field_len-1;
                csv->record[field_num][field_pos] = '\0';
                field_len = 0;
                csv->line_counter++;
                if(line_len >= csv->max_len)
                    csv->max_len = line_len;
                return EXIT_SUCCESS;
            
            case CSV_DELIM:
                if(field_len-1 >= csv->fields_maxlen[field_num])
                    csv->fields_maxlen[field_num] = field_len-1;
                csv->record[field_num][field_pos] = '\0';
                field_num++;
                field_len = 0;
                field_pos = 0;
                break;
            
            default:
                csv->record[field_num][field_pos] = c;
                field_pos++;
        }
    }
    return EXIT_FAILURE;
}

int printRecordCSV(csv_file *csv){
    int j = 0;
    int k = 0;
    for(int i=0 ; i<CSV_FIELDCNT ; i++){
        while(csv->header[i][j] != '\0'){
            printf("%c",csv->header[i][j]);
            j++;
        }
        putchar(':');
        while(j < 22){
            putchar('-');
            j++;
        }
        putchar(':');
        while(csv->record[i][k] != '\0'){
            printf("%c",csv->record[i][k]);
            k++;
        }
        k = 0;
        j = 0;
        printf("\n");
    }

    return EXIT_SUCCESS;
}

int printFieldmaxCSV(csv_file *csv){
    int j = 0;
    printf("+--------------------------------------+\n");
    printf("| Nom champ               | Taille max |\n");
    printf("|--------------------------------------|\n");
    for(int i=0 ; i<CSV_FIELDCNT ; i++){
        printf("| ");
        while(csv->header[i][j] != '\0'){
            printf("%c",csv->header[i][j]);
            j++;
        }
        while(j < 24){
            printf(" ");
            j++;
        }
        printf("|     %2d     |",csv->fields_maxlen[i]);
        j = 0;
        printf("\n");
    }
    printf("+--------------------------------------+\n");
    return EXIT_SUCCESS;
}

int closeCSV(csv_file *csv){
    if(fclose(csv->fcsv) == EOF){
        fprintf(stderr, "Couldn't close %s: %s\n", CSV_FILENAME, strerror(errno));
        return EXIT_FAILURE;
    }
    csv->is_open = false;
    return EXIT_SUCCESS;
}

int getHeader(csv_file *csv){
    char c = '\0';
    int field_pos = 0;
    int field_num = 0;
    while(c != EOF){

        c = fgetc(csv->fcsv);

        switch(c){
            case '\n':
                csv->header[field_num][field_pos] = '\0';
                csv->read_header = false;
                return EXIT_SUCCESS;
            
            case CSV_DELIM:
                csv->header[field_num][field_pos] = '\0';
                field_num++;
                field_pos = 0;
                break;
            
            default:
                csv->header[field_num][field_pos] = c;
                field_pos++;
        }
    }
    return EXIT_FAILURE;
}