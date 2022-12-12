#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>
#include "gui.h"

// Stockage de trucs

GtkWidget *window;
GtkWidget *container;
GtkWidget *event_box;
GtkWidget *drawing_area;
GtkWidget *label_me;
GtkWidget *label_playing;
GtkWidget *label_move;
GtkWidget *entry;
GtkWidget *button;
GtkWidget *click;

Game *gui_last_game;
Cell gui_last_me;
State gui_last_state;
Move gui_last_move;

int has_clicked = 0;
int i1, i2, j1, j2;

// Fonctions internes

char *char_to_string(char c) {
    char *string = malloc(2 * sizeof(char));
    string[0] = c;
    string[1] = '\0';
    return string;
}

char *chars_to_string(char c, char c2) {
    char *string = malloc(2 * sizeof(char));
    string[0] = c;
    string[1] = c2;
    string[2] = '\0';
    return string;
}

void play_sound(char *path) {
    /*
     * Joue un son
     */

    char command[100];
#ifdef __APPLE__
    sprintf(command, "afplay %s &", path);
#else
    sprintf(command, "aplay %s 2>/dev/null &", path);
#endif
    system(command);
}

void gui_background_start(Game *game) {
    /*
     * Initialisation du background thread
     * Pour que le jeu se fasse en background et ne bloque pas l'interface
     */

    pthread_t thread;
    pthread_create(&thread, NULL, game_start, game);
}

void gui_background_turn() {
    if (gui_last_game->ia_override) {
        return;
    }
    game_turn(gui_last_game, gui_last_move);
}

void gui_background_turn_ia() {
    if (gui_last_game->ia_override) {
        ia_update(gui_last_game, gui_last_me, gui_last_state);
    }
}

void gui_button_callback() {
    /*
     * Fonction appelée sur le background thread
     * après avoir mi à jour le jeu (et lu le move si besoin)
     */

    if (gui_last_game->playing != gui_last_me || gui_last_state != STATE_PLAYING) {
        return;
    }

    gtk_widget_set_sensitive(button, FALSE);
    gui_last_move = move_from_string(g_strdup(gtk_entry_get_text(GTK_ENTRY(entry))));
    gtk_entry_set_text(GTK_ENTRY(entry), "");

    if (move_apply(gui_last_move, gui_last_me, gui_last_game->board, 0) == 0) {
        gtk_label_set_text(GTK_LABEL(label_move), g_strdup_printf("Coup invalide !"));
        return;
    }

    pthread_t thread;
    pthread_create(&thread, NULL, gui_background_turn, NULL);
}

gboolean gui_entry_callback(GtkWidget *widget, GdkEventKey *event, gpointer user_data) {
    // Tester si entré est pressé:
    if (event->keyval == GDK_KEY_Return) {
        gui_button_callback();
        return TRUE;
    }
    return FALSE;
}

gboolean gui_click_callback(GtkWidget *widget, GdkEventButton *event, gpointer user_data) {
    // (x,y) = prendre coor sourri
    int x = event->x;
    int y = event->y;
    int i = (y - 65) / 70;
    int j = (x - 65) / 70;

    if (has_clicked) {
        i2 = i;
        j2 = j;
        gui_last_move = move_create(i1, j1, i2, j2);
        gtk_entry_set_text(GTK_ENTRY(entry), move_to_string(gui_last_move));
        gui_button_callback();
        has_clicked = 0;
    }
    else {
        i1 = i;
        j1 = j;
        gtk_entry_set_text(GTK_ENTRY(entry), chars_to_string('A' + i1, '1' + j1));
        has_clicked = 1;
    }
}

void gui_draw_callback() {
    gtk_widget_queue_draw(drawing_area);
}

static void gui_destroy(GtkWidget *widget, gpointer data) {
    gtk_main_quit();
}

void clear(cairo_t *cr) {
    /* Save current context */
    cairo_save(cr);
    cairo_set_source_rgb(cr, 1, 1, 1);
    cairo_paint(cr);
    /* Restore context */
    cairo_restore(cr);
}

gboolean gui_update_grid(GtkWidget *widget, cairo_t *cr, gpointer data) {
    /*
     * Mise à jour de la grille dans l'interface graphique
     */

    // Set the line width and color for the rectangle
    clear(cr);
    // Draw the circles
    for (int i = 0; i < 8; i++) {
        cairo_select_font_face(cr, "Calibri", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
        cairo_set_font_size(cr, 24);
        cairo_move_to(cr, 92.5 + i * 70, 50);
        cairo_set_source_rgba(cr, 0, 0, 0, 1);
        cairo_show_text(cr, char_to_string('1' + i));
        cairo_set_source_rgba(cr, 0, 0, 0, 0);
        for (int j = 0; j < 8; j++) {
            cairo_select_font_face(cr, "Calibri", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
            cairo_set_font_size(cr, 24);
            cairo_move_to(cr, 20, 105 + j * 70);
            cairo_set_source_rgba(cr, 0, 0, 0, 1);
            cairo_show_text(cr, char_to_string('A' + j));
            int stroke = 0;
            switch (board_get_cell(gui_last_game->board, i, j)) {
            case CELL_BLACK:
                cairo_set_source_rgb(cr, 0.1, 0.1, 0.1);
                break;
            case CELL_WHITE:
                cairo_set_source_rgb(cr, 1.0, 1.0, 1.0);
                stroke = 1;
                break;
            default:
                cairo_set_source_rgb(cr, 0.85, 0.85, 0.85);
                break;
            }
            cairo_arc(cr, 100.00 + 70 * j, 100.00 + 70 * i, 25.00, 0, 2 * G_PI);
            cairo_fill(cr);
            if (stroke) {
                cairo_set_line_width(cr, 2.0);
                cairo_set_source_rgb(cr, 0, 0, 0);
                cairo_arc(cr, 100.00 + 70 * j, 100.00 + 70 * i, 26.00, 0, 2 * G_PI);
                cairo_stroke(cr);
            }
            cairo_set_source_rgba(cr, 0, 0, 0, 0);
            cairo_set_line_width(cr, 0);
        }
    }

    // On actualise aussi les labels
    gtk_label_set_text(GTK_LABEL(label_me), g_strdup_printf("Vous êtes : %s", gui_last_me == CELL_BLACK ? "Noir" : "Blanc"));
    switch (gui_last_state) {
    case STATE_PLAYING:
        gtk_label_set_text(GTK_LABEL(label_playing), g_strdup_printf("Au tour de : %s", gui_last_game->playing == CELL_BLACK ? "Noir" : "Blanc"));
        break;
    case STATE_WIN_BLACK:
        gtk_label_set_text(GTK_LABEL(label_playing), g_strdup_printf("Le gagnant est : Noir"));
        break;
    case STATE_WIN_WHITE:
        gtk_label_set_text(GTK_LABEL(label_playing), g_strdup_printf("Le gagnant est : Blanc"));
        break;
    }
    if (gui_last_game->last_move != MOVE_NONE) {
        gtk_label_set_text(GTK_LABEL(label_move), g_strdup_printf("Dernier coup : %s", move_to_string(gui_last_game->last_move)));
    }

    // Si c'est mon tour
    gtk_widget_set_sensitive(
        button,
        gui_last_game->playing == gui_last_me &&
                gui_last_game->ia_override == 0 &&
                gui_last_state == STATE_PLAYING
            ? TRUE
            : FALSE);

    // C'est updated, on dit qu'on s'arrête là (sinon ça update à l'infini)
    return FALSE;
}

void gui_init_window() {
    // Initialisation de GTK
    gtk_init(NULL, NULL);
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Abalone");
    //gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
    gtk_window_set_default_size(GTK_WINDOW(window), 630, 750);
    g_signal_connect(window, "destroy", G_CALLBACK(gui_destroy), NULL);

    container = gtk_grid_new();
    gtk_grid_set_row_homogeneous(GTK_GRID(container), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(container), TRUE);

    GtkWidget *header = gtk_grid_new();
    gtk_grid_set_row_homogeneous(GTK_GRID(header), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(header), TRUE);

    label_me = gtk_label_new("");
    label_playing = gtk_label_new("");
    label_move = gtk_label_new("");

    gtk_grid_attach(GTK_GRID(header), label_me, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(header), label_playing, 1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(header), label_move, 2, 0, 1, 1);

    GtkWidget *footer = gtk_grid_new();
    gtk_grid_set_row_homogeneous(GTK_GRID(footer), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(footer), TRUE);

    GtkWidget *label = gtk_label_new("Votre coup :");
    entry = gtk_entry_new();
    button = gtk_button_new_with_label("Jouer");

    g_signal_connect(button, "clicked", G_CALLBACK(gui_button_callback), NULL);

    // détection de touche
    g_signal_connect(entry, "key_press_event", G_CALLBACK(gui_entry_callback), NULL);

    gtk_grid_attach(GTK_GRID(footer), label, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(footer), entry, 1, 0, 2, 1);
    gtk_grid_attach(GTK_GRID(footer), button, 3, 0, 1, 1);

    event_box = gtk_event_box_new();
    g_signal_connect(G_OBJECT(event_box), "button_press_event", G_CALLBACK(gui_click_callback), NULL);

    drawing_area = gtk_drawing_area_new();
    g_signal_connect(G_OBJECT(drawing_area), "draw", G_CALLBACK(gui_update_grid), NULL);
    gtk_container_add(GTK_CONTAINER(event_box), drawing_area);

    gtk_grid_attach(GTK_GRID(container), header, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(container), event_box, 0, 1, 1, 11);
    gtk_grid_attach(GTK_GRID(container), footer, 0, 13, 1, 1);
    gtk_container_add(GTK_CONTAINER(window), container);

    gtk_widget_show_all(window);
}

// Fonctions publiques

void gui_init(Cell owner, int ia_override, void (*refresh_opponent)(Game *game, Cell me, State state), char address[ADDRESS_LENGTH], int port) {
    /*
     * Fonction d'initialisation de l'interface
     */

    // Initialisation de la partie
    Game *game = game_new(owner, ia_override);
    strcpy(game->address, address);
    game->port = port;
    game->refresh = gui_update;
    game->refresh_opponent = refresh_opponent;

    // Initialisation de GTK
    gui_init_window();

    // Démarrage
    gui_background_start(game);

    // Boucle principale (bloquante, donc ne rien mettre en dessous)
    gtk_main();
}

void gui_update(Game *game, Cell me, State state) {
    /*
     * Fonction appelée par le jeu avec les données à jour
     */

    // On enregistre les trucs (pour les passer au main thread)
    gui_last_game = game;
    gui_last_me = me;
    gui_last_state = state;

    // On laisse l'UI se mettre à jour (sur le main thread)
    GSource *source = g_idle_source_new();
    g_source_set_callback(source, gui_draw_callback, NULL, NULL);
    g_source_attach(source, g_main_context_default());
    g_source_unref(source);

    // Si y'a un dernier coup, on joue le son
    if (gui_last_game->last_move != MOVE_NONE) {
        play_sound("assets/move.wav");
    }

    // Si c'est l'IA qui joue
    if (game->playing == me && game->ia_override) {
        pthread_t thread;
        pthread_create(&thread, NULL, gui_background_turn_ia, NULL);
    }
}
