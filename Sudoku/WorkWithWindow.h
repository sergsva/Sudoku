
class WorkWithWindow
{

public:

	static void ResetGameField()
	{
		for (size_t i = 0; i < hIDEDIT.size(); i++)
		{
			for (size_t j = 0; j < hIDEDIT[i].size(); j++)
			{
				SendMessage(hIDEDIT[i][j], WM_SETTEXT, 0, (LPARAM)"");
			}
		}
	}


	static bool InputValidation(size_t number_of_string, size_t number_of_column, string Value, HWND hwnd)
	{

		//Проверяем после ввода правильно ли мы ввели
		if (!InputValidation::InputValidationInString(ValueFromField, number_of_string, number_of_column, Value)
			|| !InputValidation::InputValidationInColumn(ValueFromField, number_of_string, number_of_column, Value)
			|| !InputValidation::InputValidationInBlock(ValueFromField, number_of_string, number_of_column, Value))
		{
			return 0;
		}

		return 1;
	}


	static void ProccesingInputText(size_t number_of_string, size_t number_of_column, HWND hwnd, size_t &token)
	{
		CHAR temp[256];
		SendMessage(hIDEDIT[number_of_string][number_of_column], WM_GETTEXT, (WPARAM)255, (LPARAM)temp);
		if (atoi(temp)>0 && atoi(temp) < 10 && InputValidation(number_of_string, number_of_column, temp, hwnd))
		{

			ValueFromField[number_of_string][number_of_column] = temp;
			newgame.RecordAct(number_of_string, number_of_column, temp);

		}
		else
		{
			if (!InputValidation(number_of_string, number_of_column, temp, hwnd))
			{
				MessageBox(hwnd, "В строке, столбце или блоке уже есть такое число!", "Информация", MB_OK | MB_ICONINFORMATION);
			}
			else if (atoi(temp)>0 && atoi(temp))
			{
				MessageBox(hwnd, "Значение недопустимо!", "Информация", MB_OK | MB_ICONINFORMATION);
			}
			ValueFromField[number_of_string][number_of_column] = "";
			SendMessage(hIDEDIT[number_of_string][number_of_column], WM_SETTEXT, 0, (LPARAM)"");

		}

		token = 0;


	}

	static void EnterInField(vector<vector<string>> NewField)
	{
		for (size_t i = 0; i < NewField.size(); i++)
		{
			for (size_t j = 0; j < NewField[i].size(); j++)
			{
				SendMessage(hIDEDIT[i][j], WM_SETTEXT, 0, (LPARAM)NewField[i][j].c_str());
			}
		}
		ValueFromField = NewField;
	}

	

	~WorkWithWindow(){}


};