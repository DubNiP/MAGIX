#pragma once
#include "State.hpp"
#include "MenuRanking.hpp"
#include "Menu.hpp"
#include "Jogo.hpp"
#include "Gerenciador_Grafico.hpp"
#include "Gerenciador_Eventos.hpp"
#include <vector>

using namespace sf;

namespace estados {
    class MenuRankingState : public State {
    private:
        MenuRanking menu;
    public:
        MenuRankingState(Jogo* contexto);
        ~MenuRankingState();

        void Entrar();
        void handle();
        void Sair();
        void update(int i);
    };
}