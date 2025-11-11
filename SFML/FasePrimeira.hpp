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


		void criarTeias();

		void carregarFundo();

	public:
		FasePrimeira(entidades::personagens::Mago* pJog);         //FASE ESTÁ CONHECENDO Mago AQUI, E NO DIAGRAMA NÃO TEM NADA, PODE?
		~FasePrimeira();
	};

}