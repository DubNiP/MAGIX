#include "MenuPrincipalState.hpp"
#include "MenuRankingState.hpp"

using namespace estados;

MenuPrincipalState::MenuPrincipalState(Jogo* contexto): 
    State(contexto),
    font(),
    inputText(),
    buffer(),
    menu() 
{

    inputText.setFont(font);
    inputText.setCharacterSize(48u);
    inputText.setFillColor(Color::White);
    inputText.setOutlineColor(Color::Black);
    inputText.setOutlineThickness(2.f);
}

MenuPrincipalState::~MenuPrincipalState() {
    Gerenciador::GerenciadorEvento::getGerenciadorEvento()->dettach(this);               //Padrão de projeto Observer
}

void MenuPrincipalState::Entrar() {
    Gerenciadores::GerenciadorGrafico::getGG().resetarCamera();
    menu.setNomeMago((contexto->getMago1()->getNome()));
    menu.resetaFlags();
    menu.reseta();
    Gerenciador::GerenciadorEvento::getGerenciadorEvento()->attach(this);                //Padrão de projeto Observer
    Gerenciador::GerenciadorEvento::getGerenciadorEvento()->soltaTeclas();

    const char* atual = contexto->getMago1()->getNome();
    buffer = atual ? atual : "";
    inputText.setString(buffer);
    inputText.setPosition(200.f, 300.f);

    if (atual) menu.setNomeMago(atual);

}

void MenuPrincipalState::handle() {
    auto& GG = Gerenciadores::GerenciadorGrafico::getGG();
    auto* GE = Gerenciador::GerenciadorEvento::getGerenciadorEvento();
    RenderWindow* window = GG.getWindow();

    const std::size_t MAX_NAME_LEN = 49;

    while (window && window->isOpen() && !menu.getIniciar() && !menu.getSair() && !menu.getRanking()) {
        if (!GE->verificarEventosJanela(window)) {
            return;
        }

        Event event;
        while (GE->proximoEvento(event)) {
            if (event.type == Event::Closed) {
                window->close();
                return;
            }
            else if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::BackSpace) {
                    if (buffer.getSize() > 0) {
                        buffer.erase(buffer.getSize() - 1, 1);
                        inputText.setString(buffer);
                        string tmp = buffer.toAnsiString();
                        menu.setNomeMago(tmp.c_str());
                    }
                }
                // Enter é tratado via executarMenu() e notify -> update(3)
            }
            else if (event.type == Event::TextEntered) {
                uint32_t uni = event.text.unicode;
                if (uni >= 32 && uni != 127) {

                    // só permite até MAX_NAME_LEN caracteres
                    if (buffer.getSize() < MAX_NAME_LEN) {
                        buffer += (Uint32)uni;
                        inputText.setString(buffer);
                        string tmp = buffer.toAnsiString();
                        menu.setNomeMago(tmp.c_str());
                    }
                }
            }
        }

        GE->executarMenu();
        menu.draw_menu();

        string novo = buffer.toAnsiString();
        contexto->getMago1()->setNome(novo.c_str());
    }
}

void MenuPrincipalState::Sair() {

    Gerenciador::GerenciadorEvento::getGerenciadorEvento()->dettach(this);              //Padrão de projeto Observer
    if (menu.getRanking()) {
		contexto->mudarEstado(new MenuRankingState(contexto));
    }
    else if (menu.getIniciar()) {
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