// NEW PART 2
#include "pch.h"
#include "MapaSolucio.h"

// Pots esborrar tot aquest fitxer i utilitzar el teu si ho veus oportu.

void MapaSolucio::getPdis(std::vector<PuntDeInteresBase *> & pdis) {
    pdis = m_pdis;
}

void MapaSolucio::getCamins(std::vector<CamiBase *> & camins) {
    camins.clear();
    for (auto c : m_camins)
    {
        camins.push_back(c);
    }
}

void MapaSolucio::parsejaXmlElements(std::vector<XmlElement> &xmlElements) {
    m_nodes.clear();
    m_pdis.clear();
    m_camins.clear();

    for (auto& element : xmlElements)
    {
        if (element.id_element == "node")
        {
            parseNode(element);
        }
    }

    for (auto& element : xmlElements)
    {
        if (element.id_element == "way")
        {
            parseWay(element);
        }
    }

    m_graf = Graf(m_camins);
}

void MapaSolucio::parseNode(XmlElement& node)
{
    std::string id;
    double lat = 0.0, lon = 0.0;

    std::string name = "sense_nom";
    std::string shop = "undefinit";
    std::string opening_hours = "undefinit";
    std::string wheelchair = "undefinit";
    std::string cuisine = "undefinit";
    std::string amenity = "undefinit";
    bool esPDI = false;

    for (auto& attr : node.atributs)
    {
        if (attr.first == "id") id = attr.second;
        else if (attr.first == "lat") lat = std::stod(attr.second);
        else if (attr.first == "lon") lon = std::stod(attr.second);
    }

    Coordinate coord = { lat, lon };
    m_nodes[id] = coord;

    for (auto& fill : node.fills)
    {
        if (fill.first == "tag")
        {
            auto kv = Util::kvDeTag(fill.second);

            if (kv.first == "name")
                name = kv.second;
            else if (kv.first == "shop")
            {
                shop = kv.second;
                esPDI = true;
            }
            else if (kv.first == "opening_hours")
                opening_hours = kv.second;
            else if (kv.first == "wheelchair")
                wheelchair = kv.second;
            else if (kv.first == "cuisine")
            {
                cuisine = kv.second;
                esPDI = true;
            }
            else if (kv.first == "amenity")
            {
                amenity = kv.second;
                esPDI = true;
            }
        }
    }

    if (!esPDI || name == "sense_nom" || name.empty())
        return;

    if (shop != "undefinit")
    {
        m_pdis.push_back(new PuntDeInteresBotigaSolucio(coord, name, shop, opening_hours, wheelchair));
    }
    else if (amenity == "restaurant" || cuisine != "undefinit")
    {
        m_pdis.push_back(new PuntDeInteresRestaurantSolucio(coord, name, wheelchair, cuisine));
    }
    else
    {
        m_pdis.push_back(new PuntDeInteresBase(coord, name));
    }
}

void MapaSolucio::parseWay(XmlElement& way)
{
    std::string id;
    std::string highwayType;
    std::string name = "sense_nom";
    std::vector<Coordinate> coords;

    for (auto& attr : way.atributs)
    {
        if (attr.first == "id") id = attr.second;
    }

    for (auto& fill : way.fills)
    {
        if (fill.first == "nd")
        {
            std::string refNode;
            for (auto& attr : fill.second)
            {
                if (attr.first == "ref")
                    refNode = attr.second;
            }

            if (m_nodes.find(refNode) != m_nodes.end())
            {
                coords.push_back(m_nodes[refNode]);
            }
        }
        else
            if (fill.first == "tag")
            {
                auto kv = Util::kvDeTag(fill.second);
                if (kv.first == "highway") highwayType = kv.second;
                else if (kv.first == "name") name = kv.second;
            }
    }

    if (!highwayType.empty() && !coords.empty())
    {
        CamiSolucio* cami = new CamiSolucio(id, name, highwayType, coords);
        m_camins.push_back(cami);
    }
}

CamiBase * MapaSolucio::buscaCamiMesCurt(PuntDeInteresBase *desde, PuntDeInteresBase *a)
{
    if (m_graf.getNodes().empty() || desde == nullptr || a == nullptr)
    {
        return nullptr;
    }
    BallTree arbre;
    arbre.construirArbre(m_graf.getNodes());
    Coordinate node1 = { 0.0, 0.0 };
    Coordinate node2 = { 0.0, 0.0 };
    arbre.nodeMesProper(desde->getCoord(), node1, &arbre);
    arbre.nodeMesProper(a->getCoord(), node2, &arbre);
    if (node1.lat == 0.0 && node1.lon == 0.0) return nullptr;
    if (node2.lat == 0.0 && node2.lon == 0.0) return nullptr;

    std::stack<Coordinate> pilaCami = m_graf.buscaCamiMesCurt(node1, node2);

    std::vector<Coordinate> coordsCami;
    while (!pilaCami.empty())
    {
        coordsCami.push_back(pilaCami.top());
    	pilaCami.pop();
    }
    if (coordsCami.empty()) return nullptr;
    return new CamiSolucio(coordsCami);
}