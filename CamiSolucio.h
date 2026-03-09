#pragma once
#include "CamiBase.h"
#include <vector>

class CamiSolucio : public CamiBase
{
private:
    std::vector<Coordinate> m_coords;
    //Atributs Tasca 7
    std::string m_id;
    std::string m_nom;
    std::string m_tipusCarretera;


public:
    CamiSolucio();
    CamiSolucio(std::vector<Coordinate> coords);
    std::vector<Coordinate> getCamiCoords() override;
    CamiSolucio(std::string id, std::string nom, std::string tipuscarretera, std::vector<Coordinate> coords);

    //Metodes tasca 7
    std::string getNom() { return m_nom; }
    std::string getTipusCarretera() { return m_tipusCarretera; }
};