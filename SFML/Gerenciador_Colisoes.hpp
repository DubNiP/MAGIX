#pragma once

#include "Entidade.hpp"
#include "Mago.hpp"
#include "Inimigo.hpp"
#include "Teia.hpp"
#include "Plataforma.hpp"
#include "Projetil.hpp"
#include "Saida.hpp"
#include "Bloco.hpp"
#include <vector>
#include <list>
#include <set>

using namespace std;


namespace Gerenciadores {

    class GerenciadorColisoes {
    private:
        vector<entidades::personagens::Inimigo*>  LIs;
        list<entidades::obstaculos::Obstaculo*>  LOs;
        list<entidades::obstaculos::Bloco*> LBs;
        set<Projetil*>    LPs;  
        entidades::personagens::Mago* pJog1;
        RenderWindow* window;
        bool faseConcluida;
    public:
        GerenciadorColisoes(entidades::personagens::Mago* pJog = NULL,RenderWindow* window = NULL);
        ~GerenciadorColisoes();
        
        const bool getFaseConcluida() const;

        const bool verificarColisao(Entidade* pe1, Entidade* pe2) const;
        void colidiu(Entidade* pe1, Entidade* pe2);
        bool estaSobre(const FloatRect& obst, const FloatRect& ent, Entidade* b, float folga = 6.f);

        void tratarColisoesJogsObstacs();
        void tratarColisoesJogsBlocos();
        void tratarColisoesJogsInimgs();
        void tratarColisoesJogsProjeteis();

        void tratarColisoesInimgsObstacs();
        void tratarColisoesInimgsBlocos();
        void tratarColisoesProjeteisObstacs();
        void tratarColisoesProjeteisInimgs();
        void tratarColisoesInimgs();

        void incluirInimigo(entidades::personagens::Inimigo* pInimigo);
        void incluirObstaculo(entidades::obstaculos::Obstaculo* pObstaculo);
        void incluirBloco(entidades::obstaculos::Bloco* pBloco);
        void incluirProjetil(Projetil* pProjetil);

        void limparObstaculos();
        void limparBlocos();
        void limparInimigos();
        void limparProjetis();
        void removerMortos();

        void executar();

        void setJog(entidades::personagens::Mago* pJog);
        void setWindow(RenderWindow* win);

        void limiteDeTela();
        void limiteDeTelaMago(float X, float Y);
        void limiteDeTelaProjeteis(float X, float Y);
    };

}