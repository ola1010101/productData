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
    // �������� ������������� �����
    bool CheckIfFileExists(const string& filename) {
        ifstream file(filename);
        bool exists = file.good();
        file.close();
        return exists;
    }

    // ������� ���������� ����� � �����
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

    // ������ ����� ������ � ����
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
            cout << "������: �� ������� ������� ���� " << filename << endl;
        }
    }

    // ������ ���� ����� �� �����
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

    // ������� �����
    void ClearFileContents(const string& filename) {
        ofstream file(filename);
        file.close();
    }

    // ���������� ����������� �����
    void FillSpecificFile(const string& filename, const string& description) {
        cout << "\n=== " << description << " ===" << endl;

        bool fileExists = CheckIfFileExists(filename);
        bool shouldAppend = true;

        if (fileExists) {
            cout << "���� " << filename << " ��� ����������!" << endl;
            cout << "�������� ��������:" << endl;
            cout << "1 - �������� ����� ������ � ����� �����" << endl;
            cout << "2 - ������� ������ ������ � �������� �����" << endl;
            cout << "0 - ��������� � ������� ����" << endl;

            int userChoice;
            cout << "��� �����: ";
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

        cout << "\n������� 3 �������� ��� ����� " << filename << ":" << endl;

        int i = 1;
        while (i <= 3) {
            string value;
            cout << i << ") ";
            getline(cin, value);
            WriteLineToFile(filename, value, true);
            i = i + 1;
        }

        cout << "������ ������� �������� � ����!" << endl;
    }

    // ���������� ������� � ��������
    void DisplayProductsTable() {
        cout << "\n=== ������� ������� ===" << endl;

        vector<string> products = ReadLinesFromFile(productFile);
        vector<string> quantities = ReadLinesFromFile(quantityFile);
        vector<string> prices = ReadLinesFromFile(priceFile);

        // ���������, ���� �� ������ � ������
        if (products.size() == 0 || quantities.size() == 0 || prices.size() == 0) {
            cout << "������: ���� ��� ��������� ������ �����!" << endl;
            return;
        }

        // ������� ����������� ���������� �������
        int minRecords = products.size();
        if (quantities.size() < minRecords) {
            minRecords = quantities.size();
        }
        if (prices.size() < minRecords) {
            minRecords = prices.size();
        }

        if (minRecords == 0) {
            cout << "��� ������ ��� �����������!" << endl;
            return;
        }

        // ������� ��������� �������
        cout << "Id  ��������           ���-��     ����" << endl;
        cout << "----------------------------------------" << endl;

        // ������� ������
        int i = 0;
        while (i < minRecords) {
            cout << i + 1 << "   " << products[i] << "   " << quantities[i] << "   " << prices[i] << endl;
            i = i + 1;
        }
    }

    // �������� ������ ���� ������
    void ShowAllFilesStatus() {
        cout << "\n=== ������ ������ ===" << endl;

        // ������ ����� �������� �������
        if (CheckIfFileExists(productFile)) {
            int count = CountLinesInFile(productFile);
            cout << "�������� �������: ����������, �������: " << count << endl;
        }
        else {
            cout << "�������� �������: �� ����������" << endl;
        }

        // ������ ����� ���������
        if (CheckIfFileExists(quantityFile)) {
            int count = CountLinesInFile(quantityFile);
            cout << "����������: ����������, �������: " << count << endl;
        }
        else {
            cout << "����������: �� ����������" << endl;
        }

        // ������ ����� ���
        if (CheckIfFileExists(priceFile)) {
            int count = CountLinesInFile(priceFile);
            cout << "����: ����������, �������: " << count << endl;
        }
        else {
            cout << "����: �� ����������" << endl;
        }
    }

    // ������ ����������
    void Run() {
        int userChoice;

        while (true) {
            cout << "\n=== ������� ���������� �������� ===" << endl;
            cout << "1 - ��������� ���� �������� �������" << endl;
            cout << "2 - ��������� ���� ���������" << endl;
            cout << "3 - ��������� ���� ���" << endl;
            cout << "4 - ����������� ������� �������" << endl;
            cout << "5 - ��������� ������ ������" << endl;
            cout << "0 - �����" << endl;

            cout << "�������� ��������: ";
            cin >> userChoice;
            cin.ignore();

            if (userChoice == 1) {
                FillSpecificFile(productFile, "���������� ����� �������� �������");
            }
            else if (userChoice == 2) {
                FillSpecificFile(quantityFile, "���������� ����� ���������");
            }
            else if (userChoice == 3) {
                FillSpecificFile(priceFile, "���������� ����� ���");
            }
            else if (userChoice == 4) {
                DisplayProductsTable();
            }
            else if (userChoice == 5) {
                ShowAllFilesStatus();
            }
            else if (userChoice == 0) {
                cout << "����� �� ���������..." << endl;
                break;
            }
            else {
                cout << "�������� �����! ���������� �����." << endl;
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