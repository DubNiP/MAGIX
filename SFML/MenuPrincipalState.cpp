#include "MenuPrincipalState.hpp"

MenuPrincipalState::MenuPrincipalState(Jogo* contexto): 
    State(contexto),
    menu() 
{
}

MenuPrincipalState::~MenuPrincipalState() {
    Gerenciador::GerenciadorEvento::getGerenciadorEvento()->dettach(this);               //Padrão de projeto Observer
}

void MenuPrincipalState::Entrar() {
    Gerenciadores::GerenciadorGrafico::getGG().resetarCamera();
    menu.resetaFlags();
    menu.reseta();
    Gerenciador::GerenciadorEvento::getGerenciadorEvento()->attach(this);                //Padrão de projeto Observer
    Gerenciador::GerenciadorEvento::getGerenciadorEvento()->soltaTeclas();
}

void MenuPrincipalState::handle() {
    auto& GG = Gerenciadores::GerenciadorGrafico::getGG();
    auto* GE = Gerenciador::GerenciadorEvento::getGerenciadorEvento();
    RenderWindow* window = GG.getWindow();


    while (window && window->isOpen() && !menu.getIniciar() && !menu.getSair()) {        //Se não iniciou e não saiu e não clicou no close, executa menu.
        if (!GE->verificarEventosJanela(window)) { 
            return;
        }

        GE->executarMenu();
        menu.draw_menu();
    }
}

void MenuPrincipalState::Sair() {

    Gerenciador::GerenciadorEvento::getGerenciadorEvento()->dettach(this);               //Padrão de projeto Observer
    if (menu.getIniciar()) {
        contexto->mudarEstado(new SelecaoFaseState(contexto));
    }
    else if (menu.getSair()) {
        auto& GG = Gerenciadores::GerenciadorGrafico::getGG();
        RenderWindow* window = GG.getWindow();
        if (window) {
            window->close();
        }
    }
}

void MenuPrincipalState::update(int i) {                                                //Padrão de projeto Observer
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