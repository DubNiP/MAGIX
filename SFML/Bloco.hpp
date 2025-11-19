#pragma once
#include "Obstaculo.hpp"

namespace entidades {
    namespace obstaculos {

        class Bloco : public Entidade {
        private:
            const float larguraB;
            const float alturaB;
        public:
            Bloco(Vector2f pos, Vector2f tam);
            ~Bloco();

            void executar();
            void salvar();
            void salvarDataBuffer();

            void carregarSprite();
            const float getLargura() const;
            const float getAltura()  const;

        };

    }
}