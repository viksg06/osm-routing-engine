// NEW PART 2
#include "pch.h"
#include "BallTree.h"

void BallTree::construirArbre(const std::vector<Coordinate>& coordenades)
{
    if (coordenades.empty()) return;

    m_coordenades = coordenades;
    std::vector<Coordinate> copia = coordenades;
    m_pivot = Util::calcularPuntCentral(copia);
    double maxRadi = 0.0;
    for (const auto& coord : coordenades)
    {
        double d = Util::DistanciaHaversine(m_pivot, coord);
        if (d > maxRadi) maxRadi = d;
    }
    m_radi = maxRadi;
    if (coordenades.size() <= 1 || m_radi < 1e-10) return;
    Coordinate puntA = coordenades[0];
    double maxDistA = -1.0;
    for (const auto& coord : coordenades) 
    {
        double d = Util::DistanciaHaversine(m_pivot, coord);
        if (d > maxDistA) 
        {
            maxDistA = d;
            puntA = coord;
        }
    }
    Coordinate puntB = puntA;
    double maxDistB = -1.0;
    for (const auto& coord : coordenades) 
    {
        double d = Util::DistanciaHaversine(puntA, coord);
        if (d > maxDistB) 
        {
            maxDistB = d;
            puntB = coord;
        }
    }
    std::vector<Coordinate> leftCoords;
    std::vector<Coordinate> rightCoords;
    for (const auto& coord : coordenades) 
    {
        double distA = Util::DistanciaHaversine(coord, puntA);
        double distB = Util::DistanciaHaversine(coord, puntB);

        if (distA < distB) 
        {
            leftCoords.push_back(coord);
        } 
        else 
        {
            rightCoords.push_back(coord);
        }
    }
    if (leftCoords.size() == coordenades.size() || rightCoords.size() == coordenades.size()) 
    {
        return; 
    }
    BallTree* arrelApassar = (this->m_root != nullptr) ? this->m_root : this;
if (!leftCoords.empty()) 
{
        m_left = new BallTree();
        m_left->construirArbre(leftCoords);
    }
    if (!rightCoords.empty()) 
    {
        m_right = new BallTree();
        m_right->construirArbre(rightCoords);
    }
}

void BallTree::inOrdre(std::vector<std::list<Coordinate>>& out) 
{
    if(m_left != nullptr)
    {
        m_left->inOrdre(out);
    }
    out.push_back(std::list<Coordinate>(m_coordenades.begin(), m_coordenades.end()));
    if(m_right != nullptr)
    {
        m_right->inOrdre(out);
    }
}
void BallTree::preOrdre(std::vector<std::list<Coordinate>>& out) 
{
    out.push_back(std::list<Coordinate>(m_coordenades.begin(), m_coordenades.end()));
    if(m_left != nullptr)
    {
        m_left->preOrdre(out);
    }
    if(m_right != nullptr)
    {
        m_right->preOrdre(out);
    }
}

void BallTree::postOrdre(std::vector<std::list<Coordinate>>& out) 
{
    if(m_left != nullptr)
    {
        m_left->postOrdre(out);
    }
    if(m_right != nullptr)
    {
        m_right->postOrdre(out);
    }
    out.push_back(std::list<Coordinate>(m_coordenades.begin(), m_coordenades.end()));
}

Coordinate BallTree::nodeMesProper(Coordinate targetQuery, Coordinate& Q, BallTree* ball)
{

    if (ball == nullptr) return Q;
    double d2;
    if (Q.lat == 0.0 && Q.lon == 0.0) 
    {
        d2 = std::numeric_limits<double>::infinity();
    } else
    {
        d2 = Util::DistanciaHaversine(targetQuery, Q);
    }
    double d1 = Util::DistanciaHaversine(ball->getPivot(), targetQuery);
    if (d2 != std::numeric_limits<double>::infinity() && (d1 - ball->getRadi()) >= d2) 
    {
        return Q;
    }
    if (ball->getEsquerre() == nullptr && ball->getDreta() == nullptr) 
    {
        for (const auto& coord : ball->getCoordenades())
        {
            double dist = Util::DistanciaHaversine(coord, targetQuery);
            if (dist < d2) {
                d2 = dist;
                Q = coord;
            }
        }
        return Q;
    }
    double distEsq = (ball->getEsquerre()) ? Util::DistanciaHaversine(targetQuery, ball->getEsquerre()->getPivot()) : std::numeric_limits<double>::infinity();
    double distDre = (ball->getDreta()) ? Util::DistanciaHaversine(targetQuery, ball->getDreta()->getPivot()) : std::numeric_limits<double>::infinity();
    if (distEsq < distDre) {
        Q = nodeMesProper(targetQuery, Q, ball->getEsquerre());
        Q = nodeMesProper(targetQuery, Q, ball->getDreta());
    } else {
        Q = nodeMesProper(targetQuery, Q, ball->getDreta());
        Q = nodeMesProper(targetQuery, Q, ball->getEsquerre());
    }

    return Q;
}