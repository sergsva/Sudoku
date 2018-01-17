#pragma once
class InputValidation
{
public:
	//Проверяем правильность ввода по строке
	static bool InputValidationInString(vector<vector<string>> Field, size_t number_of_string, size_t number_of_column, string Value)
	{
		auto iter = find(Field[number_of_string].begin(), Field[number_of_string].end(), Value);
		if (distance(Field[number_of_string].begin(), iter) == number_of_column)
		{
			iter = find(++iter, Field[number_of_string].end(), Value);
		}

		if (iter == Field[number_of_string].end() || *iter == "")
		{
			return 1;
		}
		return 0;
	}

	//Проверяем правильность ввода по столбцу
	static bool InputValidationInColumn(vector<vector<string>> Field, size_t number_of_string, size_t number_of_column, string Value)
	{
		vector<string> Temp;
		for (size_t i = 0; i < Field.size(); i++)
		{
			if (i != number_of_string)
				Temp.push_back(Field[i][number_of_column]);
		}

		auto iter = find(Temp.begin(), Temp.end(), Value);
		if (iter == Temp.end() || *iter == "")
		{
			return 1;
		}
		return 0;
	}

	//Проверяем правильность ввода по блоку
	static bool InputValidationInBlock(vector<vector<string>> Field, size_t number_of_string, size_t number_of_column, string Value)
	{
		vector<string> Temp;
		size_t temp_num_of_str = number_of_string, temp_num_of_col = number_of_column;
		while (temp_num_of_str % 3 != 0)
		{
			temp_num_of_str--;
		}
		while (temp_num_of_col % 3 != 0)
		{
			temp_num_of_col--;
		}


		for (size_t i = temp_num_of_str; i < temp_num_of_str + 3; i++)
		{
			for (size_t j = temp_num_of_col; j < temp_num_of_col + 3; j++)
			{
				if (i != number_of_string && j != number_of_column)
					Temp.push_back(Field[i][j]);
			}

		}
		auto iter = find(Temp.begin(), Temp.end(), Value);
		if (iter == Temp.end() || *iter == "")
		{
			return 1;
		}
		return 0;
	}


};

