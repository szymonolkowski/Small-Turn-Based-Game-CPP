#include "BarszczSosnowskiego.h"
#include "Swiat.h"
#include "Zwierze.h"
#include "CyberOwca.h"
#include <string>

// Konstruktor: inicjalizacja poprzez bazową Roslina
BarszczSosnowskiego::BarszczSosnowskiego(int x, int y, Swiat& swiat)
    : Roslina(x, y, swiat)
{
    // siła i inicjatywa bazowej Roslina są wystarczające
}

// BarszczSosnowskiego.cpp

#include "BarszczSosnowskiego.h"
#include "Swiat.h"
#include "Zwierze.h"
#include "CyberOwca.h"
#include <string>

void BarszczSosnowskiego::akcja(Swiat& swiat) {
    // 1) najpierw zrób sianie tak jak każda roślina:
    Roslina::akcja(swiat);

    // 2) a dopiero potem eksterminuj zwierzęta wokół:
    static const int DX[8] = { -1,-1,-1,  0, 0, 1, 1, 1 };
    static const int DY[8] = { -1, 0,  1, -1, 1,-1, 0, 1 };
    for (int i = 0; i < 8; ++i) {
        int nx = x_ + DX[i], ny = y_ + DY[i];
        if (!swiat.czyWZakresie(nx, ny)) continue;
        auto occupant = swiat.zwrocOrganizm(nx, ny);
        if (!occupant) continue;
        // Tylko zwierzęta (poza cyber-owcą)
        if (auto zw = std::dynamic_pointer_cast<Zwierze>(occupant)) {
            if (!std::dynamic_pointer_cast<CyberOwca>(occupant)) {
                swiat.usunOrganizm(occupant);
                swiat.dodajDoLogu(
                  "BarszczSosnowskiego zabil zwierze na "
                  + std::to_string(nx) + "," + std::to_string(ny)
                );
            }
        }
    }
}


void BarszczSosnowskiego::kolizja(const std::shared_ptr<Organizm>& inny) {
    // Jeżeli zderzył się zwierzę
    auto zw = std::dynamic_pointer_cast<Zwierze>(inny);
    if (zw) {
        // Cyber-Owca odporna
        if (!std::dynamic_pointer_cast<CyberOwca>(inny)) {
            swiat_.usunOrganizm(inny);
            swiat_.dodajDoLogu("Zwierz zginal po zjedzeniu barszczu sosnowskiego");
        }
    }
    // Roślina usuwa się sama
    Roslina::kolizja(inny);
}

char BarszczSosnowskiego::rysowanie() const {
    return 'B';
}

std::shared_ptr<Organizm> BarszczSosnowskiego::utworzSadzonke(int x, int y) {
    return std::make_shared<BarszczSosnowskiego>(x, y, swiat_);
}
