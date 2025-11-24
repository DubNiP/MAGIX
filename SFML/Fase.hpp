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
		entidades::personagens::Mago* jog1;
		entidades::personagens::Mago* jog2;
		bool faseIniciada;
		bool pause;
		bool cenarioCriado;
		bool doisJog;

		//padrão de projeto Template Method, criar cenário chama essas 5 funções dentro dele.
		virtual void criarInimigos() = 0;
		virtual void criarObstaculo() = 0;
		virtual void criarBlocos() = 0;
		virtual void criarPlataformas() = 0;
		virtual void carregarFundo() = 0;
		void criarCenario();                           
		virtual Vector2f getPosicaoInicialJogador() const = 0;
		virtual void carregarPlataforma(int i, bool ativ, float temp) = 0;
		Entidade* criaEntidade(Entidade* e);
		void limparCenario();
	public:
		Fase(entidades::personagens::Mago* pJog1, entidades::personagens::Mago* pJog2);
		~Fase();
		void criarProjetil(Vector2f pos, bool dir, bool bond);
		void inicializar();
		void executar();
		void resetar();

		void setdoisJog(bool doisJ);

		const bool getFaseIniciada() const;
		const bool getPause() const;

		listas::ListaEntidades* getListaEntidades();

		void carregarSave(const std::string& caminho);
		void setarEntidade(Entidade* ent, Vector2f posL, bool emTerra,
						   bool emAcl, Vector2f vel, Vector2f velInit, bool olhandoDir);
	};

}