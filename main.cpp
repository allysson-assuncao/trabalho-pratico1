#include <iostream>
#include <random>

using namespace std;

int main() {
    int distanciaInicial, velocidadeS, velocidadeD;

    cout << "Informe a distancia inicial entre o Seu Jose e a Dona Maria: " << endl;
    cin >> distanciaInicial;

    cout << "Informe a velocidade do Seu Jose: " << endl;
    cin >> velocidadeS;

    cout << "Informe a velocidade da Dona Maria: " << endl;
    cin >> velocidadeD;

    //O tamanho será a distancia entre Jose e Maria + 1 para cada automovel + 1 para fuba - 1 pois comeca em 0
    int tamanhoTotal = distanciaInicial + 2;
    random_device rd;
    mt19937 gerador(rd());
    // Gerando a posição de forma que Fubá não comece já sendo encontrado na primeira linha
    uniform_int_distribution<> distribuicao(2, distanciaInicial - 2);
    /*int posicaoFuba = distribuicao(gerador);*/
    int posicaoFuba = tamanhoTotal / 2;
    int posicaoS = 0;
    int posicaoD = tamanhoTotal;

    bool joseEncontrou = true;
    bool fubaResgatado = false;
    int tempoBusca = 0;
    while (!fubaResgatado) {
        tempoBusca++;
        uniform_int_distribution<> movimentoFuba(1, 3);
        bernoulli_distribution direcaoFuba(0.5);
        for (int i = 0; i < tamanhoTotal + 1; i++) {
            if (i < posicaoS || i > posicaoD) {
                cout << "-" << " ";
            } else if (i == posicaoS) {
                cout << "S" << " ";
            } else if (i == posicaoFuba) {
                cout << "F" << " ";
            } else if ((i > posicaoS && i < posicaoFuba) || (i > posicaoFuba && i < posicaoD)) {
                cout << "." << " ";
            } else if (i == posicaoD) {
                cout << "D" << " ";
            }
        }
        //Quebra de linha
        cout << endl;
        if (posicaoFuba <= posicaoS + 1 || posicaoFuba >= posicaoD - 1) {
            fubaResgatado = true;
        }
        bool esquerda = direcaoFuba(gerador);
        if (esquerda) {
            posicaoFuba -= movimentoFuba(gerador);
        } else {
            posicaoFuba += movimentoFuba(gerador);
        }
        //Caso o movimento aleatório de Fuba ultrapasse algum dos automoveis a posicao dele é definida para logo ao lado do automovel
        if (posicaoFuba <= posicaoS) {
            posicaoFuba = posicaoS + 1;
            if (posicaoD <= posicaoFuba) {
                posicaoD = posicaoFuba + 1;
            } else {
                posicaoD -= velocidadeD;
            }
        } else if (posicaoFuba <= posicaoS + velocidadeS) {
            posicaoS = posicaoFuba - 1;
            if (posicaoD <= posicaoFuba) {
                posicaoD = posicaoFuba + 1;
            } else {
                posicaoD -= velocidadeD;
            }
        } else if (posicaoFuba >= posicaoD) {
            joseEncontrou = false;
            posicaoFuba = posicaoD - 1;
            if (posicaoS >= posicaoFuba) {
                posicaoS = posicaoFuba - 1;
            } else {
                posicaoS += velocidadeS;
            }
        } else if (posicaoFuba >= posicaoD - velocidadeS) {
            joseEncontrou = false;
            posicaoD = posicaoFuba + 1;
            if (posicaoD <= posicaoFuba) {
                posicaoD = posicaoFuba + 1;
            } else {
                posicaoD -= velocidadeD;
            }
        } else {
            posicaoS += velocidadeS;
            posicaoD -= velocidadeD;
        }
    }

    cout << "Após " << tempoBusca << " minutos de busca, " << (joseEncontrou ? "Jose " : "Maria ") << "encontrou Fuba!" << endl;

    return 0;

}