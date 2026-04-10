#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <chrono>
#include <thread>

using namespace std;

// Configurações do Console NBA
const int LARGURA_TELA = 60; // Resolução horizontal
const int ALTURA_TELA = 20;  // Resolução vertical
const int MAPA_RES = 12;

void limpar() {
    cout << "\033[2J\033[1;1H";
}

void delay(int ms) {
    this_thread::sleep_for(chrono::milliseconds(ms));
}

// --- INTRO GIGANTE ESTILO GAMEBOY ---
void introNBA() {
    string logo[5] = {
        "  _   _ ___ ____ _  __  ____   ______   __ ",
        " | \\ | |_ _/ ___| |/ / | __ ) / _ \\ \\ / / ",
        " |  \\| || | |   | ' /  |  _ \\| | | \\ V /  ",
        " | |\\  || | |___| . \\  | |_) | |_| || |   ",
        " |_| \\_|___\\____|_|\\_\\ |____/ \\___/ |_|   "
    };
    for (int i = 0; i < 6; i++) {
        limpar();
        for (int s = 0; s < i; s++) cout << endl;
        for (int l = 0; l < 5; l++) cout << logo[l] << endl;
        delay(120);
    }
    cout << "\n              A  D  V  A  N  C  E            " << endl;
    cout << "         [ SYSTEM VERSION 3.0 JOGAVEL ]        " << endl;
    delay(2000);
}

// --- JOGO: ROBLOX 3D HORROR NBA EDITION ---
void jogoRoblox3D() {
    // Mapa: # é parede de tijolos do Roblox, . é espaço vazio
    string mapa = 
        "############"
        "#..........#"
        "#..#####...#"
        "#..#.......#"
        "#..#...##..#"
        "#......##..#"
        "#..#.......#"
        "#..#########"
        "#..........#"
        "#..####....#"
        "#..........#"
        "############";

    float pX = 2.0f, pY = 2.0f, pA = 0.0f; // Posição X, Y e Ângulo
    const float FOV = 3.14159f / 3.0f;     // Campo de visão ampliado
    const float DIST_MAX = 14.0f;

    while (true) {
        // Criar buffer de tela vazio
        vector<string> buffer(ALTURA_TELA, string(LARGURA_TELA, ' '));

        // Raycasting: Processa cada coluna horizontal da tela
        for (int x = 0; x < LARGURA_TELA; x++) {
            float anguloRaio = (pA - FOV / 2.0f) + ((float)x / (float)LARGURA_TELA) * FOV;
            float dParede = 0;
            bool hitParede = false;

            float olhoX = sinf(anguloRaio);
            float olhoY = cosf(anguloRaio);

            while (!hitParede && dParede < DIST_MAX) {
                dParede += 0.1f;
                int testeX = (int)(pX + olhoX * dParede);
                int testeY = (int)(pY + olhoY * dParede);

                if (testeX < 0 || testeX >= MAPA_RES || testeY < 0 || testeY >= MAPA_RES) {
                    hitParede = true;
                    dParede = DIST_MAX;
                } else if (mapa[testeY * MAPA_RES + testeX] == '#') {
                    hitParede = true;
                }
            }

            // Cálculo da altura da parede baseado na distância (Perspectiva)
            int teto = (float)(ALTURA_TELA / 2.0) - ALTURA_TELA / (float)dParede;
            int chao = ALTURA_TELA - teto;

            // Escolha do caractere baseado na distância (Shading)
            char shade = ' ';
            if (dParede <= DIST_MAX / 4.0f) shade = 'M';      // Muito perto
            else if (dParede < DIST_MAX / 3.0f) shade = 'H';  // Perto
            else if (dParede < DIST_MAX / 2.0f) shade = 'X';  // Médio
            else if (dParede < DIST_MAX)       shade = '.';  // Longe

            for (int y = 0; y < ALTURA_TELA; y++) {
                if (y < teto) buffer[y][x] = ' ';           // Céu
                else if (y >= teto && y <= chao) buffer[y][x] = shade; // Parede
                else buffer[y][x] = '_';                    // Chão
            }
        }

        // Renderização Final
        limpar();
        cout << " [ NBA ROBLOX 3D - WORLD RENDER ] " << endl;
        cout << "------------------------------------------------------------" << endl;
        for (int y = 0; y < ALTURA_TELA; y++) {
            cout << buffer[y] << endl;
        }
        cout << "------------------------------------------------------------" << endl;
        cout << " CONTROLES: [A] GIRAR ESQ | [D] GIRAR DIR | [W] ANDAR | [Q] SAIR" << endl;
        cout << " ACAO: ";

        char input;
        cin >> input;

        if (input == 'q' || input == 'Q') break;
        if (input == 'a' || input == 'A') pA -= 0.35f;
        if (input == 'd' || input == 'D') pA += 0.35f;
        if (input == 'w' || input == 'W') {
            float proxX = pX + sinf(pA) * 0.7f;
            float proxY = pY + cosf(pA) * 0.7f;
            // Detecção de colisão com as paredes do mapa
            if (mapa[(int)proxY * MAPA_RES + (int)proxX] != '#') {
                pX = proxX;
                pY = proxY;
            }
        }
    }
}

// --- MENU LAUNCHER ---
int main() {
    introNBA();
    while (true) {
        limpar();
        cout << " ############################################" << endl;
        cout << " #        NICK BOY ADVANCE - LAUNCHER       #" << endl;
        cout << " ############################################" << endl;
        cout << " #                                          #" << endl;
        cout << " #  [1] ROBLOX 3D HORROR (NBA EDITION)      #" << endl;
        cout << " #  [2] DESLIGAR CONSOLE                    #" << endl;
        cout << " #                                          #" << endl;
        cout << " ############################################" << endl;
        cout << " SELECIONE O JOGO: ";
        
        string op;
        cin >> op;

        if (op == "1") jogoRoblox3D();
        else if (op == "2") break;
    }

    limpar();
    cout << "NBA desligado. Volte logo, Nick!" << endl;
    return 0;
}