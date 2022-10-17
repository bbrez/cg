#include "olcPixelGameEngine.h"

#include "rasterizacao.h"

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
void plotLine(int x1, int y1, int x2, int y2, const olc::Pixel& cor, olc::PixelGameEngine* e) {
    if (abs(y2 - y1) < abs(x2 - x1)) {
        if (x1 > x2) {
            std::swap(x1, x2);
            std::swap(y1, y2);
        };
        plotLineLow(x1, y1, x2, y2, cor, e);
    } else {
        if (y1 > y2) {
            std::swap(x1, x2);
            std::swap(y1, y2);
        }
        plotLineHigh(x1, y1, x2, y2, cor, e);
    }
}

namespace {
void plotLineV(int x, int y, int len, const olc::Pixel& cor, olc::PixelGameEngine* e) {
    for (auto i = 0; i < len; ++i) { e->Draw(x, y + i, cor); }
}

void plotLineH(int x, int y, int len, const olc::Pixel& cor, olc::PixelGameEngine* e) {
    for (auto i = 0; i < len; ++i) { e->Draw(x + i, y, cor); }
}

/**
 * @brief Função auxiliar para o algoritmo de reta do ponto médio
 * @param x1 x do ponto inicial
 * @param y1 y do ponto inicial
 * @param x2 x do ponto final
 * @param y2 y do ponto final
 * @param cor cor da reta a ser desenhada
 * @param e ponteiro para a engine
 */

void plotLineLow(int x1, int y1, int x2, int y2, const olc::Pixel& cor, olc::PixelGameEngine* e) {
    auto dx = x2 - x1;
    auto dy = y2 - y1;

    if (dx == 0) { //Reta é vertical
        plotLineV(x1, y1, dy, cor, e);
        return;
    }

    if (dy == 0) { //Reta é horizontal
        plotLineH(x1, y1, dx, cor, e);
        return;
    }

    auto y_inc = 1;

    if (dy < 0) {
        y_inc = -1;
        dy = -dy;
    }

    auto d = (2 * dy) - dx;
    auto incNE = 2 * (dy - dx);
    auto incE = 2 * dy;

    auto y = y1;

    for (auto x = x1; x <= x2; ++x) {
        e->Draw(x, y, cor);
        if (d > 0) {
            y += y_inc;
            d += incNE;
        } else {
            d += incE;
        }
    }
}

/**
 * @brief Função auxiliar para o algoritmo de reta do ponto médio
 * @param x1 x do ponto inicial
 * @param y1 y do ponto inicial
 * @param x2 x do ponto final
 * @param y2 y do ponto final
 * @param cor cor da reta a ser desenhada
 * @param e ponteiro para a engine
 */
void plotLineHigh(int x1, int y1, int x2, int y2, const olc::Pixel& cor, olc::PixelGameEngine* e) {
    auto dx = x2 - x1;
    auto dy = y2 - y1;

    if (dx == 0) {
        plotLineV(x1, y1, dy, cor, e);
        return;
    }

    if (dy == 0) {
        plotLineH(x1, y1, dx, cor, e);
        return;
    }

    auto x_inc = 1;
    if (dx < 0) {
        x_inc = -1;
        dx = -dx;
    }

    auto d = (2 * dx) - dy;
    auto incNE = 2 * (dx - dy);
    auto incE = 2 * dx;

    auto x = x1;

    for (auto y = y1; y <= y2; ++y) {
        e->Draw(x, y, cor);
        if (d > 0) {
            x += x_inc;
            d += incNE;
        } else {
            d += incE;
        }
    }
}
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
void inc_circle(int x_centro, int y_centro, int raio, olc::PixelGameEngine* e) {
    int x = raio, y = 0;
    olc::Pixel branco(0xff, 0xff, 0xff);
    olc::Pixel azul(0x89, 0xd2, 0xff);
    olc::Pixel amarelo(0xff, 0xf2, 0x00);
    olc::Pixel roxo(0x88, 0x00, 0x99);
    e->Draw(y + x_centro, -x + y_centro, branco);

    if (raio > 0) {
        e->Draw(x + x_centro, -y + y_centro, azul);
        e->Draw(-x + x_centro, y + y_centro, amarelo);
        e->Draw(-y + x_centro, x + y_centro, roxo);
    }

    int p = 1 - raio;
    while (x > y) {
        y++;
        if (p <= 0) {
            p = p + 2 * y + 1;
        } else {
            x--;
            p = p + 2 * y - 2 * x + 1;
        }

        if (x < y) { break; }

        e->Draw(x + x_centro, -y + y_centro, branco);
        e->Draw(-x + x_centro, -y + y_centro, azul);
        e->Draw(x + x_centro, y + y_centro, amarelo);
        e->Draw(-x + x_centro, y + y_centro, roxo);

        if (x != y) {
            e->Draw(y + x_centro, -x + y_centro, branco);
            e->Draw(-y + x_centro, -x + y_centro, azul);
            e->Draw(y + x_centro, x + y_centro, amarelo);
            e->Draw(-y + x_centro, x + y_centro, roxo);
        }
    }
}

#pragma endregion

#pragma region cohen_sutherland

/** 
     * Algoritmo de cohen-sutherland para realizar o clipping de uma reta
     * @param x1 coordenada x do primeiro ponto
     * @param y1 coordenada y do primeiro ponto
     * @param x2 coordenada x do segundo ponto
     * @param y2 coordenada y do segundo ponto
     */
void cohen_sutherland(int x1, int y1, int x2, int y2, olc::PixelGameEngine* e) {

    int cod1 = calcula_codigo(x1, y1);
    int cod2 = calcula_codigo(x2, y2);

    bool aceita = false;

    while (true) {
        if (cod1 == 0 && cod2 == 0) {
            aceita = true;
            break;
        } else if (cod1 & cod2) {
            break;
        } else {

            int cod_out; //verifica qual dos pontos esta fora da reta
            int x, y;    //novo x e y para realizar o clipping

            if (cod1 != 0) {
                cod_out = cod1;
            } else {
                cod_out = cod2;
            }

            if (cod_out & ACIMA) {
                // ponto esta acima do retangulo
                x = x1 + (x2 - x1) * (y_max - y1) / (y2 - y1);
                y = y_max;
            } else if (cod_out & ABAIXO) {
                // ponto esta abaixo do retangulo
                x = x1 + (x2 - x1) * (y_min - y1) / (y2 - y1);
                y = y_min;
            } else if (cod_out & DIREITA) {
                // ponto esta a direita do retangulo
                y = y1 + (y2 - y1) * (x_max - x1) / (x2 - x1);
                x = x_max;
            } else if (cod_out & ESQUERDA) {
                // ponto esta a esquerda do retangulo
                y = y1 + (y2 - y1) * (x_min - x1) / (x2 - x1);
                x = x_min;
            }

            if (cod_out == cod1) {
                x1 = x;
                y1 = y;
                cod1 = calcula_codigo(x1, y1);
            } else {
                x2 = x;
                y2 = y;
                cod2 = calcula_codigo(x2, y2);
            }
        }
    }

    //Se a linha foi aceita ela sera desenhada
    if (aceita) {
        olc::Pixel azul(0x89, 0xd2, 0xff);

        e->DrawLine(x1, y1, x2, y2, azul);
    } else {
        //std::cout << "linha rejeitada";
    }
}

namespace {
/**
     * Funcao para verificar em que area esta a reta
     * @param x coordenada x do ponto
     * @param y coordenada y do ponto
     * @return a area em que esta a reta
     */
int calcula_codigo(int x, int y) {

    //Inicializa a reta como dentro do retangulo
    int cod = DENTRO;

    if (x < x_min) // Se esta a esquerda do retangulo
        cod |= ESQUERDA;
    else if (x > x_max) // Se esta a direita do retangulo
        cod |= DIREITA;
    if (y < y_min) // Se esta abaixo do retangulo
        cod |= ABAIXO;
    else if (y > y_max) // Se esta acima do retangulo
        cod |= ACIMA;

    return cod;
}
} // namespace

#pragma endregion

#pragma region preenchimento

/**
 * Desenha o exterior de um polígono
 * @param poli poligono para ser desenhado
 * @param cor cor do poligono
 * @param e ponteiro para engine
*/
void desenha_poligono(poligono poli, const olc::Pixel& cor, olc::PixelGameEngine* e) {
    for (auto& ar : poli) {
        plotLine(ar.first.x(), ar.first.y(), ar.second.x(), ar.second.y(), cor, e);
    }
}

/**
 * Preenche um polígono de acordo com algoritmo de scanline
 * @param poli poligno para ser preenchido
 * @param cor cor para preencher
 * @param e ponteiro para engine
*/
void preenche_poligono(poligono poli, const olc::Pixel& cor, olc::PixelGameEngine* e) {
    et_t et;
    make_et(et, poli);

    auto y = et.begin()->first; // 1. Obtem a menor coordenada de y armazenada na ET
    std::vector<et_node> aet;   // 2. Inicializa a AET como vazia

    while (!aet.empty() || !et.empty()) { // 3. Repita até que a ET e a AET estejam vazias
        // 4. Transfere do bucket y de ET para AET as arestas cujo ymin = y, mantendo aet ordenada em x
        if (et.contains(y)) {
            aet.insert(aet.end(), et.at(y).begin(), et.at(y).end());
            et.erase(y);
        }

        std::sort(aet.begin(), aet.end(),
                  [](et_node a, et_node b) { return a.x_y_min < b.x_y_min; });

        // 5. Retira os lados que possuem y = ymax
        std::erase_if(aet, [y](et_node no) { return y == no.y_max; });

        for (auto i = 0; !aet.empty() && (i < aet.size() - 1); i += 2) {
            // 6. Desenhe os pixels do bloco na linha de varredura y usando pares de coordenadas x da AET;
            plotLine(ceil(aet[i].x_y_min), y, ceil(aet[i + 1].x_y_min), y, cor, e);
        }

        y += 1; // 7. Incrementa y de 1;
        for (auto& no : aet) {
            // 8. Para cada aresta não vertical que permanece na AET, atualiza x para o novo y
            no.x_y_min = no.x_y_min + no.inc_x;
        }

        //9. Como o passo anterior pode ter desordenado a AET, reordena a AET
        //Desnecessário, pois ordenamos a AET entre o passo 4 e 5
        //std::sort(aet.begin(), aet.end(),
        //          [](et_node a, et_node b) { return a.x_y_min > b.x_y_min; });
    }
}

/**
 * @brief o ponto com menor y de uma aresta
 * @param ar aresta
 * @return ponto
*/
auto menor_y(aresta ar) -> ponto { return ar.first.y() < ar.second.y() ? ar.first : ar.second; }

/**
 * @brief retorna o ponto com maior y de uma reta
 * @param ar 
 * @return ponto 
 */
auto maior_y(aresta ar) -> ponto { return ar.first.y() > ar.second.y() ? ar.first : ar.second; }

namespace {
/**
 * @brief monta uma ET a partir de um polígono 
 * @param et referência à ET a ser montada
 * @param poli referência constante ao polígono
 */
void make_et(et_t& et, const poligono& poli) {
    auto calc_ang = [](aresta ar) -> float {
        return static_cast<float>(ar.first.x() - ar.second.x()) /
               static_cast<float>(ar.first.y() - ar.second.y());
    };

    for (const aresta& a : poli) {
        et_node no{.y_max = maior_y(a).y(),
                   .x_y_min = static_cast<float>(menor_y(a).x()),
                   .inc_x = calc_ang(a)};
        if (et.contains(menor_y(a).y())) {
            et[menor_y(a).y()].emplace_back(no);
        } else {
            et[menor_y(a).y()] = {no};
        }
    }

    for (auto& no : et) {
        std::sort(no.second.begin(), no.second.end(),
                  [](et_node a, et_node b) { return a.x_y_min > b.x_y_min; });
    }
}
} // namespace

#pragma endregion