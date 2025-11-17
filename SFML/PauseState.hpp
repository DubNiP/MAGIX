#pragma once
#include "State.hpp"
#include "MenuPause.hpp"

using namespace sf;

class PauseState : public State {
private:
    MenuPause menu;
    int faseAtual;

public:
    PauseState(Jogo* contexto, int numFase);
    ~PauseState();

    void Entrar();
    void handle();
    void Sair();
};