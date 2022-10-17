// A biblioteca deve ser baixada do link a seguir e estar disponível na mesma pasta que o arquivo fonte
// https://raw.githubusercontent.com/OneLoneCoder/olcPixelGameEngine/master/olcPixelGameEngine.h
// o comando de compilação é g++ ponto_medio_circulo.cpp rasterizacao.cpp -o circulo.exe  -luser32 -lgdi32 -lopengl32 -lgdiplus -lShlwapi -ldwmapi -lstdc++fs -static -std=c++20
#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "rasterizacao.h"

class PontoMedioCirculoApp : public olc::PixelGameEngine {

public:

    PontoMedioCirculoApp() { this->sAppName = "Ponto Medio - Circulo"; }

    //Codigo de inicialização
    bool OnUserCreate() override { return true; }

    //Codigo de atualização
    bool OnUserUpdate(float fElapsedTime) override {

        inc_circle(250, 250, 200, this);

        return true;
    }

private:
};

auto main() -> int {
    PontoMedioCirculoApp pmca;
    if (pmca.Construct(500, 500, 1, 1, false, true)) { pmca.Start(); }
}
