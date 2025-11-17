#pragma once
#include "Menu.hpp"

class MenuPause : public Menu {
private:
    bool continuar;
    bool voltarMenu;

protected:
    void set_values();

public:
    MenuPause();
    ~MenuPause();

    void confirmar();
    bool getContinuar() const;
    bool getVoltarMenu() const;
    void resetaFlags();
};