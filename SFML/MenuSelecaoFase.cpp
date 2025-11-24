#include "MenuSelecaoFase.hpp"

MenuSelecaoFase::MenuSelecaoFase() :
    Menu(),
    voltar(false),
    faseEscolhida(-1),
    numJogadores(1)
{
    set_values();
    reseta();
}

MenuSelecaoFase::~MenuSelecaoFase() {
}

void MenuSelecaoFase::set_values() {
    const char* opcoes[] = { "Carregar Jogo", "1 Jogador - Fase 1", "1 Jogador - Fase 2","2 Jogadores - Fase 1","2 Jogadores - Fase 2","Voltar" }; //COLOCAR OPCAO DE CARREGAR
    const Vector2f posicoes[] = { {500.f, 110.f},{520.f, 250.f},{520.f, 320.f},{500.f, 390.f},{500.f, 460.f},{600.f, 550.f} };
    const unsigned int tamanhos[] = { 60u, 40u, 40u, 40u, 40u, 50u };

    texts.clear();
    texts.reserve(6);

    for (size_t i = 0; i < 6; i++) {
        Text t;
        t.setFont(font);
        t.setString(opcoes[i]);
        t.setCharacterSize(tamanhos[i]);
        t.setPosition(posicoes[i]);
        t.setFillColor(Color::White);
        t.setOutlineColor(Color::Black);
        t.setOutlineThickness(0.f);
        texts.push_back(t);
    }

    posMin = 0; 
    posMax = 5;  
    pos = posMin;
}

void MenuSelecaoFase::confirmar() {
    if (pos == 0) {
        faseEscolhida = 3;
    }
    else if (pos == 1) {
        faseEscolhida = 1;
        numJogadores = 1;
    }
    else if (pos == 2) {
        faseEscolhida = 2;
        numJogadores = 1;
    }
    else if (pos == 3) { 
        faseEscolhida = 1;
        numJogadores = 2;
    }
    else if (pos == 4) {  
        faseEscolhida = 2;
        numJogadores = 2;
    }
    else if (pos == 5) {
        voltar = true;
    }

}

bool MenuSelecaoFase::getVoltar() const {
    return voltar;
}

int MenuSelecaoFase::getFaseEscolhida() const {
    return faseEscolhida;
}

int MenuSelecaoFase::getNumJogadores() const {  
    return numJogadores;
}

void MenuSelecaoFase::resetaFlags() {
    voltar = false;
    faseEscolhida = -1;
    numJogadores = -1;
}