#include <iostream>
#include <vector>
using namespace std;

// Tamanho do tabuleiro de xadrez
#define N 8

// Função para verificar se uma posição (x, y) é válida no tabuleiro
bool isValid(int x, int y, vector<vector<int>>& sol) {
    return (x >= 0 && x < N && y >= 0 && y < N && sol[x][y] == -1);
}

// Função utilitária para imprimir a solução
void printSolution(vector<vector<int>>& sol) {
    cout << "Solução:" << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            cout << sol[i][j] << "\t";
        cout << endl;
    }
}

// Função para resolver o problema do percurso do cavalo usando backtracking
bool solveKTUtil(int x, int y, int movei, vector<vector<int>>& sol, int xMove[], int yMove[]) {
    int k, next_x, next_y;
    if (movei == N * N)
        return true;

    // Tenta todos os próximos movimentos do cavalo a partir da posição atual
    for (k = 0; k < 8; k++) {
        next_x = x + xMove[k];
        next_y = y + yMove[k];
        if (isValid(next_x, next_y, sol)) {
            sol[next_x][next_y] = movei;
            if (solveKTUtil(next_x, next_y, movei + 1, sol, xMove, yMove))
                return true;
            else
                sol[next_x][next_y] = -1; // backtrack
        }
    }
    return false;
}

// Função principal para resolver o problema do percurso do cavalo
void solveKT() {
    vector<vector<int>> sol(N, vector<int>(N, -1));

    // Possíveis movimentos do cavalo
    int xMove[] = { 2, 1, -1, -2, -2, -1, 1, 2 };
    int yMove[] = { 1, 2, 2, 1, -1, -2, -2, -1 };

    // Inicializando a posição do cavalo na solução
    sol[0][0] = 0;

    // Começando do canto superior esquerdo do tabuleiro
    if (solveKTUtil(0, 0, 1, sol, xMove, yMove)) {
        cout << "Caminho percorrido pelo cavalo:" << endl;
        // Imprime o tabuleiro com as casas numeradas de acordo com a ordem do cavalo
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++)
                cout << sol[i][j] << "\t";
            cout << endl;
        }
    }
    else {
        cout << "Não existe solução para o problema." << endl;
    }
}

int main() {
    solveKT();
    return 0;
}
