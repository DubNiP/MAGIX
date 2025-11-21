#pragma once
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics.hpp>
#include "Mago.hpp"
#include "Menu.hpp"
#include "Subject.hpp"

// Gerenciador de Eventos com apoio do padrão de projeto Observer.

namespace Gerenciador {

    class GerenciadorEvento : public subject {
    private:
        static GerenciadorEvento* pEvento;
        entidades::personagens::Mago* pMago1;
        entidades::personagens::Mago* pMago2;
        bool prevUp;
        bool prevDown;
        bool prevEnter;

        GerenciadorEvento();

    public:
        ~GerenciadorEvento();

        static GerenciadorEvento* getGerenciadorEvento();

        void setMago1(entidades::personagens::Mago* pj);
        void setMago2(entidades::personagens::Mago* pj);

        void executar();
        void executarMenu();
        void soltaTeclas();
        bool verificarEventosJanela(RenderWindow* window);


    };

}