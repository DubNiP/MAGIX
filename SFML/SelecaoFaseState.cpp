#include "SelecaoFaseState.hpp"

using namespace estados;

SelecaoFaseState::SelecaoFaseState(Jogo* contexto) :
    State(contexto),
    menu()
{
}

SelecaoFaseState::~SelecaoFaseState() {
}

void SelecaoFaseState::Entrar() {
    Gerenciadores::GerenciadorGrafico::getGG().resetarCamera();
    menu.resetaFlags();
    menu.reseta();
    Gerenciador::GerenciadorEvento::getGerenciadorEvento()->soltaTeclas();
    Gerenciador::GerenciadorEvento::getGerenciadorEvento()->attach(this);                                //Padrão de projeto Observer
}

void SelecaoFaseState::handle() {
    auto& GG = Gerenciadores::GerenciadorGrafico::getGG();
    auto* GE = Gerenciador::GerenciadorEvento::getGerenciadorEvento();
    RenderWindow* window = GG.getWindow();

    while (window && window->isOpen() && menu.getFaseEscolhida() == -1 && !menu.getVoltar()) {          //Enquanto não selecionar uma fase e não clicar para voltar...
        if (!GE->verificarEventosJanela(window)) {
            return;
        }

        GE->executarMenu();
        menu.draw_menu();
    }
}

void SelecaoFaseState::Sair() {

    Gerenciador::GerenciadorEvento::getGerenciadorEvento()->dettach(this);                              //Padrão de projeto Observer
    if (menu.getVoltar()) {
        contexto->mudarEstado(new MenuPrincipalState(contexto));
    }
    
    else if (menu.getFaseEscolhida() == 1) {
        contexto->mudarEstado(new JogandoState(contexto, 1, menu.getNumJogadores()));
    }
    else if (menu.getFaseEscolhida() == 2) {
        contexto->mudarEstado(new JogandoState(contexto, 2, menu.getNumJogadores()));
    }
    else if (menu.getFaseEscolhida() == 3) {
        contexto->mudarEstado(new JogandoState(contexto, 3, menu.getNumJogadores(), false));
    }
}

void SelecaoFaseState::update(int i) {
    if (i == 1) {
        menu.moverBaixo();
    }
    else if (i == 2) {
        menu.moverCima();
    }
    else if (i == 3) {
        menu.confirmar();
    }
}