#include "GUI_init.h"


GtkWidget* CreateScrollingTextbox() {
    GtkWidget *scrolled_window = gtk_scrolled_window_new();
    GtkWidget *text_view = gtk_text_view_new();
    gtk_widget_add_css_class(text_view, "textbox-text");

    // Make text view read-only
    gtk_text_view_set_editable(GTK_TEXT_VIEW(text_view), FALSE);
    gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(text_view), FALSE);

    // Disable word wrapping to enable horizontal scrolling
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(text_view), GTK_WRAP_NONE);

    // Ensure proper expansion
    gtk_widget_set_hexpand(scrolled_window, TRUE);
    gtk_widget_set_vexpand(scrolled_window, FALSE);

    // Force scrollbar to always be visible
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window), 
                                   GTK_POLICY_ALWAYS, GTK_POLICY_NEVER);

    // Add text view inside the scrolling window
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scrolled_window), text_view);

    return scrolled_window;
}

// Function to initialize GUI
void ActivateFirstWindow(GtkApplication *app) {
 
    // Set styles
    GdkDisplay *display = gdk_display_get_default();
    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(provider, "./style.css");
    gtk_style_context_add_provider_for_display(display,
                                            GTK_STYLE_PROVIDER(provider),
                                            GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
                        

    // Create main window
    GtkWidget *window1 = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window1), "GUI - moodle HTML Name Scanner");
    gtk_window_set_default_size(GTK_WINDOW(window1), 1000, 500);

    // Create a grid layout
    GtkWidget *grid = gtk_grid_new();
    gtk_window_set_child(GTK_WINDOW(window1), grid);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 20);
    gtk_grid_set_row_spacing(GTK_GRID(grid), 20);
    gtk_widget_add_css_class(grid, "custom-grid");


    // INPUT FILE
    GtkWidget *inputLab = gtk_label_new("input.txt :");
    //gtk_widget_add_css_class(inputLab, "label-file");
    gtk_grid_attach(GTK_GRID(grid), inputLab, 1, 1, 1, 1);

    GtkWidget *inputText = CreateScrollingTextbox();
    gtk_grid_attach(GTK_GRID(grid), inputText, 1, 2, 15, 3); 

    GtkWidget *inputBut = gtk_button_new_with_label("reLOAD");
    gtk_grid_attach(GTK_GRID(grid), inputBut, 16, 2, 1, 2);
    g_signal_connect(inputBut, "clicked", G_CALLBACK(OnInputReloadClicked), inputText);
    OnInputReloadClicked(inputBut, inputText);

    // OUTPUT FILE
    GtkWidget *outputLab = gtk_label_new("output.txt :");
    gtk_widget_add_css_class(outputLab, "label-file");
    gtk_grid_attach(GTK_GRID(grid), outputLab, 1, 5, 1, 1); 

    GtkWidget *outputText = CreateScrollingTextbox();
    gtk_grid_attach(GTK_GRID(grid), outputText, 1, 6, 15, 3);  

    GtkWidget *outputBut = gtk_button_new_with_label("reLOAD");
    gtk_grid_attach(GTK_GRID(grid), outputBut, 16, 6, 1, 2);   
    g_signal_connect(outputBut, "clicked", G_CALLBACK(OnOutputReloadClicked), outputText);
    OnOutputReloadClicked(outputBut, outputText);

  
    // PREFIX FILE
    GtkWidget *prefixLab = gtk_label_new("prefix.txt :");
    gtk_widget_add_css_class(prefixLab, "label-file");
    gtk_grid_attach(GTK_GRID(grid), prefixLab, 1, 9, 1, 1);  
 
    GtkWidget *prefixText = CreateScrollingTextbox();
    ReadFirstLineAndUpdate("prefix.txt", prefixText);
    gtk_grid_attach(GTK_GRID(grid), prefixText, 1, 10, 15, 3);  

    GtkWidget *prefixBut = gtk_button_new_with_label("reLOAD");
    gtk_grid_attach(GTK_GRID(grid), prefixBut, 16, 10, 1, 2);  
    g_object_set_data(G_OBJECT(prefixBut), "id", GINT_TO_POINTER(BUTTON_PREFIX_RELOAD));
    g_signal_connect(prefixBut, "clicked", G_CALLBACK(OnReloadClicked), prefixText);  

   
    // SUFFIX_A FILE
    GtkWidget *suffixALab = gtk_label_new("suffixa.txt :");
    gtk_widget_add_css_class(suffixALab, "label-file");
    gtk_grid_attach(GTK_GRID(grid), suffixALab, 1, 13, 1, 1); 

    GtkWidget *suffixAText = CreateScrollingTextbox();
    ReadFirstLineAndUpdate("suffixa.txt", suffixAText);    
    gtk_grid_attach(GTK_GRID(grid), suffixAText, 1, 14, 15, 3);

    GtkWidget *suffixABut = gtk_button_new_with_label("reLOAD");
    gtk_grid_attach(GTK_GRID(grid), suffixABut, 16, 14, 1, 2);   
    g_object_set_data(G_OBJECT(suffixABut), "id", GINT_TO_POINTER(BUTTON_SUFFIX_A_RELOAD));
    g_signal_connect(suffixABut, "clicked", G_CALLBACK(OnReloadClicked), suffixAText);  

   
    // SUFFIX_D FILE
    GtkWidget *suffixDLab = gtk_label_new("suffixd.txt :");
    gtk_widget_add_css_class(suffixDLab, "label-file");
    gtk_grid_attach(GTK_GRID(grid), suffixDLab, 1, 17, 1, 1);  

    GtkWidget *suffixDText = CreateScrollingTextbox();
    ReadFirstLineAndUpdate("suffixd.txt", suffixDText);    
    gtk_grid_attach(GTK_GRID(grid), suffixDText, 1, 18, 15, 3);  

    GtkWidget *suffixDBut = gtk_button_new_with_label("reLOAD");
    gtk_grid_attach(GTK_GRID(grid), suffixDBut, 16, 18, 1, 2);
    g_object_set_data(G_OBJECT(suffixDBut), "id", GINT_TO_POINTER(BUTTON_SUFFIX_D_RELOAD));
    g_signal_connect(suffixDBut, "clicked", G_CALLBACK(OnReloadClicked), suffixDText);     
   
   
    // MARKER FILE
    GtkWidget *markerLab = gtk_label_new("marker.txt :");
    gtk_grid_attach(GTK_GRID(grid), markerLab, 1, 21, 1, 1);  
    gtk_widget_add_css_class(markerLab, "label-file");

    GtkWidget *markerText = CreateScrollingTextbox();
    ReadFirstLineAndUpdate("marker.txt", markerText);
    gtk_grid_attach(GTK_GRID(grid), markerText, 1, 22, 15, 3);  

    GtkWidget *markerBut = gtk_button_new_with_label("reLOAD");
    gtk_grid_attach(GTK_GRID(grid), markerBut, 16, 22, 1, 2);
    g_object_set_data(G_OBJECT(markerBut), "id", GINT_TO_POINTER(BUTTON_MARKER_RELOAD));
    g_signal_connect(markerBut, "clicked", G_CALLBACK(OnReloadClicked), markerText); 


    // === EMPTY LABEL (SPACER) ===
    GtkWidget *emptyLabel = gtk_label_new(" ");
    gtk_grid_attach(GTK_GRID(grid), emptyLabel, 18, 2, 20, 3); 

    // README BUTTON
    GtkWidget *readmeBut = gtk_button_new_with_label("README.MD");
    gtk_grid_attach(GTK_GRID(grid), readmeBut, 49, 2, 1, 3);
    g_signal_connect(readmeBut, "clicked", G_CALLBACK(OnReadMeClicked), NULL);

    // RUN BUTTON
    GtkWidget *runBut = gtk_button_new_with_label("RUN");
    gtk_widget_add_css_class(runBut, "run-button");
    gtk_grid_attach(GTK_GRID(grid), runBut, 43, 9, 7, 5);
    g_signal_connect(runBut, "clicked", G_CALLBACK(OnRunClicked), app);

    // EXIT BUTTON
    GtkWidget *exitBut = gtk_button_new_with_label("EXIT");
    gtk_grid_attach(GTK_GRID(grid), exitBut, 49, 22, 1, 3);
    g_signal_connect(exitBut, "clicked", G_CALLBACK(OnExitClicked), app);


    // Show window
    gtk_window_present(GTK_WINDOW(window1));

}

