#include <iostream>
#include <vector>
#include <climits>
#include <locale>
using namespace std;

// Estrutura para representar um movimento do cavalo
struct Movimento {
    int vertical, horizontal;
};

// Função para verificar se um movimento é válido dentro do tabuleiro
bool movimentoValido(int vertical, int horizontal, vector<vector<int>>& tabuleiro, int tamanhoTabuleiro) {
    return (vertical >= 0 && horizontal >= 0 && vertical < tamanhoTabuleiro && horizontal < tamanhoTabuleiro && tabuleiro[vertical][horizontal] == -1);
}

// Função para encontrar o próximo movimento com base na heurística de Warnsdorff
int proximoMovimentoWarnsdorff(int x, int y, vector<vector<int>>& tabuleiro, int tamanhoTabuleiro) {
    static int movimentoX[] = { 2, 1, -1, -2, -2, -1, 1, 2 };
    static int movimentoY[] = { 1, 2, 2, 1, -1, -2, -2, -1 };
    int minMovimentos = INT_MAX;
    int proximoX = -1, proximoY = -1;

    for (int i = 0; i < 8; i++) {
        int newX = x + movimentoX[i];
        int newY = y + movimentoY[i];

        if (movimentoValido(newX, newY, tabuleiro, tamanhoTabuleiro)) {
            int numMovimentos = 0;
            for (int j = 0; j < 8; j++) {
                int adjX = newX + movimentoX[j];
                int adjY = newY + movimentoY[j];
                if (movimentoValido(adjX, adjY, tabuleiro, tamanhoTabuleiro)) {
                    numMovimentos++;
                }
            }
            if (numMovimentos < minMovimentos) {
                minMovimentos = numMovimentos;
                proximoX = newX;
                proximoY = newY;
            }
        }
    }

    return proximoX * tamanhoTabuleiro + proximoY;
}

// Função recursiva para encontrar o percurso do cavalo usando backtracking com heurística de Warnsdorff
bool encontrarPercursoCavaloWarnsdorff(int x, int y, int contadorMovimentos, vector<vector<int>>& tabuleiro, vector<Movimento>& movimentos, int tamanhoTabuleiro) {
    if (contadorMovimentos == tamanhoTabuleiro * tamanhoTabuleiro)
        return true;

    for (int i = 0; i < 8; i++) {
        int proximoMovimento = proximoMovimentoWarnsdorff(x, y, tabuleiro, tamanhoTabuleiro);
        int newX = proximoMovimento / tamanhoTabuleiro;
        int newY = proximoMovimento % tamanhoTabuleiro;

        if (movimentoValido(newX, newY, tabuleiro, tamanhoTabuleiro)) {
            tabuleiro[newX][newY] = contadorMovimentos;
            movimentos.push_back({ newX, newY });

            if (encontrarPercursoCavaloWarnsdorff(newX, newY, contadorMovimentos + 1, tabuleiro, movimentos, tamanhoTabuleiro))
                return true;

            tabuleiro[newX][newY] = -1;
            movimentos.pop_back();
        }
    }

    return false;
}

// Função para resolver o percurso do cavalo usando a heurística de Warnsdorff
void resolverPercursoCavaloWarnsdorff(int tamanhoTabuleiro, int inicioVertical, int inicioHorizontal) {
    vector<vector<int>> tabuleiro(tamanhoTabuleiro, vector<int>(tamanhoTabuleiro, -1)); // Inicializa o tabuleiro com -1 (não visitado)
    vector<Movimento> movimentos; // Lista de movimentos

    tabuleiro[inicioVertical][inicioHorizontal] = 0; // Marca a posição inicial como visitada
    movimentos.push_back({ inicioVertical, inicioHorizontal });

    // Tenta encontrar o percurso do cavalo
    if (encontrarPercursoCavaloWarnsdorff(inicioVertical, inicioHorizontal, 1, tabuleiro, movimentos, tamanhoTabuleiro)) {
        // Se encontrou um percurso válido, mostra o tabuleiro com a sequência de movimentos
        /*for (auto movimento : movimentos) {
            cout << "(" << movimento.vertical << ", " << movimento.horizontal << ") -> ";
        }
        cout << "Fim" << endl;*/

        // Mostra o tabuleiro com os números dos movimentos
        for (int i = 0; i < tamanhoTabuleiro; i++) {
            for (int j = 0; j < tamanhoTabuleiro; j++) {
                cout << tabuleiro[i][j] << "\t";
            }
            cout << endl;
        }
    }
    else {
        cout << "Não foi possível encontrar um percurso válido." << endl;
    }
}

int main() {
    // Define a localidade para exibir caracteres especiais corretamente
    setlocale(LC_ALL, "");

    int tamanhoTabuleiro;
    int inicioVertical, inicioHorizontal;

    // Solicita ao usuário o tamanho do tabuleiro e a posição inicial
    cout << "Digite o tamanho do tabuleiro: ";
    cin >> tamanhoTabuleiro;
    cout << "Digite a posição inicial do cavalo (linha e coluna): ";
    cin >> inicioVertical >> inicioHorizontal;

    // Executa o algoritmo para resolver o percurso do cavalo
    resolverPercursoCavaloWarnsdorff(tamanhoTabuleiro, inicioVertical, inicioHorizontal);
    return 0;
}
