#pragma once

class Jogo;

class State {
protected:
    Jogo* contexto;

public:
    State(Jogo* context) : contexto(context) {}
    virtual ~State() {}

    virtual void Entrar() = 0;     
    virtual void handle() = 0;    
    virtual void Sair() = 0;       
};