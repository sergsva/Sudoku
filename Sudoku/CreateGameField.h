#pragma once
using namespace std;
class CreateGameField
{
private:
	vector<vector<string>> RandomField;
	size_t size;

	//��������� ������ ��������� �� 1 �� 9
	void PushFrom1To9(vector<string> &Obj)
	{
		for (size_t i = 1; i <= size; i++)
		{
			char temp[256];
			_itoa(i, temp, 10);
			Obj.push_back(temp);
		}
	}

public:
	//������� ������� ����, ������� ����� ������ � �������
	CreateGameField()
	{
		size = 9;
		RandomField = { size, vector<string>(size, "") };
		for (size_t i = 0; i < RandomField.size(); i++)
		{
			switch (i)
			{
			case 0:
				RandomField[i].clear();
				PushFrom1To9(RandomField[i]);
				break;
			case 3:
			case 6:
				RandomField[i] = RandomField[i - 1];
				rotate(RandomField[i].begin(), RandomField[i].begin() + 4, RandomField[i].end());
				break;
			default:
				RandomField[i] = RandomField[i - 1];
				rotate(RandomField[i].begin(), RandomField[i].begin() + 3, RandomField[i].end());
				break;
			}
		}
	}

	
	// ���������� ��������� ��������� ����������� ���������� ������� ����
	vector<vector<string>> GetRandomField() const
	{
		return RandomField;
	}
	
	// ���������������� ����
	void TransField()
	{
		vector<vector<string>> Temp{ size, vector<string>(size, "") };
		for (size_t i = 0; i < size; i++)
		{
			for (size_t j = 0; j < size; j++)
			{
				Temp[i][j] = RandomField[size - j - 1][i];

			}
		}

		RandomField.clear();
		RandomField = Temp;
	}

	//������������� ���� � �������� �������
	void ReverseField()
	{
		for (size_t i = 0; i < RandomField.size(); i++)
		{
			reverse(RandomField[i].begin(), RandomField[i].end());
		}
	}

	// ����������� ����� ����
	void RotateField(size_t step)
	{
		for (size_t i = 0; i < RandomField.size(); i++)
		{
			rotate(RandomField[i].begin(), RandomField[i].begin() + step, RandomField[i].end());
		}
	}

	//������������ �����, ��������� ���� �� ���� ������ ���� � ������ ����� �� 1 �� 3 � ���� ����
	void SwapStringInPartField(size_t partOfField, size_t from, size_t where)
	{
		if (partOfField > 0 && partOfField <4 && from > 0 && from <4 && where > 0 && where <4)
		{
			vector<string> Temp = RandomField[from - 1 + (partOfField - 1) * 3];
			RandomField[from - 1 + (partOfField - 1) * 3] = RandomField[where - 1 + (partOfField - 1) * 3];
			RandomField[where - 1 + (partOfField - 1) * 3] = Temp;
		}
	}

	//������������ ��������, ��������� ���� �� ���� ������ ���� � ������ ����� �� 1 �� 3 � ���� ����
	void SwapColumnInPartField(size_t partOfField, size_t from, size_t where)
	{
		if (partOfField > 0 && partOfField <4 && from > 0 && from <4 && where > 0 && where <4)
		{
			string Temp;
			for (size_t i = 0; i < size; i++)
			{
				Temp = RandomField[i][from - 1 + (partOfField - 1) * 3];
				RandomField[i][from - 1 + (partOfField - 1) * 3] = RandomField[i][where - 1 + (partOfField - 1) * 3];
				RandomField[i][where - 1 + (partOfField - 1) * 3] = Temp;
			}
		}
	}

	//������������ �������������� ������ �� ���� �����, ��������� ������ ������ �� 1 �� 3 � ���� ����
	void SwapGorizontalPartField(size_t from, size_t where)
	{
		if (from > 0 && from <4 && where > 0 && where <4)
		{
			vector<vector<string>> Temp{ 3, vector<string>(9, "") };
			for (size_t i = 0; i < 3; i++)
			{
				Temp[i] = RandomField[i + (from - 1) * 3];
				RandomField[i + (from - 1) * 3] = RandomField[i + (where - 1) * 3];
				RandomField[i + (where - 1) * 3] = Temp[i];
			}
		}
	}


	//������������ ������������ ������ �� ���� ��������, ��������� ������ ������ �� 1 �� 3 � ���� ����
	void SwapVerticalPartField(size_t from, size_t where)
	{
		if (from > 0 && from <4 && where > 0 && where <4)
		{
			vector<vector<string>> Temp{ 9, vector<string>(3, "") };
			for (size_t j = 0; j < 3; j++)
			{
				for (size_t i = 0; i < 9; i++)
				{
					Temp[i][j] = RandomField[i][j + (from - 1) * 3];
					RandomField[i][j + (from - 1) * 3] = RandomField[i][j + (where - 1) * 3];
					RandomField[i][j + (where - 1) * 3] = Temp[i][j];
				}
			}
		}
	}
	~CreateGameField(){}
};

