#pragma once
#include "State.hpp"
#include "MenuPrincipal.hpp"
#include "SelecaoFaseState.hpp"
#include "Menu.hpp"
#include "Jogo.hpp"
#include "Gerenciador_Grafico.hpp"
#include "Gerenciador_Eventos.hpp"

using namespace sf;

namespace estados {

    class MenuPrincipalState : public State {
    private:
        MenuPrincipal menu;
        Font font;
        Text inputText;
        String buffer;
    public:
        MenuPrincipalState(Jogo* contexto);
        ~MenuPrincipalState();

            void Entrar();
            void handle();
            void Sair();
            void update(int i);
    };
}