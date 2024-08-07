#include <iostream>
#include <vector>
#include <random>

using namespace std;

bool imprimeVetor(vector<char> &vetor) {
    for (char caractere : vetor) {
        cout << caractere << " ";
    }
    cout << endl;
}

int main() {
    int distanciaInicial, velocidadeS, velocidadeD;

    cout << "Informe a distancia inicial entre o Seu José e a Dona Maria: " << endl;
    cin >> distanciaInicial;

    cout << "Informe a velocidade do Seu José" << endl;
    cin >> velocidadeS;

    cout << "Informe a velocidade da Dona Maria" << endl;
    cin >> velocidadeD;

    bool fubaResgatado = false;
    int tamanhoTotal = distanciaInicial + 3;
    random_device rd;
    mt19937 gerador(rd());
    // Gerando a posição de forma que Fubá não comece já sendo encontrado na primeira linha
    uniform_int_distribution<> distribuicao(2, distanciaInicial - 2);
    int posicaoFuba = distribuicao(gerador);
    vector<char> linhaAtual(tamanhoTotal);
    linhaAtual.push_back('S');

    for (int i = 0; i < linhaAtual.size() - 3; i++) {
        if (i == posicaoFuba) {
            linhaAtual.push_back('F');
        } else {
            linhaAtual.push_back('.');
        }
    }
    linhaAtual.push_back('D');
    imprimeVetor(linhaAtual);

    while (!fubaResgatado) {
        fubaResgatado = imprimeVetor(linhaAtual);
    }

    return 0;
}