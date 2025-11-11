#pragma once

#include <SFML/Graphics.hpp>

namespace listas { class ListaEntidades; }

using namespace sf;

namespace Gerenciadores {

    class GerenciadorGrafico {
    private:
        static GerenciadorGrafico* uniqueInstance;
        RenderWindow* window;
        View camera;
        GerenciadorGrafico();
        ~GerenciadorGrafico();
    public:
        static GerenciadorGrafico& Instance();
        void desenharEnte(const Drawable& shape);
        void clearWindow(Color cor = Color::Black);
        void displayWindow();
        void desenhaTodos(listas::ListaEntidades* LE, Sprite* sp = NULL);       //coloco essa relação?
        void atualizarCamera(const Vector2f posMago);
        RenderWindow* getWindow() const;
        View getCamera() const;
    };
}

//Colocar executar no futuro?