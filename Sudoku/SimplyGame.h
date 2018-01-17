#pragma once
class SimplyGame
{
private:

	 CreateGameField RandField;
	 stack <CoordinateAndValue> Progress;
	 size_t diff_level;
	 vector<vector<string>>GameField;

public:

	 void Start()
	{
		SetDiffLevel(1);
		GameField = RandField.GetRandomField();
	}

	//Устанавливаем уровень сложности игры
	 void SetDiffLevel(size_t level)
	{
		if (level >= 0 && level<3)
		{
			diff_level = ++level;
		}
	}

	//Проверка занятости стека
	bool ProgressIsEmpty()
	{
		return Progress.empty();
	}

	//Очистка стека
	void StackClear()
	{
		while (!Progress.empty())
		{
			Progress.pop();
		}
	}
	//Возвращаем игровое поле
		vector<vector<string>> GetGameField() 
	{
		return GameField;
	}

	//Возвращаем решение
	 vector<vector<string>> ReadSolution() 
	{
		return RandField.GetRandomField();
	}

	//Записываем в стек последний ход
	 void RecordAct(size_t _i, size_t _j, string _value)
	{
		if (Progress.empty() || (Progress.top().i != _i || Progress.top().j != _j))
		{
			Progress.push(MakeCell(_i, _j, _value));
		}

	}

	//Возвращаем координаты последнего хода из стека
	 CoordinateAndValue StepToBack()
	{
		CoordinateAndValue Temp = Progress.top();
		Progress.pop();
		return Temp;
	}

	//Создаем случайное игровое поле
	 void GeneratorFullField()
	{
		do
		{
			size_t Temp;
			RandField.TransField();
			Temp = 1 + rand() % 2;
			RandField.SwapStringInPartField(1 + rand() % 3, Temp, 1 + Temp);
			Temp = 1 + rand() % 2;
			RandField.SwapColumnInPartField(1 + rand() % 3, Temp, 1 + Temp);
			Temp = 1 + rand() % 2;
			RandField.SwapGorizontalPartField(Temp, 1 + Temp);
			Temp = 1 + rand() % 2;
			RandField.SwapVerticalPartField(Temp, 1 + Temp);
			RandField.ReverseField();
			RandField.RotateField((1 + rand() % 3) * 3);
		} while (rand() % 100);
		GameField = RandField.GetRandomField();
	}

	//В зависимости от уровня сложности учищаем некоторые поля
	 void PrepareField()
	{
		size_t clearField = diff_level * 20;

		while (clearField)
		{
			size_t flag = 0;
			size_t itemp = rand() % 9;
			size_t jtemp = rand() % 9;
			if (GameField[itemp][jtemp] != "")
			{
				GameField[itemp][jtemp] = "";
				flag = 1;
			}
			if (flag)
			{
				clearField--;
			}
		}
	}


	//Случайная подсказка
	 CoordinateAndValue HelpOneCell()
	{
		//vector<vector<string>> Temp = RandField.GetRandomField();

		while (true)
		{

			size_t itemp = 0, jtemp = 0;
			vector<string>::iterator Iter;
			itemp = rand() % 9;
			Iter = find(ValueFromField[itemp].begin(), ValueFromField[itemp].end(), "");
			if (Iter != ValueFromField[itemp].end())
			{
				ValueFromField[itemp][distance(ValueFromField[itemp].begin(), Iter)] = RandField.GetRandomField()[itemp][distance(ValueFromField[itemp].begin(), Iter)];
				RecordAct(itemp, distance(ValueFromField[itemp].begin(), Iter), RandField.GetRandomField()[itemp][distance(ValueFromField[itemp].begin(), Iter)]);
				return	MakeCell(itemp, distance(ValueFromField[itemp].begin(), Iter), RandField.GetRandomField()[itemp][distance(ValueFromField[itemp].begin(), Iter)]);
			}

		}
	}

};

