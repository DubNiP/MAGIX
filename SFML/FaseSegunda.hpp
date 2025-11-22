#pragma once
#include "Fase.hpp"

namespace fases {

    class FaseSegunda : public Fase {
    private:
        const int maxChefoes;

    protected:
        void criarInimigos();
        void criarChefoes();
        void criarSapos();
        void criarObstaculo();
        void criarPlataformas();
		void criarPlataforma(int i, bool ativ);
        void criarEspinho();
       
        void criarBlocos();
        void carregarFundo();
        Vector2f getPosicaoInicialJogador() const;


    public:
        FaseSegunda(entidades::personagens::Mago* pJog);
        ~FaseSegunda();
    };

}