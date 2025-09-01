#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "write.h"
#include "sort.h"

void read_students(char **prefix, char **sufixA, char **sufixD) 
{
    FILE *pfile = fopen("prefix.txt", "r");
    
    if (!pfile ){
        perror("viga prefix.txt avamisel");
        exit(EXIT_FAILURE);
    }
    
    
    FILE *sfileA = fopen("suffixa.txt", "r");
    
    if (!sfileA ){
        perror("viga suffixa.txt avamisel");
        fclose(pfile);
        exit(EXIT_FAILURE);
    }
    
    FILE *sfileD = fopen("suffixd.txt", "r");
    
    if (!sfileD ){
        perror("viga suffixd.txt avamisel");
        fclose(pfile);
        fclose(sfileA);
        exit(EXIT_FAILURE);
    }
    
    *prefix = malloc(MAX_LINE_LENGTH * sizeof(char));
    *sufixA = malloc(MAX_LINE_LENGTH * sizeof(char));
    *sufixD = malloc(MAX_LINE_LENGTH * sizeof(char));
    
    if (!*prefix || !*sufixA || !*sufixD) {
        fprintf(stderr, "Mälu eraldamine ebaõnnestus\n");
        exit(EXIT_FAILURE);
    }
    
    if (!fgets(*prefix, MAX_LINE_LENGTH, pfile)){
        perror("Viga prefix faili lugemisel");
    }
    if (!fgets(*sufixA, MAX_LINE_LENGTH, sfileA)){
        perror("Viga suffixA faili lugemisel");
    }
    if (!fgets(*sufixD, MAX_LINE_LENGTH, sfileD)){
        perror("Viga suffixD faili lugemisel");
    }
    
    (*prefix)[strcspn(*prefix, "\n")] = 0;
    (*sufixA)[strcspn(*sufixA, "\n")] = 0; 
    (*sufixD)[strcspn(*sufixD, "\n")] = 0; 
    
    fclose(pfile);
    fclose(sfileA);
    fclose(sfileD);

    printf("prefix:\n%s\n", *prefix);
    printf("sufixA:\n%s\n", *sufixA);
    printf("sufixD:\n%s\n\n", *sufixD);

}

void write_students(Student *students, int studentCount, char *prefix, char *sufixA, char *sufixD) 
{
    FILE *output_file = fopen("output.txt", "r");
    if(output_file != NULL){
        fclose(output_file);
        perror("Väljund faili juba eksisteerib");
        return;
    }
    output_file = fopen("output.txt", "w");
    if (!output_file) 
    {
        perror("Väljund faili avamisel tekkis viga");
        return;
    }

    fprintf(output_file, "  HTMLi originaaljärjestuses:   Eesnimi  Perenimi\n");
    for(int i = 0; i < studentCount; i++){
        fprintf(output_file, "%s  %s\n", students[i].fName, students[i].lName);
    }
    fprintf(output_file, "\n\n");

    fprintf(output_file, "  prefix  Eesnimi Perenimi  suffix :   HTMLi originaaljärjestuses\n");
    size_t spaceAmount = 0;
    for (int i = 0; i < studentCount; i++) 
    {
        fprintf(output_file, "%s", prefix);

        spaceAmount = NAME_SIZE - CountUtf8Letters(students[i].fName);
        for(size_t a = 0; a < spaceAmount; a++){
            fprintf(output_file, " ");
        }
        fprintf(output_file, "%s <B> %s", students[i].fName, students[i].lName);

        spaceAmount = NAME_SIZE - CountUtf8Letters(students[i].lName);
        for(size_t a = 0; a < spaceAmount; a++){
            fprintf(output_file, " ");
        }

        fprintf(output_file, "%s\n", students[i].submissionStatus ? sufixD : sufixA);
    }
    fprintf(output_file, "\n\n");

    SortNames(students, studentCount);

    fprintf(output_file, "  alfabeetiliselt:   Perenimi  Eesnimi\n");
    for(int i = 0; i < studentCount; i++){
        fprintf(output_file, "%s  %s\n", students[i].lName, students[i].fName);
    }

    fprintf(output_file, "\n\n");
    fprintf(output_file, "  prefix  Eesnimi Perenimi  suffix :   alfabeetiliselt Perenimi\n");
    spaceAmount = 0;
    for (int i = 0; i < studentCount; i++) 
    {
        fprintf(output_file, "%s", prefix);

        spaceAmount = NAME_SIZE - CountUtf8Letters(students[i].fName);
        for(size_t a = 0; a < spaceAmount; a++){
            fprintf(output_file, " ");
        }
        fprintf(output_file, "%s <B> %s", students[i].fName, students[i].lName);

        spaceAmount = NAME_SIZE - CountUtf8Letters(students[i].lName);
        for(size_t a = 0; a < spaceAmount; a++){
            fprintf(output_file, " ");
        }

        fprintf(output_file, "%s\n", students[i].submissionStatus ? sufixD : sufixA);
    }
    fclose(output_file);
    printf("output.txt  VALMIS\n");
}


size_t CountUtf8Letters(const char *utf8_str) {
    size_t count = 0;
    for (const unsigned char *ptr = (const unsigned char *)utf8_str; *ptr; ++ptr) {
        if ((*ptr & 0xC0) != 0x80) {
            count++;
        }
    }
    return count;
}