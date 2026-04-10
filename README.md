# Processamento de Sinais 1D

Este projeto contém implementações em C++ para diversas transformações de sinais unidimensionais, com visualização em tempo real no terminal e geração de gráficos SVG.

## 📂 Estrutura do Projeto

- **ExercicioA**: Reflexão do sinal ($y[n] = x[-n]$).
- **ExercicioB**: Mudança de escala no tempo ($y[n] = x[n/a]$).
- **ExercicioC**: Mudança de amplitude ($y[n] = A \cdot x[n]$).
- **ExercicioD**: Deslocamento temporal ($y[n] = x[n-k]$).
- **ExercicioE**: Soma de sinal com degrau ($y[n] = x[n] + A$).

## 🛠️ Requisitos

Para rodar os códigos, você precisará de:
1. **Compilador C++** (ex: `g++`)
2. **Terminal** com suporte a cores ANSI e caracteres Unicode (padrão no Linux/WSL).

## 🚀 Como Executar

Escolha a pasta do exercício desejado e siga os passos:

1. **Acesse a pasta**:
   ```bash
   cd ExercicioA  # Substitua pelo exercício desejado
   ```

2. **Compile o código**:
   ```bash
   g++ -O3 *.cpp -o programa
   ```

3. **Inicie o programa**:
   ```bash
   ./programa
   ```

Os gráficos serão plotados no terminal e arquivos `.svg` (gráficos de alta definição) serão salvos na mesma pasta.
