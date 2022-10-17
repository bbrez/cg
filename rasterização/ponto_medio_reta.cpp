// A biblioteca deve ser baixada do link a seguir e estar disponível na mesma pasta que o arquivo fonte
// https://raw.githubusercontent.com/OneLoneCoder/olcPixelGameEngine/master/olcPixelGameEngine.h
// o comando de compilação é `g++ ponto_medio_reta.cpp rasterizacao.cpp -o reta.exe  -luser32 -lgdi32 -lopengl32 -lgdiplus -lShlwapi -ldwmapi -lstdc++fs -static -std=c++20`
#include <vector>
#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "rasterizacao.h"

class PontoMedioRetaApp : public olc::PixelGameEngine {

public:

    PontoMedioRetaApp() { this->sAppName = "Ponto Medio - Reta"; }

    //Codigo de inicialização;
    bool OnUserCreate() override { return true; }

    //Codigo de atualização
    bool OnUserUpdate(float fElapsedTime) override {

        //Pressionar a barra de espaço alterna qual a reta está sendo destacada
        if (GetKey(olc::Key::SPACE).bPressed) { highlight = (highlight + 1) % (pontos.size() + 1); }

        Clear(olc::Pixel(0x00, 0x00, 0x00));

        olc::Pixel cor(0xff, 0xff, 0xff);
        auto x_centro = larg_tela / 2;
        auto y_centro = alt_tela / 2;

        int atual = 0;
        for (auto& pto : pontos) {
            auto x_final = x_centro + pto.x() * 100;
            auto y_final = y_centro + pto.y() * 100;

            if (atual == highlight) {
                plotLine(x_centro, y_centro, x_final, y_final, olc::Pixel(0xff, 0x00, 0x00), this);
            } else {
                plotLine(x_centro, y_centro, x_final, y_final, cor, this);
            }

            ++atual;
        }
        return true;
    }

    static const auto larg_tela = 500;
    static const auto alt_tela = 500;

private:

    std::vector<ponto> pontos{
        {-2, -2},
        {-1, -2},
        { 0, -2},
        { 1, -2},
        { 2, -2},
        { 2, -1},
        { 2,  0},
        { 2,  1},
        { 2,  2},
        { 1,  2},
        { 0,  2},
        {-1,  2},
        {-2,  2},
        {-2,  1},
        {-2,  0},
        {-2, -1},
    };

    int highlight = pontos.size() + 1;
};

auto main() -> int {
    PontoMedioRetaApp pma;
    if (pma.Construct(PontoMedioRetaApp::larg_tela, PontoMedioRetaApp::alt_tela, 1, 1, false,
                      true)) {
        pma.Start();
    }
    return 0;
}