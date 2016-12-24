#include "TXLib.h"

//Раньше эта функция рисовала чёрный фон; сейчас она не используется
void blackBackground()
{
    txSetFillColor(TX_BLACK);
    txClear();
}

//Задаёт начальные координаты и смещения для звёзд.
//Звёзды передаются в массивах.
void createStars(int windowWidth, int windowHeight,
                 double starX[], double starY[], double starDX[], double starDY[], int starsCount)
{
    int windowCenterX = windowWidth / 2;
    int windowCenterY = windowHeight / 2;
    int starIndex = 0;
    while (starIndex < starsCount)
    {
        starX[starIndex] = windowCenterX;
        starY[starIndex] = windowCenterY;
        starDX[starIndex] = random(-1, 1);
        starDY[starIndex] = random(-1, 1);
        starIndex = starIndex + 1;
    }
}

void drawStars(int windowWidth, int windowHeight,
               double starX[], double starY[], double starDX[], double starDY[], int starsCount)
{
    int windowCenterX = windowWidth / 2;
    int windowCenterY = windowHeight / 2;
    txSetFillColor(TX_BLACK);
    txClear();
    int starIndex = 0;
    while (starIndex < starsCount)
    {
        txSetPixel(starX[starIndex], starY[starIndex], TX_WHITE);
        starX[starIndex] += starDX[starIndex];
        starY[starIndex] += starDY[starIndex];
        if (starX[starIndex] < 0 || starX[starIndex] > windowWidth || starY[starIndex] < 0 || starY[starIndex] > windowHeight)
        {
            starX[starIndex] = windowCenterX;
            starY[starIndex] = windowCenterY;
            starDX[starIndex] = random(-1, 1);
            starDY[starIndex] = random(-1, 1);
        }
        starIndex = starIndex + 1;
    }
}

void createBlasts(int cthunX, int cthunY,
                  double blastX[], double blastY[], double blastDX[], double blastDY[], int blastCount)
{
    int blastIndex = 0;
    while (blastIndex < blastCount)
    {
        blastX[blastIndex] = cthunX;
        blastY[blastIndex] = cthunY;
        blastDX[blastIndex] = random(-1, 1);
        blastDY[blastIndex] = random(-1, 1);
        blastIndex = blastIndex + 1;
    }
}

void drawBlasts(int windowWidth, int windowHeight, int cthunX, int cthunY,
                double blastX[], double blastY[], double blastDX[], double blastDY[], int blastCount)
{
    txSetFillColour(TX_RED);
    int blastIndex = 0;
    txSetColor(TX_RED);
    txSetFillColor(TX_RED);
    while (blastIndex < blastCount)
    {
        txCircle(blastX[blastIndex], blastY[blastIndex], 10);
        blastX[blastIndex] += blastDX[blastIndex];
        blastY[blastIndex] += blastDY[blastIndex];
        if (blastX[blastIndex] < 0 || blastX[blastIndex] > windowWidth ||
                blastY[blastIndex] < 0 || blastY[blastIndex] > windowHeight)
        {
            blastX[blastIndex] = cthunX;
            blastY[blastIndex] = cthunY;
            blastDX[blastIndex] = random(-1, 1);
            blastDY[blastIndex] = random(-1, 1);
        }
        blastIndex = blastIndex + 1;
    }
}

void cthun(int x, int y, double size, int lookAtX, int lookAtY)
{
    txSetColour(TX_MAGENTA, 3 * size);
    int tentacles = 0;
    while (tentacles < 100)
    {
        double dx = random(-100, 100);
        double dy = random(-100, 100);
        double len = sqrt(dx * dx + dy * dy);
        len += random(-3, 3);
        dx *= 200.0 / len * size;
        dy *= 200.0 / len * size;

        txLine(x, y, x + dx, y + dy);

        tentacles = tentacles + 1;
    }

    txSetFillColour(TX_YELLOW);
    txSetColour(TX_YELLOW);
    txCircle(x, y, 100 * size);

    double dx = (lookAtX - x) / 8;
    double dy = (lookAtY - y) / 8;

    txSetFillColour(TX_BLACK);
    txSetColour(TX_BLACK);
    txEllipse(x + (-20 + dx) * size, y  + (-60 + dy) * size, x + (20 + dx) * size, y + (60 + dy) * size);

    //txSetColour(TX_PINK);
    //txSetFillColour(TX_PINK);
    //txRectangle(x - 100, y - 100, x + 100,  y - 60);

    txSetColour(TX_MAGENTA, 50 * size);
    txSetFillColour(TX_NULL);
    txCircle(x, y, 100 * size);
}

void droid(int x, int y, int r, COLORREF color, COLORREF colored)
{
    txSetFillColour(colored);
    txSetColour(colored);
    txCircle(x, y, r);

    txSetFillColour(TX_DARKGRAY);
    txSetColour(TX_DARKGRAY);

    txLine(x + r * cos(2.530), y + r * sin(2.530),
           x + r * cos(0.611), y + r * sin(0.611));
    txLine(x + r * cos(3.752), y + r * sin(3.752),
           x + r * cos(5.672), y + r * sin(5.672));

    txSetFillColour(color);
    txSetColour(color);
    txCircle(x, y, (r /2.5));

    txSetFillColour(TX_WHITE);
    txSetColour(TX_WHITE);

    txLine(x + r * cos(4.712), y + r * sin(4.712),
           x + (r * 1.5) * cos(4.712), y + (r * 1.5) * sin(4.712));

    txSetFillColour(TX_WHITE);
    txSetColour(TX_WHITE);
    txCircle(x + (r / 5 ) * cos(4.712), y + (r * 1.5 ) * sin(4.712), r / 5);
}

void droidSide(int droidX1, int droidY1, int sideX, int sideY, int r1, int r2)
{
    txSetFillColour(TX_ORANGE);
    txSetColour(TX_ORANGE);
    txLine(droidX1, droidY1, sideX, sideY);

    txSetFillColour(TX_PINK);
    txSetColour(TX_PINK);
    txCircle(sideX, sideY, r1);

    txSetFillColour(TX_BLACK);
    txSetColour(TX_BLACK);
    txCircle(sideX, sideY, r2);
}

void drawLives(int lives)
{
    txSetColor(TX_LIGHTGREEN);
    txSetFillColor(TX_LIGHTGREEN);
    int circles = 0;
    while (circles < lives)
    {
        txCircle(10 * circles + 10, 10, 5);
        circles = circles + 1;
    }
}

void move(double *coord, double *speed)
{
    *coord += *speed;
    if (*coord < 0)
        *speed *= -1;
    if (*coord > 700)
        *speed *= -1;
}

int main()
{
    int windowWidth = 700, windowHeight = 700;
    txCreateWindow(windowWidth, windowHeight);
    int lives = 10;
    txBegin();

    //создаём звёзды
    double starX[10000];
    double starY[10000];
    double starDX[10000];
    double starDY[10000];
    createStars(windowWidth, windowHeight, starX, starY, starDX, starDY, 1000);

    double droidX = 200, droidY = 200, droidRadius = 50;
    double droidVX = 0, droidVY = 0;

    int droidSideX, droidSideY;
    double droidSideAngle = 0;

    double cthunX = 350, cthunY = 350;
    double cthunVX = 2, cthunVY = 3;

    //HDC destroy  = txLoadImage ("700.bmp");

    double blastX[10000];
    double blastY[10000];
    double blastDX[10000];
    double blastDY[10000];
    createBlasts(cthunX, cthunY, blastX, blastY, blastDX, blastDY, 1000);

    int damageTimer = 0;

    int healTimer = 0;

    while (!GetAsyncKeyState(VK_ESCAPE))
    {
        drawStars(windowWidth, windowHeight, starX, starY, starDX, starDY, 1000);
        //txBitBlt (txDC(), 0, 0, 700, 700, destroy, 0, 0);

        //droidX = txMouseX();
        //droidY = txMouseY();
        move(&droidX, &droidVX);
        move(&droidY, &droidVY);

        if (GetAsyncKeyState(VK_RIGHT))
            droidVX += 0.1;
        if (GetAsyncKeyState(VK_LEFT))
            droidVX -= 0.1;
        if (GetAsyncKeyState(VK_UP))
            droidVY -= 0.1;
        if (GetAsyncKeyState(VK_DOWN))
            droidVY += 0.1;
        if (GetAsyncKeyState(VK_SPACE))
        {
            droidVX *= 0.5;
            droidVY *= 0.5;
        }




        cthun(cthunX, cthunY, 1, droidX, droidY);
        txSetColour(TX_WHITE);
//       txSetFillColour(TX_WHITE);
        txEllipse (cthunX + 50, cthunY - 50, cthunX + 350, cthunY - 250);
        txTextOut (cthunX + 100, cthunY - 200, "УМРИ УЖЕ!");
        txTextOut (cthunX + 100, cthunY - 150, "ДОСТАЛ ХИЛИТЬСЯ!");

        move(&cthunX, &cthunVX);
        move(&cthunY, &cthunVY);


        drawBlasts(windowWidth, windowHeight, cthunX, cthunY, blastX, blastY, blastDX, blastDY, 30);
        if (txGetPixel(droidX, droidY) == TX_RED && damageTimer <= 0)
        {
            lives = lives - 1;
            damageTimer = 50;
        }

        if (lives <= 0)
        {
            txMessageBox("YOU IDIOT!", "SNAKE");
            txMessageBox("...", "Старший Лейтинант Вольтрон Лайтнинг");
            txMessageBox("Я был о вас лучшего мнения, капитан!", "Старший Лейтинант Вольтрон Лайтнинг");
            txMessageBox("Но какое это имеет значение?", "Старший Лейтинант Вольтрон Лайтнинг");
            txMessageBox("Наш корабль уничтожил глаз с щуплами!", "Старший Лейтинант Вольтрон Лайтнинг");
            txMessageBox("Который мы еще и подбить успели.", "Старший Лейтинант Вольтрон Лайтнинг");
            txMessageBox("... Горсподи... Как же тупо это звучит...", "Старший Лейтинант Вольтрон Лайтнинг");
            txMessageBox("Ей богу! Мочилово воргенов и нежити не выглядело столь бессмысленным и тупым!", "Старший Лейтинант Вольтрон Лайтнинг");
            txMessageBox("Сколько времени до падения на Азерот? Часов 5? ОК. ", "Старший Лейтинант Вольтрон Лайтнинг");
            txMessageBox("'Не зная, что он бы мог сделать в данной ситуации, да и от простого пофигизма, поднялся к себе в комнату, лег на кровать и уснул.'", "Старший Лейтинант Вольтрон Лайтнинг");
            break;
        }
        droidSideX = droidX + droidRadius * 2 * cos(droidSideAngle);
        droidSideY = droidY + droidRadius * 2 * sin(droidSideAngle);
        droidSide(droidX, droidY, droidSideX, droidSideY, droidRadius / 1.666, droidRadius / 5);

        droidSideX = droidX - droidRadius * 2 * cos(droidSideAngle);
        droidSideY = droidY - droidRadius * 2 * sin(droidSideAngle);
        droidSide(droidX, droidY, droidSideX, droidSideY, droidRadius / 1.666, droidRadius / 5);

        if (damageTimer > 0)
            droid(droidX, droidY, droidRadius, TX_RED, TX_BLUE);
        else
            droid(droidX, droidY, droidRadius, TX_GREEN, TX_ORANGE);

        droidSideAngle += 0.0174533;

        drawLives(lives);

        damageTimer = damageTimer - 1;

        healTimer = healTimer + 1;
        if (healTimer >= 1000)
        {
            if (lives < 10)
                lives = lives + 1;
            healTimer = 0;
        }


        txSleep(10);
    }

//txDeleteDC(destroy);
}
