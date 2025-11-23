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
    Gerenciadores::GerenciadorGrafico::getGG().resetarCamera();
    menu.resetaFlags();
    menu.reseta();

    Gerenciador::GerenciadorEvento::getGerenciadorEvento()->soltaTeclas();
    Gerenciador::GerenciadorEvento::getGerenciadorEvento()->attach(this);
}

void PauseState::handle() {
    auto* GE = Gerenciador::GerenciadorEvento::getGerenciadorEvento();
    auto& GG = Gerenciadores::GerenciadorGrafico::getGG();
    RenderWindow* window = GG.getWindow();

    while (window && window->isOpen() && !menu.getContinuar() && !menu.getVoltarMenu()) {
        if (menu.getSalvar()) {
            contexto->getMago()->salvarLinha();
			contexto->getFase1()->getListaEntidades()->salvarTodos();
            cout << "Entrou" << endl;
            menu.setSalvar(false);
        }
        
        if (!GE->verificarEventosJanela(window)) {
            return;
        }

        GE->executarMenu();
        menu.draw_menu();
    }
}

void PauseState::Sair() {
    Gerenciador::GerenciadorEvento::getGerenciadorEvento()->dettach(this);

    if (menu.getContinuar()) {
        contexto->mudarEstado(new JogandoState(contexto, faseAtual));
    }
    else if (menu.getVoltarMenu()) {
        contexto->getMago()->reseta(Vector2f(100.f, 630.f), 15, 0);
        contexto->mudarEstado(new MenuPrincipalState(contexto));
    }
}

void PauseState::update(int i) {
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