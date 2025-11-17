#include "SelecaoFaseState.hpp"

SelecaoFaseState::SelecaoFaseState(Jogo* contexto) :
    State(contexto),
    menu(),
    evento()
{
}

SelecaoFaseState::~SelecaoFaseState() {
}

void SelecaoFaseState::Entrar() {
    contexto->getGG().resetarCamera();
    menu.resetaFlags();
    menu.reseta();
    Gerenciador::GerenciadorEvento::getGerenciadorEvento()->setMenu(&menu);
    Gerenciador::GerenciadorEvento::getGerenciadorEvento()->soltaTeclas();
}

void SelecaoFaseState::handle() {
    auto& GG = contexto->getGG();
    auto* GE = Gerenciador::GerenciadorEvento::getGerenciadorEvento();
    RenderWindow* window = GG.getWindow();

    while (window && window->isOpen() && menu.getFaseEscolhida() == -1 && !menu.getVoltar()) {
        if (!GE->verificarEventosJanela(window)) {
            return;
        }

        GE->executarMenu();
        menu.draw_menu();
    }
}

void SelecaoFaseState::Sair() {
    Gerenciador::GerenciadorEvento::getGerenciadorEvento()->setMenu(NULL);

    if (menu.getVoltar()) {
        contexto->mudarEstado(new MenuPrincipalState(contexto));
    }
    else if (menu.getFaseEscolhida() == 1) {
        contexto->mudarEstado(new JogandoState(contexto, 1));
    }
    else if (menu.getFaseEscolhida() == 2) {
        contexto->mudarEstado(new JogandoState(contexto, 2));
    }
}