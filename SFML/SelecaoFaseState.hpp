#pragma once
#include "Jogo.hpp"
#include "State.hpp"
#include "MenuSelecaoFase.hpp"
#include "MenuPrincipalState.hpp"
#include "JogandoState.hpp"
#include "Gerenciador_Grafico.hpp"
#include "Gerenciador_Eventos.hpp"

using namespace sf;

class SelecaoFaseState : public State {
private:
    MenuSelecaoFase menu;
    Event evento;

public:
    SelecaoFaseState(Jogo* contexto);
    ~SelecaoFaseState();

    void Entrar();
    void handle();
    void Sair();
};