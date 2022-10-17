//A biblioteca deve ser baixada do link a seguir e estar disponível na mesma pasta que o arquivo fonte
//https://raw.githubusercontent.com/OneLoneCoder/olcPixelGameEngine/master/olcPixelGameEngine.h
//o comando de compilação é g++ desenho.cpp -o desenho.exe  -luser32 -lgdi32 -lopengl32 -lgdiplus -lShlwapi -ldwmapi -lstdc++fs -static -std=c++20
#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

class DesenhoApp : public olc::PixelGameEngine
{

public:
	DesenhoApp() :
        cor_branco(0xff, 0xff, 0xff),
        cor_preto(0x00, 0x00, 0x00),
        cor_vermelho(0xff, 0x00, 0x00),
        cor_roxo(0x88, 0x00, 0x99)
	{
		this->sAppName = "Desenho"; //Título da janela
	}

	//Codigo de inicialização;
	bool OnUserCreate() override
	{
		return true;
	}

	//Codigo de atualização
	bool OnUserUpdate(float fElapsedTime) override
	{
        Clear(this->cor_branco);

        auto cor = this->cor_vermelho;
        for(int i = 5 ; i >= 0 ; --i)
        {
            FillCircle(250, 250, 40 * i, cor);

            if(cor.b == 0xff){
                cor = this->cor_vermelho;
            } else {
                cor = this->cor_branco;
            }
        }

        for(int i = 0; i <= 20; ++i) //penas flecha
        {
            DrawLine(110 + i, 110 + i, 100 + i, 85 + i, this->cor_roxo);
            DrawLine(110 + i, 110 + i, 85 + i, 100 + i, this->cor_roxo);
        }

        for(int i = 0; i <= 1; ++i) //Haste flecha
        {
            DrawLine(100 - i, 100 + i, 235 - i, 235 + i, this->cor_preto);
            DrawLine(100 - i + 1, 100 + i, 235 - i + 1, 235 + i, this->cor_preto);
            DrawLine(100 + i, 100 - i, 235 + i, 235 - i, this->cor_preto);
            DrawLine(100 + i - 1, 100 - i, 235 + i - 1, 235 - i, this->cor_preto);
        }

        FillTriangle(102, 102, 100, 98, 98, 100, this->cor_branco);

        FillTriangle(250, 250, 239, 231, 231, 239, olc::Pixel(0x40, 0x40, 0x40));
        FillCircle(250, 250, 4, this->cor_vermelho);
        return true;
	}

private:
    const olc::Pixel cor_branco;
    const olc::Pixel cor_preto;
    const olc::Pixel cor_vermelho;
    const olc::Pixel cor_roxo;
};

auto main() -> int {
	DesenhoApp da;
	if (da.Construct(500, 500, 2, 2))
	{
		da.Start();
	}

	return 0;
}