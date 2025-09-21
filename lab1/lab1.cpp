#include <iostream>
#include <string>
#include <limits>
#include <fstream>

using namespace std;

float CheckFloatInput() {
    float value;
    while (true) {
        cin >> value;
        if (cin.fail() || value <= 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Введите положительное число!" << endl;
        }
        else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
    }
}

int CheckIntInput() {
    int value;
    while (true) {
        cin >> value;
        if (cin.fail() || value <= 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Введите положительное целое число!" << endl;
        }
        else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
    }
}

struct Pipe {
    string name = "";
    float length;
    int diameter;
    bool status;
};

struct CS {
    string name = "";
    int count;
    int inwork;
    string category;
};

void AddPipe(Pipe& t) {
    cout << "Введите название трубы: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, t.name);
    cout << "Введите длину трубы: ";
    t.length = CheckFloatInput();
    cout << "Введите диаметр трубы: ";
    t.diameter = CheckIntInput();
    t.status = true;
}

void AddCS(CS& cs) {
    cout << "Введите название компрессорной станции: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, cs.name);
    cout << "Введите количество цехов: ";
    cs.count = CheckIntInput();
    cout << "Введите количество цехов в работе: ";
    cs.inwork = CheckIntInput();
    while (cs.inwork > cs.count) {
        cout << "Количество работающих цехов не может превышать общее количество! Введите снова: ";
        cs.inwork = CheckIntInput();
    }
    cout << "Введите класс станции: ";
    cin >> cs.category;
}

void ShowPipe(const Pipe& t) {
    if (t.name.empty()) {
        cout << "Труба не добавлена" << endl;
        return;
    }
    cout << "=== Труба ===" << endl;
    cout << "Название: " << t.name << endl;
    cout << "Длина: " << t.length << endl;
    cout << "Диаметр: " << t.diameter << endl;
    cout << "В ремонте: " << (t.status ? "Да" : "Нет") << endl;
}

void ShowCS(const CS& cs) {
    if (cs.name.empty()) {
        cout << "Компрессорная станция не добавлена" << endl;
        return;
    }
    cout << "=== Компрессорная станция ===" << endl;
    cout << "Название: " << cs.name << endl;
    cout << "Количество цехов: " << cs.count << endl;
    cout << "Цехов в работе: " << cs.inwork << endl;
    cout << "Класс станции: " << cs.category << endl;
}

void EditPipeStatus(Pipe& t) {
    if (t.name.empty()) {
        cout << "Сначала добавьте трубу!" << endl;
        return;
    }
    cout << "Текущий статус ремонта: " << (t.status ? "В ремонте" : "Не в ремонте") << endl;
    cout << "Изменить статус? (1 - да, 0 - нет): ";
    int choice;
    cin >> choice;
    if (choice == 1) {
        t.status = !t.status;
        cout << "Статус изменен на: " << (t.status ? "В ремонте" : "Не в ремонте") << endl;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void EditCSWorkshops(CS& cs) {
    if (cs.name.empty()) {
        cout << "Сначала добавьте компрессорную станцию!" << endl;
        return;
    }
    cout << "Текущее состояние: " << cs.inwork << " из " << cs.count << " цехов в работе" << endl;
    cout << "1. Запустить цех\n2. Остановить цех\n3. Отмена\nВыберите действие: ";
    int choice;
    cin >> choice;
    switch (choice) {
    case 1:
        if (cs.inwork < cs.count) {
            cs.inwork++;
            cout << "Цех запущен. Теперь " << cs.inwork << " из " << cs.count << " цехов в работе" << endl;
        }
        else {
            cout << "Все цехи уже работают!" << endl;
        }
        break;
    case 2:
        if (cs.inwork > 0) {
            cs.inwork--;
            cout << "Цех остановлен. Теперь " << cs.inwork << " из " << cs.count << " цехов в работе" << endl;
        }
        else {
            cout << "Нет работающих цехов!" << endl;
        }
        break;
    case 3:
        cout << "Отмена операции" << endl;
        break;
    default:
        cout << "Неверный выбор!" << endl;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void SaveToFile(const Pipe& t, const CS& cs) {
    ofstream outFile("data.txt");
    if (!outFile.is_open()) {
        cout << "Ошибка открытия файла для записи!" << endl;
        outFile.close();
        return;
    }
    outFile << "PIPE" << endl;
    outFile << t.name << endl;
    outFile << t.length << endl;
    outFile << t.diameter << endl;
    outFile << t.status << endl;

    outFile << "CS" << endl;
    outFile << cs.name << endl;
    outFile << cs.count << endl;
    outFile << cs.inwork << endl;
    outFile << cs.category << endl;

    outFile.close();
    cout << "Данные успешно сохранены в файл 'data.txt'" << endl;
}


void LoadFromFile(Pipe& t, CS& cs) {
    ifstream inFile("data.txt");
    if (!inFile.is_open()) {
        cout << "Файл 'data.txt' не найден или не может быть открыт!" << endl;
        return;
    }
    string marker;
    // Загрузка данных трубы
    getline(inFile, marker);
    if (marker != "PIPE") {
        cout << "Ошибка формата файла!" << endl;
        inFile.close();
        return;
    }

    getline(inFile, t.name);
    inFile >> t.length;
    inFile >> t.diameter;
    inFile >> t.status;
    inFile.ignore(numeric_limits<streamsize>::max(), '\n');

    // Загрузка данных КС
    getline(inFile, marker);
    if (marker != "CS") {
        cout << "Ошибка формата файла!" << endl;
        inFile.close();
        return;
    }

    getline(inFile, cs.name);
    inFile >> cs.count;
    inFile >> cs.inwork;
    inFile >> cs.category;
    inFile.ignore(numeric_limits<streamsize>::max(), '\n');

    inFile.close();
    cout << "Данные успешно загружены из файла 'data.txt'" << endl;
}

void menu(Pipe& t, CS& cs) {
    int option;
    while (true) {
        cout << "\nВыберите действие: \n1. Добавить трубу\n2. Добавить КС\n3. Просмотр всех объектов\n4. Редактировать трубу\n5. Редактировать КС\n6. Сохранить\n7. Загрузить\n0. Выход\n";
        cout << "Ваш выбор: ";
        cin >> option;

        switch (option) {
        case 1:
            AddPipe(t);
            break;
        case 2:
            AddCS(cs);
            break;
        case 3:
            ShowPipe(t);
            ShowCS(cs);
            break;
        case 4:
            EditPipeStatus(t);
            break;
        case 5:
            EditCSWorkshops(cs);
            break;
        case 6:
            SaveToFile(t, cs);
            break;
        case 7:
            LoadFromFile(t, cs);
            break;
        case 0:
            cout << "Выход из программы..." << endl;
            return;
        default:
            cout << "Неверный выбор! Попробуйте снова." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");
    Pipe pipe;
    CS cs;
    menu(pipe, cs);
    return 0;
}