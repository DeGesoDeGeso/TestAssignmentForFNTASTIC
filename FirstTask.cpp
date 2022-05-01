#include <iostream>
#include <map>

struct CharacterInfo
{
	bool bIsRepeated;
	int index;
};

class Bracketer
{
public:
	void InsertCharacter(const char c, const int index)
	{
		std::map<char, CharacterInfo> ::iterator it = characterMap_.find(c);
		if (it == characterMap_.end())
		{
			characterMap_[c] = MakeInfo(false, index);
			output_.push_back('(');
		}
		else
		{
			if(it->second.bIsRepeated == false)
			{
				output_[it->second.index] = ')';
				output_.push_back(')');
				it->second.bIsRepeated = true;
			}
			else
			{
				output_.push_back(')');
			}
		}
	}

	std::string GetOutput()
	{
		return output_;
	}

private:
	CharacterInfo MakeInfo(const bool condition, const int index)
	{
		CharacterInfo tmp = {condition, index};
		return tmp;
	}
	
	std::string output_;
	std::map<char, CharacterInfo> characterMap_;
};


int main()
{
	Bracketer bracketer;
	char c;
	int index = 0;
	while (std::cin.get(c)) 
	{
		if (c == '\n')
		{
			break;
		}
		bracketer.InsertCharacter(tolower(c), index);
		index++;
	}
	std::cout << bracketer.GetOutput();
}
