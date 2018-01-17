#pragma once
#include<string>
#include"MyFun.h"

CoordinateAndValue MakeCell(size_t _i, size_t _j, std::string _value)
{
	CoordinateAndValue Obj;
	Obj.i = _i;
	Obj.j = _j;
	Obj.value = _value;
	return Obj;
}

