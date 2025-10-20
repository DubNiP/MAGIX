#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
class Ente;

class GerenciadorGrafico {
public:
    static GerenciadorGrafico* getInstancia();
    void clearWindow();
    void drawWindow(const Drawable& corpo);
    void displayWindow();
    RenderWindow* getWindow();
    void executar();
    ~GerenciadorGrafico();

private:
    GerenciadorGrafico();
    static GerenciadorGrafico* instancia;
    RenderWindow* window;
};