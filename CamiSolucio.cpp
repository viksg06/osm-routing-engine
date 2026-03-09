#include "pch.h"
#include "CamiSolucio.h"

CamiSolucio::CamiSolucio() {}

CamiSolucio::CamiSolucio(std::vector<Coordinate> coords)
{
    m_coords = coords;
}

std::vector<Coordinate> CamiSolucio::getCamiCoords()
{
    return m_coords;
}
CamiSolucio::CamiSolucio(std::string id, std::string nom, std::string tipuscarretera, std::vector<Coordinate> coords)
{
    m_id = id;
    m_nom = nom;
    m_tipusCarretera = tipuscarretera;
    m_coords = coords;
}
