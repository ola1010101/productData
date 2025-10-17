#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class FileManager {
private:
    string productFile = "products.txt";
    string quantityFile = "quantity.txt";
    string priceFile = "price.txt";

public:
    // Проверка существования файла
    bool CheckIfFileExists(const string& filename) {
        ifstream file(filename);
        bool exists = file.good();
        file.close();
        return exists;
    }

    // Подсчет количества строк в файле
    int CountLinesInFile(const string& filename) {
        ifstream file(filename);
        string line;
        int count = 0;

        if (file.is_open()) {
            while (getline(file, line)) {
                count = count + 1;
            }
            file.close();
        }

        return count;
    }

    // Запись одной строки в файл
    void WriteLineToFile(const string& filename, const string& data, bool addToEnd) {
        ofstream file;

        if (addToEnd) {
            file.open(filename, ios::app);
        }
        else {
            file.open(filename);
        }

        if (file.is_open()) {
            file << data << endl;
            file.close();
        }
        else {
            cout << "Ошибка: не удалось открыть файл " << filename << endl;
        }
    }

    // Чтение всех строк из файла
    vector<string> ReadLinesFromFile(const string& filename) {
        vector<string> lines;
        ifstream file(filename);
        string line;

        if (file.is_open()) {
            while (getline(file, line)) {
                lines.push_back(line);
            }
            file.close();
        }

        return lines;
    }

    // Очистка файла
    void ClearFileContents(const string& filename) {
        ofstream file(filename);
        file.close();
    }

    // Заполнение конкретного файла
    void FillSpecificFile(const string& filename, const string& description) {
        cout << "\n=== " << description << " ===" << endl;

        bool fileExists = CheckIfFileExists(filename);
        bool shouldAppend = true;

        if (fileExists) {
            cout << "Файл " << filename << " уже существует!" << endl;
            cout << "Выберите действие:" << endl;
            cout << "1 - Дописать новые данные в конец файла" << endl;
            cout << "2 - Удалить старые данные и записать новые" << endl;
            cout << "0 - Вернуться в главное меню" << endl;

            int userChoice;
            cout << "Ваш выбор: ";
            cin >> userChoice;
            cin.ignore();

            if (userChoice == 0) {
                return;
            }
            if (userChoice == 2) {
                shouldAppend = false;
                ClearFileContents(filename);
            }
        }

        cout << "\nВведите 3 значения для файла " << filename << ":" << endl;

        int i = 1;
        while (i <= 3) {
            string value;
            cout << i << ") ";
            getline(cin, value);
            WriteLineToFile(filename, value, true);
            i = i + 1;
        }

        cout << "Данные успешно записаны в файл!" << endl;
    }

    // Отобразить таблицу с товарами
    void DisplayProductsTable() {
        cout << "\n=== ТАБЛИЦА ТОВАРОВ ===" << endl;

        vector<string> products = ReadLinesFromFile(productFile);
        vector<string> quantities = ReadLinesFromFile(quantityFile);
        vector<string> prices = ReadLinesFromFile(priceFile);

        // Проверяем, есть ли данные в файлах
        if (products.size() == 0 || quantities.size() == 0 || prices.size() == 0) {
            cout << "Ошибка: один или несколько файлов пусты!" << endl;
            return;
        }

        // Находим минимальное количество записей
        int minRecords = products.size();
        if (quantities.size() < minRecords) {
            minRecords = quantities.size();
        }
        if (prices.size() < minRecords) {
            minRecords = prices.size();
        }

        if (minRecords == 0) {
            cout << "Нет данных для отображения!" << endl;
            return;
        }

        // Выводим заголовок таблицы
        cout << "Id  Название           Кол-во     Цена" << endl;
        cout << "----------------------------------------" << endl;

        // Выводим данные
        int i = 0;
        while (i < minRecords) {
            cout << i + 1 << "   " << products[i] << "   " << quantities[i] << "   " << prices[i] << endl;
            i = i + 1;
        }
    }

    // Показать статус всех файлов
    void ShowAllFilesStatus() {
        cout << "\n=== СТАТУС ФАЙЛОВ ===" << endl;

        // Статус файла названий товаров
        if (CheckIfFileExists(productFile)) {
            int count = CountLinesInFile(productFile);
            cout << "Названия товаров: существует, записей: " << count << endl;
        }
        else {
            cout << "Названия товаров: не существует" << endl;
        }

        // Статус файла количеств
        if (CheckIfFileExists(quantityFile)) {
            int count = CountLinesInFile(quantityFile);
            cout << "Количества: существует, записей: " << count << endl;
        }
        else {
            cout << "Количества: не существует" << endl;
        }

        // Статус файла цен
        if (CheckIfFileExists(priceFile)) {
            int count = CountLinesInFile(priceFile);
            cout << "Цены: существует, записей: " << count << endl;
        }
        else {
            cout << "Цены: не существует" << endl;
        }
    }

    // Запуск приложения
    void Run() {
        int userChoice;

        while (true) {
            cout << "\n=== СИСТЕМА УПРАВЛЕНИЯ ТОВАРАМИ ===" << endl;
            cout << "1 - Заполнить файл названий товаров" << endl;
            cout << "2 - Заполнить файл количеств" << endl;
            cout << "3 - Заполнить файл цен" << endl;
            cout << "4 - Просмотреть таблицу товаров" << endl;
            cout << "5 - Проверить статус файлов" << endl;
            cout << "0 - Выход" << endl;

            cout << "Выберите действие: ";
            cin >> userChoice;
            cin.ignore();

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
                cout << "Выход из программы..." << endl;
                break;
            }
            else {
                cout << "Неверный выбор! Попробуйте снова." << endl;
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