#include "PauseState.hpp"
#include "Jogo.hpp"
#include "JogandoState.hpp"
#include "MenuPrincipalState.hpp"
#include "Gerenciador_Grafico.hpp"
#include "Gerenciador_Eventos.hpp"

PauseState::PauseState(Jogo* contexto, int numFase)
    : State(contexto), 
    menu(),  
    faseAtual(numFase) 
{
}

PauseState::~PauseState() {
}

void PauseState::Entrar() {
    Gerenciadores::GerenciadorGrafico::Instance().resetarCamera();
    menu.resetaFlags();
    menu.reseta();

    if (faseAtual == 1) {
        menu.setListaEntidades(contexto->getFase1()->getListaEntidades());
    } else if (faseAtual == 2) {
        menu.setListaEntidades(contexto->getFase2()->getListaEntidades());
    } else {
        menu.setListaEntidades(nullptr);
    }

    std::cout << "PauseState::Entrar() -> menu.lista_ents = " << menu.getListaEntidades() << std::endl;

    Gerenciador::GerenciadorEvento::getGerenciadorEvento()->setMenu(&menu);
    Gerenciador::GerenciadorEvento::getGerenciadorEvento()->soltaTeclas();
}

void PauseState::handle() {
    auto* GE = Gerenciador::GerenciadorEvento::getGerenciadorEvento();
    auto& GG = Gerenciadores::GerenciadorGrafico::Instance();
    RenderWindow* window = GG.getWindow();

    while (window && window->isOpen() && !menu.getContinuar() && !menu.getVoltarMenu()) {
        if (!GE->verificarEventosJanela(window)) {
            return;
        }

        GE->executarMenu();
        menu.draw_menu();
    }
}

void PauseState::Sair() {
    Gerenciador::GerenciadorEvento::getGerenciadorEvento()->setMenu(NULL);

    if (menu.getContinuar()) {
        contexto->mudarEstado(new JogandoState(contexto, faseAtual));
    }
    else if (menu.getVoltarMenu()) {
        contexto->getMago()->reseta(Vector2f(100.f, 630.f), 15, 0);
        contexto->mudarEstado(new MenuPrincipalState(contexto));
    }
}