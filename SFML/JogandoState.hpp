#pragma once

#include "Jogo.hpp"
#include "State.hpp"
#include "MenuPrincipalState.hpp"
#include "GameOverState.hpp"
#include "PauseState.hpp"
#include "Gerenciador_Grafico.hpp"
#include "Gerenciador_Eventos.hpp"
#include "FasePrimeira.hpp"
#include "FaseSegunda.hpp"

class JogandoState : public State {
private:
    int numeroFase;
    entidades::personagens::Mago* pMago;
    fases::Fase* faseAtual;

public:
    JogandoState(Jogo* contexto, int numFase);
    ~JogandoState();

    void Entrar();
    void handle();
    void Sair();
};