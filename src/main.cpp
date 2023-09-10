#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <sstream>
#include <cpr/cpr.h>



class SendArguments
{
private:
	std::map<std::string, std::string> requests; // Словарь для хранения ключа и значения;
	cpr::Response r; // Создание объекта класса cpr::Response;
	// Функция для проверки правильности ввода данных;
	bool is_correct_data(const std::string& command)
	{
		int count = 0;
		for (int i = 0; i < command.length(); ++i)
		{
			if (command[i] == ' ')
				++count;
		}
		if (count != 1) return false;
		return true;
	}
public:

	SendArguments()
	{
		std::string command; // Создание объекта класса std::string для ввода данных пользователем;
		while (command != "Post" && command != "post" &&
			command != "Get" && command != "get")
		{
			std::cout << "Commands:\nPost\nGet\n" << std::endl;
			std::cout << "Enter the arguments or command: ";
			std::getline(std::cin, command); // Ввод данных пользователем;

			if (command == "Post" || command == "post")
			{
				if (requests.empty()) // Проверка на заполненность массива;
				{
					std::cout << "No requests. " << std::endl;
					r = cpr::Post(cpr::Url("http://httpbin.org/post")); // post запрос;
					std::cout << r.text << std::endl; // Вывод данных без передачи параметров, так-как пользователь их не ввёл;
				}
				else
				{
					std::vector<cpr::Pair> temp; // Создаю временный вектор;
					// Конвертация map<string, string> в vector<cpr::Pair>;
					for (auto it = requests.begin(); it != requests.end(); ++it)
						temp.emplace_back(it->first, it->second);

					r = cpr::Post(cpr::Url("http://httpbin.org/post"),
						cpr::Payload(temp.begin(), temp.end())); // Передача пользовательских параметров post запросом;

					std::cout << r.text << std::endl; // Вывод данных с пользовательскими параметрами;
				}
			}
			else if (command == "Get" || command == "get") 
			{
				if (requests.empty()) // Проверка на заполненность массива;
				{
					
					std::cout << "No requests. " << std::endl;
					r = cpr::Get(cpr::Url("http://httpbin.org/get")); // get запрос;
					std::cout << r.text << std::endl; // Вывод данных без передачи параметров, так-как пользователь их не ввёл;
				}
				else
				{
					std::string temp = ""; // Берём данные из списка;
					for (auto it = requests.begin(); it != requests.end(); ++it) // Конвертируем каждый элемент списка;
						temp += it->first + "=" + it->second + "&";

					r = cpr::Get(cpr::Url("http://httpbin.org/get?" + temp)); // Передача пользовательских параметров get запросом;

					std::cout << r.text << std::endl; // Вывод данных без передачи параметров, так-как пользователь их не ввёл;
				}
			}
			else
			{
				if (!is_correct_data(command)) // Проверка правильности ввода данных;
					std::cerr << "Error! Incorrect input data. Try again. " << std::endl;
				else
				{
					std::stringstream separationObj(command);
					std::string key, value;

					separationObj >> key >> value; // Разделяем и присваиваем данные, введённые пользователем на ключ и значение;

					requests.emplace(key, value); // Добавляем ключ и значение в словарь;
				}
			}
		}
	}
};

int main()
{
	SendArguments SA;
	
	return 0;
}