# Árvore AVL em C++

Este projeto é uma implementação em C++ de uma **Árvore Binária de Busca Auto-Balanceável (AVL)**.

A Árvore AVL é uma estrutura de dados fundamental que garante um tempo de busca, inserção e remoção de elementos de complexidade **O(log n)**, evitando o pior caso de uma árvore binária de busca simples (que seria O(n)).

## Conceitos Demonstrados

*   **Estruturas de Dados Avançadas:** Implementação completa da lógica de uma Árvore AVL.
*   **Programação Orientada a Objetos (POO):** Uso de classes, herança (`MinhaArvoreAVL` herda de `ArvoreBinariaDeBusca`), e templates (`template <typename T>`) para criar uma estrutura genérica.
*   **Algoritmos de Balanceamento:** Implementação das quatro operações de rotação necessárias para manter a propriedade AVL:
    *   **Rotação Simples à Direita**
    *   **Rotação Simples à Esquerda**
    *   **Rotação Dupla Esquerda-Direita**
    *   **Rotação Dupla Direita-Esquerda**
*   **Recursão:** Uso extensivo de funções recursivas para operações como inserção, remoção, contagem de nós e travessias (em-ordem, pré-ordem, pós-ordem).
*   **Gerenciamento de Memória:** Uso de `new` e `delete` para alocação e desalocação dinâmica de nós.

## Estrutura do Projeto

*   `MinhaArvoreAVL.h`: Contém a implementação da classe `MinhaArvoreAVL` com toda a lógica de balanceamento e operações.
*   `ArvoreBinariaDeBusca.h`: Arquivo de cabeçalho base (provavelmente fornecido pelo professor) que define a interface da Árvore Binária de Busca.
*   `MinhaListaEncadeada.h`, `ListaEncadeadaAbstrata.h`, `Elemento.h`, `excecoes.h`: Arquivos auxiliares para a implementação das travessias (que retornam uma lista encadeada).

## Como Compilar e Executar

Este projeto é um conjunto de arquivos de cabeçalho e implementação. Para compilar, é necessário um arquivo `main.cpp` (presente no diretório) que instancie e teste a classe `MinhaArvoreAVL`.

1.  Certifique-se de ter um compilador C++ (como g++) instalado.
2.  Compile o projeto:
    ```bash
    g++ -std=c++17 main.cpp -o avl_test
    ```
3.  Execute o teste:
    ```bash
    ./avl_test
    ```

---
**Linguagem:** C++
**Tópicos:** Árvore AVL, Estruturas de Dados, Algoritmos de Balanceamento, POO, Recursão.
'''
