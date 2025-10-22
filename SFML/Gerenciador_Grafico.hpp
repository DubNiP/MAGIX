#pragma once

#include <SFML/Graphics.hpp>
#include "Entidade.hpp"

using namespace sf;
class Ente;

class GerenciadorGrafico {
private:
    RenderWindow* window;
public:
    GerenciadorGrafico();
    ~GerenciadorGrafico();
    //void desenharEnte(Ente* pE);
    void clearWindow(Color cor = Color::Black);
    void drawWindow(const Drawable& corpo);
    void displayWindow();
    RenderWindow* getWindow() const;
};