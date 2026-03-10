#include "Antylopa.h"
#include "Swiat.h"

#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

Antylopa::Antylopa(int x, int y, Swiat& swiat)
    : Zwierze(4, 4, x, y, swiat)
{
    // Jeden raz zainicjuj generator
    std::srand(static_cast<unsigned>(std::time(nullptr)));
}

void Antylopa::akcja(Swiat& swiat) {
    // Przygotuj wszystkie możliwe przesunięcia o max. 2 w każdą stronę
    std::vector<std::pair<int,int>> dirs;
    for (int dx = -2; dx <= 2; ++dx) {
        for (int dy = -2; dy <= 2; ++dy) {
            if (dx == 0 && dy == 0) continue;
            // ograniczamy ruch do pola w obrębie planszy
            dirs.emplace_back(dx, dy);
        }
    }
    std::random_shuffle(dirs.begin(), dirs.end());

    for (auto [dx, dy] : dirs) {
        int nx = x_ + dx;
        int ny = y_ + dy;
        if (!swiat.czyWZakresie(nx, ny)) continue;
        auto occupant = swiat.zwrocOrganizm(nx, ny);
        if (!occupant) {
            // wolne pole → ruch
            swiat.przesunOrganizm(shared_from_this(), nx, ny);
        } else {
            // kolizja z innym organizmem
            kolizja(occupant);
        }
        break; // wykonujemy tylko jedną akcję
    }
}

void Antylopa::kolizja(const std::shared_ptr<Organizm>& inny) {
    // Rozmnażanie jak w bazowym Zwierze
    if (typeid(*inny) == typeid(*this)) {
        Zwierze::kolizja(inny);
        return;
    }

    // Walka: 50% szans na ucieczkę
    if (std::rand() % 2 == 0) {
        auto [px, py] = swiat_.znajdzWolnePoleObok(x_, y_);
        if (px != -1) {
            swiat_.przesunOrganizm(shared_from_this(), px, py);
            return;  // udało się uciec
        }
        // jeśli brak wolnego pola, przechodzimy do walki
    }
    // normalna walka
    Zwierze::kolizja(inny);
}

std::shared_ptr<Organizm> Antylopa::utworzPotomka(int x, int y) {
    return std::make_shared<Antylopa>(x, y, swiat_);
}

char Antylopa::rysowanie() const {
    return 'M'; // np. 'M' od „antyLopa” (można zmienić na dowolny znak)
}
