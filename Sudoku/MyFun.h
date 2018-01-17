#pragma once
#include<string>


struct  CoordinateAndValue
{
	size_t i;
	size_t j;
	std::string value;

	bool operator<(const CoordinateAndValue& Obj2) const
	{

		if (this->i<Obj2.i)
		{
			return true;
		}
		return false;
	}

	bool operator==(const CoordinateAndValue& Obj2) const
	{

		if (this->i == Obj2.i && this->j == Obj2.j)
		{
			return true;
		}
		return false;
	}



};

CoordinateAndValue MakeCell(size_t _i, size_t _j, std::string _value);