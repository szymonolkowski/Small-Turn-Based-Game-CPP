#include "Swiat.h"
#include "Organizm.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iomanip>
#include "Antylopa.h"
#include "Owca.h"
#include "Lis.h"
#include "Wilk.h"
#include "Zolw.h"
#include "CyberOwca.h"
#include "Trawa.h"
#include "Mlecz.h"
#include "Guarana.h"
#include "WilczeJagody.h"
#include "BarszczSosnowskiego.h"
#include "Czlowiek.h"

Swiat::Swiat(int width, int height)
    : width_{width}, height_{height} {
    czyscLog();
}

void Swiat::czyscLog() {
    log_.clear();
}

void Swiat::dodajDoLogu(const std::string& msg) {
    log_.push_back(msg);
}

void Swiat::wykonajTure() {
    czyscLog();

    //sortowanie wedlug inicjatywy pozniej po wieku malejaco
    std::sort(organizmy_.begin(), organizmy_.end(), [](const auto& a, const auto& b) {
        if (a->getInicjatywa() != b->getInicjatywa())
            return a->getInicjatywa() > b->getInicjatywa();
        return a->getWiek() > b->getWiek();
    });

    // wykonanie akcji
    auto snapshot = organizmy_;  // zabezpieczenie na wypadek modyfikacji listy
    for (auto& org : snapshot) {
        org->akcja(*this);
    }

    // obsługa kolizji
    for (size_t i = 0; i < organizmy_.size(); ++i) {
        for (size_t j = i + 1; j < organizmy_.size(); ++j) {
            if (organizmy_[i]->getX() == organizmy_[j]->getX() &&
                organizmy_[i]->getY() == organizmy_[j]->getY()) {
                // tarcza wyjatek
                if (auto c = dynamic_cast<Czlowiek*>(organizmy_[i].get());
                    c && c->czyTarczaAktywna() && dynamic_cast<Zwierze*>(organizmy_[j].get())) {
                    c->kolizja(organizmy_[j]);
                    } else if (auto c = dynamic_cast<Czlowiek*>(organizmy_[j].get());
                        c && c->czyTarczaAktywna() && dynamic_cast<Zwierze*>(organizmy_[i].get())) {
                        c->kolizja(organizmy_[i]);
                    } else {
                        organizmy_[i]->kolizja(organizmy_[j]);
                        organizmy_[j]->kolizja(organizmy_[i]);
                    }
            }
        }
    }
}

void Swiat::rysujSwiat() const {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    const std::vector<std::string> legenda = {
        "===Legenda===",
        ".  - puste pole",
        "C  - Czlowiek",
        "W  - Wilk",
        "O  - Owca",
        "M  - Antylopa",
        "L  - Lis",
        "Z  - Zolw",
        "Y  - Cyber-Owca",
        "T  - Trawa",
        "m  - Mlecz",
        "U  - Guarana",
        "J  - Wilcze Jagody",
        "B  - Barszcz Sosnowskiego"
    };

    const int legendSize = static_cast<int>(legenda.size());
    const int leftHeight = height_ + legendSize;
    const int totalLines = std::max(leftHeight, static_cast<int>(log_.size()));
    const int leftWidth = width_ * 2;

    std::cout << "=== SYMULACJA ===\n";

    for (int y = 0; y < totalLines; ++y) {
        if (y < height_) {
            for (int x = 0; x < width_; ++x) {
                char symbol = '.';
                for (const auto& org : organizmy_) {
                    if (org->getX() == x && org->getY() == y) {
                        symbol = org->rysowanie();
                        break;
                    }
                }
                std::cout << symbol << ' ';
            }
        } else if (y - height_ < legendSize) {
            const std::string& linia = legenda[y - height_];
            std::cout << linia;
            int pad = leftWidth - static_cast<int>(linia.size());
            if (pad > 0) std::cout << std::string(pad, ' ');
        } else {
            std::cout << std::string(leftWidth, ' ');
        }

        std::cout << " | ";
        if (y < static_cast<int>(log_.size())) {
            std::cout << log_[y];
        }
        std::cout << '\n';
    }

    std::cout << std::endl;
}

void Swiat::dodajOrganizm(const std::shared_ptr<Organizm>& org) {
    organizmy_.push_back(org);
}

void Swiat::usunOrganizm(const std::shared_ptr<Organizm>& org) {
    organizmy_.erase(
        std::remove(organizmy_.begin(), organizmy_.end(), org),
        organizmy_.end());
}

void Swiat::zapiszDoPliku(const std::string& filename) const {
    std::ofstream out(filename);
    if (!out) { std::cerr << "Blad otwarcia pliku do zapisu\n"; return; }

    out << width_ << ' ' << height_ << '\n';
    out << organizmy_.size() << '\n';

    for (auto& org : organizmy_) {
        // typ
        if      (dynamic_cast<Antylopa*   >(org.get())) out << "Antylopa";
        else if (dynamic_cast<Owca*       >(org.get())) out << "Owca";
        else if (dynamic_cast<Lis*        >(org.get())) out << "Lis";
        else if (dynamic_cast<Wilk*       >(org.get())) out << "Wilk";
        else if (dynamic_cast<Zolw*       >(org.get())) out << "Zolw";
        else if (dynamic_cast<CyberOwca*  >(org.get())) out << "CyberOwca";
        else if (dynamic_cast<Czlowiek*   >(org.get())) out << "Czlowiek";
        else if (dynamic_cast<Trawa*      >(org.get())) out << "Trawa";
        else if (dynamic_cast<Mlecz*      >(org.get())) out << "Mlecz";
        else if (dynamic_cast<Guarana*    >(org.get())) out << "Guarana";
        else if (dynamic_cast<WilczeJagody*>(org.get())) out << "WilczeJagody";
        else if (dynamic_cast<BarszczSosnowskiego*>(org.get())) out << "BarszczSosnowskiego";
        else out << "Nieznany";

        out << ' ' << org->getX()
            << ' ' << org->getY()
            << ' ' << org->getWiek();

        if (auto c = dynamic_cast<Czlowiek*>(org.get())) {
            out << ' ' << c->getKierunekInt()
                << ' ' << (c->czyTarczaAktywna() ? 1 : 0)
                << ' ' << c->getTuryTarczy()
                << ' ' << c->getTuryCooldown();
        }

        out << '\n';
    }
}

void Swiat::wczytajZPliku(const std::string& filename) {
    std::ifstream in(filename);
    if (!in) { std::cerr << "Blad otwarcia pliku do odczytu\n"; return; }

    organizmy_.clear();
    log_.clear();

    in >> width_ >> height_;

    size_t n; in >> n;

    for (size_t i = 0; i < n; ++i) {
        std::string typ;
        int x, y, wiek;
        in >> typ >> x >> y >> wiek;

        if (typ == "Czlowiek") {
            int kierInt, tarczaOn, turyAktyw, turyCd;
            in >> kierInt >> tarczaOn >> turyAktyw >> turyCd;

            auto human = std::make_shared<Czlowiek>(x, y, *this);
            for (int t = 0; t < wiek; ++t) human->zwiekszWiek();
            human->ustawKierunekInt(kierInt);
            human->ustawTarczaAktywna(tarczaOn != 0);
            human->ustawTuryTarczy(turyAktyw);
            human->ustawTuryCooldown(turyCd);

            organizmy_.push_back(human);
        }
        else {
            std::shared_ptr<Organizm> org;
            if      (typ == "Antylopa")      org = std::make_shared<Antylopa>(x, y, *this);
            else if (typ == "Owca")          org = std::make_shared<Owca>(x, y, *this);
            else if (typ == "Lis")           org = std::make_shared<Lis>(x, y, *this);
            else if (typ == "Wilk")          org = std::make_shared<Wilk>(x, y, *this);
            else if (typ == "Zolw")          org = std::make_shared<Zolw>(x, y, *this);
            else if (typ == "CyberOwca")     org = std::make_shared<CyberOwca>(x, y, *this);
            else if (typ == "Trawa")         org = std::make_shared<Trawa>(x, y, *this);
            else if (typ == "Mlecz")         org = std::make_shared<Mlecz>(x, y, *this);
            else if (typ == "Guarana")       org = std::make_shared<Guarana>(x, y, *this);
            else if (typ == "WilczeJagody")  org = std::make_shared<WilczeJagody>(x, y, *this);
            else if (typ == "BarszczSosnowskiego") org = std::make_shared<BarszczSosnowskiego>(x, y, *this);
            else {
                std::cerr << "Nieznany typ organizmu: " << typ << "\n";
                continue;
            }
            for (int t = 0; t < wiek; ++t) org->zwiekszWiek();
            organizmy_.push_back(org);
        }
    }
}


bool Swiat::czyWZakresie(int x, int y) const {
    return x >= 0 && x < width_ && y >= 0 && y < height_;
}

std::shared_ptr<Organizm> Swiat::zwrocOrganizm(int x, int y) const {
    for (const auto& org : organizmy_) {
        if (org->getX() == x && org->getY() == y) {
            return org;
        }
    }
    return nullptr;
}

void Swiat::przesunOrganizm(const std::shared_ptr<Organizm>& org, int nx, int ny) {
    org->ustawPozycje(nx, ny);
}

std::pair<int,int> Swiat::znajdzWolnePoleObok(int x, int y) const {
    static const int DX[8] = { -1,-1,-1, 0, 0, 1, 1, 1 };
    static const int DY[8] = { -1, 0, 1,-1, 1,-1, 0, 1 };
    for (int i = 0; i < 8; ++i) {
        int nx = x + DX[i], ny = y + DY[i];
        if (czyWZakresie(nx, ny) && !zwrocOrganizm(nx, ny)) {
            return {nx, ny};
        }
    }
    return {-1, -1};
}

const std::vector<std::shared_ptr<Organizm>>& Swiat::getOrganizmy() const {
    return organizmy_;
}

int Swiat::getWidth() const {
    return width_;
}

int Swiat::getHeight() const {
    return height_;
}