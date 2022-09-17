#pragma once
// MIT License
// 
// Copyright (c) kbx
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
// 
//    █▀▄ █▀█ █▀▀ ▀█▀ █▄▀             small and simple res/fps picker for linux using GTK
//    █▄▀  █▀▀  █▄█ ░█░ █░█             2184 bytes
//                                              by kbx (github.com/kb-x)
//

#include <gtk/gtk.h>


#pragma GCC diagnostic push 
#pragma GCC diagnostic ignored "-Wformat"
#pragma GCC diagnostic pop


void dpgtk(int *winresx, int *winresy, int *fps)
{
    gtk_init(NULL, NULL);

    // setup window
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    gtk_window_set_default_size(GTK_WINDOW(window), 250, 100);
    g_signal_connect(GTK_WIDGET(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // add resolution picker
    GdkRectangle workarea;
    gdk_monitor_get_workarea(gdk_display_get_primary_monitor(gdk_display_get_default()), &workarea);
    GtkWidget *resolution_picker = gtk_combo_box_text_new();
    uint_fast16_t max_width = workarea.width;
    uint_fast16_t max_height = workarea.height;
    for (int_fast8_t i = 0; i < 20; i++)
    {
        uint_fast16_t width = max_width - (i * 64);
        uint_fast16_t height = max_height - (i * 36);
        if (width <= 854 || height <= 480)
            break;
        char *resolution = g_strdup_printf("%lix%li", width, height);

        gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(resolution_picker), resolution);
        g_free(resolution);
    }

    // fps picker
    GtkWidget *fps_picker = gtk_combo_box_text_new();
    for (int_fast8_t i = 0; i < 10; i++)
    {
        uint_fast8_t fps = 30 + (i * 30);
        char *fps_str = (char *)malloc(10);
        sprintf(fps_str, "%i", fps);
        gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(fps_picker), fps_str);
    }

    // start button
    GtkWidget *start_button = gtk_button_new_with_label("Start");
    g_signal_connect(GTK_WIDGET(start_button), "clicked", G_CALLBACK(gtk_main_quit), NULL);

    // add widgets to window
    GtkWidget *picker_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_box_pack_start(GTK_BOX(picker_box), resolution_picker, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(picker_box), fps_picker, TRUE, TRUE, 0);

    GtkWidget *button_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_box_pack_start(GTK_BOX(button_box), picker_box, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(button_box), start_button, TRUE, TRUE, 0);
    gtk_container_add(GTK_CONTAINER(window), button_box);

    gtk_combo_box_set_active(GTK_COMBO_BOX(resolution_picker), 0);
    gtk_combo_box_set_active(GTK_COMBO_BOX(fps_picker), 0);

    gtk_widget_show_all(window);

    gtk_main();

    // get resolution
    char *resolution = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(resolution_picker));
    char *width_str = strtok(resolution, "x");
    char *height_str = strtok(NULL, "x");
    *winresx = atoi(width_str);
    *winresy = atoi(height_str);

    // get fps
    char *fps_str = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(fps_picker));
    *fps = atoi(fps_str);
}