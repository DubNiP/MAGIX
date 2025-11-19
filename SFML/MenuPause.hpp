#pragma once
#include "Menu.hpp"
#include "ListaEntidades.hpp"

class MenuPause : public Menu {
private:
    bool continuar;
    bool voltarMenu;
    listas::ListaEntidades* lista_ents;
protected:
    void set_values();

public:
    MenuPause();
    ~MenuPause();

    void confirmar();
    bool getContinuar() const;
    bool getVoltarMenu() const;
    void resetaFlags();

    void setListaEntidades(listas::ListaEntidades* l);
    listas::ListaEntidades* getListaEntidades() const;
};