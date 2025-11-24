#include "JogandoState.hpp"

using namespace estados;

JogandoState::JogandoState(Jogo* contexto, int numFase, int numJog, bool reseta):

    State(contexto), 
    numeroFase(numFase), 
    numJogadores(numJog),
    pMago1(NULL), 
    pMago2(NULL),
    faseAtual(NULL),
    resetaFase(reseta)
{

    pMago1 = contexto->getMago1();
    if (numJogadores == 2) {  
        pMago2 = contexto->getMago2();
    }
}

JogandoState::~JogandoState() {
    pMago1 = NULL;                    
    pMago2 = NULL;
    faseAtual = NULL;
}

void JogandoState::Entrar() {
    if (numeroFase == 1) {
        faseAtual = contexto->getFase1();
        Gerenciadores::GerenciadorGrafico::getGG().setSegundaTela(false);
    }
    else if (numeroFase == 2) {
        faseAtual = contexto->getFase2();
        Gerenciadores::GerenciadorGrafico::getGG().setSegundaTela(true);
    }
    else if (numeroFase == 3) {
        ifstream arquivoFase(contexto->getMago1()->getCaminho());

        char n[50];
        int p, f;

        arquivoFase >> n >> p >> f;

        if (f == 1) {
            faseAtual = contexto->getFase1();
            Gerenciadores::GerenciadorGrafico::getGG().setSegundaTela(false);
        }
        else {
            faseAtual = contexto->getFase2();
            Gerenciadores::GerenciadorGrafico::getGG().setSegundaTela(true);
        }

        faseAtual->inicializar();

        faseAtual->carregarSave(contexto->getMago1()->getCaminho());
    }

    if (faseAtual) {
        if (numJogadores == 2) {
            faseAtual->setdoisJog(true);
        }
        else {
            faseAtual->setdoisJog(false);
        }
    }

    if (resetaFase) {
        faseAtual->resetar();
    }


    Gerenciador::GerenciadorEvento::getGerenciadorEvento()->setMago1(pMago1);
    if (numJogadores == 2 && pMago2) {
        Gerenciador::GerenciadorEvento::getGerenciadorEvento()->setMago2(pMago2);
    }
    else {
        Gerenciador::GerenciadorEvento::getGerenciadorEvento()->setMago2(NULL);
    }
}

void JogandoState::handle() {
    if (faseAtual) {
        faseAtual->executar();                                                                //Se saiu do looping desse método, aconteceu algo...

       
        if (pMago1 && pMago1->getVidas() <= 0) {
            contexto->mudarEstado(new GameOverState(contexto, numeroFase, numJogadores));
            return;
        }

        if (faseAtual->getPause()) {
            contexto->mudarEstado(new PauseState(contexto, numeroFase, numJogadores));
            return;
        }
        
        if (pMago1 && pMago1->getConcluiuFase()) {
            faseAtual->resetar();
            contexto->mudarEstado(new MenuPrincipalState(contexto));
            return;
        }

    }
}

void JogandoState::Sair() {
    if (numeroFase == 2) {
        Gerenciadores::GerenciadorGrafico::getGG().setSegundaTela(false);
    }
    Gerenciador::GerenciadorEvento::getGerenciadorEvento()->setMago1(NULL);
    Gerenciador::GerenciadorEvento::getGerenciadorEvento()->setMago2(NULL);
}