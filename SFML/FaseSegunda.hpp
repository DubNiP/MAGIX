#pragma once
#include "Fase.hpp"

namespace fases {

    class FaseSegunda : public Fase {
    private:
        const int maxChefoes;

    protected:
        void criarInimigos() override;
        void criarObstaculo() override;
        void criarChefoes();
        void criarObsMedios();
        void criarPlataformas();
        void criarAlavancas();
        void criarBlocos() override;
        void carregarFundo() override;

    public:
        FaseSegunda(entidades::personagens::Jogador* pJog);
        ~FaseSegunda();
    };

}