#pragma once
#include "Obstaculo.hpp"

namespace entidades {
    namespace obstaculos {

        class Bloco : public Entidade {
        private:
            float larguraB;
            float alturaB;
        public:
            Bloco(Vector2f pos, Vector2f tam);
            Bloco(const Bloco& copia, Vector2f pos, Vector2f tam);
            ~Bloco();

            Entidade* clone(Vector2f pos, Vector2f tam) const;
            void executar();
            void salvar() { return; }

            void carregarSprite();
            const float getLargura() const;
            const float getAltura()  const;

        };

    }
}