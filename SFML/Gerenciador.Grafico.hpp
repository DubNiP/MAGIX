#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
class Ente;

class GerenciadorGrafico {
public:
    void clearWindow(Color cor = Color::Black);
    void drawWindow(const Drawable& corpo);
    void displayWindow();
    RenderWindow* getWindow();
    ~GerenciadorGrafico();
    GerenciadorGrafico();
    //void desenharEnte(Ente* pE);

private:
    RenderWindow* window;
};