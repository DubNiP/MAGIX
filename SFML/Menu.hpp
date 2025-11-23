#pragma once
#include "Ente.hpp"
#include <SFML/Graphics.hpp>
#include <vector>

namespace Gerenciadores { class GerenciadorGrafico; }

using namespace sf;
using namespace std;

class Menu: public Ente {
protected:
    int pos;
    int posMin;
    int posMax;
    Font font;
    vector<Text> texts;

    virtual void set_values() = 0;

public:
    Menu();
    virtual ~Menu();

    void executar();
    void moverBaixo();
    void moverCima();

    virtual void confirmar() = 0;

    void draw_menu();

    void reseta();
    const int getPosicao() const;
};