#include <iostream>
#include <iomanip>
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
using namespace std;

void getvalue(int &a)
{
    while (true) {
        cin >> a;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(32767, '\n');
            cout << "Вы ввели некорректное значение, попробуйте еще раз\n";
            continue;
        }
        cin.ignore(32767, '\n');
        if (std::cin.gcount() > 1) {
            cout << "Вы ввели некорректное значение, попробуйте еще раз\n";
            continue;
        }
        break;
    }
}

typedef struct node {
    int data;
    int* arr;
    node *next;
};

void print(node *head) {
    node *current = head;
    if (current == NULL) { cout << "Список пуст\n"; }
    else {
        cout << "Список: \n";
        int i = 0;
        while (current != NULL) {
            cout << i << ": Число: " << current->data << " Массив: ";
            for (int t = 0; t < current->data; ++t) {
                cout << current->arr[t]; 
                cout << " ";
            }
            cout << "Следующий: " << (void*)current->next << endl;
            i += 1;
            current = current->next;
        }
    }
}

void push(node *&head) {
    int data = 0;
    int* arr = NULL;
    if (head == NULL) {
        head = (node*)malloc(sizeof(node));
        cout << "Введите число: ";
        getvalue(data);
        head->arr = (int*)malloc(sizeof(int) * data);
        cout << "Введите массив:\n";
        for (int i = 0; i < data; ++i) {
            cout << "a[" << i << "] = ";
            getvalue(head->arr[i]);
        }
        head->data = data;
        head->next = NULL;
    }
    else {
        node* current = head;
        int i = 1;
        while (current->next != NULL) {
            current = current->next;
            i += 1;
        }
        if (i > 199) {
            cout << "Список не может содержать больше 200 элементов\n";
            return;
        }
        current->next = (node*)malloc(sizeof(node));
        cout << "Введите число: ";
        getvalue(data);
        current->next->arr = (int*)malloc(sizeof(int) * data);
        cout << "Введите массив:\n";
        for (int i = 0; i < data; ++i) {
            cout << "a[" << i << "] = ";
            getvalue(current->next->arr[i]);
        }
        current->next->data = data;
        current->next->next = NULL;
    }
}

void remove(node** head, int n) {
    int i = 0;
    node* current = *head;
    node* temp = NULL;
    if (*head == NULL) {
        cout << "Список пуст\n";
        return;
    }
    if (n == 0) {
        temp = (*head)->next;
        free((*head)->arr);
        free(*head);
        *head = temp;
        cout << "Элемент удален\n";
        return;
    }
    for (int i = 0; i < n - 1; i++) {
        if (current->next == NULL) {
            cout << "Элемент не найден\n";
            return;
        }
        current = current->next;
    }
    temp = current->next;
    current->next = temp->next;
    free(temp->arr);
    free(temp);
    cout << "Элемент удален\n";
}

void purify(node** head) {
    node* temp = NULL;
    while (*head != NULL) {
        temp = (*head)->next;
        free((*head)->arr);
        free(*head);
        *head = temp;
    }
    cout << "Элементы удалены\n";
}

int main()
{
    setlocale(0, "");
    _CrtMemState s1;
    _CrtMemCheckpoint(&s1);
    node* list = NULL;
    int k = 0;
    bool loop = true;
    while (loop == true) {
        cout << "\n1 - Добавить элемент в список\n" << "2 - Вывести список на экран\n" << "3 - Удалить элемент из списка\n" << "4 - Удалить все элементы списка\n" << "5 - Выход\n\n";
        int command = 0;
        getvalue(command);
        switch (command) {
            case 1: { 
                push(list); 
                break;
            }
            case 2: { 
                print(list); 
                break;
            }
            case 3: {
                cout << "Введите номер элемента, который будет удален\n";
                getvalue(k);
                remove(&list, k);
                break;
            }
            case 4: { 
                purify(&list); 
                break;
            }
            case 5: { 
                loop = false;
                purify(&list);
                break;
            }
        }
    }
    _CrtMemDumpStatistics(&s1);
    _CrtDumpMemoryLeaks();
    return 0;
}
