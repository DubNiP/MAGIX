#include "GameOverState.hpp"
#include "Jogo.hpp"
#include "JogandoState.hpp"
#include "MenuPrincipalState.hpp"
#include "Gerenciador_Grafico.hpp"
#include "Gerenciador_Eventos.hpp"

GameOverState::GameOverState(Jogo* contexto, int numFase) : 
    State(contexto),
    menu(),
    faseAtual(numFase) 
{
}

GameOverState::~GameOverState() {
}

void GameOverState::Entrar() {
    contexto->getGG().resetarCamera();
    menu.resetaFlags();
    menu.reseta();
    Gerenciador::GerenciadorEvento::getGerenciadorEvento()->setMenu(&menu);
    Gerenciador::GerenciadorEvento::getGerenciadorEvento()->soltaTeclas();
}

void GameOverState::handle() {
    auto& GG = contexto->getGG();
    auto* GE = Gerenciador::GerenciadorEvento::getGerenciadorEvento();
    RenderWindow* window = GG.getWindow();

    while (window && window->isOpen() && !menu.getReiniciar() && !menu.getVoltarMenu()) {
        if (!GE->verificarEventosJanela(window)) {
            return;
        }

        GE->executarMenu();
        menu.draw_menu();
    }
}

void GameOverState::Sair() {
    Gerenciador::GerenciadorEvento::getGerenciadorEvento()->setMenu(NULL);
    contexto->getMago()->reseta(Vector2f(100.f, 630.f), 15, 0);
    if (menu.getReiniciar()) {
        contexto->mudarEstado(new JogandoState(contexto, faseAtual));
    }
    else if (menu.getVoltarMenu()) {
        contexto->mudarEstado(new MenuPrincipalState(contexto));
    }
}