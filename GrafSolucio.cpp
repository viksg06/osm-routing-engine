#include "pch.h"
#include "GrafSolucio.h"
constexpr size_t Graf::NPOS;
using namespace std;

Graf::Graf(vector<CamiSolucio*> camins)
{
	size_t i;
	for (i = 0; i < camins.size(); i++)
	{
		vector<Coordinate> coords = camins[i]->getCamiCoords();

		if (coords.size() > 0)
		{
			size_t j = 0;

			afegirNode(coords[j]);

			for (j = 1; j < coords.size(); j++)
			{
				afegirAresta(coords[j], coords[j-1]);
			}
		}
	}
}

bool Graf::cercaNode(const Coordinate& c, size_t& pos) const
{
	bool trobat = false;
	pos = 0;
	while (!trobat && pos < m_nodes.size())
	{
		if (m_nodes[pos].lat == c.lat && m_nodes[pos].lon == c.lon)
		{
			trobat = true;
		}
		else
		{
			pos++;
		}
	}

	return trobat;
}

bool Graf::cercaAresta(size_t pos1, size_t pos2, double& pes) const
{
	if (pos1 >= m_veins.size())
	{
		return false;
	}

	pes = -1;
	bool trobat = false;
	forward_list<pair<size_t, double>>::const_iterator it = m_veins[pos1].begin();
	while (!trobat && it != m_veins[pos1].end())
	{
		if ((*it).first == pos2)
		{
			trobat = true;

			pes = (*it).second;
		}
		else
		{
			it++;
		}
	}

	return trobat;
}

size_t Graf::afegirNodeIntern(const Coordinate& c)
{
	m_nodes.push_back(c);
	m_veins.emplace_back();

	return m_nodes.size() - 1;
}

void Graf::afegirNode(const Coordinate& c)
{
	size_t pos = 0;
	if (!cercaNode(c, pos))
	{
		afegirNodeIntern(c);
	}
}

void Graf::afegirArestaIntern(size_t pos1, size_t pos2)
{
	double dummy;
	if (cercaAresta(pos1, pos2, dummy))
	{
		return;
	}

	double pes = Util::DistanciaHaversine(m_nodes[pos1], m_nodes[pos2]);
	m_veins[pos1].push_front(pair<size_t, double>(pos2, pes));
	m_veins[pos2].push_front(pair<size_t, double>(pos1, pes));
}

void Graf::afegirAresta(const Coordinate& c1, const Coordinate& c2)
{
	size_t pos1 = 0;
	if (!cercaNode(c1, pos1))
	{
		pos1 = afegirNodeIntern(c1);
	}

	size_t pos2 = 0;
	if (!cercaNode(c2, pos2))
	{
		pos2 = afegirNodeIntern(c2);
	}

	afegirArestaIntern(pos1, pos2);
}

stack<Coordinate> Graf::buscaCamiMesCurt(const Coordinate& desde, const Coordinate& a) const
{
	size_t pos1 = 0;
	if (!cercaNode(desde, pos1))
	{
		return stack<Coordinate>();
	}

	size_t pos2 = 0;
	if (!cercaNode(a, pos2))
	{
		return stack<Coordinate>();
	}

	vector<double> distancies;
	vector<size_t> anterior;

	dijkstra(pos1, pos2, distancies, anterior);

	if (anterior[pos2] == NPOS)
	{
		return stack<Coordinate>();
	}

	stack<Coordinate> cami;

	size_t it = pos2;
	cami.push(m_nodes[pos2]);

	while (it != pos1)
	{
		cami.push(m_nodes[anterior[it]]);
		it = anterior[it];
	}

	return cami;
}

void Graf::dijkstra(size_t node, size_t obj, vector<double>& dist, vector<size_t>& anterior) const
{
	vector<bool> visitats;
	visitats.resize(m_nodes.size(), false);

	dist.resize(m_nodes.size(), numeric_limits<double>::infinity());
	anterior.resize(m_nodes.size(), NPOS);

	dist[node] = 0;
	anterior[node] = node;

	size_t count;
	for (count = 0; count + 1 < m_nodes.size(); count++)
	{
		size_t posVeiAct = minDistance(dist, visitats);

		if (posVeiAct == obj || posVeiAct == NPOS)
		{
			return;
		}

		visitats[posVeiAct] = true;

		forward_list<pair<size_t, double>>::const_iterator vei;
		for (vei = m_veins[posVeiAct].begin(); vei != m_veins[posVeiAct].end(); vei++)
		{
			if (!visitats[(*vei).first])
			{
				if (dist[posVeiAct] + (*vei).second < dist[(*vei).first])
				{
					dist[(*vei).first] = dist[posVeiAct] + (*vei).second;
					anterior[(*vei).first] = posVeiAct;
				}
			}
		}
	}
}

size_t Graf::minDistance(const vector<double>& dist, const vector<bool>& visitats) const
{
	size_t i;
	double min = (numeric_limits<double>::max)();
	size_t pos = NPOS;
	for (i=0; i<dist.size(); i++)
	{
		if (!visitats[i] && dist[i] < min)
		{
			min = dist[i];
			pos = i;
		}
	}

	return pos;
}