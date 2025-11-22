#pragma once
#include <SFML/Graphics.hpp>
#include "Gerenciador_Grafico.hpp"
#include "Gerenciador_Colisoes.hpp"
#include "Mago.hpp"
#include "Espinho.hpp"
#include "Ente.hpp"
#include "Projetil.hpp"
#include "ListaEntidades.hpp"
#include "Bloco.hpp"
#include "Plataforma.hpp"
#include "Sapo.hpp"
#include "Alavanca.hpp"
#include "Gerenciador_Eventos.hpp"


using namespace sf;

namespace fases {

	class Fase: public Ente {
	protected:
		static listas::ListaEntidades lista_ents;
		Gerenciadores::GerenciadorColisoes GC;
		entidades::personagens::Mago* jog;
		Texture* textFundo;
		Sprite* spriteFundo;
		bool faseIniciada;
		bool pause;
		bool cenarioCriado;
		virtual void criarInimigos() = 0;
		virtual void criarObstaculo() = 0;
		virtual void criarBlocos() = 0;
		virtual void criarPlataformas() = 0;
		void criarCenario();                            //fazer ser virtual no futuro??? (diagrama não deixa a princípio)
		virtual void carregarFundo() = 0;
		virtual Vector2f getPosicaoInicialJogador() const = 0;
		virtual void criarPlataforma(int i, bool ativ) = 0;
		Entidade* criaEntidade(Entidade* e);
		void limparCenario();
	public:
		Fase(entidades::personagens::Mago* pJog);
		~Fase();
		void criarProjetil(Vector2f pos, bool dir, bool bond);
		void inicializar();
		void executar();         //nao foi implementado executar nas derivadas de fase. Aqui existe uma dúvida em relação a esse executar
		void resetar();
		const bool getFaseIniciada() const;
		const bool getPause() const;

		listas::ListaEntidades* getListaEntidades();

		void carregarSave(const std::string& caminho);
		void setarEntidade(Entidade* ent, Vector2f posL, bool emTerra,
						   bool emAcl, Vector2f vel, Vector2f velInit, bool olhandoDir);
	};

}