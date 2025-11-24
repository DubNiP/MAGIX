#include "Bloco.hpp"

namespace entidades {
    namespace obstaculos {

        Bloco::Bloco(Vector2f pos, Vector2f tam)
            : Entidade(pos, Vector2f(0.f, 0.f), true),
            larguraB(tam.x),
            alturaB(tam.y)
        {
            carregarSprite();
        }

        Bloco::Bloco(const Bloco& copia,Vector2f pos, Vector2f tam):                      //padrão de projeto Prototype.
            Entidade(pos, copia.vel, true),
            larguraB(tam.x),
            alturaB(tam.y)
        {
            textura = new Texture();
            *textura = *copia.textura;

            pSprite->setTexture(*textura, true);
            pSprite->setTextureRect(IntRect(0, 0, (int)larguraB, (int)alturaB));
        }

        Bloco::~Bloco() {
        }

        Entidade* Bloco::clone(Vector2f pos, Vector2f tam) const {                        //padrão de projeto Prototype.

            return new Bloco(*this,pos,tam);
        }

        void Bloco::executar() {
            gravidade();
            vel.y = 0.f;
            attPos();
        }

        void Bloco::carregarSprite() {
            if (!carregarTexturaSprite("Textures/DungeonTile.png", true, false)) {
                throw "Textura não carregada";
            }
            if (Sprite* sp = getSprite()) {
                sp->setTextureRect(IntRect(0, 0, static_cast<int>(larguraB), static_cast<int>(alturaB)));
            }
            setScale(Vector2f(1.f, 1.f));
            setPos(pos);
        }

        const float Bloco::getLargura() const {
            return larguraB;
        }
        const float Bloco::getAltura()  const {
            return alturaB;
        }

    }
}