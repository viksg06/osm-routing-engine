#pragma once

#include "pch.h"
#include "Common.h"
#include "Util.h"
#include "CamiSolucio.h"
#include <vector>
#include <forward_list>
#include <utility>
#include <stack>
#include <limits>

class Graf
{
public:
	Graf() {}
	Graf(std::vector<CamiSolucio*> camins);

	void afegirNode(const Coordinate& c);
	void afegirAresta(const Coordinate& c1, const Coordinate& c2);

	std::vector<Coordinate> getNodes() const { return m_nodes; }
	
	std::stack<Coordinate> buscaCamiMesCurt(const Coordinate& desde, const Coordinate& a) const;

private:
	std::vector<std::forward_list<std::pair<size_t, double>>> m_veins;
	std::vector<Coordinate> m_nodes;

	bool cercaNode(const Coordinate& c, size_t& pos) const;
	bool cercaAresta(size_t pos1, size_t pos2, double& pes) const;
	void afegirArestaIntern(size_t pos1, size_t pos2);
	size_t afegirNodeIntern(const Coordinate& c);

	void dijkstra(size_t node, size_t obj, std::vector<double>& dist, std::vector<size_t>& anterior) const;
	size_t minDistance(const std::vector<double>& dist, const std::vector<bool>& visitats) const;

	static constexpr size_t NPOS = (std::numeric_limits<size_t>::max)();
};