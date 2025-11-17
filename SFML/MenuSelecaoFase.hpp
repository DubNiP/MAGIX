#pragma once
#include "Menu.hpp"

class MenuSelecaoFase : public Menu {
private:
    bool voltar;
    int faseEscolhida;

protected:
    void set_values();

public:
    MenuSelecaoFase();
    ~MenuSelecaoFase();

    void confirmar();
    bool getVoltar() const;
    int getFaseEscolhida() const;
    void resetaFlags();
};