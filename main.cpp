#include <windows.h>
#include <conio.h>
#include <iostream>
#include <vector>

using namespace std;


#define HEIGHT 20
#define WIDTH 40

vector<vector<char>> game_matrix(HEIGHT, vector<char>(WIDTH, ' ')); // matrice 2D del campo di gioco
vector<vector<char>> snake_matrix(HEIGHT, vector<char>(WIDTH, ' ')); // matrice 2D del serpente

struct Position {
    int y;
    int x;
};

enum Directions{ 
    Up, 
    Down, 
    Right, 
    Left,
};


void clear(Position &head_pos) { // di default parte dal angolo in alto a sinistra
    game_matrix[head_pos.y][head_pos.x] = ' ';
    cout << "\033[" << head_pos.y+3 << ";" << head_pos.x +1 << "H"; // + 3 per le due frasi sopra
    cout << ' ';
    cout << "\033[0;0H";
}

void init_snake_matrix() {
    for (unsigned int y = 0; y < HEIGHT; ++y) {
        for (unsigned int x = 0; x < WIDTH; ++x) {
            snake_matrix[y][x] = ' ';
        }
    }
}

void reset_game() { // genera muri e svuota il campo
    for (unsigned int y = 0; y < HEIGHT; ++y) {
        for (unsigned int x = 0; x < WIDTH; ++x) {
            if (y == 0 && x == 0) { // angolo in alto a sinistra
                game_matrix[y][x] = '\xC9'; // simbolo: ╔
            } else if (y == 0 && x == WIDTH - 1) { // angolo in alto a destra
                game_matrix[y][x] = '\xBB'; // simbolo: ╗
            } else if (y == HEIGHT - 1 && x == 0) { // angolo in basso a sinistra
                game_matrix[y][x] = '\xC8'; // simbolo: ╚
            } else if (y == HEIGHT - 1 && x == WIDTH - 1) { // angolo in basso a destra
                game_matrix[y][x] = '\xBC'; // simbolo: ╝
            } else if (y == 0 || y == HEIGHT - 1) { // la prima o ultima riga
                game_matrix[y][x] = '\xCD'; // simbolo: ═
            } else if (x == 0 || x == WIDTH - 1) { // la prima o ultima colonna
                game_matrix[y][x] = '\xBA'; // simbolo: ║
            } else { // le altre celle al centro vengono svuotate
                game_matrix[y][x] = ' ';
            }
        }
    }
}

void show_game() { // mostra il campo
    cout << "PREMERE 'e' PER USCIRE" << endl;
    cout << "USARE LE FRECCIE PER MUOVERSI :)" << endl;

    for (unsigned int y = 0; y < HEIGHT; ++y) {
        for (unsigned int x = 0; x < WIDTH; ++x) {
            cout << game_matrix[y][x];
        }
        cout << endl;
    }
}

void exit_game() { // quando si perde, pulisce lo schermo e chiude
    system("cls");
    cout << "HAI PERSO!" << endl;
    for (int sec = 3; sec >= 0; --sec){
        cout << "Uscita tra " << sec << "...";
        Sleep(1000);
        cout << "\033[1G\033[2K"; // torna a inizio riga e pulisce
    }
    system("cls");
    exit(0);
}

bool touch_border(Position head_pos) { // verifica se il serpente tocca il bordo
    if (head_pos.y == 0 || head_pos.y == HEIGHT-1) {
        return 1;
    } else if (head_pos.x == 0 || head_pos.x == WIDTH-1) {
        return 1;
    } else {
        return 0;
    }
}

void move_snake(int &length, Directions direction, Position &head_pos) {
    if (direction == Up && !touch_border(head_pos)) {
        --head_pos.y;
    }
    if (direction == Down && !touch_border(head_pos)) {
        ++head_pos.y;
    }
    if (direction == Right && !touch_border(head_pos)) {
        ++head_pos.x;
    }
    if (direction == Left && !touch_border(head_pos)) {
        --head_pos.x;
    }
    if (touch_border(head_pos)) {
        exit_game();
    }
    game_matrix[head_pos.y][head_pos.x] = '#';
}

int main() {
    Position head_position = {HEIGHT/2, WIDTH/2}; // testa del serpente, inizia al centro
    Directions direction = Up; // di default parte verso alto
    int snake_length = 2; // lunghezza iniziale serpente
    int user_input; // int perche getch() restituisce valore ascii

    reset_game(); // qui usata per creare il campo di gioco
    system("cls"); // pulisce il terminale prima di iniziare il gioco

    while(1) {        
        if (_kbhit()) { // se viene premuto un tasto
            user_input = getch(); // legge valore ascii del tasto
            if (user_input == -32 || user_input == 224) { // freccette di movimento
                user_input = getch();
                switch (user_input) {
                    case 72: // sopra
                        direction = Up;
                        break;
                    case 75: // sinistra
                        direction = Left;
                        break;
                    case 77: // destra
                        direction = Right;
                        break;
                    case 80: // sotto
                        direction = Down;
                        break;
                }
            }
            if (user_input == 101) { // tasto "e" per uscire
                break;
            }
        }
        move_snake(snake_length, direction, head_position); 
        show_game();
        Sleep(300); // velocita del serpente
        clear(head_position);  
    }

    system("cls");

	return 0;
}
