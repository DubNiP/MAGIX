#pragma once
#include "Menu.hpp"

class MenuPause : public Menu {
private:
    bool continuar;
    bool voltarMenu;
	bool salvar;
protected:
    void set_values();

public:
    MenuPause();
    ~MenuPause();

    void confirmar();
    bool getContinuar() const;
    bool getVoltarMenu() const;
	bool getSalvar() const;
	void setSalvar(bool s);
    void resetaFlags();
};