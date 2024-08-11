#include <iostream>
#include <random>

using namespace std;

int main() {
    // Variaveis para a distancia entre Seu Jose e Dona Maria e suas respectivas velocidades
    int distanciaInicial, velocidadeS, velocidadeD;

    // Entrada de dados
    cout << "Informe a distancia inicial entre o Seu Jose e a Dona Maria: " << endl;
    cin >> distanciaInicial;

    cout << "Informe a velocidade do Seu Jose: " << endl;
    cin >> velocidadeS;

    cout << "Informe a velocidade da Dona Maria: " << endl;
    cin >> velocidadeD;

    // O tamanho do percurso sera a distancia entre Jose e Maria, + 1 para cada automovel, + 1 para fuba - 1 pois comeca em 0
    int tamanhoTotal = distanciaInicial + 2;

    // Processo de geracao de numeros aleatorios em c++
    random_device rd;
    mt19937 gerador(rd());

    // Gerando a posicao de forma que Fuba não comece ja sendo encontrado na primeira linha
    uniform_int_distribution<> distribuicao(2, distanciaInicial - 2);

    // Iniciando a posicao de Fuba de forma aleatoria (mais realista, dificulta os testes e a simulacao, mas funciona)
    int posicaoFuba = distribuicao(gerador);

    // Iniciando a posicao de Fuba como o meio do  percurso, para facilitar os testes e nao encontra-lo muito rapido
    // Deixei essa forma como oficial, sobrescrevendo a anterior, mas basta comentar essa para manter a geracao aleatoria
    posicaoFuba = tamanhoTotal / 2;
    int posicaoS = 0;
    int posicaoD = tamanhoTotal;

    // Variavel que determina quem encontrou Fuba primeiro: Jose -> tue     Maria -> false
    bool joseEncontrou = true;

    // Variavel que determina se Fuba já foi resgatado
    bool fubaResgatado = false;

    // Tempo de busca em segundos (jaa que a velocidade de fuba é de 3km/s, cada caractere é um km)
    int tempoBusca = 0;

    // Quebra de linha
    cout << endl;

    // A busa segue entuanto Fuba nao for resgatado
    while (!fubaResgatado) {
        // Incrementando o tempo de busca
        tempoBusca++;

        // Movimentacao aleatoria de Fuba, entre 0 e 3 km por segundo, para a esquerda (-) ou para direita (+)
        uniform_int_distribution<> movimentoFuba(-3, 3);

        // Imprimindo o estado atual do percurso
        for (int i = 0; i < tamanhoTotal + 1; i++) {
            // Percurso que precede Jose ou sucede Maria é preenchido com "-"
            if (i < posicaoS || i > posicaoD) {
                cout << "-" << " ";
            } else if (i == posicaoS) { // A posicao de Jose é representada com "S"
                cout << "S" << " ";
            } else if (i == posicaoFuba) { // A posicao de Fuba é representada com "F"
                cout << "F" << " ";
            } else if ((i > posicaoS && i < posicaoFuba) || (i > posicaoFuba && i < posicaoD)) {
                // Percurso ainda nao percorrido é preenchido com "."
                cout << "." << " ";
            } else if (i == posicaoD) { // A posicao de Maria é representada com "D"
                cout << "D" << " ";
            }
        }
        // Quebra de linha
        cout << endl;

        // Verificando se Fuba foi encontrado antes de atualizar as posicoes
        // De forma que a linha onde o encontro acontece sempre sera monstrada
        if (posicaoFuba <= posicaoS + 1 || posicaoFuba >= posicaoD - 1) {
            fubaResgatado = true;
        }

        // Atualizando a posicao de Fuba
        posicaoFuba += movimentoFuba(gerador);

        // Caso o movimento aleatório de Fuba ultrapasse algum dos automoveis a posicao dele é definida para logo ao lado do automovel
        // E caso o movimento dos automoveis passe a posicao de Fuba, o automovel para ao lado de Fuba
        // Essas verificacoes ocorrem para simular uma situacao real e evitar resultados inesperados
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
            // Define que Maria encontrou Fuba e nao Jose
            joseEncontrou = false;
            posicaoFuba = posicaoD - 1;
            if (posicaoS >= posicaoFuba) {
                posicaoS = posicaoFuba - 1;
            } else {
                posicaoS += velocidadeS;
            }
        } else if (posicaoFuba >= posicaoD - velocidadeS) {
            // Define que Maria encontrou Fuba e nao Jose
            joseEncontrou = false;
            posicaoD = posicaoFuba + 1;
            if (posicaoD <= posicaoFuba) {
                posicaoD = posicaoFuba + 1;
            } else {
                posicaoD -= velocidadeD;
            }
        } else { // Caso basico, apenas atualiza a posicao de Jose e Maria
            posicaoS += velocidadeS;
            posicaoD -= velocidadeD;
        }
    }

    //Saida com o tempo de busca em segundos e o nome de quem encontrou Fuba
    cout << endl << "Após " << tempoBusca << " segundos de busca, " << (joseEncontrou ? "Jose " : "Maria ") << "encontrou Fuba!" << endl;

    return 0;

}