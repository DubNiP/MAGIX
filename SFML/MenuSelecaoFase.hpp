#pragma once
#include "Menu.hpp"

class MenuSelecaoFase : public Menu {
private:
    bool voltar;
    int faseEscolhida;
    int numJogadores;

protected:
    void set_values();

public:
    MenuSelecaoFase();
    ~MenuSelecaoFase();

    void confirmar();
    bool getVoltar() const;
    int getFaseEscolhida() const;
    int getNumJogadores() const;
    void resetaFlags();
};