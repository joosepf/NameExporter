#include "main.h"
#include "sort.h"



int main(int argc, char **argv)
{
    // tagide muutujad
    char marker[START_TAG_LEN];
    char endTag[TAG_LEN] = "</a>";
    char subTag[TAG_LEN] = "submissionstatus";

    Student *studentData = NULL; // dünaamiline massiiv õpilaste andmete jaoks

    int nrOfNames = 0;

    if (argc != 2)
    { // kui on vale arv käsureargumente siis
        GtkApplication *app = gtk_application_new("com.example.gtkgrid", G_APPLICATION_DEFAULT_FLAGS);

        // Connect "activate" signal
        g_signal_connect(app, "activate", G_CALLBACK(ActivateFirstWindow), NULL);

        // Run the application
        int status = g_application_run(G_APPLICATION(app), argc, argv);
        if(status != 0){
            fprintf(stderr,"GUI ERROR: %d\n", status);
        }
        ReadMarker(marker);
        nrOfNames = ReadNames(&studentData, marker, endTag, subTag, "input.txt");
    }
    else{
        if(!strcmp(argv[1], "/?")){
            //printf("Usage: %s <input_file>\n", argv[0]);
            //printf("Example: %s input.txt\n", argv[0]);
            printf("*** NIMEDE korjamine Moodle HTML-ist ***\n");
            printf("vaikimisi sisendfail:   input.txt\n");
            printf("kuni 3 andmefaili:  prefix.txt  suffixa.txt  suffixd.txt marker.txt\n");
            printf("marker.txt  võib puududa\n");
            printf("Rohkem infot readme.md");
            return 0;
        }
        ReadMarker(marker);
        nrOfNames = ReadNames(&studentData, marker, endTag, subTag, argv[1]);
    }
    
    SeparateNames(studentData, nrOfNames);

    char *sufixA = NULL;
    char *sufixD = NULL;
    char *prefix = NULL;

    read_students(&prefix, &sufixA, &sufixD);
    //PrintNames(studentData, nrOfNames);
    write_students(studentData, nrOfNames, prefix, sufixA, sufixD);

    free(studentData); // vabastame mälu

    return 0;
}
