#pragma once
#include "State.hpp"
#include "MenuGameOver.hpp"

using namespace sf;

class GameOverState : public State {
private:
    MenuGameOver menu;
    int faseAtual;

public:
    GameOverState(Jogo* contexto, int numFase);
    ~GameOverState();

    void Entrar();
    void handle();
    void Sair();
};