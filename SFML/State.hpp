#pragma once
#include "Observer.cpp"


class Jogo;


//Essa classe é obrigatória para a comunicação entre Jogo e seu estado por meio do padrão de projeto Observer


class State : public Observer {
protected:
    Jogo* contexto;
public:
    State(Jogo* context) : Observer(), contexto(context) {}
    virtual ~State() {}

    virtual void Entrar() = 0;     
    virtual void handle() = 0;    
    virtual void Sair() = 0;
    virtual void update(int i) = 0;
};