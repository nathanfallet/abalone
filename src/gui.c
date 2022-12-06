#include <gtk/gtk.h>
#include <pthread.h>
#include <unistd.h>
#include "gui.h"

// Stockage de trucs

GtkWidget *window;
GtkWidget *container;
GtkWidget *grid;
GtkWidget *label_me;
GtkWidget *label_playing;
GtkWidget *label_move;
GtkWidget *entry;
GtkWidget *button;

PGame last_game;
Cell last_me;
State last_state;
Move last_move;

// Couleurs

const static GdkRGBA color_background = {.red = 0.17, .green = 0.48, .blue = 0.0, .alpha = 1.0};
const static GdkRGBA color_background_alt = {.red = 0.12, .green = 0.43, .blue = 0.0, .alpha = 1.0};
const static GdkRGBA color_black = {.red = 0.0, .green = 0.0, .blue = 0.0, .alpha = 1.0};
const static GdkRGBA color_white = {.red = 1.0, .green = 1.0, .blue = 1.0, .alpha = 1.0};

// Fonctions internes

void gui_background_start(PGame game) {
    /*
    * Initialisation du background thread
    * Pour que le jeu se fasse en background et ne bloque pas l'interface
    */

    pthread_t thread;
    pthread_create(&thread, NULL, game_start, game);
}

void gui_background_turn() {
    game_turn(last_game, last_move);
}

void gui_button_callback() {
    /*
    * Fonction appelée sur le background thread
    * après avoir mi à jour le jeu (et lu le move si besoin)
    */

    gtk_widget_set_sensitive(button, FALSE);
    last_move = move_from_string(g_strdup(gtk_entry_get_text(GTK_ENTRY(entry))));
    gtk_entry_set_text(GTK_ENTRY(entry), "");

    pthread_t thread;
    pthread_create(&thread, NULL, gui_background_turn, NULL);
}

static void gui_destroy(GtkWidget *widget, gpointer data){
    gtk_main_quit();
}

void gui_init_window() {
    // Initialisation de GTK
    gtk_init(NULL, NULL);
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Abalone");
    gtk_window_set_default_size(GTK_WINDOW(window), 500, 500);
    g_signal_connect(window, "destroy", G_CALLBACK (gui_destroy), NULL);
    
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

    gtk_grid_attach(GTK_GRID(footer), label, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(footer), entry, 1, 0, 2, 1);
    gtk_grid_attach(GTK_GRID(footer), button, 3, 0, 1, 1);

    gtk_grid_attach(GTK_GRID(container), header, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(container), footer, 0, 11, 1, 1);
    gtk_container_add(GTK_CONTAINER(window), container);
}

gboolean gui_update_grid() {
    /*
    * Mise à jour de la grille dans l'interface graphique
    */

    // On enlève la grille précédente
    if (grid != NULL) {
        gtk_container_remove(GTK_CONTAINER(container), grid);
    }

    // Création de la grille
    grid = gtk_grid_new();
    gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);

    for (int i = 0; i <= ROWS+1; i++) {
        for (int j = 0; j <= COLS+1; j++) {
            GtkWidget *label = gtk_label_new("");

            if ((i == 0 || i == COLS+1) && j != 0 && j != ROWS+1) {
                // Top row - numbers
                gtk_label_set_text(GTK_LABEL(label), g_strdup_printf("%c", '1' + j - 1));
            } else if ((j == 0 || j == ROWS+1) && i != 0 && i != COLS+1) {
                // Left column - letters
                gtk_label_set_text(GTK_LABEL(label), g_strdup_printf("%c", 'A' + i - 1));
            } else if (i != 0 && i != COLS+1 && j != 0 && j != ROWS+1) {
                // Board
                gtk_widget_override_background_color(
                    label, GTK_STATE_FLAG_NORMAL,
                    i % 2 == j % 2 ? &color_background : &color_background_alt
                );
                switch (last_game->board[i-1][j-1]) {
                    case Black:
                        gtk_label_set_text(GTK_LABEL(label), g_strdup_printf("⬤"));
                        gtk_widget_override_color(label, GTK_STATE_FLAG_NORMAL, &color_black);
                        break;
                    case White:
                        gtk_label_set_text(GTK_LABEL(label), g_strdup_printf("⬤"));
                        gtk_widget_override_color(label, GTK_STATE_FLAG_NORMAL, &color_white);
                        break;
                    default:
                        break;
                }
            }

            gtk_label_set_xalign(GTK_LABEL(label), 0.5);
            gtk_label_set_yalign(GTK_LABEL(label), 0.5);
            gtk_grid_attach(GTK_GRID(grid), label, j, i, 1, 1);
        }
    }

    // On l'ajoute et on rafrachit
    gtk_grid_attach(GTK_GRID(container), grid, 0, 1, 1, 9);
    gtk_widget_show_all(window);

    // On actualise aussi les labels
    gtk_label_set_text(GTK_LABEL(label_me), g_strdup_printf("Vous êtes : %s", last_me == Black ? "Noir" : "Blanc"));
    gtk_label_set_text(GTK_LABEL(label_playing), g_strdup_printf("Au tour de : %s", last_game->playing == Black ? "Noir" : "Blanc"));
    gtk_label_set_text(GTK_LABEL(label_move), g_strdup_printf("Dernier coup : %s", move_to_string(last_game->last_move)));

    // Si c'est mon tour
    gtk_widget_set_sensitive(button, last_game->playing == last_me ? TRUE : FALSE);

    // C'est updated, on dit qu'on s'arrête là (sinon ça update à l'infini)
    return FALSE;
}

// Fonctions publiques

void gui_init(Cell owner, void (*actualiser_adversaire)(PGame game, Cell me, State state)) {
    /*
    * Fonction d'initialisation de l'interface
    */

    // Initialisation de la partie
    PGame game = new_game(owner);
    game->actualiser = gui_update;
    game->actualiser_adversaire = actualiser_adversaire;

    // Initialisation de GTK
    gui_init_window();

    // Démarrage
    gui_background_start(game);

    // Boucle principale (bloquante, donc ne rien mettre en dessous)
    gtk_main();
}

void gui_update(PGame game, Cell me, State state) {
    /*
    * Fonction appelée par le jeu avec les données à jour
    */

    // On enregistre les trucs (pour les passer au main thread)
    last_game = game;
    last_me = me;
    last_state = state;

    // On laisse l'UI se mettre à jour (sur le main thread)
    GSource *source = g_idle_source_new();
    g_source_set_callback(source, gui_update_grid, NULL, NULL);
    g_source_attach(source, g_main_context_default());
    g_source_unref(source);
}
