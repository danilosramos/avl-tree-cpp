#ifndef MINHA_ARVORE_AVL_HPP
#define MINHA_ARVORE_AVL_HPP

#include "ArvoreBinariaDeBusca.h"

/**
 * @brief Representa uma árvore AVL.
 *
 * @tparam T O tipo de dado guardado na árvore.
 */
template <typename T>
class MinhaArvoreAVL final : public ArvoreBinariaDeBusca<T>
{
    virtual ~MinhaArvoreAVL()
    {
        // escreva o algoritmo esperado
        destrutor(this->raiz);
    };

    void destrutor(Nodo<T> *nodo)
    {
        if (nodo != nullptr)
        {
            destrutor(nodo->filhoEsquerda);
            destrutor(nodo->filhoDireita);
            delete nodo;
        }
    }

    /**
     * @brief Verifica se a arvore esta vazia
     * @return Verdade se a arvore esta vazia.
     */
    virtual bool vazia() const
    {
        if (this->raiz == nullptr)
        {
            return true;
        }
        return false;
    };

    /**
     * @brief Retornar quantidade de chaves na arvore
     * @return Numero natural que representa a quantidade de chaves na arvore
     */
    virtual int quantidade() const
    {
        // substitua a linha abaixo pelo algoritmo esperado
        if (vazia())
        {
            return 0;
        }
        else
        {
            return quantidadeRecursiva(this->raiz);
        }
    };

    int quantidadeRecursiva(Nodo<T> *nodo) const
    {
        if (nodo == nullptr)
        {
            return 0;
        }
        return 1 + quantidadeRecursiva(nodo->filhoDireita) + quantidadeRecursiva(nodo->filhoEsquerda);
    }

    /**
     * @brief Verifica se a arvore contem uma chave
     * @param chave chave a ser procurada na arvore
     * @return Verdade se a arvore contem a chave
     */
    virtual bool contem(T chave) const
    {
        // substitua a linha abaixo pelo algoritmo esperado
        return contemRecursivo(this->raiz, chave);
    };

    bool contemRecursivo(Nodo<T> *nodo, T chave) const
    {
        if (nodo == nullptr)
        {
            return false;
        }
        if (chave == nodo->chave)
        {
            return true;
        }
        else if (chave < nodo->chave)
        {
            return contemRecursivo(nodo->filhoEsquerda, chave);
        }
        else
        {
            return contemRecursivo(nodo->filhoDireita, chave);
        }
    }

    /**
     * @brief Retorna a altura da (sub)arvore
     * @param chave chave que é raiz da (sub)arvore cuja altura queremos.
     * @return Numero inteiro representando a altura da (subarvore). Se chave nao esta na arvore, retorna std::nullopt
     */
    virtual std::optional<int> altura(T chave) const
    {
        // substitua a linha abaixo pelo algoritmo esperado
        return alturaRecursivo(this->raiz, chave);
    };

    std::optional<int> alturaRecursivo(Nodo<T> *nodo, T chave) const
    {
        if (nodo == nullptr)
        {
            return std::nullopt;
        }
        if (chave == nodo->chave)
        {
            return std::optional<int>{nodo->altura};
        }
        else if (chave < nodo->chave)
        {
            return alturaRecursivo(nodo->filhoEsquerda, chave);
        }
        else
        {
            return alturaRecursivo(nodo->filhoDireita, chave);
        }
    };

    /**
     * @brief Insere uma chave na arvore
     * @param chave chave a ser inserida
     */
    virtual void inserir(T chave)
    {
        // escreva o algoritmo esperado
        this->raiz = inserirRecursivo(this->raiz, chave);
    };
    Nodo<T> *inserirRecursivo(Nodo<T> *nodo, T chave)
    {
        if (nodo == nullptr)
        {
            return new Nodo<T>{chave, 0, nullptr, nullptr};
        }
        if (chave < nodo->chave)
        {
            nodo->filhoEsquerda = inserirRecursivo(nodo->filhoEsquerda, chave);
        }
        else if (chave > nodo->chave)
        {
            nodo->filhoDireita = inserirRecursivo(nodo->filhoDireita, chave);
        }
        else
        {
            return nodo;
        }

        nodo->altura = 1 + std::max(alturaDoNodo(nodo->filhoEsquerda), alturaDoNodo(nodo->filhoDireita));
        int b = Balanceamento(nodo);

        if (b > 1 && chave < nodo->filhoEsquerda->chave)
        {
            return rotacaoDireita(nodo);
        }
        if (b < -1 && chave > nodo->filhoDireita->chave)
        {
            return rotacaoEsquerda(nodo);
        }
        if (b > 1 && chave > nodo->filhoEsquerda->chave)
        {
            return rotacaoEsquerdaDireita(nodo);
        }
        if (b < -1 && chave < nodo->filhoDireita->chave)
        {
            return rotacaoDireitaEsquerda(nodo);
        }
        return nodo;
    };

    int Balanceamento(Nodo<T> *nodo) const
    {
        if (nodo == nullptr)
        {
            return 0;
        }
        return alturaDoNodo(nodo->filhoEsquerda) - alturaDoNodo(nodo->filhoDireita);
    };

    int alturaDoNodo(Nodo<T> *nodo) const
    {
        if (nodo == nullptr)
        {
            return -1;
        }
        return 1 + std::max(alturaDoNodo(nodo->filhoEsquerda), alturaDoNodo(nodo->filhoDireita));
    };

    Nodo<T> *rotacaoDireita(Nodo<T> *y)
    {
        Nodo<T> *x = y->filhoEsquerda;
        Nodo<T> *T2 = x->filhoDireita;
        x->filhoDireita = y;
        y->filhoEsquerda = T2;
        y->altura = 1 + std::max(alturaDoNodo(y->filhoEsquerda), alturaDoNodo(y->filhoDireita));
        x->altura = 1 + std::max(alturaDoNodo(x->filhoEsquerda), alturaDoNodo(x->filhoDireita));
        return x;
    };

    Nodo<T> *rotacaoEsquerda(Nodo<T> *x)
    {
        Nodo<T> *y = x->filhoDireita;
        Nodo<T> *T2 = y->filhoEsquerda;
        y->filhoEsquerda = x;
        x->filhoDireita = T2;
        x->altura = 1 + std::max(alturaDoNodo(x->filhoEsquerda), alturaDoNodo(x->filhoDireita));
        y->altura = 1 + std::max(alturaDoNodo(y->filhoEsquerda), alturaDoNodo(y->filhoDireita));
        return y;
    };

    Nodo<T> *rotacaoEsquerdaDireita(Nodo<T> *nodo)
    {
        nodo->filhoEsquerda = rotacaoEsquerda(nodo->filhoEsquerda);
        return rotacaoDireita(nodo);
    };

    Nodo<T> *rotacaoDireitaEsquerda(Nodo<T> *nodo)
    {
        nodo->filhoDireita = rotacaoDireita(nodo->filhoDireita);
        return rotacaoEsquerda(nodo);
    };

    /**
     * @brief Remove uma chave da arvore
     * @param chave chave a removida
     */
    virtual void remover(T chave)
    {
        // escreva o algoritmo esperado
        this->raiz = removeRecursivo(this->raiz, chave);
    };

    Nodo<T> *removeRecursivo(Nodo<T> *nodo, T chave)
    {
        if (nodo == nullptr)
        {
            return nullptr;
        }
        if (chave < nodo->chave)
        {
            nodo->filhoEsquerda = removeRecursivo(nodo->filhoEsquerda, chave);
        }
        else if (chave > nodo->chave)
        {
            nodo->filhoDireita = removeRecursivo(nodo->filhoDireita, chave);
        }
        else
        {
            if (nodo->filhoEsquerda == nullptr && nodo->filhoDireita == nullptr)
            {
                delete nodo;
                return nullptr;
            }
            else if (nodo->filhoEsquerda == nullptr)
            {
                Nodo<T> *aux = nodo->filhoDireita;
                delete nodo;
                return aux;
            }
            else
            {
                Nodo<T> *menorDireita = menorValor(nodo->filhoDireita);
                nodo->chave = menorDireita->chave;
                nodo->filhoDireita = removeRecursivo(nodo->filhoDireita, menorDireita->chave);
            }
        }

        nodo->altura = 1 + std::max(alturaDoNodo(nodo->filhoEsquerda), alturaDoNodo(nodo->filhoDireita));
        int b = Balanceamento(nodo);

        if (b > 1 && Balanceamento(nodo->filhoEsquerda) >= 0)
        {
            return rotacaoDireita(nodo);
        }
        if (b < -1 && Balanceamento(nodo->filhoDireita) <= 0)
        {
            return rotacaoEsquerda(nodo);
        }
        if (b > 1 && Balanceamento(nodo->filhoEsquerda) < 0)
        {
            return rotacaoEsquerdaDireita(nodo);
        }
        if (b < -1 && Balanceamento(nodo->filhoDireita) > 0)
        {
            return rotacaoDireitaEsquerda(nodo);
        }
        return nodo;
    };

    Nodo<T> *menorValor(Nodo<T> *nodo) const
    {
        Nodo<T> *atual = nodo;
        while (atual->filhoEsquerda != nullptr)
        {
            atual = atual->filhoEsquerda;
        }
        return atual;
    }

    Nodo<T> *buscaNodo(Nodo<T> *nodo, T chave) const
    {
        if (nodo == nullptr)
        {
            return nullptr;
        }
        if (chave == nodo->chave)
        {
            return nodo;
        }
        else if (chave < nodo->chave)
        {
            return buscaNodo(nodo->filhoEsquerda, chave);
        }
        else
        {
            return buscaNodo(nodo->filhoDireita, chave);
        }
    }

    /**
     * @brief Busca a chave do filho a esquerda de uma (sub)arvore
     * @param chave chave da arvore que eh pai do filho a esquerda
     * @return Chave do filho a esquerda. Se chave nao esta na arvore, retorna std::nullopt
     */
    virtual std::optional<T> filhoEsquerdaDe(T chave) const
    {
        // substitua a linha abaixo pelo algoritmo esperado
        Nodo<T> *nodo = buscaNodo(this->raiz, chave);
        if (nodo != nullptr && nodo->filhoEsquerda != nullptr)
        {
            return nodo->filhoEsquerda->chave;
        }

        return std::nullopt;
    };

    /**
     * @brief Busca a chave do filho a direita de uma (sub)arvore
     * @param chave chave da arvore que eh pai do filho a direita
     * @return Chave do filho a direita. Se chave nao esta na arvore, retorna nullptr
     */
    virtual std::optional<T> filhoDireitaDe(T chave) const
    {
        // substitua a linha abaixo pelo algoritmo esperado
        Nodo<T> *nodo = buscaNodo(this->raiz, chave);
        if (nodo != nullptr && nodo->filhoDireita != nullptr)
        {
            return nodo->filhoDireita->chave;
        }
        return std::nullopt;
    };

    /**
     * @brief Lista chaves visitando a arvore em ordem
     * @return Lista encadeada contendo as chaves em ordem.
     */
    virtual ListaEncadeadaAbstrata<T> *emOrdem() const
    {
        // substitua a linha abaixo pelo algoritmo esperado
        MinhaListaEncadeada<T> *lista = new MinhaListaEncadeada<T>();
        emOrdemRecursivo(this->raiz, lista);
        return lista;
    };

    void emOrdemRecursivo(Nodo<T> *nodo, ListaEncadeadaAbstrata<T> *lista) const
    {
        if (nodo == nullptr)
        {
            return;
        }
        emOrdemRecursivo(nodo->filhoEsquerda, lista);
        lista->inserirNoFim(nodo->chave);
        emOrdemRecursivo(nodo->filhoDireita, lista);
    }

    /**
     * @brief Lista chaves visitando a arvore em pre-ordem
     * @return Lista encadeada contendo as chaves em pre-ordem.
     */
    virtual ListaEncadeadaAbstrata<T> *preOrdem() const
    {
        // substitua a linha abaixo pelo algoritmo esperado
        MinhaListaEncadeada<T> *lista = new MinhaListaEncadeada<T>();
        preOrdemRecursivo(this->raiz, lista);
        return lista;
    };

    void preOrdemRecursivo(Nodo<T> *nodo, ListaEncadeadaAbstrata<T> *lista) const
    {
        if (nodo == nullptr)
        {
            return;
        }
        lista->inserirNoFim(nodo->chave);
        preOrdemRecursivo(nodo->filhoEsquerda, lista);
        preOrdemRecursivo(nodo->filhoDireita, lista);
    }

    /**
     * @brief Lista chaves visitando a arvore em pos-ordem
     * @return Lista encadeada contendo as chaves em pos ordem.
     */
    virtual ListaEncadeadaAbstrata<T> *posOrdem() const
    {
        // substitua a linha abaixo pelo algoritmo esperado
        MinhaListaEncadeada<T> *lista = new MinhaListaEncadeada<T>();
        posOrdemRecursivo(this->raiz, lista);
        return lista;
    };

    void posOrdemRecursivo(Nodo<T> *nodo, ListaEncadeadaAbstrata<T> *lista) const
    {
        if (nodo == nullptr)
        {
            return;
        }
        posOrdemRecursivo(nodo->filhoEsquerda, lista);
        posOrdemRecursivo(nodo->filhoDireita, lista);
        lista->inserirNoFim(nodo->chave);
    }
};

#endif