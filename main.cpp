#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>  // Para medir o tempo de execução

using namespace std;
using namespace std::chrono;

// Estrutura para armazenar o valor e o peso
struct Resultado {
    int valor;
    int peso;
};

// Função recursiva para calcular o valor máximo e o peso total que pode ser obtido
Resultado knapsack(int W, vector<int>& weights, vector<int>& values, int n) {
    // Caso base: sem mais itens ou sem capacidade
    if (n == 0 || W == 0)
        return {0, 0};

    // Se o peso do n-ésimo item for maior que a capacidade atual da mochila, não podemos incluí-lo
    if (weights[n-1] > W)
        return knapsack(W, weights, values, n-1);

    // Caso contrário, decidimos entre incluir ou não incluir o item
    // 1. Incluir o item
    Resultado incluir = knapsack(W - weights[n-1], weights, values, n-1);
    incluir.valor += values[n-1];
    incluir.peso += weights[n-1];

    // 2. Não incluir o item
    Resultado nao_incluir = knapsack(W, weights, values, n-1);

    // Retornamos o resultado com o maior valor
    if (incluir.valor > nao_incluir.valor) {
        return incluir;
    } else {
        return nao_incluir;
    }
}

int main() {
    int N, W;
    cin >> N >> W;

    vector<int> weights(N);
    vector<int> values(N);

    for (int i = 0; i < N; i++) {
        cin >> weights[i] >> values[i];
    }

    // Capturar o tempo de início
    auto inicio = high_resolution_clock::now();

    // Executa a função de mochila
    Resultado res = knapsack(W, weights, values, N);

    // Capturar o tempo de fim
    auto fim = high_resolution_clock::now();

    // Calcular o tempo de execução em milissegundos
    auto duracao = duration_cast<milliseconds>(fim - inicio).count();

    // Imprimir o peso ocupado, valor máximo e tempo de execução
    cout << "Peso ocupado: " << res.peso << " Kg, Valor alcançado: " << res.valor << " dinheiros" << endl;
    cout << "Tempo de execução: " << duracao << " ms" << endl;

    return 0;
}
