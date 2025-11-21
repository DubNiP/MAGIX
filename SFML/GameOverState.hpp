#pragma once
#include "State.hpp"
#include "MenuGameOver.hpp"

using namespace sf;

class GameOverState : public State {
private:
    MenuGameOver menu;
    int faseAtual;
    int numJog;

public:
    GameOverState(Jogo* contexto, int numFase, int numJog);
    ~GameOverState();

    void Entrar();
    void handle();
    void Sair();
    void update(int i);
};