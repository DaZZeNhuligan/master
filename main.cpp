#include <iostream> // ��� �����/������ ����� ������� (cin, cout)
#include <fstream>  // ��� ������ � ������� (ifstream, ofstream)
#include <cstring>  // ��� ������ �� �������� (char[])
#include <iomanip>  // ��� ��������� �������������� ������ (setw, left)

using namespace std; // ����� �� ������ std:: ����� ������ cout, cin � �.�.

const int MAX_EXPENSES = 1000; // ������������ ���������� ��������, ������� ����� ���������

// ��������� ��� ������ �������
struct Expense
{
    char date[11];     // ������ ��� ���� (������: "��.��.����", ��������: "24.09.2025")
    char category[30]; // ������ ��� ��������� (��������: "���", "���������")
    float amount;      // ����� ������� � ������
};

// ���������� ������ ��� �������� ���� ��������
Expense expenses[MAX_EXPENSES];
int expenseCount = 0; // ������� ���������� ������� ��������

// --- ������� ��� �������� �������� �� ����� ---
void loadExpenses(const char *filename)
{
    ifstream fin(filename); // ��������� ���� �� ������

    if (!fin)
        return; // ���� ���� �� ������ � ������� �� �������

    // ������ ������ ���������, ���� ���� ��� ������
    while (fin >> expenses[expenseCount].date >> expenses[expenseCount].category >> expenses[expenseCount].amount)
    {
        expenseCount++; // ����������� ������� ����� ��������� ������
    }

    fin.close(); // ��������� ����
}

// --- ������� ��� ���������� ������ ������� � ���� ---
void saveExpenseToFile(const char *filename, Expense e)
{
    setlocale(LC_ALL, "Russian");
    ofstream fout(filename, ios::app); // ��������� ���� � ������ ���������� (append)

    if (!fout)
    {
        cout << "������ ��� ���������� �����!" << endl;
        return;
    }

    // ���������� ����, ��������� � ����� � ���� ����� ������
    fout << e.date << " " << e.category << " " << e.amount << endl;

    fout.close(); // ��������� ����
}

// --- ������� ��� ���������� ������ ������� ---
void addExpense()
{
    setlocale(LC_ALL, "Russian");
    // ���������, �� �������� �� �����
    if (expenseCount >= MAX_EXPENSES)
    {
        cout << "�������� ����� ��������!" << endl;
        return;
    }

    Expense e; // ������ ����� ���������� ��� �������

    // ��������� ������ �� ������������
    cout << "������� ���� (��.��.����): ";
    cin >> e.date;

    cout << "������� ���������: ";
    cin >> e.category;

    cout << "������� �����: ";
    cin >> e.amount;

    // ��������� � ������ � ��������� � ����
    expenses[expenseCount++] = e;
    saveExpenseToFile("expenses.txt", e);

    cout << "������ ��������!\n";
}

// --- ������� ��� ����������� ���� �������� ---
void showAllExpenses()
{
    setlocale(LC_ALL, "Russian");
    if (expenseCount == 0)
    {
        cout << "��� ������ � ��������.\n";
        return;
    }

    // ��������� �������
    cout << "\n--- ��� ������� ---\n";
    cout << left << setw(12) << "����"
         << setw(15) << "���������"
         << "�����\n";
    cout << "------------------------------\n";

    // ������� ������ ������
    for (int i = 0; i < expenseCount; i++)
    {
        cout << left << setw(12) << expenses[i].date
             << setw(15) << expenses[i].category
             << expenses[i].amount << " ���.\n";
    }
}

// --- ������� ��� ������ ���������� ---
void showStats()
{
    setlocale(LC_ALL, "Russian");
    if (expenseCount == 0)
    {
        cout << "��� ������ ��� �������.\n";
        return;
    }

    float total = 0;                // ����� �����
    float max = expenses[0].amount; // ����� ������� ����� (�������� � ������)

    // ������� ����� � ������� ��������
    for (int i = 0; i < expenseCount; i++)
    {
        total += expenses[i].amount;

        if (expenses[i].amount > max)
        {
            max = expenses[i].amount;
        }
    }

    float average = total / expenseCount; // ������� ��������

    // ������� ����������
    cout << "\n--- ���������� ---\n";
    cout << "����� ���������: " << total << " ���.\n";
    cout << "������� �����: " << average << " ���.\n";
    cout << "������������ �����: " << max << " ���.\n";
}

// --- ������� ��� ����������� ���� ������������ ---
void showMenu()
{
    setlocale(LC_ALL, "Russian");
    cout << "\n=== ������ �������� ===\n";
    cout << "1. �������� ������\n";
    cout << "2. �������� ��� �������\n";
    cout << "3. �������� ����������\n";
    cout << "4. �����\n";
    cout << "�������� �����: ";
}

// --- ������� ������� ��������� ---
int main()
{
    setlocale(LC_ALL, "Russian");
    loadExpenses("expenses.txt"); // ��������� ������ �� ����� (���� �� ����)

    int choice; // ���������� ��� �������� ������ ������������

    // �������� ���� ����
    do
    {
        showMenu();    // ���������� ����
        cin >> choice; // ��������� �����

        // ��������� �������� �� ������
        switch (choice)
        {
        case 1:
            addExpense(); // �������� ������
            break;
        case 2:
            showAllExpenses(); // �������� ��� �������
            break;
        case 3:
            showStats(); // �������� ����������
            break;
        case 4:
            cout << "����� �� ���������.\n"; // ����������
            break;
        default:
            cout << "�������� �����.\n"; // ������ ������
        }

    } while (choice != 4); // ���� ������������ �� ������ "�����"

    return 0; // ���������� 0 � ������� ��������� ����������
}
