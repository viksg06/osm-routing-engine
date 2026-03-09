#pragma once
#include "pch.h"

#include <string>
#include "Common.h"
#include "PuntDeInteresBase.h"

class PuntDeInteresBotigaSolucio : public PuntDeInteresBase
{
public:
	PuntDeInteresBotigaSolucio();
	PuntDeInteresBotigaSolucio(Coordinate coord, std::string name,
		std::string shop, std::string opening_hours, std::string wheelchair);

	std::string getShop() { return m_shop; }
	std::string getOpeningHours() { return m_opening_hours; }
	std::string getWheelchair() { return m_wheelchair; }

	unsigned int getColor() override;



private:
	std::string m_shop;
	std::string m_opening_hours;
	std::string m_wheelchair;

	bool obertHores();

};