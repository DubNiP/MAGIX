#pragma once
#include "Menu.hpp"

class MenuGameOver : public Menu {
private:
    bool reiniciar;
    bool voltarMenu;

protected:
    void set_values();

public:
    MenuGameOver();
    ~MenuGameOver();

    void confirmar();
    bool getReiniciar() const;
    bool getVoltarMenu() const;
    void resetaFlags();
};