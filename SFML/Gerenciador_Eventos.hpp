#pragma once
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics.hpp>
#include "Mago.hpp"
#include "Menu.hpp"
#include "Subject.hpp"
#include <deque>

namespace Gerenciador {

    class GerenciadorEvento : public subject {
    private:
        static GerenciadorEvento* pEvento;
        entidades::personagens::Mago* pMago;
        bool prevUp;
        bool prevDown;
        bool prevEnter;

        // fila local de eventos coletados da janela
        deque<sf::Event> eventQueue;

        GerenciadorEvento();

    public:
        ~GerenciadorEvento();

        static GerenciadorEvento* getGerenciadorEvento();

        void setMago(entidades::personagens::Mago* pj);

        void executar();
        void executarMenu();
        void soltaTeclas();

        // coleta eventos da janela e os armazena internamente
        // retorna false se janela foi fechada
        bool verificarEventosJanela(RenderWindow* window);

        // APIs para consumir a fila de eventos coletada
        bool temEvento() const;
        bool proximoEvento(sf::Event& out);
    };

}