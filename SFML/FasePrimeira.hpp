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
		void criarPlataforma(int i, bool ativ);

		void carregarFundo();

		Vector2f getPosicaoInicialJogador() const;

	public:
		FasePrimeira(entidades::personagens::Mago* pJog);        
		~FasePrimeira();
	};

}