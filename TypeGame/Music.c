#include <stdio.h>
#include <windows.h>

// Definições das notas musicais em Hertz
#define NOTE_C 261
#define NOTE_D 294
#define NOTE_E 329
#define NOTE_F 349
#define NOTE_G 392
#define NOTE_A 440
#define NOTE_B 493
#define REST 0

// Definições das durações em milissegundos
#define WHOLE_NOTE 2000
#define HALF_NOTE 1000
#define QUARTER_NOTE 500
#define EIGHTH_NOTE 250

// Função para tocar uma nota
void play(int note, int duration) {
    if (note == REST) {
        Sleep(duration);
    } else {
        Beep(note, duration);
        Sleep(duration);
    }
}

int main() {
    // Tocando a melodia
    play(NOTE_C, QUARTER_NOTE);
    play(NOTE_D, QUARTER_NOTE);
    play(NOTE_E, QUARTER_NOTE);
    play(NOTE_F, QUARTER_NOTE);
    play(NOTE_G, QUARTER_NOTE);
    play(NOTE_A, QUARTER_NOTE);
    play(NOTE_B, QUARTER_NOTE);
    play(NOTE_C * 2, QUARTER_NOTE);
    play(NOTE_B, QUARTER_NOTE);
    play(NOTE_A, QUARTER_NOTE);
    play(NOTE_G, QUARTER_NOTE);
    play(NOTE_F, QUARTER_NOTE);
    play(NOTE_E, QUARTER_NOTE);
    play(NOTE_D, QUARTER_NOTE);
    play(NOTE_C, QUARTER_NOTE);
    play(REST, QUARTER_NOTE); // Pausa de uma colcheia

    // Repetindo a mesma melodia, mas duas vezes mais rápida
    play(NOTE_C, EIGHTH_NOTE);
    play(NOTE_D, EIGHTH_NOTE);
    play(NOTE_E, EIGHTH_NOTE);
    play(NOTE_F, EIGHTH_NOTE);
    play(NOTE_G, EIGHTH_NOTE);
    play(NOTE_A, EIGHTH_NOTE);
    play(NOTE_B, EIGHTH_NOTE);
    play(NOTE_C * 2, EIGHTH_NOTE);
    play(NOTE_B, EIGHTH_NOTE);
    play(NOTE_A, EIGHTH_NOTE);
    play(NOTE_G, EIGHTH_NOTE);
    play(NOTE_F, EIGHTH_NOTE);
    play(NOTE_E, EIGHTH_NOTE);
    play(NOTE_D, EIGHTH_NOTE);
    play(NOTE_C, EIGHTH_NOTE);
    play(REST, EIGHTH_NOTE); // Pausa de uma semicolcheia

    // Tocando a mesma melodia uma oitava mais alta
    play(NOTE_C * 2, QUARTER_NOTE);
    play(NOTE_D * 2, QUARTER_NOTE);
    play(NOTE_E * 2, QUARTER_NOTE);
    play(NOTE_F * 2, QUARTER_NOTE);
    play(NOTE_G * 2, QUARTER_NOTE);
    play(NOTE_A * 2, QUARTER_NOTE);
    play(NOTE_B * 2, QUARTER_NOTE);
    play(NOTE_C * 4, QUARTER_NOTE);
    play(NOTE_B * 2, QUARTER_NOTE);
    play(NOTE_A * 2, QUARTER_NOTE);
    play(NOTE_G * 2, QUARTER_NOTE);
    play(NOTE_F * 2, QUARTER_NOTE);
    play(NOTE_E * 2, QUARTER_NOTE);
    play(NOTE_D * 2, QUARTER_NOTE);
    play(NOTE_C * 2, QUARTER_NOTE);
    play(REST, QUARTER_NOTE); // Pausa de uma colcheia

    return 0;
}
