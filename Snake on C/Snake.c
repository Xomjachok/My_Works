#include <time.h>
#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#define DELAY 45000
#define TIMEOUT 10
#define FOOD "  "
#define FOOD_COLOR COLOR_RED

    typedef enum                                    // Глобальні перемінні напрямку для гри 
    {
        UP,
        DOWN,
        LEFT,
        RIGHT,
    } direction_type;

    typedef struct Point                            // Координати екрану для змійки і фруктів
    {
        int x;
        int y;
    } Point;

    int x = 0, y = 0, maxY = 0, maxX = 0, 
    nextX = 0, nextY = 0, Length = 5, score = 0;    // перемінні для гри
    
    bool gameover = false;
    direction_type currentDir = RIGHT;              // Напрямок
    Point snakeParts[255] = {};                     // Довжинна змійки
    Point food;                                     // Маркер на яблуко

    void createFood() 
    {
        food.x = (rand() % (maxX - 20)) + 10;       // Рандомна точка по Х для яблука
        food.y = (rand() % (maxY - 10)) + 5;        //  Рандомна точка по У для яблука
    }

    void drawPart(Point drawPoint)
    {
        start_color();                              // Необхідна функція для запуску використання кольорів
        init_pair(1, COLOR_RED, COLOR_RED);        // Кольорова палітра
        attron(COLOR_PAIR(1));                      // Старт використання кольорів
        mvprintw(drawPoint.y, drawPoint.x, FOOD);   // Вивід яблука
        attroff(COLOR_PAIR(1));                     // Завершення використання кольорів
    }

    void cursesExec()
    {
        initscr();                                  // Ініціалізація вікна
        noecho();                                   // Щоб не виводило нажаті клавіші
        keypad(stdscr, TRUE);                       // Юзання клави
        cbreak();                                   // Заборона буферзації
        timeout(TIMEOUT);
        curs_set(FALSE);                            // Без курсора
        getmaxyx (stdscr, maxY, maxX);
    }

    void exec()
    {
        srand(time(NULL));                          // Вибір рандомного чвсу для функції ранд
        currentDir = RIGHT;                         // направлення змійки в самому початку
        Length = 5;                                 // Довжинна змійки
        gameover = false;
        score = 0;                                  // Рахунок
        

        clear();                                    // Очистка 
        int count = 0;
        for (int i = Length; i >= 0; i--)
        {
            Point currPoint;
            currPoint.x = i;
            currPoint.y = maxY / 2;

            snakeParts[count] = currPoint;
            count++;
        }

        createFood();                               // Создання їжі
        refresh();
    }

    void SSnake()
        {
            Point tmp = snakeParts[Length - 1];

            for(int i = Length - 1; i > 0; i--) {
                snakeParts[i] = snakeParts[i-1];
            }

            snakeParts[0] = tmp;
        }

    void drawScreen() 
    {
        clear();                                    // Очистка екрану
        // Вивід Game Over якщо гра закінчилась
        if(gameover)
            mvprintw(maxY / 2, maxX / 2, "Game Over!");
        // Вивід змійки
        for(int i = 0; i < Length; i++) 
        {
            drawPart(snakeParts[i]);
        }
        drawPart(food);                             // Вивід їди
        
        mvprintw(1, 2, "Score: %i", score);         // Вивід очків
        refresh();        
        usleep(DELAY);                              // Пауза між діями
    }

    int main (int argc, char *argv[])
    {
    cursesExec();		
    exec();
    if(has_colors() == FALSE)
	{	endwin();
		printf("Your terminal does not support color\n");
		exit(1);
	}
    int dir;
    
		while(1) 
        {
			getmaxyx(stdscr, maxY, maxX);
            //Food_color();
			/* Провірка на закінчення гри */
			if(gameover) {
				sleep(2);
                mvprintw(maxY / 2, maxX / 2, "Game Over!");
				endwin();
                return 0;
			}
                /*Контроль вводу*/
				dir = getch();
				if(( dir == 'd' || dir == 'D' || dir == KEY_RIGHT) && (currentDir != RIGHT && currentDir != LEFT)) {
					currentDir = RIGHT;
				} else if (( dir =='a' || dir =='A' || dir == KEY_LEFT) && (currentDir != RIGHT && currentDir != LEFT)) {
					currentDir = LEFT;
				} else if((dir =='s' || dir =='S' || dir == KEY_DOWN) && (currentDir != UP && currentDir != DOWN)) {
					currentDir = DOWN;
				} else if((dir =='w' || dir =='W' || dir == KEY_UP) && (currentDir != UP && currentDir != DOWN)) {
					currentDir = UP;
				}

			    /* Переміщення */
				nextX = snakeParts[0].x;
				nextY = snakeParts[0].y;

				if(currentDir == RIGHT) nextX++;
				else if(currentDir == LEFT) nextX--;
				else if(currentDir == UP) nextY--;
				else if(currentDir == DOWN) nextY++;

				if(nextX == food.x && nextY == food.y) 
                {
					Point tail;
					tail.x = nextX;
					tail.y = nextY;

					snakeParts[Length] = tail;

					if(Length < 255)
						Length++;
					else
					{
                        mvprintw(maxX / 2, maxY / 2, "Oops, you'r tail so big, we need finish game)");
                        sleep(3);
                        gameover = true;
                    }

					score += 5;
					createFood();
				}
                else 
                {
					//Вивід змійки на екран
					for(int i = 0; i < Length; i++) 
                    {
						if(nextX == snakeParts[i].x && nextY == snakeParts[i].y) 
                        {
							gameover = true;
							break;
						}
					}

					//  Додавання нової голови
					snakeParts[Length - 1].x = nextX;
					snakeParts[Length - 1].y = nextY;
				}
                // Вивід змійки
				SSnake();

				//Game Over якщо вдарилась в ганицю поля
				if((nextX >= maxX || nextX < 0) || (nextY >= maxY || nextY < 0)) 
                {
					gameover = true;
				}

			/* Вивід екрану */
				drawScreen();
		}

		endwin(); //Відновлення нормального терміналу
		nocbreak();
		return 0;
}
