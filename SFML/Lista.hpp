#pragma once

template <class TL>
class Lista
{
private:

    template <class TE>
    class Elemento
    {
    private:
        Elemento<TE>* pProx;
        TE* pInfo;

    public:
        Elemento();
        ~Elemento();

        void setProx(Elemento<TE>* pE) { pProx = pE; }
        void setInfo(TE* p) { pInfo = p; }
        Elemento<TE>* getProximo() const { return pProx; }
        TE* getInfo() const { return pInfo; }
    };

    Elemento<TL>* pPrimeiro;
    Elemento<TL>* pUltimo;

    int len;

public:
    Lista();
    ~Lista();

    int getLen() { return len; }
    void limpar() {}
    TL* getItem(int pos);
    Elemento<TE>* getPrimeiro const() { return pPrimeiro };
    void inserir(TL* item);
    void deletar(TL* item);
    bool vazia() { return pPrimeiro == nullptr; }
};

template <class TL>
template <class TE>
Lista<TL>::Elemento<TE>::Elemento() : pProx(nullptr), pInfo(nullptr)
{
}

template <class TL>
template <class TE>
Lista<TL>::Elemento<TE>::~Elemento()
{
}

template<class TL>
Lista<TL>::Lista() : pPrimeiro(nullptr), pUltimo(nullptr), len(0)
{
}

template<class TL>
Lista<TL>::~Lista()
{
    limpar();
}

template<class TL>
void Lista<TL>::limpar()
{
    Elemento<TL>* pATual = pPrimeiro;

    while (atual != nullptr) {
        Elemento<TL>* proximo = atual->getPProx();
        delete atual;
        atual = proximo;
    }
}

template<class TL>
TL* Lista<TL>::getItem(int posicao) {
    if (posicao < 0 || posicao >= len) {
        return nullptr;
    }

    Elemento<TL>* temp = pPrimeiro;

    if (posicao == 0) {
        return temp->getItem();
    }

    for (int i = 0; i < posicao; i++) {
        temp = temp->getPProx();
    }

    return temp->getItem();
}

template<class TL>
void Lista<TL>::inserir(TL* item) {
    if (pPrimeiro == nullptr) {
        pPrimeiro = new Elemento();
        pPrimeiro->setItem(item);
        pUltimo = pPrimeiro;
    }
    else {
        Elemento<TL>* temp = new Elemento();
        temp->setItem(item);
        pUltimo->setPProx(temp);
        pUltimo = temp;
    }
    len++;
}

template<class TL>
void Lista<TL>::deletar(TL* item) {
    if (pPrimeiro == nullptr || item == nullptr) {
        return;
    }

    Elemento<TL>* temp = pPrimeiro;
    Elemento<TL>* tempAnt = nullptr;

    while (temp != nullptr && temp->getItem() != item) {
        tempAnt = temp;
        temp = temp->getPProx();
    }


    if (temp == nullptr) {
        return;
    }

    if (temp == pPrimeiro) {
        pPrimeiro = temp->getPProx();

        if (pPrimeiro == nullptr) {
            pUltimo = nullptr;
        }
    }
    else if (temp == pUltimo) {
        tempAnt->setPProx(nullptr);
        pUltimo = tempAnt;
    }
    else {
        tempAnt->setPProx(temp->getPProx());
    }

    delete temp;
    len--;
}