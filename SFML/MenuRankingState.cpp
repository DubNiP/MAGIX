#include "MenuRankingState.hpp"

using namespace estados;

MenuRankingState::MenuRankingState(Jogo* contexto):
    State(contexto)
{
}

MenuRankingState::~MenuRankingState() {
    Gerenciador::GerenciadorEvento::getGerenciadorEvento()->dettach(this);
}

void MenuRankingState::Entrar() {
    Gerenciadores::GerenciadorGrafico::getGG().resetarCamera();
    menu.resetaFlags();
    menu.reseta();
    Gerenciador::GerenciadorEvento::getGerenciadorEvento()->attach(this);
    Gerenciador::GerenciadorEvento::getGerenciadorEvento()->soltaTeclas();

}

void MenuRankingState::handle() {
    auto& GG = Gerenciadores::GerenciadorGrafico::getGG();
    auto* GE = Gerenciador::GerenciadorEvento::getGerenciadorEvento();
    RenderWindow* window = GG.getWindow();

    while (window && window->isOpen() && !menu.getSair() ) {
        if (!GE->verificarEventosJanela(window)) {
            return;
        }
       
        menu.mostrarRanking();
        GE->executarMenu();
        menu.draw_menu();
    }
}

void MenuRankingState::Sair() {

    Gerenciador::GerenciadorEvento::getGerenciadorEvento()->dettach(this);
    if (menu.getSair()) {
        contexto->mudarEstado(new MenuPrincipalState(contexto));
    }

}

void MenuRankingState::update(int i) {
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