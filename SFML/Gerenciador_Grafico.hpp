#pragma once

#include <SFML/Graphics.hpp>


/*    TROCAR O NOME DO ARQUIVO, É GERENCIADOR_GRAFICO E NAO GERENCIADOR.GRAFICO   (no cpp tbm)         */


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