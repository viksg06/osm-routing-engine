#include "pch.h"
#include "PuntDeInteresRestaurantSolucio.h"

PuntDeInteresRestaurantSolucio::PuntDeInteresRestaurantSolucio() : PuntDeInteresBase()
{
	m_wheelchair = "undefinit";
	m_cusine = "undefinit";
}

PuntDeInteresRestaurantSolucio::PuntDeInteresRestaurantSolucio(Coordinate coord, std::string name,
	std::string wheelchair, std::string cusine) : PuntDeInteresBase(coord, name)
{
	m_wheelchair = wheelchair;
	m_cusine = cusine;
}

unsigned int PuntDeInteresRestaurantSolucio::getColor()
{
	if (m_cusine == "pizza" && m_wheelchair == "yes")
	{
		return 0x7FFFD4;
	}

	if (m_cusine == "chinese")
	{
		return 0x00FFFF;
	}

	if (m_wheelchair == "yes")
	{
		return 0x5D3FD3;
	}

	return PuntDeInteresBase::getColor();
}