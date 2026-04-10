#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <fstream>
#include <cmath>

// Estrutura para representar uma amostra do sinal (índice n e amplitude x[n])
struct Sample {
    int n;
    double val;
};

// Função para exibir um gráfico de hastes (stem plot) estilizado no terminal (Padrão Horizontal)
void plotASCII(const std::vector<Sample>& signal, const std::string& title, const std::string& colorCode) {
    if (signal.empty()) return;

    const std::string RESET = "\033[0m";
    const std::string BOLD  = "\033[1m";
    const std::string DIM   = "\033[2m";
    const std::string AXIS  = "\033[90m"; 

    // Moldura do Título
    std::cout << "  " << colorCode << BOLD << "┌";
    for(int i=0; i<50; ++i) std::cout << "─";
    std::cout << "┐" << RESET << "\n";
    std::cout << "  " << colorCode << BOLD << "│ " << std::setw(48) << std::left << title << " │" << RESET << "\n";
    std::cout << "  " << colorCode << BOLD << "└";
    for(int i=0; i<50; ++i) std::cout << "─";
    std::cout << "┘" << RESET << "\n";

    double maxAbs = 0;
    for (const auto& s : signal) {
        if (std::abs(s.val) > maxAbs) maxAbs = std::abs(s.val);
    }
    if (maxAbs < 0.0001) maxAbs = 1.0;

    const int height = 6;
    
    for (int h = height; h >= -height; --h) {
        // Eixo Y e Labels
        if (h == height)      std::cout << std::setw(8) << std::fixed << std::setprecision(2) << maxAbs << " " << AXIS << "┤" << RESET;
        else if (h == 0)      std::cout << std::setw(8) << "0.00" << " " << AXIS << "┼" << RESET;
        else if (h == -height) std::cout << std::setw(8) << std::fixed << std::setprecision(2) << -maxAbs << " " << AXIS << "┤" << RESET;
        else                  std::cout << std::setw(9) << "" << AXIS << "│" << RESET;

        for (const auto& s : signal) {
            bool isPoint = false;
            bool isStem = false;
            
            double valNorm = (s.val * (double)height) / maxAbs;
            int roundedVal = (int)std::round(valNorm);

            if (h > 0 && s.val > 0) {
                if (h <= roundedVal) {
                    isStem = true;
                    if (h == roundedVal) isPoint = true;
                }
            } else if (h < 0 && s.val < 0) {
                if (h >= roundedVal) {
                    isStem = true;
                    if (h == roundedVal) isPoint = true;
                }
            } else if (h == 0) {
                if (std::abs(s.val) < 0.0001) isPoint = true;
            }

            if (isPoint)      std::cout << colorCode << " ● " << RESET;
            else if (isStem)  std::cout << colorCode << " │ " << RESET;
            else if (h == 0)  std::cout << AXIS << "───" << RESET;
            else              std::cout << DIM << " . " << RESET;
        }
        std::cout << "\n";
    }

    std::cout << std::setw(10) << "";
    for (const auto& s : signal) {
        if (s.n >= 0 && s.n < 10) std::cout << " " << s.n << " ";
        else if (s.n < 0 && s.n > -10) std::cout << s.n << " ";
        else if (s.n >= 10 && s.n < 100) std::cout << " " << s.n;
        else std::cout << std::setw(3) << s.n;
    }
    std::cout << DIM << "   (n)\n\n" << RESET;
}

// Função para gerar um arquivo SVG com design premium
void generateSVG(const std::vector<Sample>& signal, const std::string& filename, const std::string& title, const std::string& color) {
    std::ofstream file(filename);
    if (!file.is_open()) return;

    const int width = 800;
    const int height = 400;
    const int margin = 60;

    file << "<svg viewBox=\"0 0 " << width << " " << height << "\" xmlns=\"http://www.w3.org/2000/svg\">\n";
    file << "  <rect width=\"100%\" height=\"100%\" fill=\"#121212\" />\n";
    file << "  <line x1=\"" << margin << "\" y1=\"" << height/2 << "\" x2=\"" << width - margin << "\" y2=\"" << height/2 << "\" stroke=\"#333\" stroke-width=\"1\" />\n";

    double maxVal = 0.1, minVal = -0.1;
    int minN = signal[0].n, maxN = signal[0].n;
    for (const auto& s : signal) {
        if (s.val > maxVal) maxVal = s.val;
        if (s.val < minVal) minVal = s.val;
        if (s.n < minN) minN = s.n;
        if (s.n > maxN) maxN = s.n;
    }
    maxVal *= 1.2;
    minVal *= 1.2;

    auto mapX = [&](int n) {
        if (maxN == minN) return (double)width/2;
        double t = (double)(n - minN) / (maxN - minN);
        return margin + t * (width - 2 * margin);
    };

    auto mapY = [&](double val) {
        double range = maxVal - minVal;
        double t = (val - minVal) / range;
        return (height - margin) - t * (height - 2 * margin);
    };

    double yZero = mapY(0);

    file << "  <text x=\"" << width/2 << "\" y=\"40\" text-anchor=\"middle\" font-family=\"sans-serif\" font-size=\"24\" font-weight=\"bold\" fill=\"#fff\">" << title << "</text>\n";
    file << "  <line x1=\"" << margin << "\" y1=\"" << yZero << "\" x2=\"" << width-margin << "\" y2=\"" << yZero << "\" stroke=\"#888\" stroke-width=\"2\" />\n";

    for (const auto& s : signal) {
        double px = mapX(s.n);
        double py = mapY(s.val);
        file << "  <line x1=\"" << px << "\" y1=\"" << yZero << "\" x2=\"" << px << "\" y2=\"" << py << "\" stroke=\"" << color << "\" stroke-width=\"3\" stroke-linecap=\"round\" />\n";
        file << "  <circle cx=\"" << px << "\" cy=\"" << py << "\" r=\"6\" fill=\"" << color << "\" />\n";
        file << "  <text x=\"" << px << "\" y=\"" << (yZero > py ? yZero + 25 : yZero - 15) << "\" text-anchor=\"middle\" font-family=\"monospace\" font-size=\"14\" fill=\"#aaa\">" << s.n << "</text>\n";
    }

    file << "</svg>";
    file.close();
}

int main() {
    int N, k;

    std::cout << "\033[1;32m--- Deslocamento Temporal (Time Shifting) ---\033[0m\n";
    std::cout << "Informe o número de amostras (N): ";
    if (!(std::cin >> N) || N <= 0) return 1;

    std::vector<Sample> original(N);
    std::cout << "Insira as amplitudes originais:\n";
    for (int i = 0; i < N; ++i) {
        original[i].n = i;
        std::cout << "  x[" << i << "] = ";
        std::cin >> original[i].val;
    }

    std::cout << "Informe o valor do deslocamento (k): ";
    std::cout << "\n  (k > 0: Atraso/Direita, k < 0: Avanço/Esquerda)\n  k = ";
    if (!(std::cin >> k)) return 1;

    // Deslocamento: y[n] = x[n - k]
    // Isso significa que a amostra que estava em n=0 agora está em n=k
    std::vector<Sample> shifted(N);
    for (int i = 0; i < N; ++i) {
        shifted[i].n = original[i].n + k;
        shifted[i].val = original[i].val;
    }

    // Plotagens ASCII seguindo o novo padrão "horizontal"
    plotASCII(original, "Sinal Original x[n]", "\033[36m"); // Ciano
    plotASCII(shifted, "Sinal Deslocado (k=" + std::to_string(k) + ")", "\033[32m"); // Verde

    // Geração de SVGs
    generateSVG(original, "original.svg", "Sinal Original x[n]", "#00d4ff");
    generateSVG(shifted, "deslocado.svg", "Sinal Deslocado (k=" + std::to_string(k) + ")", "#00ff88");

    std::cout << "\n\033[1;32mSucesso!\033[0m Gráficos premium gerados: \033[36m'original.svg'\033[0m e \033[36m'deslocado.svg'\033[0m.\n";

    return 0;
}
