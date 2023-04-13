#include <ncurses.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

void Start(); // Шоб не вийобувалось на послідовність функції

struct user // Структура. name імя ігрока яке він вводить. lastname фамілія ігрока яку він вводить
{
    char name [20];
    char lastname [20];
};

void dinasour1(int y, int x) // Перша моделька динозаврика
{
	init_pair(7, COLOR_CYAN, COLOR_BLACK); // Вибір палітри кольорів. COLOR_CYAN колір шрифту. COLOR_BLACK колір фону 
    attron(COLOR_PAIR(7));                 // Включення вибраного кольору
    mvprintw(y-4, x, "          e-e  ");
	mvprintw(y-3, x, "        /(\\_/)");
	mvprintw(y-2, x, ",___.--` /'-` ");
	mvprintw(y-1, x, " '-._, )/'");
	mvprintw(y, x,   "      \\/");
    attroff(COLOR_PAIR(7));                // Виключення вибраного кольору
}

void dinasour2(int y, int x) // Друга моделька динозаврика
{
	init_pair(7, COLOR_CYAN, COLOR_BLACK);
    attron(COLOR_PAIR(7));
    mvprintw(y-4, x, "          e-e  ");
	mvprintw(y-3, x, "        /(\\_/)");
	mvprintw(y-2, x, ",___.--` /'-` ");
	mvprintw(y-1, x, " '-._, )/'");
	mvprintw(y, x,   "      /\\");
    attroff(COLOR_PAIR(7));
}

void clearDinasourDown(int diY, int diX) // Нижнє очищення динозаврика
{
	mvprintw(diY+3, diX+10, "        ");
	mvprintw(diY+4, diX+8, "        ");
	mvprintw(diY+5, diX, "             ");
	mvprintw(diY+6, diX, "           ");
	mvprintw(diY+7, diX, "          "); 
}

void clearDinasourUp(int diY, int diX) // Верхнє очищення динозаврика
{
    
    mvprintw(diY-7, diX+4, "         ");
	mvprintw(diY-8, diX+1, "               ");
	mvprintw(diY-9, diX, "             ");
	mvprintw(diY-10, diX, "                 ");
	mvprintw(diY-11, diX+8, "     ");

}

void cactus1(int y, int x) // Перша моделька кактуса
{
	init_pair(6,COLOR_BLUE,COLOR_BLACK);
    attron(COLOR_PAIR(6));
    mvprintw(y-5, x, "    _ ");
	mvprintw(y-4, x, " _ ( )   ");
	mvprintw(y-3, x, "( \\| | _");
	mvprintw(y-2, x, " \\,. |/ )");
	mvprintw(y-1, x, "   |  /'");
	mvprintw(y, x, "   | |");
    attroff(COLOR_PAIR(6));
}

void cactus2(int y, int x) // Друга моделька кактуса
{
	init_pair(5,COLOR_GREEN,COLOR_BLACK);
	attron(COLOR_PAIR(5));
	mvprintw(y-6, x, "    _");
	mvprintw(y-5, x, "   ( ) _");
	mvprintw(y-4, x, "  _| |/ )");
	mvprintw(y-3, x, " ( \\  /'");
	mvprintw(y-2, x, "  \\  |");
	mvprintw(y-1, x, "   | |");
	mvprintw(y, x, "   | |");
	attroff(COLOR_PAIR(5));
}

void clearCactus(int y, int x) // Очищення кактуса
{
	// Якщо кактус перед динозавриком
    mvprintw(y-6, x+8, "        ");
	mvprintw(y-5, x+9, "           ");
	mvprintw(y-4, x+10, "             ");
	mvprintw(y-3, x+9, "              ");
	mvprintw(y-2, x+10, "                ");
	mvprintw(y-1, x+10, "                 ");
	mvprintw(y, x+10, "      ");
	// Якщо кактус під динозавриком
    if (x <= 10) 
    {
	mvprintw(y-6,  1,   "                  ");
	mvprintw(y-5,  1,   "                  ");
	mvprintw(y-4,  1,   "                  ");
	mvprintw(y-3,  1,   "                  ");
	mvprintw(y-2,  1,   "                  ");
	mvprintw(y-1,  1,   "                  ");
	mvprintw(y,    1,   "                  ");
	}
}

void sun(int y, int x) // Моделька сонця
{
    init_pair(3, COLOR_YELLOW,COLOR_BLACK);
    attron(COLOR_PAIR(3));
	mvprintw(y-8, x, "      ;   :   ;");
	mvprintw(y-7, x, "   .   \\_,!,_/   ,");
	mvprintw(y-6, x, "    `.,'     `.,'");
	mvprintw(y-5, x, "     /         \\");
	mvprintw(y-4, x, "~ -- :         : -- ~");
	mvprintw(y-3, x, "     \\         /");
	mvprintw(y-2, x, "    ,'`._   _.'`.");
	mvprintw(y-1, x, "   '   / `!` \\   `");
	mvprintw(y, x, "      ;   :   ;");
    attroff(COLOR_PAIR(3));
}

int times (int delay) // Зміна швидкості
{
    if (delay >= 150000) delay -=900;
    else if (delay >= 100000) delay -=600;
    else delay -= 200;
    return delay;
}

void Menu() // Меню гри ///
{
	struct user firstUser; // Підключення структури

	int maxX = getmaxx(stdscr)/2; // Половина максимальної широти вікна
	int maxY = getmaxy(stdscr)/2; // Половина максимальної висоти вікна

	init_pair(3,COLOR_GREEN,COLOR_BLACK);
	attroff(COLOR_PAIR(3));
	mvprintw(maxY+1, maxX-24, "Stlacte Enter pre start hry.");
	mvprintw(maxY+2, maxX-21, "Stlecte Space pre skok!");
	mvprintw(maxY+3, maxX-15, "Meno: ");
	getstr(firstUser.name); // Отримання Імя ігрока
	mvprintw(maxY+4, maxX-15, "Priezvisko: ");
	getstr(firstUser.lastname); // Отримання Фамілії ігрока
	noecho(); // щоб не відобржались Імя і Фамілія на тому місці де вони вводились  
    Start(firstUser); // Старт гри
}

int checkGame(int y, int x, int diY, int diX) // Провірка на зіткнення динозаврика і кактуса
{
	if (diY == y) {        
		if (abs((diX+14)-x) <= 4) // Провірка колізії Динозаврики і Кактуса якщо зіткнулись повертає 0
        {
            return 0;
        }
	}
	return 1;
}

void endGame (int score, int diY, int diX, struct user firstUser) // Завершення гри або рестарт
{
    
    nodelay(stdscr, FALSE); // Зупинка часу
    init_pair(2, COLOR_RED, COLOR_BLACK);
    int maxYY = getmaxy(stdscr);    // Максимальня висота вікна гри
    int maxX = getmaxx(stdscr) / 2; // Половина максимальної широти вікна
    int maxY = getmaxy(stdscr) / 2; // Половина максимальної висоти вікна
    attron(COLOR_PAIR(2));
    mvprintw(diY + 11, maxX - 8, "Game Over!");
    mvprintw(diY + 13, maxX - 15, "Press 'r' to play again");
    mvprintw(diY + 15, maxX - 15, "Or 'q' to exit from game.");
    mvprintw(maxYY - 10, diX, "          X-X "); // Зміна очей динозаврика при програші
    mvprintw(maxYY - 6, diX, "      ||");        // зміна ніг динозаврика при програші
    char Exit = getch();  // Отримання віршення ігрока
    if (Exit == 'r')      // Рестарт гри
    {
        attroff(COLOR_PAIR(2));
        Start(firstUser);
    }
    else if (Exit == 'q') return; // Вихід з гри
    else endGame(score, diY, diX, firstUser); // Якщо ігрок ввів не дозволений символ, рестарт функції
}

void showDin (int diY, int diX) // Вивід модельок динозаврика, щоб казалось що він біжить
{
    static int count = 0;

    if (count == 0)
    {
        dinasour1(diY, diX); // Вивід першої модельки динозаврика
        count++;
    }
    else
    {
        dinasour2(diY, diX); // Вивід другої можельки динозаврика
        count--;
    }
}

void Start (struct user firstUser) // Основна функція гри (логіка)
{
    srand(time(NULL)); // Шоб rand вибирав рандомне значення а не лише одне
    int x, y, diX = 5, score = 0, delay = 200000, gameStatus = 1, cactusNum = 0, prize = 0, userPrize = 0; // Перемінні для гри
    int maxX = getmaxx(stdscr); // Отримання максимальної ширини віна
    x = maxX - 20;
    y = getmaxy(stdscr) - 6; // Отримання максимальної висоти віна - 6
    int diY = y;
    int arrowX = (diX + 15), arrowY = (diY - 3);
    bool fire = FALSE;
    int jumping = -1;
    char userInput; // char для вводу ігрока
    clear(); // Очищення вікна
    nodelay(stdscr, TRUE); // щоб щас запустився
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(4, COLOR_BLUE, COLOR_BLACK);
    while (gameStatus = 1) // Цикл гри 
    {
        mvprintw(1, 6, "%s %s", firstUser.name, firstUser.lastname); // Вивід Іменні та Фамілії ігрока
        userInput = getch(); // Отримання вводу гравця
        attron(COLOR_PAIR(1));
        sun(10, (maxX / 2) - 10); // Вивід Сонця
        score++;
        mvprintw(1, getmaxx(stdscr) - 9, "%d", score); // Вивід очків гравця
        box (stdscr, ACS_VLINE, ACS_HLINE); // колізія Кактуса і Динозаврика
        clearDinasourUp(diY, diX); // очищення верхньої частини динозаврика
        if (x <= 7)
        {
            x = getmaxx(stdscr) - 20;
            cactusNum = rand() % 2; // Вибір одного з двох кактусів
        }
        if (userInput == ' ' && jumping < 0) // Стрибок динозаврика
        {
            diY -= 7;
            jumping = 5;
        }
        showDin(diY, diX); // Вивід динозаврика
        if (userInput == ' ') clearDinasourDown(diY, diX); // Очищення нижньої часті Динозаврика
        if (x - diX <= 7) x -= 10;
        if(cactusNum == 0) cactus1(y, x); // Вивід першого Кактусу
        else cactus2(y, x);               // Вивід другого Кактусу
        if (x - diX <= 7) x += 10;
        gameStatus = checkGame (y, x, diY,diX); // провірка на закінчення гри
        if (gameStatus == 0) 
        {
            clearCactus(y, x); // очищення Кактусу при смерті
            break;
        }
        jumping--;
        if (jumping == 0) diY += 7;
        mvhline (y + 1, 1, '-', getmaxx(stdscr) - 3);
        refresh(); // Вивід всієї картинки
        clearCactus(y, x - 1); // Просто очищення Кактусу
        refresh(); // Вивід того що був очищений Кактус
        usleep(delay); // Засипання на час швидкості, чим вона менше тим швидкішою буде гра
        x -=7;
        delay == times(delay); // Отримання швидкості
        userInput = 'q'; // Заглушка для char
    }
    endGame(score, diX, diX, firstUser); // Вивід екрану смерті
    attroff(COLOR_PAIR(1)); // Виключення кольорів
}

int main () // Включення коду
{
    initscr();        // Ініціалізація вікна
    start_color();    // Ініціалізація кольорів
    curs_set(FALSE);  // Відключення курсору
    Menu();           // Старт меню
    endwin();         // правильний вихід з вікна гри
}