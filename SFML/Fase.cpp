#include "Fase.hpp"
#include <random>

using namespace fases;  


/*AQUI EM FASE TEMOS UM ERRO:
O METODO CRIAR PLATAFORMA EXISTE EM FASE MAS DEVERIA EXISTIR SEPARADAMENTE PARA AS FASES,
E O RAFA TÁ CRIANDO DIRETO EM CRIAR OBSTACULO NA FASE 2*/

Fase::Fase(entidades::personagens::Mago* pJog1, entidades::personagens::Mago* pJog2):
    Ente(),
    lista_ents(),
    GC(),
    jog1(pJog1),
    jog2(pJog2),
    textFundo(NULL),
    spriteFundo(NULL),
    faseIniciada(false),
    pause(false),
    cenarioCriado(false),
    doisJog(false)
{
    GC.setJog1(pJog1);
    if (pJog2) { 
        GC.setJog2(pJog2);
    }
}

Fase::~Fase() {
    GC.limparObstaculos();
    GC.limparInimigos();
    GC.limparProjetis();
    GC.limparBlocos();

    lista_ents.limparPreservando(jog1, jog2);           //estranho..               //preserva os jogadores porque não estão agregados a fase.


    if (spriteFundo) {
        delete spriteFundo;
        spriteFundo = NULL;
    }
    if (textFundo) {
        delete textFundo;
        textFundo = NULL;
    }
    
    jog1 = NULL;
    jog2 = NULL;
}

void Fase::criarSapos() {
    vector<Vector2f>v;
    v.push_back(Vector2f(300.f, 250.f));
    v.push_back(Vector2f(400.f, 250.f));
    v.push_back(Vector2f(200.f, 250.f));
    v.push_back(Vector2f(1190.f, 180.f));
    
    uniform_int_distribution<int> dist2(0, 1);
    int i = dist2(rng) + 3;
    while (i--) {
        uniform_int_distribution<int> dist2(0, 50);
        int j = dist2(rng) % v.size();
        criaEntidade(new entidades::personagens::Sapo(v[j], jog1, Vector2f(20.f, 70.f)));
        v[j] = v.back();
        v.pop_back();
    }
}

void Fase::criarPlataformas() {

    auto* plat1 = dynamic_cast<entidades::obstaculos::Plataforma*>(criaEntidade(new entidades::obstaculos::Plataforma(Vector2f(400.f, 588.f), Vector2f(200.f, 20.f), false, 90.f, 5.f)));
    auto* plat2 = dynamic_cast<entidades::obstaculos::Plataforma*>(criaEntidade(new entidades::obstaculos::Plataforma(Vector2f(760.f, 380.f), Vector2f(220.f, 20.f), false, 100.f, 5.f)));

    criaEntidade(new entidades::obstaculos::Alavanca(Vector2f(1100.f, 670.f), Vector2f(30.f, 50.f), plat1));
    criaEntidade(new entidades::obstaculos::Alavanca(Vector2f(1030.f, 120.f), Vector2f(30.f, 50.f), plat2));
}

void Fase::criarCenario() {
 
    GC.limparObstaculos();
    GC.limparInimigos();
    GC.limparProjetis();
    GC.limparBlocos();

   lista_ents.limparPreservando(jog1, jog2);        //estranho..

    carregarFundo();

    Vector2f posInicial = getPosicaoInicialJogador();

    if (jog1) {
        jog1->reseta(posInicial, 15, 0);

		jog1->setFaseAtual(this);
        lista_ents.incluir(jog1);
    }

    if (jog2 && doisJog) {
        jog2->reseta(posInicial, 15, 0);

        jog2->setFaseAtual(this);
        lista_ents.incluir(jog2);
        GC.setJog2(jog2);
    }
    else {
        GC.setJog2(NULL);
    }


    //padrão de projeto Template Method
    carregarFundo();
    criarObstaculo();
    criarInimigos();
    criarBlocos();
}

Vector2f Fase::getPosicaoInicialJogador() const {
    return Vector2f(160.f, 630.f);
}

Entidade* Fase::criaEntidade(Entidade* e) {
    if (e) {

        lista_ents.incluir(e);

        if (auto* ob = dynamic_cast<entidades::obstaculos::Obstaculo*>(e)) {
            GC.incluirObstaculo(ob);
        }
        else if (auto* ini = dynamic_cast<entidades::personagens::Inimigo*>(e)) {
            GC.incluirInimigo(ini);
        }
        else if (auto* prj = dynamic_cast<entidades::Projetil*>(e)) {
            GC.incluirProjetil(prj);
        }
        else if (auto* bloco = dynamic_cast<entidades::obstaculos::Bloco*>(e)) { 
            GC.incluirBloco(bloco);
        }

        return e;
    }
    return NULL;
}


void Fase::inicializar() {
    if (!cenarioCriado) {
        criarCenario();
        cenarioCriado = true;
    }
}

void Fase::executar() {
    inicializar();
    lista_ents.retomarTodos();                                             //Despausa os clocks das entidades.
    pause = false;
    if (pGG) {
        GC.setWindow(pGG->getWindow());
        RenderWindow* window = pGG->getWindow();
        Event event;
        faseIniciada = true;
        bool teclaEscAnterior = false;
        while (window && window->isOpen() && jog1 && jog1->getVidas() > 0 && !GC.getFaseConcluida()) {        //Enquanto as vidas do jogador1 > 0 e a fase não ser concluída..
            pGG->atualizarCamera(jog1->getPos());
		    View cam = pGG->getCamera();

            window->setView(cam);
            
            while (window->pollEvent(event)) {          //Talvez chamar função do GE aqui..
                if (event.type == Event::Closed) {
                    window->close();
                    return;
                }
            }
            bool teclaEsc = Keyboard::isKeyPressed(Keyboard::Escape);
            if (teclaEsc && !teclaEscAnterior) {
                pause = true;
                return; 
            }
            teclaEscAnterior = teclaEsc;

            Gerenciador::GerenciadorEvento::getGerenciadorEvento()->executar();
            lista_ents.executarTodos();
            GC.executar();

            if (jog2 && jog2->getVidas() <= 0) {
                lista_ents.excluir(jog2);
                Gerenciador::GerenciadorEvento::getGerenciadorEvento()->setMago2(NULL);
                GC.setJog2(NULL);
                doisJog = false;
            }

            pGG->desenhaTodos(&lista_ents,spriteFundo);   
        }
        jog1->setConcluiuFase(GC.getFaseConcluida());
    }
}

void Fase::resetar() {
    cenarioCriado = false;
    faseIniciada = false;
    inicializar();
}

void Fase::criarProjetil(Vector2f pos, bool dir, bool bond) {
    criaEntidade(new entidades::Projetil(pos, dir, bond));
}

void Fase::setdoisJog(bool doisJ) {
    doisJog = doisJ;
}

const bool Fase::getFaseIniciada() const {
    return faseIniciada;
}

const bool Fase::getPause() const {
    return pause;
}

listas::ListaEntidades* Fase::getListaEntidades() {
    return &lista_ents;
}