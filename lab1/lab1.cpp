// lab1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>

using namespace std;

struct Pipe {
    string name="";
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
    cout << "Insert pipe name: ";
    getline(cin, t.name);
    cout << "Insert pipe length: ";
    CheckDoubleInput(t.length);
}

void CheckDoubleInput(double length) {
    while (true) {
        cin >> length;
        if (cin.fail() || length <= 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Insert positive number!" << endl;
        }
        else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return length;
        }
    }
}

void ShowPipe(Pipe& t) {
    cout << "Название: " << t.name << endl;
    cout << "Длина: " << t.length << endl;
    cout << "Диаметр: " << t.diameter << endl;
    cout << "В ремонте: " << (t.status? "Да" : "Нет") << endl;
}
void menu(Pipe& t, CS& cs) {
    int option;
    while (true){
        cout << "Выберите действие: \n 1. Добавить трубу; \n 2.Добавить КС; \n 3.Просмотр всех объектов; \n 4.Редактировать трубу; \n 5.Редактировать КС; \n 6.Сохранить; \n 7.Загрузить; \n 0.Выход;";
        cin >> option;
        switch (option) {
        case 1:
        {
            AddPipe(t)
            break
        }
        case 2:
        {
            
            break
        }
        case 3:
        {
            ShowPipe()
            
            break
        }
        case 4:
        {

            break
        }
        case 5:
        {

            break
        }
        case 6:
        {

            break
        }
        case 7:
        {

            break
        }
        case 0:
        {

            break
        }
        }
    }
}

int main()
{
    std::cout << "Hello World!\n";
    Pipe pipe;
    CS cs;
    menu(pipe,cs);
    return 0;
}
