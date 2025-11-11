#pragma once
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics.hpp>
#include "Mago.hpp"
#include "Menu.hpp"

namespace Gerenciador {

    class GerenciadorEvento {
    private:
        static GerenciadorEvento* pEvento;
        entidades::personagens::Mago* pMago;
        Menu* pMenu;

        bool prevUp;
        bool prevDown;
        bool prevEnter;

        GerenciadorEvento();

    public:
        ~GerenciadorEvento();

        static GerenciadorEvento* getGerenciadorEvento();

        void setMago(entidades::personagens::Mago* pj);
        void setMenu(Menu* pm);

        void executar();
        void executarMenu();

    };

}