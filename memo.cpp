#include <iostream>
#include <vector>
#include <chrono>  // Para medir o tempo de execução

using namespace std;
using namespace std::chrono;

// Estrutura para armazenar o valor e o peso
struct Resultado {
    int valor;
    int peso;
};

// Função recursiva para calcular o valor máximo e o peso total que pode ser obtido com memoização
Resultado knapsack(int W, vector<int>& weights, vector<int>& values, int n, vector<vector<Resultado>>& memo) {
    // Caso base: sem mais itens ou sem capacidade
    if (n == 0 || W == 0)
        return {0, 0};

    // Se já tivermos resolvido esse subproblema, retornamos o resultado memoizado
    if (memo[n][W].valor != -1)
        return memo[n][W];

    // Se o peso do n-ésimo item for maior que a capacidade atual da mochila, não podemos incluí-lo
    if (weights[n-1] > W)
        return memo[n][W] = knapsack(W, weights, values, n-1, memo);

    // Caso contrário, decidimos entre incluir ou não incluir o item
    // 1. Incluir o item
    Resultado incluir = knapsack(W - weights[n-1], weights, values, n-1, memo);
    incluir.valor += values[n-1];
    incluir.peso += weights[n-1];

    // 2. Não incluir o item
    Resultado nao_incluir = knapsack(W, weights, values, n-1, memo);

    // Retornamos o resultado com o maior valor e armazenamos na tabela de memoização
    if (incluir.valor > nao_incluir.valor) {
        return memo[n][W] = incluir;
    } else {
        return memo[n][W] = nao_incluir;
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

    // Inicializando a tabela de memoização com -1 para indicar que ainda não calculamos esses subproblemas
    vector<vector<Resultado>> memo(N + 1, vector<Resultado>(W + 1, {-1, 0}));

    // Capturar o tempo de início
    auto inicio = high_resolution_clock::now();

    // Executa a função de mochila com memoização
    Resultado res = knapsack(W, weights, values, N, memo);

    // Capturar o tempo de fim
    auto fim = high_resolution_clock::now();

    // Calcular o tempo de execução em milissegundos
    auto duracao = duration_cast<milliseconds>(fim - inicio).count();

    // Imprimir o peso ocupado, valor máximo e tempo de execução
    cout << "Peso ocupado: " << res.peso << " Kg, Valor alcançado: " << res.valor << " dinheiros" << endl;
    cout << "Tempo de execução: " << duracao << " ms" << endl;

    return 0;
}
