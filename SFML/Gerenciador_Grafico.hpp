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
    void desenhaTodos(ListaEntidades* LE, Sprite* sp = NULL );       //coloco essa relação?
    RenderWindow* getWindow() const;
};

//Colocar executar no futuro?