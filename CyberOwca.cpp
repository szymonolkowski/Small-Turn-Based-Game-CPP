#include "CyberOwca.h"
#include "Swiat.h"
#include "BarszczSosnowskiego.h"
#include <limits>
#include <cmath>

CyberOwca::CyberOwca(int x, int y, Swiat& swiat)
    : Owca(x, y, swiat)
{
    // Nadpisujemy parametry siły i inicjatywy
    sila_ = 10;
    inicjatywa_ = 4;
}

void CyberOwca::akcja(Swiat& swiat) {
    // 1. Wyszukaj najbliższego barszczu sosnowskiego (Manhattan)
    int bestDist = std::numeric_limits<int>::max();
    std::shared_ptr<Organizm> target = nullptr;
    for (auto& org : swiat.getOrganizmy()) {
        auto barszcz = std::dynamic_pointer_cast<BarszczSosnowskiego>(org);
        if (!barszcz) continue;
        int dx = barszcz->getX() - x_;
        int dy = barszcz->getY() - y_;
        int dist = std::abs(dx) + std::abs(dy);
        if (dist < bestDist) {
            bestDist = dist;
            target = barszcz;
        }
    }

    if (target) {
        // 2. Ruch o jedno pole w kierunku celu
        int dx = target->getX() - x_;
        int dy = target->getY() - y_;
        int stepX = (dx == 0 ? 0 : (dx / std::abs(dx)));
        int stepY = (dy == 0 ? 0 : (dy / std::abs(dy)));
        int nx = x_ + stepX;
        int ny = y_ + stepY;

        if (swiat.czyWZakresie(nx, ny)) {
            auto occupant = swiat.zwrocOrganizm(nx, ny);
            if (!occupant) {
                swiat.przesunOrganizm(shared_from_this(), nx, ny);
            } else {
                // Próba zjedzenia lub walka
                kolizja(occupant);
            }
        }
    } else {
        // 3. Brak barszczu – zachowanie jak zwykła owca
        Owca::akcja(swiat);
    }
}

char CyberOwca::rysowanie() const {
    // 1) Sprawdzamy, czy jest na świecie jakikolwiek Barszcz Sosnowskiego
    for (const auto& org : swiat_.getOrganizmy()) {
        if (dynamic_cast<BarszczSosnowskiego*>(org.get())) {
            // jeśli tak — rysujemy Cyber-owcę
            return 'Y';
        }
    }
    // 2) jeśli nie ma żadnego barszczu — rysujemy jak zwykła owca
    return Owca::rysowanie();
}

std::shared_ptr<Organizm> CyberOwca::utworzPotomka(int x, int y) {
    return std::make_shared<CyberOwca>(x, y, swiat_);
}
