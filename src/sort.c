#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sort.h"
#include "write.h"

/**
 * funktsioon loeb failist nimede algustagi
 *
 * parameeter tag - HTML-i tag, mis tähistab nime algust
 * parameeter argv - programmi käsurea argumendid (argv[2] = tagi faili nimi)
 */

void ReadMarker(char marker[START_TAG_LEN])
{

    FILE *markerFile = fopen("marker.txt", "r");
    // tag faili avamine ja kontroll
    if (markerFile == NULL)
    {
        strcpy(marker, "marker.txt");
        return;
    }

    if (fgets(marker, START_TAG_LEN, markerFile) == NULL)
    { // loeb faili lõpuni
        perror("Viga tag faili lugemisel");
        fclose(markerFile);
        exit(EXIT_FAILURE); // kui viga siis fail kinni ja veateade
    }

    marker[strcspn(marker, "\n")] = 0; // trailing \n parandus

    fclose(markerFile);
}

/**
 * funktsioon loeb HTML failist nimed ja määrab, kas töö on esitatud.
 *
 * parameeter students - massiiv õpilastest
 * parameeter tag - HTML-i tag, mis tähistab nime algust
 * parameeter endTag - HTML-i tag, mis tähistab nime lõppu
 * parameeter subtag - HTML-i tag, mis tähistab töö esituse staatuse algust
 * parameeter argv - programmi käsurea argumendid (argv[1] = sisend faili nimi)
 * tagastab loetud nimede arvu
 */

int ReadNames(Student **students, char tag[START_TAG_LEN], char endTag[TAG_LEN], char subTag[TAG_LEN], char *inputFileName)
{

    FILE *inputFile = fopen(inputFileName, "r");

    if (inputFile == NULL)
    {
        perror("Viga sisendfaili avamisel");
        exit(EXIT_FAILURE);
    }

    char *startPos;
    char *endPos;
    unsigned int numberOfNames = 0;
    unsigned int numberOfStudents = INITIAL_SIZE; // algne maht õpilaste andmete jaoks

    fseek(inputFile, 0, SEEK_END); // leiame faili suuruse
    size_t fileSize = (size_t)ftell(inputFile);
    rewind(inputFile);

    if (fileSize <= 0)
    {
        perror("Faili suuruse määramine ebaõnnestus");
        fclose(inputFile);
        exit(EXIT_FAILURE);
    }

    // küsime mälu terve faili jaoks
    char *htmlContent = (char *)malloc(fileSize + 1); //+1 on null terminaatori jaoks
    if (htmlContent == NULL)
    {
        perror("Mälu eraldamine HTML-i jaoks ebaõnnestus");
        fclose(inputFile);
        exit(EXIT_FAILURE);
    }

    size_t bytesRead = fread(htmlContent, 1, fileSize, inputFile); // loeme terve faili
    if (bytesRead != fileSize)
    {
        perror("Viga faili lugemisel");
        free(htmlContent);
        fclose(inputFile);
        exit(EXIT_FAILURE);
    }

    htmlContent[fileSize] = '\0'; // lisame null terminaatori

    *students = (Student *)malloc(numberOfStudents * sizeof(Student)); // dünaamilise mälu eraldamine õpilaste andmete jaoks
    if (*students == NULL)
    {
        perror("Mälu eraldamine ebaõnnestus");
        free(htmlContent);
        fclose(inputFile);
        exit(EXIT_FAILURE);
    }

    startPos = htmlContent; // töötleme kogu HTML-i korraga
    while ((startPos = strstr(startPos, tag)) != NULL)
    {                                      // otsime tagi tekstist
        startPos += strlen(tag);           // liigutame positsiooni edasi tagi pikkuse võrra
        endPos = strstr(startPos, endTag); // määrame lõpu positsiooniks koha kus on lõpu täg
        if (endPos)
        { // kui lõpupositsioon on suurem nullist salvestame nime massiivi
            *endPos = '\0';

            if (numberOfNames >= numberOfStudents)
            {                          // kui õpilaste andmete massiiv täitub, suurendame selle mahtu
                numberOfStudents *= 2; // Kahekordistame mahtu
                Student *temp = (Student *)realloc(*students, numberOfStudents * sizeof(Student));
                if (temp == NULL)
                {
                    perror("Mälu suurendamine ebaõnnestus");
                    free(*students);
                    free(htmlContent);
                    fclose(inputFile);
                    exit(EXIT_FAILURE);
                }
                *students = temp;
            }

            strncpy((*students)[numberOfNames].rName, startPos, RAW_LEN - 1); // kopeerime startPositsioonist nime ja salvestame selle struktuuri raw nimena (ees+perenimi)
            (*students)[numberOfNames].rName[RAW_LEN - 1] = '\0';             // Paneme null terminaatori nime lõppu
            (*students)[numberOfNames].submissionStatus = 0;                  // määrame esitamise muutuja nulliks

            *endPos = endTag[0]; // Taastame esimese märgi, et strstr saaks jätkata otsingut

            char *statusPos = strstr(endPos + strlen(endTag), subTag); // liigume edasi kuni näeme tagi submissionstatus

            if (statusPos)
            {                                                 // kontroll kui peaks juhtuma et ei ole rohkem submissionstatus tagi
                statusPos += strlen(subTag);                  // liigume submissionstatus pikkuse võrra edasi
                char *statusEndPos = strstr(statusPos, "\""); // määrame lõpu positsiooniks koha kus on / sümbol
                if (statusEndPos)
                { // kontroll kas on vell / sümboleid
                    char tempChar = *statusEndPos;
                    *statusEndPos = '\0';
                    if (strcmp(statusPos, "submitted") == 0)
                    {                                                    // kui saame peale submissionstatus submitted siis
                        (*students)[numberOfNames].submissionStatus = 1; // muudame esitamise väärtuseks 1 (tõene)
                    }
                    *statusEndPos = tempChar; // Taastame märgi
                }
            }

            numberOfNames++; // suurendame nimede lugejat ühe võrra

            if(numberOfNames >= 999)
            { // kui nimede arv on suurem kui 999 siis lõpetame
                printf("Leitsin 999 nime, lõpetan\n");
                break; 
            }
        }
        else
        {
            break; // kui rohkem nimesid ei ole liigume tsüklist välja
        }
    }

    if (numberOfNames > 0 && numberOfNames < numberOfStudents)
    { // kui on rohkem mahtu vaja õpilaste andmete jaoks
        Student *temp = (Student *)realloc(*students, numberOfNames * sizeof(Student));
        if (temp != NULL)
        {
            *students = temp;
        }
        // kui realloc ebaõnnestub, jätkame olemasoleva mäluga
    }

    free(htmlContent); // vabastame HTML puhvri mälu
    fclose(inputFile); // sulgeme sisendfaili
    printf("....leitud %d nime sisendfailis  %s\n\n", numberOfNames, inputFileName);
    return (int)numberOfNames; // tagastab mitu nime leidis
}

void PrintNames(Student *students, int len)
{
    for (int i = 0; i < len; i++)
    {
        printf("%s  %s\n",  students[i].lName, students[i].fName);
    }
    printf("\n");
}

/**
 * funktsioon sorteerib õpilased eesnimede järgi
 *
 * parameeter students - massiiv õpilastest
 * parameeter len - õpilaste arv
 */

void SortNames(Student *students, int len)
{
    Student temp; // loome ajutise õpilase

    for (int i = 0; i < len; i++)
    {
        for (int j = 0; j < len - i - 1; j++)
        {
            if (strcmp(students[j].lName, students[j + 1].lName) > 0)
            {
                temp = students[j + 1];
                students[j + 1] = students[j];
                students[j] = temp;
            }
        }
    }
}

/**
 * funktsioon eemaldab eesnimed perenimedes ja jätab alles max 2 eesnime
 *
 * parameeter students - massiiv õpilastest
 * parameeter len - õpilaste arv
 */

void SeparateNames(Student *students, int len)
{ // funktsioon eemaldab eesnimed perenimedes ja jätab alles max 2 eesnime

    for (int i = 0; i < len; i++)
    {
        char *parts[10]; // loodame et ei ole rohkem kui 10 nime kellelgi
        int cnt = 0;

        char *token = strtok(students[i].rName, " "); // jagame nimed osadeks tühikute järgi
        while (token != NULL && cnt < 10)
        {                              // otsime niikaua tühikuid kuni neid jagub aga ei lase üle kümne
            parts[cnt++] = token;      // Nime eralid osad erinevasse parts muutuja indeksile
            token = strtok(NULL, " "); // paneme iga tokeni vahele null terminatsiooni
        }

        if (cnt == 0)
            return; // kui nime pole lõpetame

        strncpy(students[i].lName, parts[cnt - 1], RAW_LEN - 1); // perenimi on alati viimane osa
        students[i].lName[RAW_LEN - 1] = '\0';                   // paneme selle lõpu ka null terminatsiooni

        students[i].fName[0] = '\0'; // tühjendame esinime muutuja
        for (int j = 0; j < cnt - 1 && j < 2; j++)
        {
            if (j > 0)
            {
                strcat(students[i].fName, " "); // paneme nime vahele tühiku ja kui eesnime pole siis jätame nimeks tühiku
            }
            strcat(students[i].fName, parts[j]); // kas esimest nime osa jätame eesnimeks
        }
    }
}
