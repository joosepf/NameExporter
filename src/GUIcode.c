#include "GUIcode.h"
#include "GUI_init.h"

void ReadFirstLineAndUpdate(char *filename, gpointer user_data){
    FILE *file = fopen(filename, "r");

    if (file == NULL){
        UpdateText(user_data, "Can't open/find file");
        gtk_widget_remove_css_class(user_data, "custom-textbox"); // Clear any existing styles
        gtk_widget_add_css_class(user_data, "custom-textbox-red"); // Apply new style;
        return;
    }
    char buffer[BUFFER_LEN] = {""};
    fgets(buffer, BUFFER_LEN, file);
    fclose(file);
    //printf("%d", buffer[0]);
    if(buffer[0] == 10){
        UpdateText(user_data, "First line missing text");
        gtk_widget_remove_css_class(user_data, "custom-textbox"); // Clear any existing styles
        gtk_widget_add_css_class(user_data, "custom-textbox-red"); // Apply new style;
        return;
    }
    UpdateText(user_data, buffer);
    gtk_widget_remove_css_class(user_data, "custom-textbox-red"); // Clear any existing styles
    gtk_widget_add_css_class(user_data, "custom-textbox"); // Apply new style;
}


void OnReloadClicked(GtkWidget *button, gpointer user_data) {
    int id = GPOINTER_TO_INT(g_object_get_data(G_OBJECT(button), "id"));

    switch (id) {
        //BUTTON GET LABEL FAILINIMEKS, FAILINIMED DEFINEERIDA, LUGEDA TEXBOXI MUUTUJAID
        case BUTTON_PREFIX_RELOAD:
            //g_print("Reloading prefix.txt\n");
            ReadFirstLineAndUpdate("prefix.txt", user_data);
            break;
        case BUTTON_SUFFIX_A_RELOAD:
            //g_print("Reloading suffixa.txt\n");
            ReadFirstLineAndUpdate("suffixa.txt", user_data);
            break;
        case BUTTON_SUFFIX_D_RELOAD:
            //g_print("Reloading suffixd.txt\n");
            ReadFirstLineAndUpdate("suffixd.txt", user_data);
            break;
        case BUTTON_MARKER_RELOAD:
            //g_print("Reloading marker.txt\n");
            ReadFirstLineAndUpdate("marker.txt", user_data);
            break;
        default:
            g_print("Unknown button clicked!\n");
    }
}

void UpdateText(GtkWidget *scrolled_window, const char *new_text) {
    // Get the child (which is the GtkTextView)
    GtkWidget *text_view = gtk_scrolled_window_get_child(GTK_SCROLLED_WINDOW(scrolled_window));
    
    if (GTK_IS_TEXT_VIEW(text_view)) { // Ensure it's a text view
        GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
        gtk_text_buffer_set_text(buffer, new_text, -1);
    }
}


void OnInputReloadClicked(GtkWidget *button, gpointer user_data){
    (void)button;
    FILE *file = fopen("input.txt", "r");
                                                        //tag faili avamine ja kontroll
    if (file == NULL){
        UpdateText(user_data, "Cannot open or find input HTML file");
        gtk_widget_remove_css_class(user_data, "custom-textbox"); // Clear any existing styles
        gtk_widget_add_css_class(user_data, "custom-textbox-red"); // Apply new style;
    }
    else{
        UpdateText(user_data, "OK :  File Found");
        gtk_widget_remove_css_class(user_data, "custom-textbox-red"); // Clear any existing styles
        gtk_widget_add_css_class(user_data, "custom-textbox"); // Apply new style;
        fclose(file);
    }
}


void OnOutputReloadClicked(GtkWidget *widget, gpointer user_data){
    GtkButton *button = (GtkButton *)widget;
    
    if(!strcmp(gtk_button_get_label(button), "reLOAD")){
        FILE *file = fopen("output.txt", "r");
        if (file == NULL){
            UpdateText(user_data, "NO output.txt exist");
            gtk_widget_remove_css_class(user_data, "custom-textbox-red"); // Clear any existing styles
            gtk_widget_add_css_class(user_data, "custom-textbox"); // Apply new style;
            gtk_button_set_label (button, "reLOAD");
        }
        else{
            fclose(file);
            UpdateText(user_data, "File exists :  remove it");
            gtk_widget_remove_css_class(user_data, "custom-textbox"); // Clear any existing styles
            gtk_widget_add_css_class(user_data, "custom-textbox-red"); // Apply new style;
            gtk_button_set_label (button, "RENAME");
        }
    }
    else{
        FILE *file = fopen("output.txt", "r");
        if (file == NULL){
            gtk_button_set_label (button, "reLOAD");
            OnOutputReloadClicked(widget, user_data);
            return;
        }
        fclose(file);
        time_t currentTime;
        time(&currentTime);
        
        struct tm *timeInfo = localtime(&currentTime);
        
        char clock[40];
        strftime(clock, sizeof clock, "%d_%m_%Y-%H_%M_%S", timeInfo);
        char outFileNew[60] = "output";
        strcat(outFileNew, clock);
        strcat(outFileNew, ".txt");
        if (rename("output.txt", outFileNew) == 0) {
            gtk_button_set_label (button, "reLOAD");
            OnOutputReloadClicked(widget, user_data);
        } else {
            fprintf(stderr, "Can't rename file");
        }
    }
}


void OnExitClicked(GtkWidget *button, gpointer user_data){
    (void)button;
    //pls mitte valgrindi proovida(ma ei tea kuhu mälu jookseb)
    g_application_quit(user_data);
    exit(EXIT_SUCCESS);
}


void OnRunClicked(GtkWidget *button, gpointer user_data){
    (void)button;
    g_application_quit(user_data);
}


void OnReadMeClicked(void){
    #ifdef _WIN32
    system("start readme.md");
    #else
    system("xdg-open readme.md");
    #endif
}
