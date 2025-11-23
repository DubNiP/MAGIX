#include "GameOverState.hpp"
#include "Jogo.hpp"
#include "JogandoState.hpp"
#include "MenuPrincipalState.hpp"
#include "Gerenciador_Grafico.hpp"
#include "Gerenciador_Eventos.hpp"

using namespace estados;

GameOverState::GameOverState(Jogo* contexto, int numFase, int numJog) : 
    State(contexto),
    menu(),
    faseAtual(numFase),
    numJog(numJog)
{
}

GameOverState::~GameOverState() {
}

void GameOverState::Entrar() {
    Gerenciador::GerenciadorEvento::getGerenciadorEvento()->attach(this);                              //Padrão de projeto Observer
    Gerenciadores::GerenciadorGrafico::getGG().resetarCamera();
    menu.resetaFlags();
    menu.reseta();
    Gerenciador::GerenciadorEvento::getGerenciadorEvento()->soltaTeclas();
}

void GameOverState::handle() {
    auto& GG = Gerenciadores::GerenciadorGrafico::getGG();
    auto* GE = Gerenciador::GerenciadorEvento::getGerenciadorEvento();
    RenderWindow* window = GG.getWindow();

    while (window && window->isOpen() && !menu.getReiniciar() && !menu.getVoltarMenu()) {             //Enquanto não reiniciou e não voltou pro menu..
        if (!GE->verificarEventosJanela(window)) {
            return;
        }

        GE->executarMenu();
        menu.draw_menu();
    }
}

void GameOverState::Sair() {
    Gerenciador::GerenciadorEvento::getGerenciadorEvento()->dettach(this);                            //Padrão de projeto Observer

    contexto->getMago1()->reseta(Vector2f(100.f, 630.f), 15, 0);
    if (numJog == 2) {
        contexto->getMago2()->reseta(Vector2f(100.f, 630.f), 15, 0);
    }

    if (menu.getReiniciar()) {
        contexto->mudarEstado(new JogandoState(contexto, faseAtual, numJog));
    }
    else if (menu.getVoltarMenu()) {
        contexto->mudarEstado(new MenuPrincipalState(contexto));
    }
}

void GameOverState::update(int i) {

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