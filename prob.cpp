#include <iostream>
#include <vector>
#include <random>  // Para geração de números aleatórios
#include <chrono>  // Para medir o tempo de execução
#include <fstream> // Para manipulação de arquivos

using namespace std;
using namespace std::chrono;

// Estrutura para armazenar o valor e o peso
struct Item {
    int peso;
    int valor;
};

// Função para preencher a mochila com seleção baseada em probabilidade
pair<int, int> preencherMochilaProbabilidade(int W, vector<Item>& itens, double limiar) {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dist(0.0, 1.0);  // Gera números aleatórios entre 0 e 1

    int pesoOcupado = 0;
    int valorTotal = 0;

    // Percorrer os itens na ordem e decidir com base em probabilidade
    for (const auto& item : itens) {
        double probabilidade = dist(gen);  // Gera um número aleatório entre 0 e 1
        if (probabilidade > limiar) {  // Se a probabilidade for maior que o limiar
            if (pesoOcupado + item.peso <= W) {
                pesoOcupado += item.peso;
                valorTotal += item.valor;
            }
        }
    }

    // Retornar o peso ocupado e o valor alcançado
    return {pesoOcupado, valorTotal};
}

// Função para gravar o resultado em um arquivo
void salvarResultadoEmArquivo(const string& nomeArquivo, int peso, int valor) {
    ofstream arquivo(nomeArquivo, ios::app); // Abre o arquivo no modo de adicionar (append)
    if (arquivo.is_open()) {
        arquivo << peso << " " << valor << "\n"; // Adiciona o peso e valor ao final do arquivo
        arquivo.close();
    } else {
        cerr << "Erro ao abrir o arquivo!" << endl;
    }
}

int main() {
    int N, W;
    cin >> N >> W;

    vector<Item> itens(N);

    for (int i = 0; i < N; i++) {
        cin >> itens[i].peso >> itens[i].valor;
    }

    double limiar = 0.5;  // Definir o limiar de probabilidade

    // Capturar o tempo de início para o preenchimento aleatório baseado em probabilidade
    auto inicioProbabilidade = high_resolution_clock::now();

    // Executa a função de preenchimento aleatório baseado em probabilidade
    auto resProbabilidade = preencherMochilaProbabilidade(W, itens, limiar);

    // Capturar o tempo de fim para o preenchimento aleatório baseado em probabilidade
    auto fimProbabilidade = high_resolution_clock::now();

    // Calcular o tempo de execução do preenchimento aleatório em milissegundos
    auto duracaoProbabilidade = duration_cast<milliseconds>(fimProbabilidade - inicioProbabilidade).count();

    // Imprimir os resultados do preenchimento aleatório baseado em probabilidade
    cout << "Preenchimento baseado em probabilidade:\n";
    cout << "Peso ocupado: " << resProbabilidade.first << " Kg, Valor alcançado: " << resProbabilidade.second << " dinheiros\n";
    cout << "Tempo de execução: " << duracaoProbabilidade << " ms\n";

    // Salvar o resultado no arquivo "resultados.txt"
    salvarResultadoEmArquivo("resultadosProb.txt", resProbabilidade.first, resProbabilidade.second);

    return 0;
}
