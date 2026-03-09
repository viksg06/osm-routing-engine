// NEW PART 2
#pragma once
#include "pch.h"
#include "MapaBase.h"
#include "CamiSolucio.h"
#include <map>
#include "Util.h"
#include "PuntDeInteresBase.h"
#include "PuntDeInteresBotigaSolucio.h"
#include "PuntDeInteresRestaurantSolucio.h"
#include "GrafSolucio.h"
#include "BallTree.h"

// Pots esborrar tot aquest fitxer i utilitzar el teu si ho veus oportu.

class MapaSolucio : public MapaBase {

public:
    MapaSolucio() {

    }

    ~MapaSolucio() {

    }

    // Metodes a implementar de la primera part
    void getPdis(std::vector<PuntDeInteresBase*>& pdis) override;
    void getCamins(std::vector<CamiBase*>& camins) override;
    void parsejaXmlElements(std::vector<XmlElement>& xmlElements) override;

    // Metode a implementar de la segona part
    CamiBase* buscaCamiMesCurt(PuntDeInteresBase* desde, PuntDeInteresBase* a);

private:
    std::vector<CamiSolucio*> m_camins;

    Graf m_graf;

    //Atributs i metodes tasca 7
    std::vector<PuntDeInteresBase*> m_pdis;
    std::map<std::string, Coordinate> m_nodes;

    void parseNode(XmlElement& node);
    void parseWay(XmlElement& way);
};