// A biblioteca deve ser baixada do link a seguir e estar disponível na mesma pasta que o arquivo fonte
// https://raw.githubusercontent.com/OneLoneCoder/olcPixelGameEngine/master/olcPixelGameEngine.h
// o comando de compilação é g++ cohen_sutherland.cpp rasterizacao.cpp -o recorte.exe  -luser32 -lgdi32 -lopengl32 -lgdiplus -lShlwapi -ldwmapi -lstdc++fs -static -std=c++20
#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "rasterizacao.h"

class CohenSutherlandApp : public olc::PixelGameEngine {

public:

    CohenSutherlandApp() { this->sAppName = "Algoritmo de Cohen-Sutherland"; }

    //Codigo de inicialização
    bool OnUserCreate() override { return true; }

    //Codigo de atualização
    bool OnUserUpdate(float fElapsedTime) override {

        //Quando a barra de espaco eh pressionada ele altera a imagem para com clipping ou sem clipping
        if (GetKey(olc::Key::SPACE).bPressed) { clipping = !clipping; }

        Clear(olc::Pixel(0x00, 0x00, 0x00));

        //Desenha o Retangulo para clipping
        olc::Pixel amarelo(0xff, 0xf2, 0x00);
        DrawLine(x_min, y_max, x_max, y_max, amarelo);
        DrawLine(x_max, y_max, x_max, y_min, amarelo);
        DrawLine(x_max, y_min, x_min, y_min, amarelo);
        DrawLine(x_min, y_min, x_min, y_max, amarelo);

        if (clipping) {
            cohen_sutherland(250, 100, 250, 400, this);
            cohen_sutherland(100, 250, 400, 250, this);
            cohen_sutherland(150, 150, 350, 350, this);
        } else {
            olc::Pixel azul(0x89, 0xd2, 0xff);
            DrawLine(250, 100, 250, 400, azul);
            DrawLine(100, 250, 400, 250, azul);
            DrawLine(150, 150, 350, 350, azul);
        }


        return true;
    }

private:

    bool clipping = true; //Indica se sera mostrada a imagem com clipping ou sem clipping
};

auto main() -> int {
    CohenSutherlandApp csa;
    if (csa.Construct(500, 500, 1, 1, false, true)) { csa.Start(); }
}