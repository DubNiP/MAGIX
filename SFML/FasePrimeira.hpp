#pragma once
#include "Fase.hpp"
#include "Golem.hpp"
#include "Mago.hpp"
#include "Plataforma.hpp"

namespace fases {

	class FasePrimeira : public Fase {
	private:
		const int maxGolems;
	protected:
		void criarInimigos();
		void criarObstaculo();
		void criarBlocos();

		void criarGolems();
		void criarSapos();
		
		void criarTeias();

		void criarPlataformas();
		void carregarPlataforma(int i, bool ativ, float temp);

		void carregarFundo();

		Vector2f getPosicaoInicialJogador() const;

	public:
		FasePrimeira(entidades::personagens::Mago* pJog1, entidades::personagens::Mago* pJog2 = NULL);
		~FasePrimeira();
	};

}