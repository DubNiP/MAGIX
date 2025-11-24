#pragma once
#include "State.hpp"
#include "MenuPause.hpp"

using namespace sf;

namespace estados {
    class PauseState : public State {
    private:
        MenuPause menu;
        int faseAtual;
        int numJog;

    public:
        PauseState(Jogo* contexto, int numFase, int numJ = 1);
        ~PauseState();

        void Entrar();
        void handle();
        void Sair();
        void update(int i);
    };
}