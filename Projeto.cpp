#include <iostream>
#include <limits>
#include <sstream>
#include <cstdlib>
#include <vector>
#include <locale>

const int LARGURA_GRAFICO = 50;

double calcularMedia(const std::vector<double>& potencias) {
    double soma = 0;
    for (int i = 0; i < potencias.size(); ++i) {
        soma += potencias[i];
    }
    return soma / potencias.size();
}

void gerarGrafico(const std::vector<double>& potencias) {
    double max_val = -std::numeric_limits<double>::infinity();
    double min_val = std::numeric_limits<double>::infinity();

    for (int i = 0; i < potencias.size(); ++i) {
        if (potencias[i] > max_val) max_val = potencias[i];
        if (potencias[i] < min_val) min_val = potencias[i];
    }

    std::cout << "\nGr�fico das Pot�ncias (m�x: " << max_val << " W, min: " << min_val << " W):\n\n";

    for (int i = 0; i < potencias.size(); ++i) {
        int num_chars = static_cast<int>(((potencias[i] - min_val) / (max_val - min_val)) * LARGURA_GRAFICO);
        
        std::cout << "|";
        for (int j = 0; j < num_chars; ++j) {
            std::cout << "*";
        }
        std::cout << " " << potencias[i] << " W\n";
    }
}

int main() {
    #ifdef _WIN32
        system("chcp 65001");
    #endif
    std::setlocale(LC_ALL, "Portuguese");

    const int n = 20;
    double potencias[n];
    std::vector<double> potencias_vetor;
    
    double potencia_maxima = -std::numeric_limits<double>::infinity();
    double potencia_minima = std::numeric_limits<double>::infinity();
    
    int opcao;
    std::cout << "Como deseja inserir os par�metros?\n";
    std::cout << "1 - Um por um\n";
    std::cout << "2 - Todos de uma vez separados por v�rgula\n";
    std::cin >> opcao;
    
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    if (opcao == 1) {
        std::cout << "Insira as pot�ncias uma por uma:\n";
        for (int i = 0; i < n; ++i) {
            std::cout << "Par�metro " << i + 1 << ": ";
            std::cin >> potencias[i];
            potencias_vetor.push_back(potencias[i]);
            
            if (potencias[i] > potencia_maxima) {
                potencia_maxima = potencias[i];
            }
            
            if (potencias[i] < potencia_minima) {
                potencia_minima = potencias[i];
            }
        }
    } 
    else if (opcao == 2) {
        bool entrada_valida = false;
        
        while (!entrada_valida) {
            std::string entrada;
            std::cout << "Insira as 20 pot�ncias separadas por v�rgula (Exemplo: 100,150,200,...):\n";
            std::getline(std::cin, entrada);
            
            std::stringstream ss(entrada);
            std::string valor;
            int i = 0;
            
            while (std::getline(ss, valor, ',') && i < n) {
                potencias[i] = std::atof(valor.c_str());
                potencias_vetor.push_back(potencias[i]);
                
                if (potencias[i] > potencia_maxima) {
                    potencia_maxima = potencias[i];
                }
                
                if (potencias[i] < potencia_minima) {
                    potencia_minima = potencias[i];
                }
                
                ++i;
            }
            
            if (i == n) {
                entrada_valida = true;
            } else {
                std::cerr << "Erro: n�mero incorreto de par�metros inseridos.\n";
                std::cerr << "Voc� inseriu " << i << " par�metros. Tente novamente.\n\n";
                potencias_vetor.clear();
            }
        }
    } 
    else {
        std::cerr << "Op��o inv�lida. Tente novamente.\n";
        return 1;
    }
    
    double media = calcularMedia(potencias_vetor);
    
    std::cout << "Pot�ncia m�xima registrada: " << potencia_maxima << " W\n";
    std::cout << "Pot�ncia m�nima registrada: " << potencia_minima << " W\n";
    std::cout << "M�dia das pot�ncias: " << media << " W\n";
    
    gerarGrafico(potencias_vetor);
    
    return 0;
}

