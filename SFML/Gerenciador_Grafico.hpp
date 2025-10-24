#pragma once

#include <SFML/Graphics.hpp>


class ListaEntidades;

using namespace sf;

class GerenciadorGrafico {
private:
    RenderWindow* window;
public:
    GerenciadorGrafico();
    ~GerenciadorGrafico();
    void desenharEnte(const Drawable &shape);
    void clearWindow(Color cor = Color::Black);                     
    void displayWindow();
    void desenhaTodos(ListaEntidades* LE, Color cor = Color::Black);
    RenderWindow* getWindow() const;
};