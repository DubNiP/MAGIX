#include "PauseState.hpp"
#include "Jogo.hpp"
#include "JogandoState.hpp"
#include "MenuPrincipalState.hpp"
#include "Gerenciador_Grafico.hpp"
#include "Gerenciador_Eventos.hpp"


using namespace estados;

PauseState::PauseState(Jogo* contexto, int numFase, int numJ): 
    State(contexto), 
    menu(),  
    faseAtual(numFase),
    numJog(numJ)
{
}

PauseState::~PauseState() {
}

void PauseState::Entrar() {
    Gerenciadores::GerenciadorGrafico::getGG().resetarCamera();
    menu.resetaFlags();
    menu.reseta();

    Gerenciador::GerenciadorEvento::getGerenciadorEvento()->soltaTeclas();
    Gerenciador::GerenciadorEvento::getGerenciadorEvento()->attach(this);                                     //Padrão de projeto Observer.
}

void PauseState::handle() {
    auto* GE = Gerenciador::GerenciadorEvento::getGerenciadorEvento();
    auto& GG = Gerenciadores::GerenciadorGrafico::getGG();
    RenderWindow* window = GG.getWindow();

    while (window && window->isOpen() && !menu.getContinuar() && !menu.getVoltarMenu()) {
        if (menu.getSalvar()) {
            contexto->getMago1()->salvarLinha();
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
    Gerenciador::GerenciadorEvento::getGerenciadorEvento()->dettach(this);                                    //Padrão de projeto Observer.

    if (menu.getContinuar()) {
        contexto->mudarEstado(new JogandoState(contexto, faseAtual, numJog, false));
    }

    else if (menu.getVoltarMenu()) {
        contexto->getMago1()->reseta(Vector2f(100.f, 630.f), 15, 0);
        if (numJog == 2) {
            contexto->getMago2()->reseta(Vector2f(100.f, 630.f), 15, 0);
        }
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