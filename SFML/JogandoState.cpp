#include "JogandoState.hpp"

JogandoState::JogandoState(Jogo* contexto, int numFase):
    State(contexto), 
    numeroFase(numFase), 
    pMago(NULL), 
    faseAtual(NULL) {

    pMago = contexto->getMago();
}

JogandoState::~JogandoState() {
    faseAtual = NULL;
}

void JogandoState::Entrar() {
    if (numeroFase == 1) {
        faseAtual = contexto->getFase1();
        contexto->getGG().setSegundaTela(false);
    }
    else if (numeroFase == 2) {
        faseAtual = contexto->getFase2();
        contexto->getGG().setSegundaTela(true);
    }
    Gerenciador::GerenciadorEvento::getGerenciadorEvento()->setMago(pMago);
}

void JogandoState::handle() {
    if (faseAtual) {
        faseAtual->executar();

       
        if (pMago && pMago->getVidas() <= 0) {
            contexto->mudarEstado(new GameOverState(contexto, numeroFase));
            return;
        }

        
        if (pMago && pMago->getConcluiuFase()) {
            faseAtual->resetar();
            contexto->mudarEstado(new MenuPrincipalState(contexto));
            return;
        }

        if (faseAtual->getPause()) {
            contexto->mudarEstado(new PauseState(contexto, numeroFase));
            return;
        }
    }
}

void JogandoState::Sair() {

    if (numeroFase == 2) {
        contexto->getGG().setSegundaTela(false);
    }
    Gerenciador::GerenciadorEvento::getGerenciadorEvento()->setMago(NULL);
}