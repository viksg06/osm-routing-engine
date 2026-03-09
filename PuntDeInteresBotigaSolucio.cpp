#include "pch.h"
#include "PuntDeInteresBotigaSolucio.h"

PuntDeInteresBotigaSolucio::PuntDeInteresBotigaSolucio() : PuntDeInteresBase()
{
	m_shop = "undefinit";
	m_opening_hours = "undefinit";
	m_wheelchair = "undefinit";
}

PuntDeInteresBotigaSolucio::PuntDeInteresBotigaSolucio(Coordinate coord, std::string name,
	std::string shop, std::string opening_hours, std::string wheelchair) : PuntDeInteresBase(coord, name)
{
	m_shop = shop;
	m_opening_hours = opening_hours;
	m_wheelchair = wheelchair;
}

unsigned int PuntDeInteresBotigaSolucio::getColor()
{
    if (m_shop == "supermarket")
        return 0xDFFF00; 

    if (m_shop == "tobacco")
        return 0xFF7F50;

    if (m_shop == "bakery" && m_wheelchair == "yes" && obertHores())
        return 0x4CBB17; 

    if (m_shop == "bakery")
        return 0xFA8072; 

    return 0xFFEA00;
}

bool PuntDeInteresBotigaSolucio::obertHores()
{
	const std::size_t n = m_opening_hours.size();
	if (n < 11)
	{
		return false;
	}

	std::size_t i = 0;
	while (i + 10 < n)
	{
		if (m_opening_hours[i] == '0' &&
			m_opening_hours[i + 1] == '6' &&
			m_opening_hours[i + 2] == ':' &&
			m_opening_hours[i + 3] == '0' &&
			m_opening_hours[i + 4] == '0' &&
			m_opening_hours[i + 5] == '-' &&
			m_opening_hours[i + 6] == '2' &&
			m_opening_hours[i + 7] == '2' &&
			m_opening_hours[i + 8] == ':' &&
			m_opening_hours[i + 9] == '0' &&
			m_opening_hours[i + 10] == '0')
		{
			return true;
		}

		i++;
	}

	return false;
}