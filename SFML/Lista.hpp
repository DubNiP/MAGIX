#pragma once

#include <iostream>

using namespace std;

namespace listas {

template <class TL>
class Lista
{
public:
    template <class TE>

    class Elemento {                                                       //Classe elemento:
    private:
        Elemento<TE>* pProx;
        TE* pInfo;

    public:
        Elemento() : pProx(NULL), pInfo(NULL) {};
        ~Elemento() = default;


        void setProx(Elemento<TE>* pE) { pProx = pE; }
        void setInfo(TE* p) { pInfo = p; }
        Elemento<TE>* getProx() const { return pProx; }
        TE* getInfo() const { return pInfo; }
    };

    class Iterator {                                                      //Classe Iterator, padrão de projeto Iterator.
    private:
        Elemento<TL>* atual;
    public:
        Iterator(Elemento<TL>* p = NULL) : atual(p) {}
        ~Iterator() {}
        TL* operator*() const {
            if (atual) {
                return atual->getInfo();
            }
            return NULL;
        }
        Iterator& operator++() {
            if (atual) {
                atual = atual->getProx();
            }
            return *this;
        }
        const bool operator!=(const Iterator& aux) const {
            return atual != aux.atual;
        }
        const bool operator==(const Iterator& aux) const {
            return atual == aux.atual;
        }
    };

private:

    Elemento<TL>* pPrimeiro;
    Elemento<TL>* pUltimo;
    int size;

public:
    Lista() : pPrimeiro(NULL), pUltimo(NULL), size(0) {}
    ~Lista() { limpar();  }

    bool vazia() const { return pPrimeiro == NULL; }
    Elemento<TL>* getPrimeiro() const { return pPrimeiro; }
    Elemento<TL>* getUltimo() const { return pUltimo; }

    Iterator begin() { return Iterator(pPrimeiro); }
    Iterator end() { return Iterator(NULL); }

    void incluir(TL* item) {
        if (pPrimeiro == NULL) {
            pPrimeiro = new Elemento<TL>();
            pPrimeiro->setInfo(item);
            pUltimo = pPrimeiro;
        }
        else {
            Elemento<TL>* temp = new Elemento<TL>();
            temp->setInfo(item);
            pUltimo->setProx(temp);
            pUltimo = temp;
        }
        size++;
    }
    void deletar(TL* item) {
        if (pPrimeiro == NULL || item == NULL) {
            return;
        }

        Elemento<TL>* temp = pPrimeiro;
        Elemento<TL>* tempAnt = NULL;

        while (temp && temp->getInfo() != item) {
            tempAnt = temp;
            temp = temp->getProx();
        }


        if (temp == NULL) {
            return;
        }

        if (temp == pPrimeiro) {
            pPrimeiro = temp->getProx();

            if (pPrimeiro == NULL) {
                pUltimo = NULL;
            }
        }
        else if (temp == pUltimo) {
            tempAnt->setProx(NULL);
            pUltimo = tempAnt;
        }
        else {
            tempAnt->setProx(temp->getProx());
        }

        delete temp;
        size--;
    }
    void limpar()
    {
        Elemento<TL>* atual = pPrimeiro;

        while (atual) {
            Elemento<TL>* proximo = atual->getProx();
            delete atual;
            atual = proximo;
        }
        pPrimeiro = NULL;
        pUltimo = NULL;
        size = 0;
    }
};
}