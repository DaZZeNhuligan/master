#include <iostream> // Для ввода/вывода через консоль (cin, cout)
#include <fstream>  // Для работы с файлами (ifstream, ofstream)
#include <cstring>  // Для работы со строками (char[])
#include <iomanip>  // Для красивого форматирования вывода (setw, left)
#include <clocale>



using namespace std;// для того чтобы не писать std:: перед каждым cout, cin и т.д.

//создаем константу максимального количества книг по задаче 
const int MAX_BOOK = 1000;

//Создадим структуру для файла 
struct Book
{
   char name[100]; //строка под имя книги до 100 символов
   char autor[50]; //строка под автора до 50 символов
   char date[5]; // строка даты прочтения (именно год)
   float rating; // рейтинг книжки(оценка книги)
};
// Глобальный массив для хранения всех книг
Book book[MAX_BOOK];
int bookcount = 0; //это счетчик книжек на данный момент 

// Создадим функцию для загрузки прочитанных книжек из файла
void loadBook(const char *filename)
{
ifstream fin(filename); // Открываем файл на чтение

if (!fin)
 return; // Если файл не найден — выходим из функции

 // Чтение данных построчно, пока есть что читать
 while( (bookcount < MAX_BOOK) && (fin >> book[bookcount].name >> book[bookcount].autor >> book[bookcount].date >> book[bookcount].rating)){

  bookcount++;// Увеличиваем счётчик после успешного чтения 

 }
    // Если в файле больше записей — их просто игнорируем после достижения лимита
    fin.close();
}

// --- Функция для сохранения одной оценки книги в файл ---
void saveBookToFile(const char *filename, Book b){
    ofstream fout(filename, ios::app); // Открываем файл в режиме добавления (append)
  
    if (!fout)
    {
        cout << "Ошибка при сохранении файла!" << endl;
        return;
    }

    // Записываем название, автора, дату и рейтинг в файл через пробел
    fout << b.name << " " << b.autor << " " << b.date << " " << b.rating << endl;

    fout.close(); // Закрываем файл
}

// --- Функция для добавления новой книги ---
void addBook()
{

    // Проверяем, не превышен ли лимит
    if (bookcount >= MAX_BOOK)
    {
        cout << "Превышен лимит книг!" << endl;
        return;
    }

    Book b; // Создаём новую переменную для книг

    cout << "Введите название книги: ";
    cin >> ws;                // <-- теперь читает строку с пробелами
    cin.getline(b.name, 100); // читает строку с пробелами

    cout << "Введите автора книги: ";
    cin.getline(b.autor, 50);

    cout << "Введите год прочтения: ";
    cin.getline(b.date, 5);   

    cout << "Ваша оценка книги (0-10): ";
    cin >> b.rating;

    // Добавляем в массив и сохраняем в файл
    book[bookcount++] = b;
    saveBookToFile("books.txt", b);

    cout << "Книга добавлена!\n";
}

// --- Функция для отображения всех книг ---
void showAllBook()
{
   
    if (bookcount == 0)
    {
        cout << "Нет данных о книгах.\n";
        return;
    }

    // Заголовок таблицы
    cout << "\n--- Все книги ---\n";
    cout << left << setw(36) << "Название" << setw(20) << "Автор"   //---Флаги для отображения ---
         
        << setw(28) << "Год прочтения"
        << setw(10) << "Оценка\n";
    cout << "-----------------------------------------------------------------------------------\n";

    // Выводим каждую запись
    for (int i = 0; i < bookcount; i++)
    {
         
        cout << left << setw(50) << book[i].name
             <<  setw(25) << book[i].autor
             << setw(15) << book[i].date
             << setw(15) << book[i].rating << "\n";
    }
}

// --- Функция для вывода статистики ---
void showStatsBook()
{
  
    if (bookcount == 0)
    {
        cout << "Нет данных.\n";
        return;
    }

   float totalBook = 0;                // Общее количество книг рейтинга
    float maxRaiting = book[0].rating; // Самая большая оценка книги (начинаем с первой)

    // Считаем сумму и находим максимум
    for (int i = 0; i < bookcount; i++)
    {
        totalBook += book[i].rating;

        if (book[i].rating > maxRaiting )
        {
           maxRaiting = book[i].rating;
        }
    }

    float average = totalBook / bookcount; // Среднее значение

    // Выводим статистику
    cout << "\n--- Статистика ---\n";
    cout << "Всего книг: " << bookcount << " книг\n";
    cout << "Средняя оценка: " << average<< " \n";
    cout << "Максимальная оценка: " << maxRaiting << "\n" ;
}


// --- Функция для отображения меню пользователя ---
void showMenu()
{
   
    cout << "\n=== Трекер книг ===\n";
    cout << "1. Добавить книгу\n";
    cout << "2. Показать все книги\n";
    cout << "3. Показать статистику\n";
    cout << "4. Выход\n";
    cout << "Выберите пункт: ";
}

// --- Главная функция программы ---
int main()
{


   setlocale(LC_ALL, "Russian");

    loadBook("books.txt"); // Загружаем данные из файла (если он есть)

    int choice; // Переменная для хранения выбора пользователя

    // Основной цикл меню
    do
    {
        showMenu();    // Показываем меню
        cin >> choice; // Считываем выбор

        // Выполняем действия по выбору
        switch (choice)
        {
        case 1:
            addBook(); // Добавить книгу
            break;
        case 2:
            showAllBook(); // Показать все книги
            break;
        case 3:
            showStatsBook(); // Показать статистику
            break;
        case 4:
            cout << "Выход из программы.\n"; // Завершение
            break;
        default:
            cout << "Неверный выбор.\n"; // Ошибка выбора
        }

    } while (choice != 4); // Пока пользователь не выбрал "Выход"

    return 0; // Возвращаем 0 — признак успешного завершения
}
