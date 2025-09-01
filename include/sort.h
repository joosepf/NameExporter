#ifndef SORT_H
#define SORT_H


#define RAW_LEN 44          //kui pikk tohib kogu nimi olla
#define FNAME_LEN 44        //maksimum eesnime pikkus
#define LNAEM_LEN 44        //maksimum perenime pikkus
#define START_TAG_LEN 11    //maksimaalne algustagi pikkus
#define TAG_LEN 17          //maksimaalne ülejäänud tagi pikkus
#define INITIAL_SIZE 256    //algne suurus

typedef struct Student{
    char rName[RAW_LEN];    //RAW massiiv (eesnimi + perenimi)
    char fName[FNAME_LEN];  //Eesnimede massiiv
    char lName[LNAEM_LEN];  //Perenimede massiiv
    int submissionStatus;   //töö esitamise staatus
}Student;

//funktsioonide prototüübid

void ReadMarker(char tag[START_TAG_LEN]);
int ReadNames(Student **students, char tag[START_TAG_LEN], char endTag[TAG_LEN], char subTag[TAG_LEN], char *inputFileName);
void PrintNames(Student *students, int len);
void SortNames(Student *students, int len);
void SeparateNames(Student *students, int len);
void write_students(Student *students, int student_count, char *prefix, char *sufixA, char *sufixD);
void read_students(char **prefix, char **sufixA, char **sufixD);


#endif // SORT_H
