#include <iostream>
#include <fstream>
#include <string>
#include <vector>



class FileManager 
{

private:
    std::string productFile = "products.txt";
    std::string quantityFile = "quantity.txt";
    std::string priceFile = "price.txt";


public:

    // Проверка существования
    bool CheckIfFileExists(const  std::string& filename) {
        std::ifstream file(filename);
        bool exists = file.good();
        file.close();
        return exists;
    }

    // количествo строк
    int CountLinesInFile(const std::string& filename) {
        std::ifstream file(filename);
        std::string line;
        int count = 0;

        if (file.is_open()) {
            while (std::getline(file, line)) {
                count = count + 1;
            }
            file.close();
        }

        return count;
    }

    // Запись одной строки 
    void WriteLineToFile(const std::string& filename, const std::string& data, bool addToEnd) {
        std::ofstream file;

        if (addToEnd) {
            file.open(filename, std::ios::app);
        }
        else {
            file.open(filename);
        }

        if (file.is_open()) {
            file << data << "\n";
            file.close();
        }
        else {
            std::cout << "Ошибка: не удалось открыть файл " << filename << "\n";
        }
    }

    // Чтение всех строк 
    std::vector<std::string> ReadLinesFromFile(const std::string& filename) {
        std::vector<std::string> lines;
        std::ifstream file(filename);
        std::string line;

        if (file.is_open()) {
            while (getline(file, line)) {
                lines.push_back(line);
            }
            file.close();
        }

        return lines;
    }

   
    void ClearFileContents(const std::string& filename) {
        std::ofstream file(filename);
        file.close();
    }

   
    void FillSpecificFile(const std::string& filename, const std::string& description) {
        std::cout << "\n=== " << description << " ===\n";

        bool fileExists = CheckIfFileExists(filename);
        bool shouldAppend = true;

        if (fileExists) {
            std::cout << "Файл " << filename << " уже существует!\n";
            std::cout << "Выберите действие:\n";
            std::cout << "1 - Дописать новые данные в конец файла\n";
            std::cout << "2 - Удалить старые данные и записать новые\n";
            std::cout << "0 - Вернуться в главное меню\n";

            int userChoice;
            std::cout << "Ваш выбор: ";
            std::cin >> userChoice;
            std::cin.ignore();

            if (userChoice == 0) {
                return;
            }
            if (userChoice == 2) {
                shouldAppend = false;
                ClearFileContents(filename);
            }
        }

        std::cout << "\nВведите 3 значения для файла " << filename << ":\n";

        int i = 1;
        while (i <= 3) {
            std::string value;
            std::cout << i << ") ";
            std::getline(std::cin, value);
            WriteLineToFile(filename, value, true);
            i = i + 1;
        }

        std::cout << "Данные успешно записаны в файл!\n";
    }

   
    void DisplayProductsTable() {
        std::cout << "\n=== ТАБЛИЦА ТОВАРОВ ===\n";

        std::vector<std::string> products = ReadLinesFromFile(productFile);
        std::vector<std::string> quantities = ReadLinesFromFile(quantityFile);
        std::vector<std::string> prices = ReadLinesFromFile(priceFile);

        // проверяем, есть ли данные в файлах
        if (products.size() == 0 || quantities.size() == 0 || prices.size() == 0) {
            std::cout << "Ошибка: один или несколько файлов пусты!0\n";
            return;
        }

        // минимальное количество записей
        int minRecords = products.size();
        if (quantities.size() < minRecords) {
            minRecords = quantities.size();
        }
        if (prices.size() < minRecords) {
            minRecords = prices.size();
        }

        if (minRecords == 0) {
            std::cout << "Нет данных для отображения!\n";
            return;
        }

       
        std::cout << "Id  Название           Кол-во     Цена\n";
        std::cout << "----------------------------------------\n";

      
        int i = 0;
        while (i < minRecords) {
            std::cout << i + 1 << "   " << products[i] << "   " << quantities[i] << "   " << prices[i] << "\n";
            i = i + 1;
        }
    }

   
    void ShowAllFilesStatus() {
        std::cout << "\n=== СТАТУС ФАЙЛОВ ===\n";

        // названий товаров
        if (CheckIfFileExists(productFile)) {
            int count = CountLinesInFile(productFile);
            std::cout << "Названия товаров: существует, записей: " << count << "\n";
        }
        else {
            std::cout << "Названия товаров: не существует\n";
        }

        // количество
        if (CheckIfFileExists(quantityFile)) {
            int count = CountLinesInFile(quantityFile);
            std::cout << "Количества: существует, записей: " << count << "\n";
        }
        else {
            std::cout << "Количества: не существует\n";
        }

        // цены
        if (CheckIfFileExists(priceFile)) {
            int count = CountLinesInFile(priceFile);
            std::cout << "Цены: существует, записей: " << count << "\n";
        }
        else {
            std::cout << "Цены: не существует\n";
        }
    }

    

    void Run() {
        int userChoice;

        while (true) {
            std::cout << "\n=== СИСТЕМА УПРАВЛЕНИЯ ТОВАРАМИ ===\n";
            std::cout << "1 - Заполнить файл названий товаров\n";
            std::cout << "2 - Заполнить файл количеств\n";
            std::cout << "3 - Заполнить файл цен\n";
            std::cout << "4 - Просмотреть таблицу товаров\n";
            std::cout << "5 - Проверить статус файлов\n";
            std::cout << "0 - Выход\n";

            std::cout << "Выберите действие: ";
            std::cin >> userChoice;
            std::cin.ignore();

            if (userChoice == 1) {
                FillSpecificFile(productFile, "ЗАПОЛНЕНИЕ ФАЙЛА НАЗВАНИЙ ТОВАРОВ");
            }
            else if (userChoice == 2) {
                FillSpecificFile(quantityFile, "ЗАПОЛНЕНИЕ ФАЙЛА КОЛИЧЕСТВ");
            }
            else if (userChoice == 3) {
                FillSpecificFile(priceFile, "ЗАПОЛНЕНИЕ ФАЙЛА ЦЕН");
            }
            else if (userChoice == 4) {
                DisplayProductsTable();
            }
            else if (userChoice == 5) {
                ShowAllFilesStatus();
            }
            else if (userChoice == 0) {
                std::cout << "Выход из программы...\n";
                break;
            }
            else {
                std::cout << "Неверный выбор! Попробуйте снова.\n";
            }
        }
    }
};

int main() {

    setlocale(LC_ALL, "ru");
    srand(time(NULL));

    FileManager manager;
    manager.Run();
    return 0;
}
