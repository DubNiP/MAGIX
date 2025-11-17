#pragma once
#include "Menu.hpp"

class MenuPrincipal : public Menu {
private:
    bool sair;
    bool iniciar;

protected:
    void set_values();

public:
    MenuPrincipal();
    ~MenuPrincipal();

    void confirmar();
    bool getIniciar() const;
    bool getSair() const;
    void resetaFlags();
};