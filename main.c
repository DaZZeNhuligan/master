// версия на C 
#include <stdio.h>
#include <string.h>
#include <locale.h>



#define MAX_EXPENSES 1000

// Структура расхода 
struct Expense {
    char date[11];     // формат "dd.mm.yyyy" + '\0' 
    char category[30]; 
    float amount;
};

//Глобальные данные 
struct Expense expenses[MAX_EXPENSES];
int expenseCount = 0;

// Загрузка из файла 
// формат строки: date category amount 
void loadExpenses(const char *filename)
{
    FILE *fin = fopen(filename, "r");
    if (!fin) return;

    while (expenseCount < MAX_EXPENSES &&
           fscanf(fin, "%10s %29s %f",
                  expenses[expenseCount].date,
                  expenses[expenseCount].category,
                  &expenses[expenseCount].amount) == 3)
    {
        expenseCount++;
    }
    fclose(fin);
}


// Функция сохранения записи
void saveExpenseToFile(const char *filename, struct Expense e)
{
    FILE *fout = fopen(filename, "a");
    if (!fout) { puts("Ошибка при сохранении файла!"); return; }
    fprintf(fout, "%s %s %.2f\n", e.date, e.category, e.amount);
    fclose(fout);
}

// Функция добавления расходов
void addExpense(void)
{
    if (expenseCount >= MAX_EXPENSES) {
        puts("Превышен лимит расходов!");
        return;
    }

    struct Expense e;
    printf("Введите дату (дд.мм.гггг): ");
    if (scanf("%10s", e.date) != 1) return;

    printf("Введите категорию: ");
    if (scanf("%29s", e.category) != 1) return;

    printf("Введите сумму: ");
    if (scanf("%f", &e.amount) != 1) return;

    expenses[expenseCount++] = e;
    saveExpenseToFile("expenses.txt", e);

    puts("Расход добавлен!");
}

// Функция показа расходов
void showAllExpenses(void)
{
    if (expenseCount == 0) {
        puts("Нет данных о расходах.");
        return;
    }

    const int W_DATE = 12, W_CAT = 15;
    puts("\n--- Все расходы ---");
    printf("%-*s%-*s%s\n", W_DATE, "Дата", W_CAT, "Категория", "Сумма");
    puts("------------------------------");

    for (int i = 0; i < expenseCount; ++i) {
        printf("%-*s%-*s%.2f руб.\n",
               W_DATE, expenses[i].date,
               W_CAT,  expenses[i].category,
               expenses[i].amount);
    }
}

// Функция статистики
void showStats(void)
{
    if (expenseCount == 0) {
        puts("Нет данных для анализа.");
        return;
    }

    float total = 0.0f;
    float maxv  = expenses[0].amount;

    for (int i = 0; i < expenseCount; ++i) {
        total += expenses[i].amount;
        if (expenses[i].amount > maxv) maxv = expenses[i].amount;
    }
    printf("\n--- Статистика ---\n");
    printf("Всего потрачено: %.2f руб.\n", total);
    printf("Средняя трата:   %.2f руб.\n", total / expenseCount);
    printf("Максимальная:    %.2f руб.\n", maxv);
}

// Функция меню
void showMenu(void)
{
    puts("\n=== Трекер расходов ===");
    puts("1. Добавить расход");
    puts("2. Показать все расходы");
    puts("3. Показать статистику");
    puts("4. Выход");
    printf("Выберите пункт: ");
}

// Функция мейн
int main(void)
{

    setlocale(LC_ALL, "Russian"); // для отображения русского языка

    loadExpenses("expenses.txt");

    int choice;
    do {
        showMenu();
        if (scanf("%d", &choice) != 1) { choice = 0; }

        switch (choice) {
            case 1: addExpense();      break;
            case 2: showAllExpenses(); break;
            case 3: showStats();       break;
            case 4: puts("Выход из программы."); break;
            default: puts("Неверный выбор.");
        }
    } while (choice != 4);

    return 0;
}
