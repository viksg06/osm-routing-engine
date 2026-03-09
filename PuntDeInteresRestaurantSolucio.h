#pragma once
#include "pch.h"

#include <string>
#include "Common.h"
#include "PuntDeInteresBase.h"

class PuntDeInteresRestaurantSolucio : public PuntDeInteresBase
{
public:
	PuntDeInteresRestaurantSolucio();
	PuntDeInteresRestaurantSolucio(Coordinate coord, std::string name,
		std::string wheelchair, std::string cusine);

	std::string getCusine() { return m_cusine; }
	std::string getWheelchair() { return m_wheelchair; }

	unsigned int getColor() override;



private:
	std::string m_wheelchair;
	std::string m_cusine;

};