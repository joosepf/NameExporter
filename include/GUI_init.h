
#ifndef GUI_INIT_H
#define GUI_INIT_H
#include <gtk/gtk.h>


void OnExitClicked(GtkWidget *button, gpointer user_data);
void UpdateText(GtkWidget *scrolled_window, const char *new_text);
void OnReadMeClicked(void);
void OnInputReloadClicked(GtkWidget *button, gpointer user_data);
void OnOutputReloadClicked(GtkWidget *button, gpointer user_data);
void OnReloadClicked(GtkWidget *button, gpointer user_data);
void ReadFirstLineAndUpdate(char *filename, gpointer user_data);
void OnRunClicked(GtkWidget *button, gpointer user_data);

typedef enum {
    BUTTON_INPUT_RELOAD,
    BUTTON_OUTPUT_RELOAD,
    BUTTON_PREFIX_RELOAD,
    BUTTON_SUFFIX_A_RELOAD,
    BUTTON_SUFFIX_D_RELOAD,
    BUTTON_MARKER_RELOAD
} ButtonID;


#endif
