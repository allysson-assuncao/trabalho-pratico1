#include <iostream>
#include <random>

using namespace std;

int main() {
    int distanciaInicial, velocidadeS, velocidadeD;

    cout << "Informe a distancia inicial entre o Seu Jose e a Dona Maria: " << endl;
    cin >> distanciaInicial;

    cout << "Informe a velocidade do Seu Jose" << endl;
    cin >> velocidadeS;

    cout << "Informe a velocidade da Dona Maria" << endl;
    cin >> velocidadeD;

    bool fubaResgatado = false;
    int tamanhoTotal = distanciaInicial + 2;
    random_device rd;
    mt19937 gerador(rd());
    // Gerando a posição de forma que Fubá não comece já sendo encontrado na primeira linha
    uniform_int_distribution<> distribuicao(2, distanciaInicial - 2);
    /*int posicaoFuba = distribuicao(gerador);*/
    int posicaoFuba = tamanhoTotal / 2;
    int posicaoS = 0;
    int posicaoD = tamanhoTotal;

    while (!fubaResgatado) {
        uniform_int_distribution<> movimentoFuba(1, 3);
        bernoulli_distribution direcaoFuba(0.5);
        for (int i = 0; i < tamanhoTotal + 1; i++) {
            if (i == posicaoFuba) {
                /*if (posicaoFuba <= posicaoS + 1 && posicaoS + 1 < posicaoD) {
                    posicaoFuba = posicaoS + 1;
                } else if (posicaoFuba >= posicaoD + 1 && posicaoD - 1 > posicaoS) {
                    posicaoFuba = posicaoS - 1;
                }*/
                cout << "F" << " ";
            } else if ((i > posicaoS && i < posicaoFuba) || (i > posicaoFuba && i < posicaoD)) {
                cout << "." << " ";
            } else if (i == posicaoS) {
                cout << "S" << " ";
            } else if (i < posicaoS || i > posicaoD) {
                cout << "-" << " ";
            } else if (i == posicaoD) {
                cout << "D" << " ";
            }
        }
        if (posicaoFuba <= posicaoS + 1 || posicaoFuba >= posicaoD - 1) {
            fubaResgatado = true;
        }
        cout << endl;
        bool esquerda = direcaoFuba(gerador);
        if (esquerda) {
            posicaoFuba -= movimentoFuba(gerador);
        } else {
            posicaoFuba += movimentoFuba(gerador);
        }
        if (posicaoFuba <= posicaoS + velocidadeS) {
            posicaoS = posicaoFuba - posicaoS - 1;
            posicaoFuba = posicaoS + 1;
            if (posicaoD <= posicaoFuba) {
                posicaoD = posicaoFuba + 1;
            }
        } else if(posicaoFuba >= posicaoD - velocidadeD){
            posicaoD = posicaoD - posicaoFuba - 1;
            posicaoFuba = posicaoS - 1;
            if (posicaoS >= posicaoFuba) {
                posicaoS = posicaoFuba - 1;
            }
        } else {
            posicaoS += velocidadeS;
            posicaoD -= velocidadeD;
        }
    }

    return 0;
}