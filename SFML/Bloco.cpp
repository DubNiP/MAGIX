#include "Bloco.hpp"

namespace entidades {
    namespace obstaculos {

        Bloco::Bloco(Vector2f pos, Vector2f tam)
            : Entidade(pos, Vector2f(0.f, 0.f), true),
            larguraB(tam.x),
            alturaB(tam.y)
        {
            id = 9;
            carregarSprite();
        }

        Bloco::~Bloco() {
        }

        void Bloco::executar() {
            attPos();
        }

        void Bloco::salvar() {
			tempBuffer.str("");
			tempBuffer.clear();

            salvarDataBuffer();

            buffer.open("Save/save.txt", ios::out | ios::app);

            if (!buffer.is_open()) {
                cerr << "Arquivo não pode ser aberto" << endl;
                fflush(stdin);
                return;
            }

			buffer << tempBuffer.str();

			buffer.close();
		}

        void Bloco::salvarDataBuffer() {
			Entidade::salvarDataBuffer();

            tempBuffer << larguraB << " "
                << alturaB << "\n";
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