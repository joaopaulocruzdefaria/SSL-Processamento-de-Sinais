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

---

## 📈 Discussão de Resultados

Esta seção apresenta a análise técnica das transformações aplicadas aos sinais em cada exercício.

### Exercício A: Reflexão Temporal
**Operação**: $y[n] = x[-n]$  
A reflexão (ou inversão) no tempo "espelha" o sinal em relação ao eixo das ordenadas ($n=0$). Tecnicamente, a amostra que estava na posição $n$ é movida para a posição $-n$.  
*   **Resultado**: Se o sinal original estava definido para $n \ge 0$, o sinal refletido estará definido para $n \le 0$. Visualmente, isso cria uma inversão horizontal completa da "forma" do sinal.

### Exercício B: Mudança de Escala no Tempo
**Operação**: $y[n] = x[n/a]$  
Dependendo do fator $a$, temos dois efeitos distintos:
*   **Expansão ($a > 1$)**: O sinal é "esticado". Como estamos em tempo discreto, isso resulta na inserção de zeros (ou interpolação) entre as amostras originais.
*   **Compressão ($a < 1$)**: O sinal é "encolhido" (decimação). Amostras são removidas para que o sinal ocupe um intervalo de tempo menor.
*   **Controle de Domínio**: O código ajusta o tamanho do novo sinal para garantir que toda a informação escalonada seja capturada.

### Exercício C: Alteração de Amplitude
**Operação**: $y[n] = A \cdot x[n]$  
Esta é uma transformação linear que altera a "força" ou "ganho" do sinal sem modificar seu comportamento no tempo.
*   **Amplificação ($A > 1$)**: Aumenta a magnitude de todas as amostras.
*   **Atenuação ($0 < A < 1$)**: Diminui a magnitude, "achatando" o sinal.
*   **Inversão**: Caso $A$ seja negativo, o sinal é invertido verticalmente (reflexão no eixo das abcissas).

### Exercício D: Deslocamento Temporal (Shifting)
**Operação**: $y[n] = x[n - k]$  
O deslocamento move o sinal integralmente ao longo do eixo do tempo.
*   **Atraso ($k > 0$)**: O sinal desloca-se para a **direita**. O que acontecia em $n=0$ agora acontece em $n=k$.
*   **Avanço ($k < -0$)**: O sinal desloca-se para a **esquerda**.
*   **Observação**: Diferente de uma janela fixa, nossa implementação ajusta os índices $n$ para que o sinal nunca "saia da tela", permitindo observar o deslocamento total.

### Exercício E: Soma de Sinal com Degrau
**Operação**: $y[n] = x[n] + A$ (para todo $n$)  
Funciona como a adição de um **nível DC** (offset) ao sinal. 
*   **Efeito**: O sinal inteiro é transladado verticalmente. Se adicionarmos um degrau de amplitude 5, um pico que estava em 2 subirá para 7.
*   **Análise**: Esta operação é fundamental para entender a superposição de sinais e a remoção ou adição de componentes de corrente contínua (DC) em circuitos de processamento.
