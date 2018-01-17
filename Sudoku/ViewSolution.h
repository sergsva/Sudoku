#pragma once
#include<stdlib.h>


class ViewSolution
{
private:
	 multimap<CoordinateAndValue, vector<string>> MaybeValue;
	 multimap<CoordinateAndValue, vector<string>>::iterator Iter;

public:

	void GetSolution(vector<vector<string>> & GameField)
	{
		UpdateDBPrognosis(GameField);
		size_t flag = 0;
		if (GetCountFillCell(GameField)>55)
		{
			return;
		}
		while (GetCountFillCell(GameField) != 0)
		{
			flag = GetCountFillCell(GameField);
			LastHeroesInBlocks(GameField, 0, 0, 3, 3);
			LastHeroesInStr(GameField);
			LastHeroesInCol(GameField);
			OnlyOne(GameField);
			if (flag == GetCountFillCell(GameField))
			{
				return;
			}
		}

	}

	//Определяем сколько еще не заполненных позиций на игровом поле
	 size_t GetCountFillCell(vector<vector<string>> & GameField)
	{
		size_t counter = 0;
		for (size_t i = 0; i < GameField.size(); i++)
		{
			counter += count(GameField[i].begin(), GameField[i].end(), "");
		}
		return counter;
	}


	//Поиск прогнозируемых значений в ячейке
	 vector<string> IdentifyPrognosisValue(vector<vector<string>> & GameField, size_t str, size_t column)
	{
		vector<string> Temp;
		char temp[256];
		if (GameField[str][column] != "")
		{
			Temp.push_back("");
		}
		else
		{
			for (size_t i = 1; i < 10; i++)
			{

				if (InputValidation::InputValidationInString(GameField, str, column, _itoa(i, temp, 10)) && InputValidation::InputValidationInColumn(GameField, str, column, itoa(i, temp, 10)) && InputValidation::InputValidationInBlock(GameField, str, column, itoa(i, temp, 10)))
				{
					Temp.push_back(temp);
				}
			}
		}
		if (Temp.empty())
		{
			Temp.push_back("");
		}
		return Temp;
	}

	//Создание хранилища прогнозов по всему полю
	 bool CreateDBPrognosis(vector<vector<string>> & GameField)
	{

		for (size_t i = 0; i < GameField.size(); i++)
		{
			for (size_t j = 0; j < GameField[i].size(); j++)
			{
				MaybeValue.insert(multimap<CoordinateAndValue, vector<string>>::value_type(MakeCell(i, j, GameField[i][j]), IdentifyPrognosisValue(GameField, i, j)));
			}
		}

		if (MaybeValue.empty())
		{
			return false;
		}

		return true;
	}

	//Обновление хранилища прогнозов по всему полю
	 bool UpdateDBPrognosis(vector<vector<string>> & GameField)
	{
		MaybeValue.clear();
		if (CreateDBPrognosis(GameField))
		{
			return true;
		}
		return false;
	}

	/*//Вывод хранилища прогнозов по всему полю в консоль (для тестов)
	void PrintDBPrognosis()
	{
	if (!MaybeValue.empty())
	{
	for (Iter = MaybeValue.begin(); Iter != MaybeValue.end(); Iter++)
	{
	cout << "Cell [" << Iter->first.i << "][" << Iter->first.j << "] = {";
	for (size_t i = 0; i < Iter->second.size(); i++)
	{
	cout << Iter->second[i] << "\t";
	}
	cout << "}" << endl;

	}
	}
	else cout << "DB is empty!" << endl;
	}*/

	//Реализация алгоритма поиска по блоку
	 void LastHeroesInBlocks(vector<vector<string>> & GameField, size_t i, size_t j, size_t li, size_t lj)
	{
		CoordinateAndValue Temp;
		for (size_t k = 1; k < 10; k++)
		{
			char temp[256];
			_itoa(k, temp, 10);
			size_t counter = 0;

			for (size_t _i = i; _i < li; _i++)
			{
				for (size_t _j = j; _j < lj; _j++)
				{
					if (GameField[_i][_j] == "" && InputValidation::InputValidationInString(GameField, _i, _j, temp) && InputValidation::InputValidationInColumn(GameField, _i, _j, temp) && InputValidation::InputValidationInBlock(GameField, _i, _j, temp))
					{
						Temp = MakeCell(_i, _j, temp);
						counter++;
					}
				}
			}
			if (counter == 1)
			{
				GameField[Temp.i][Temp.j] = temp;
				UpdateDBPrognosis(GameField);
			}
		}
		if (i == 6 && j == 6)
		{
			return;
		}
		if (lj == 9)
		{
			LastHeroesInBlocks(GameField, i + 3, 0, li + 3, 3);
		}
		else
			LastHeroesInBlocks(GameField, i, j + 3, li, lj + 3);
	}

	//Реализация алгоритма поиска по строке
	void LastHeroesInStr(vector<vector<string>> & GameField)
	{
		CoordinateAndValue Temp;
		for (size_t i = 0; i < GameField.size(); i++)
		{

			size_t counter = count(GameField[i].begin(), GameField[i].end(), "");
			if (counter == 0)
			{
				continue;
			}

			for (size_t k = 1; k < 10; k++)
			{
				char temp[256];
				_itoa(k, temp, 10);
				size_t Mycount = counter;

				for (size_t j = 0; j < GameField[i].size(); j++)
				{
					if (GameField[i][j] == "")
					{
						if (InputValidation::InputValidationInString(GameField, i, j, temp) && InputValidation::InputValidationInColumn(GameField, i, j, temp) &&
							InputValidation::InputValidationInBlock(GameField, i, j, temp))
						{
							Temp = MakeCell(i, j, temp);
						}
						else
						{
							Mycount--;
						}
					}
				}
				if (Mycount == 1)
				{
					counter--;
					GameField[Temp.i][Temp.j] = temp;
					UpdateDBPrognosis(GameField);
				}

			}

		}
	}

	//Реализация алгоритма поиска по столбцу
	void LastHeroesInCol(vector<vector<string>> & GameField)
	{
		CoordinateAndValue Temp;
		for (size_t j = 0; j < GameField.size(); j++)
		{

			for (size_t k = 1; k < 10; k++)
			{
				char temp[256];
				_itoa(k, temp, 10);
				size_t Mycount = 0;

				for (size_t i = 0; i < GameField.size(); i++)
				{
					if (GameField[i][j] == "")
					{
						if (InputValidation::InputValidationInString(GameField, i, j, temp) && InputValidation::InputValidationInColumn(GameField, i, j, temp) &&
							InputValidation::InputValidationInBlock(GameField, i, j, temp))
						{
							Mycount++;
							Temp = MakeCell(i, j, temp);
						}
					}
				}
				if (Mycount == 1)
				{
					GameField[Temp.i][Temp.j] = temp;
					UpdateDBPrognosis(GameField);
				}

			}

		}
	}




	//Реализация алгоритма поиска одиночных значений в хранилице возможных значений
	 void OnlyOne(vector<vector<string>> & GameField)
	{
		if (!MaybeValue.empty())
		{
			for (Iter = MaybeValue.begin(); Iter != MaybeValue.end(); ++Iter)
			{
				if (Iter->second[0] != "" && Iter->second.size() == 1 && InputValidation::InputValidationInString(GameField, Iter->first.i, Iter->first.j, Iter->second[0])
					&& InputValidation::InputValidationInColumn(GameField, Iter->first.i, Iter->first.j, Iter->second[0]) && InputValidation::InputValidationInBlock(GameField, Iter->first.i, Iter->first.j, Iter->second[0]))
				{
					GameField[Iter->first.i][Iter->first.j] = Iter->second[0];
				}
			}
			UpdateDBPrognosis(GameField);
		}
	}

	~ViewSolution()
	{
	}

};