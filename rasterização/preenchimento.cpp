// A biblioteca deve ser baixada do link a seguir e estar disponível na mesma pasta que o arquivo fonte
// https://raw.githubusercontent.com/OneLoneCoder/olcPixelGameEngine/master/olcPixelGameEngine.h
// o comando de compilação é `g++ preenchimento.cpp rasterizacao.cpp -o preenchimento.exe  -luser32 -lgdi32 -lopengl32 -lgdiplus -lShlwapi -ldwmapi -lstdc++fs -static -std=c++20`
#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "rasterizacao.h"

class PreenchimentoPoligonoApp : public olc::PixelGameEngine {
public:

    explicit PreenchimentoPoligonoApp(poligono poli) : poli(poli) {
        this->sAppName = "Preenchimento de Polígono";

        // Organiza as arestas por menor Y primeiro
        std::sort(poli.begin(), poli.end(), [](aresta a, aresta b) {
            auto menor_a = menor_y(a).y();
            auto menor_b = menor_y(b).y();

            return menor_a > menor_b;
        });
    }

    //Código de inicialização
    bool OnUserCreate() override { return true; }

    //Código de atualização
    bool OnUserUpdate(float fElapsedTime) override {
        if (GetKey(olc::Key::SPACE).bPressed) { pintar = !pintar; }

        Clear(olc::Pixel(0x00, 0x00, 0x00));

        desenha_poligono(poli, olc::Pixel(0xff, 0xff, 0xff), this);
        if (pintar) {
            preenche_poligono(poli, olc::Pixel(0xff, 0xff, 0xff), this);
            debug_print = false;
        }
        return true;
    }

private:

    poligono poli;

    bool pintar = true;
    bool debug_print = true;
};

auto main() -> int {
    poligono poli{
        {  {25, 40}, {100, 100}}, // FE
        {{100, 100},  {150, 15}}, //ED
        { {150, 15}, {200, 150}}, //DC
        {{200, 150}, {150, 200}}, //CB
        {{150, 200},  {50, 170}}, //BA
        { {50, 170},   {25, 40}}, //AF
    };

    PreenchimentoPoligonoApp ppa(poli);
    if (ppa.Construct(250, 250, 2, 2, false, false)) { ppa.Start(); }
    return 0;
}