#ifndef __RASTERIZACAO_H__
#define __RASTERIZACAO_H__
#include "olcPixelGameEngine.h"

#pragma region ponto_medio_reta
/**
 * @brief Algoritmo de reta do ponto médio
 * @param x1 x do ponto inicial para a reta
 * @param y1 y do ponto inicial para a reta
 * @param x2 x do ponto final para a reta
 * @param y2 y do ponto final para a reta
 * @param cor cor da reta a ser desenhada
 * @param e ponteiro para engine
 */
void plotLine(int x1, int y1, int x2, int y2, const olc::Pixel& cor, olc::PixelGameEngine* e);

namespace { /**
 * @brief Função auxiliar para o algoritmo de reta do ponto médio
 * @param x1 x do ponto inicial
 * @param y1 y do ponto inicial
 * @param x2 x do ponto final
 * @param y2 y do ponto final
 * @param cor cor da reta a ser desenhada
 * @param e ponteiro para a engine
 */
void plotLineLow(int x1, int y1, int x2, int y2, const olc::Pixel& cor, olc::PixelGameEngine* e);
/**
 * @brief Função auxiliar para o algoritmo de reta do ponto médio
 * @param x1 x do ponto inicial
 * @param y1 y do ponto inicial
 * @param x2 x do ponto final
 * @param y2 y do ponto final
 * @param cor cor da reta a ser desenhada
 * @param e ponteiro para a engine
 */
void plotLineHigh(int x1, int y1, int x2, int y2, const olc::Pixel& cor, olc::PixelGameEngine* e);
} // namespace

#pragma endregion

#pragma region ponto_medio_circulo
/**
 * @brief Algoritmo de circulo do ponto médio
 * @param x_centro x para o centro do circulo
 * @param y_centro y para o centro do circulo
 * @param raio raio do circulo
 * @param e ponteiro para engine
 */
void inc_circle(int x_centro, int y_centro, int raio, olc::PixelGameEngine* e);

#pragma endregion

#pragma region cohen_sutherland
//Par de pontos que definem o retangulo para recorte
const int x_max = 300;
const int y_max = 300;
const int x_min = 200;
const int y_min = 200;

//Define as areas em que as retas podem estar em relacao ao retangulo
const int DENTRO = 0;
const int ESQUERDA = 1;
const int DIREITA = 2;
const int ABAIXO = 4;
const int ACIMA = 8;

/** 
     * Algoritmo de cohen-sutherland para realizar o clipping de uma reta
     * @param x1 coordenada x do primeiro ponto
     * @param y1 coordenada y do primeiro ponto
     * @param x2 coordenada x do segundo ponto
     * @param y2 coordenada y do segundo ponto
     */
void cohen_sutherland(int x1, int y1, int x2, int y2, olc::PixelGameEngine* e);

namespace {
int calcula_codigo(int x, int y);
}

#pragma endregion

#pragma region preenchimento

/**
 * @brief Struct que define um ponto com coordenadas X,Y
 */
struct ponto {

public:

    ponto() = default;

    ponto(int x, int y) : coords(x, y) {}

    auto x() const { return coords.first; }

    auto y() const { return coords.second; }

private:

    std::pair<int, int> coords;
};

/**
 * @brief Tipo que define uma aresta
 */
typedef std::pair<ponto, ponto> aresta;
/**
 * @brief Tipo que define um polígono
 */
typedef std::vector<aresta> poligono;

/**
 * Desenha o exterior de um polígono
 * @param poli poligono para ser desenhado
 * @param cor cor do poligono
 * @param e ponteiro para engine
*/
void desenha_poligono(poligono poli, const olc::Pixel& cor, olc::PixelGameEngine* e);

/**
 * Preenche um polígono de acordo com algoritmo de scanline
 * @param poli poligno para ser preenchido
 * @param cor cor para preencher
 * @param e ponteiro para engine
*/
void preenche_poligono(poligono poli, const olc::Pixel& cor, olc::PixelGameEngine* e);
/**
 * @brief o ponto com menor y de uma aresta
 * @param ar aresta
 * @return ponto
*/
auto menor_y(aresta ar) -> ponto;
/**
 * @brief retorna o ponto com maior y de uma reta
 * @param ar 
 * @return ponto 
 */
auto maior_y(aresta ar) -> ponto;

namespace {
/**
 * @brief Struct para o nó de uma ET e AET
 */
struct et_node {
    int y_max;
    float x_y_min;
    float inc_x;
};

/**
 * @brief Tipo que define uma ET
 */
typedef std::map<int, std::vector<et_node>> et_t;

/**
 * @brief monta uma ET a partir de um polígono 
 * @param et referência à ET a ser montada
 * @param poli referência constante ao polígono
 */
void make_et(et_t& et, const poligono& poli);
} // namespace

#pragma endregion
#endif