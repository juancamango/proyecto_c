#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <string.h>

/*
Proyecto1 de C
Juan Carlos Gomez Montero C13201
Jefri Barrios Pernudez C21078
Daylan Pereira Arroyo C05858
Compilar con  gcc -o exe proyecto1.c `pkg-config --cflags --libs gtk+-3.0` -rdynamic
Cjecutar con ./exe

Este programa lo que hace es el juego tik tak toe o tambien llamado gato, y posee una
interfaz hecha en el programa glade*/ 

// Inicializa las variables del programa
GtkWidget *window;
GtkLabel *label;
GtkButton *b_salir;

GtkButton *boton00;
GtkButton *boton01;
GtkButton *boton02;
GtkButton *boton10;
GtkButton *boton11;
GtkButton *boton12;
GtkButton *boton20;
GtkButton *boton21;
GtkButton *boton22;

GtkBuilder *builder;

int turno = 0;// Contador de turnos
char matriz_gato [3][3] = {{' ',' ',' '},{' ',' ',' '},{' ',' ',' '}};// Matriz que contiene la plantilla del juego.
bool juego_termino = false;// Booleano para saber si alguien ha ganado.

bool jugador_gano(char simbolo){
    // Este metodo se usa para saber si un jugador gano la partida.
    // Gano por filas.
    /* Como el booleano "juego_termino" es falso este metodo retorna un verdadero, al retornar el true sirve para
    que el programa termine, debido a que este sigue conrriedo hasta que alguien gane.*/
    if (matriz_gato[0][0]==simbolo && matriz_gato[0][1]==simbolo && matriz_gato[0][2]==simbolo){
        return true;
    }
    if (matriz_gato[1][0]==simbolo && matriz_gato[1][1]==simbolo && matriz_gato[1][2]==simbolo){
        return true;
    }
    if (matriz_gato[2][0]==simbolo && matriz_gato[2][1]==simbolo && matriz_gato[2][2]==simbolo){
        return true;
    }

    // Gano por diagonal.
    if (matriz_gato[0][0]==simbolo && matriz_gato[1][1]==simbolo && matriz_gato[2][2]==simbolo){
        return true;
    }
    if (matriz_gato[2][0]==simbolo && matriz_gato[1][1]==simbolo && matriz_gato[0][2]==simbolo){
        return true;
    }

    // Gano por columna.
    if (matriz_gato[0][0]==simbolo && matriz_gato[1][0]==simbolo && matriz_gato[2][0]==simbolo){
        return true;
    }
    if (matriz_gato[0][1]==simbolo && matriz_gato[1][1]==simbolo && matriz_gato[2][1]==simbolo){
        return true;
    }
    if (matriz_gato[0][2]==simbolo && matriz_gato[1][2]==simbolo && matriz_gato[2][2]==simbolo){
        return true;
    }
    return false;
}

void jugada(GtkWidget *widget, int fila, int columna){
    gchar *display;
    // Contruye el juego, cambia el contenido de cada botón con una "X" o un "O".
    // Los turnos pares juega la "X" y los turnos impares va la "O".
    // También llama la función jugador_gano para detectar si un jugador ganó y acabar el juego.
    if(!juego_termino){
        GtkButton *boton = (GtkButton *) widget;
        char simbolo = ' ';
        if(turno%2==0){
            simbolo = 'X';
        } else {
            simbolo = 'O';
        }
        if (matriz_gato[fila][columna] == ' '){
            turno = turno + 1;
            matriz_gato[fila][columna] = simbolo;
            char str[3] = "   ";
            str[1] = simbolo;
            gtk_button_set_label(boton, str);
            juego_termino = jugador_gano(simbolo);
            if(juego_termino){
                display = g_strdup_printf("El jugador ganador es: %c.", simbolo);
                gtk_label_set_text(GTK_LABEL(label), display);
                // g_free(display);
            }
            else {
                if (turno == 9){
                    juego_termino = true;
                    display = g_strdup_printf("Empate.");
                }
                else if (simbolo == 'X'){
                    display = g_strdup_printf("Turno del jugador 'O'.");
                } else {
                    display = g_strdup_printf("Turno del jugador 'X'.");
                }
                gtk_label_set_text(GTK_LABEL(label), display);
            }
        } else {
            display = g_strdup_printf("Posision previamente seleccionada, seleccione otra.");
            gtk_label_set_text(GTK_LABEL(label), display);
        }
    }
}
// Las proximas 9 funciones llama al botón cuando se les da click.
void on_boton00_clicked(GtkWidget *widget, gpointer data){
    jugada(widget,0,0);
}

void on_boton01_clicked(GtkWidget *widget, gpointer data){
    jugada(widget,0,1);
}

void on_boton02_clicked(GtkWidget *widget, gpointer data){
    jugada(widget,0,2);
}

void on_boton10_clicked(GtkWidget *widget, gpointer data){
    jugada(widget,1,0);
}

void on_boton11_clicked(GtkWidget *widget, gpointer data){
    jugada(widget,1,1);
}

void on_boton12_clicked(GtkWidget *widget, gpointer data){
    jugada(widget,1,2);
}

void on_boton20_clicked(GtkWidget *widget, gpointer data){
    jugada(widget,2,0);
}

void on_boton21_clicked(GtkWidget *widget, gpointer data){
    jugada(widget,2,1);
}

void on_boton22_clicked(GtkWidget *widget, gpointer data){
    jugada(widget,2,2);
}
void salir(GtkWidget *widget, gpointer data){
    gtk_main_quit();
}

void construyendo_interfaz(){
    // Llama al archivo de .glade que cuenta con la plantilla del juego.
    // Crea los botones del juego y los llama.
    // A parte, conecta las señales con los handlers.
    builder = gtk_builder_new();
    gtk_builder_add_from_file(builder, "gato.glade", NULL); //"gato_interfaz.glade",
    window = GTK_WIDGET(gtk_builder_get_object(builder, "Window"));
    char str[3] = "   ";
    b_salir = GTK_BUTTON(gtk_builder_get_object(builder, "salir"));
    g_signal_connect(b_salir, "clicked", G_CALLBACK(salir), NULL);
    g_signal_connect(window, "destroy", G_CALLBACK(salir), NULL);

    boton00 = GTK_BUTTON(gtk_builder_get_object(builder, "boton00"));
    gtk_button_set_label(boton00, str);
    boton01 = GTK_BUTTON(gtk_builder_get_object(builder, "boton01"));
    gtk_button_set_label(boton01, str);
    boton02 = GTK_BUTTON(gtk_builder_get_object(builder, "boton02"));
    gtk_button_set_label(boton02, str);

    boton10 = GTK_BUTTON(gtk_builder_get_object(builder, "boton10"));
    gtk_button_set_label(boton10, str);
    boton11 = GTK_BUTTON(gtk_builder_get_object(builder, "boton11"));
    gtk_button_set_label(boton11, str);
    boton12 = GTK_BUTTON(gtk_builder_get_object(builder, "boton12"));
    gtk_button_set_label(boton12, str);

    boton20 = GTK_BUTTON(gtk_builder_get_object(builder, "boton20"));
    gtk_button_set_label(boton20, str);
    boton21 = GTK_BUTTON(gtk_builder_get_object(builder, "boton21"));
    gtk_button_set_label(boton21, str);
    boton22 = GTK_BUTTON(gtk_builder_get_object(builder, "boton22"));
    label = GTK_LABEL(gtk_builder_get_object(builder, "label"));
    gchar *display;
    display = g_strdup_printf("Turno del jugador 'X'.");
    gtk_label_set_text(GTK_LABEL(label), display);
    gtk_button_set_label(boton22, str);
    gtk_builder_connect_signals(builder, NULL);
    gtk_widget_show(window);
    gtk_main();
}
int main (int argc, char *argv[]){
    // Funcion principal llama a las funciones anteriores para juntar el programa y
    // Hacer que el código pueda complilar y correr.
    gtk_init (&argc, &argv);
    construyendo_interfaz();
    
    return 0;
}

