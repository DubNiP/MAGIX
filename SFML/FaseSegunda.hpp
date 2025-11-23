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
		void carregarPlataforma(int i, bool ativ, float temp);
        void criarEspinho();
       
        void criarBlocos();
        void carregarFundo();
        Vector2f getPosicaoInicialJogador() const;


    public:
        FaseSegunda(entidades::personagens::Mago* pJog1, entidades::personagens::Mago* pJog2);
        ~FaseSegunda();
    };

}