#pragma once

#include <SFML/Graphics.hpp>

namespace listas { class ListaEntidades; }

using namespace sf;

namespace Gerenciadores {

    class GerenciadorGrafico {
    private:
        static GerenciadorGrafico* pGrafico;
        RenderWindow* window;
        View camera;
        bool segundaTela;
        GerenciadorGrafico();
        ~GerenciadorGrafico();
    public:
        static GerenciadorGrafico& getGG();
        void desenharEnte(const Drawable& shape);
        void clearWindow(Color cor = Color::Black);
        void displayWindow();
        void desenhaTodos(listas::ListaEntidades* LE, Sprite* sp = NULL);
        void atualizarCamera(const Vector2f posMago);
        void resetarCamera();
		void setSegundaTela(bool val);

        // GETTERS:
        RenderWindow* getWindow() const;
        View getCamera() const;
    };
}

