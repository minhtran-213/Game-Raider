#include <stdio.h>
#include <stdlib.h>
#include "RAIDER.h"

#define consoleWidth 85
#define consoleHeight 25

enum stat {UP, DOWN, LEFT, RIGHT, STOP};
enum menuGame {MAIN, PAUSE, WON, LOST, STORE, NOLOSE};

int loopLogin = 1;
// bien toan cuc dung de login
int lanChay;

struct nhanvat {
        toado td;
        stat tt; // trạng thái
};
struct wall
{
        int x, y;      // tao do wall: x; y
        char shape;
};

struct spike
{
        int n;
};

struct movement
{
        char step;
};

struct  score
{
        int n;
        char str[20];
};

void printInstruct ();
int main()
{
        int LEVEL = 1;

        int levelMax; // mapChoice chay tu 1 den level Max
        int mapChoice = 1;

        int gold ;
        int totalGOLD;
        char rac, chuoiRac[20];

        /* Menu Account */
        int menuAccountLoop = 1, chooseMenuAccount = 1;
        int loopDangNhap = 1;
        printBoundary();
        printName();
        char IDUser[30];
        char passUser[30];

                // bien cua chung
        int loopLV = 1;
        int bought[10];


                // bien cua chung
        int coinWave = 0;
        do
        {
                cursor();
                while (menuAccountLoop){
                    menuCrAccount(&chooseMenuAccount, &menuAccountLoop);
                    Sleep(100);
                }
                menuGame menu = MAIN;
                printBoundary();
                printName();
                idBorder();
                passBorder();

                if (chooseMenuAccount == 2)
                {
                        ID(IDUser);
                        pass(passUser);
                        if (checkID_checkPass(IDUser, passUser))                        // truycap file có định dạng IDUser lay profile
                        {
                                printf("\a");
                                char userProfile[25];
                                sprintf(userProfile, "%s.dm", IDUser);
                                FILE *profile = fopen(userProfile, "r");
                                fscanf(profile, "%s%c%d%c%d%c%d%c%d%c%d%c%d%c%d%c%d%c%d%c%d%c%d%c%d%c%d%c", chuoiRac, &rac, &gold, &rac, &totalGOLD, &rac, &levelMax, &rac, &bought[0], &rac, &bought[1], &rac, &bought[2], &rac, &bought[3], &rac, &bought[4], &rac, &bought[5], &rac, &bought[6], &rac, &bought[7], &rac, &bought[8], &rac, &bought[9], &rac);
                                fclose(profile);
                                loopDangNhap = 0;
                                Sleep(1000);
                        }
                        else
                        {
                                Beep(429, 750);
//                                gotoxy(36,22);
//                                printf("%s", IDUser);
//                                gotoxy(36,23);
//                                printf("%s", passUser);
                                menuAccountLoop = 1;
                                Sleep(1000);
                                clrscr();
                                printBoundary();
                                printName();
                        }
                }
                else if (chooseMenuAccount == 1)
                {
                        gotoxy(7, 21);
                        printf("\\*\\ Username & Password must not exceed the limitation of 16 letters /*/");
                        ID(IDUser);
                        pass(passUser);
                        if (checkIDExisted(IDUser, passUser))
                        {
                                printf("\a");
                                signUp(IDUser, passUser);
                                char userProfile[25];
                                sprintf(userProfile, "%s.dm", IDUser);
                                FILE *profile = fopen(userProfile, "r");
                                fscanf(profile, "%s%c%d%c%d%c%d%c%d%c%d%c%d%c%d%c%d%c%d%c%d%c%d%c%d%c%d%c", chuoiRac, &rac, &gold, &rac, &totalGOLD, &rac, &levelMax, &rac, &bought[0], &rac, &bought[1], &rac, &bought[2], &rac, &bought[3], &rac, &bought[4], &rac, &bought[5], &rac, &bought[6], &rac, &bought[7], &rac, &bought[8], &rac, &bought[9], &rac);
                                fclose(profile);
                                loopDangNhap = 0;
                                menuAccountLoop = 0;
                                Sleep(1000);
                        }
                        else
                        {
                                Beep(429, 750);
                                menuAccountLoop = 1;
                                Sleep(1000);
                                clrscr();
                                printBoundary();
                                printName();
                        }
                }
        }
        while (loopDangNhap);

        hidecursor();
        int gameLOOP = 1;
        printBoundary();
        loadingBar();

        menuGame menu = MAIN;
        int skin = 1;
        do
        {
                int choice = 1, loopMenu = 1;         // khoi tao gia tri resume
                char key;
                printBoundary();
                printName();
                wall WALL[25][72];

                // xoa rac
                for (int j = 0; j < 25; j++)
                        for (int i = 0; i < 70; i++)
                                WALL[j][i].shape = '\0';
                // dung cho man 3
                movement steps[25][72];
                spike appear[10], disappear[10], turn[10];
                // dung cho man 3

                while (loopMenu)
                {
                        if (menu == MAIN)
                        {
                                gotoxy(1, 23);
                                changeColor(11);
                                printf("Username : %s", IDUser);
                                resetColor();
                                gotoxy(1, 22);
                                changeColor(14);
                                printf("Coin     : %d", gold);
                                resetColor();
                                chooseMenu(&choice, &loopMenu);
                        }
                        else if (menu == WON)
                                menuPause(&choice, &loopMenu, &coinWave);
                        else if (menu == PAUSE || menu == LOST)
                                menuLost(&choice, &loopMenu, &coinWave);
                        else if (menu ==NOLOSE)
                                menuThangNhungDelChoQuaMan(&choice, &loopMenu, &coinWave);
                        else if (menu == STORE)
                        {
                                menuStore(&choice, &loopMenu, &mapChoice, &levelMax, bought, &skin);
                                gotoxy(1, 23);
                                changeColor(11);
                                printf("Username : %s", IDUser);
                                resetColor();
                                gotoxy(1, 22);
                                changeColor(14);
                                printf("Coin     : %d", gold);
                                resetColor();
                                LEVEL = mapChoice;
                        }
                        Sleep(150);
                }

                if ((menu == LOST || menu == PAUSE) && choice == 1)
                {
                        menu = MAIN;
                }
                else if (menu == WON && choice == 2)
                {
                        menu = MAIN;
                }
                //     if (menu == MAIN)
                else if (menu == MAIN && choice == 5)
                        //system("TASKKILL /IM cb_console_runner.exe");
                        //main();
                {
                        int choiceMenuLogOut = 2;
                        int menuLogOutLoop = 1;
                        printBoundary();
                        printName();
                        while (menuLogOutLoop)
                        {
                                menuLogOut(&choiceMenuLogOut, &menuLogOutLoop);
                                Sleep(100);
                        }
                        if (choiceMenuLogOut == 2)
                                main();
                        else if (choiceMenuLogOut == 1)
                                menu = MAIN;
                }
                else if (menu == MAIN && choice == 4)
                {
                        printBoundary();
                        printInstruct();
                }
                else if (menu == MAIN && choice == 3)
                {
                        int testChuoi = 0;
                        char rac;
                        score top[9];
                        FILE *hc = fopen("HIGHSCORE.dm", "r");
                        fscanf(hc, "%s%c%d%c%s%c%d%c%s%c%d%c%s%c%d%c%s%c%d%c%s%c%d%c%s%c%d%c%s%c%d%c", top[0].str, &rac, &top[0].n, &rac, top[1].str, &rac, &top[1].n, &rac, top[2].str, &rac, &top[2].n, &rac, top[3].str, &rac, &top[3].n, &rac, top[4].str, &rac, &top[4].n, &rac, top[5].str, &rac, &top[5].n, &rac, top[6].str, &rac, &top[6].n, &rac, top[7].str, &rac, &top[7].n, &rac);
                        for (int i = 0; i <= 8; i++)
                        {
                                if (strlen(IDUser) == strlen(top[i].str))
                                {
                                        testChuoi = 1;
                                        for (int j = 0; j <= strlen(IDUser); j++)
                                        {
                                                if (IDUser[j] != top[i].str[j])
                                                        testChuoi = 0;
                                                        break;
                                        }
                                        if (testChuoi == 1)
                                        {
                                                top[i].n = totalGOLD;
                                        }
                                        break;
                                }
                        }
                        if (testChuoi == 0)
                        {
                                for (int i = 0; i <= strlen(IDUser); i++)
                                {
                                        top[8].str[i] = IDUser[i];
                                }
                                top[8].n = totalGOLD;
                        }
                        topGold(top);   // sap xep
                        printBoundary();
                        gotoxy(39, 1);
                        changeColor(6);
                        printf("%c TOP COIN %c", 233, 233);
                        resetColor();

                        printRank();
                        gotoxy(28, 6);
                        changeColor(12);
                        printf("1. %s\t\t%10d", top[0].str, top[0].n);
                        resetColor();
                        gotoxy(28, 8);
                        printf("2. %s\t\t%10d", top[1].str, top[1].n);
                        gotoxy(28, 10);
                        printf("3. %s\t\t%10d", top[2].str, top[2].n);
                        gotoxy(28, 12);
                        printf("4. %s\t\t%10d", top[3].str, top[3].n);
                        gotoxy(28, 14);
                        printf("5. %s\t\t%10d", top[4].str, top[4].n);
                        gotoxy(28, 16);
                        printf("6. %s\t\t%10d", top[5].str, top[5].n);
                        gotoxy(28, 18);
                        printf("7. %s\t\t%10d", top[6].str, top[6].n);
                        gotoxy(28, 20);
                        printf("8. %s\t\t%10d", top[7].str, top[7].n);
                        gotoxy(28, 23);
                        printf("Press ESC to go back MAIN MENU");
                        int keyPressed;
                        do {

                            keyPressed = getch();
                        } while (keyPressed != 27);
                        fclose(hc);

                        FILE *HC = fopen("HIGHSCORE.dm", "w+");
                        for (int i = 0; i < 8; i++)
                        {
                                fprintf(HC, "%s\n%d\n", top[i].str, top[i].n);
                        }
                        fclose(HC);
                }
                else if (menu == MAIN && choice == 2)
                {
                        printBoundary();
                        printName();
                        int chooseMenuChangePass = 1;
                        int menuChangePassLoop = 1;
                        char currentPass[30];
                        char newPass[30];
                        while (menuChangePassLoop)
                        {
                                menuChangePass(&chooseMenuChangePass, &menuChangePassLoop);
                                Sleep(100);
                        }
                        if (chooseMenuChangePass == 1)
                        {
                                menu = MAIN;
                        }
                        else if (chooseMenuChangePass == 2)
                        {
                                cursor();
                                printBoundary();
                                printName();
                                currentPassBorder();
                                newPassBorder();
                                current(currentPass);
                                pass(newPass);
                                int checkPass = 1;
                                if ((strlen(currentPass) != strlen(passUser)) || strlen(newPass) > 16 || strlen(newPass) == 0)
                                        checkPass = 0;
                                else
                                {
                                        for (int i = 0; i < strlen(currentPass); i++)
                                        {
                                                if (passUser[i] != currentPass[i])
                                                        checkPass = 0;
                                                break;
                                        }
                                }
                                if (checkPass == 0)
                                {
                                        gotoxy(34, 20);
                                        printf("Invalid Password");
                                        Sleep(1000);
                                        menu = MAIN;
                                }
                                else if (checkPass == 1)
                                {
                                        for (int i = 0; i < strlen(newPass); i++)
                                        {
                                                passUser[i] = newPass[i];
                                        }
                                        passUser[strlen(newPass)] = '\0';

                                        gotoxy(36, 20);
                                        printf("Success!");
                                        Sleep(1000);
                                        recordProfile(IDUser, passUser, &gold, &totalGOLD, &levelMax, bought);
                                        hidecursor();
                                        int choiceMenuLogOut = 2;
                                        int menuLogOutLoop = 1;
                                        printBoundary();
                                        printName();
                                        while (menuLogOutLoop)
                                        {
                                                menuLogOut(&choiceMenuLogOut, &menuLogOutLoop);
                                                Sleep(300);
                                        }
                                        if (choiceMenuLogOut == 2)
                                                main();
                                        else if (choiceMenuLogOut == 1)
                                                menu = MAIN;
                                }
                        }
                }
                else if (menu == MAIN && choice == 1)
                {
                        menu = STORE;
                }
                else if (menu == STORE && choice == 3)
                {
                                menu = MAIN;
                }
                else if (menu == NOLOSE && choice == 1)
                {
                        menu = MAIN;
                }
                else if ((menu == STORE &&(choice == 1 || choice == 2)) || ((menu == PAUSE ||menu ==LOST) && choice == 2) || (menu ==  WON && (choice == 1 || choice == 3)) || (menu == NOLOSE && choice == 2))
                {
                        if (menu == WON && choice == 3)
                        {
                                loopLV = 1;
                        }
                        else if (menu == NOLOSE && choice == 2)
                        {
                                loopLV = 1;
                        }
                        else if ((menu == PAUSE || menu ==LOST) && choice == 2)
                        {
                                loopLV = 1;
                        }
                        else if ((menu == STORE && (choice == 1 || choice == 2)) || (menu == WON && choice == 1))
                        {
                                int chooseMap = 2;
                                int loopMap = 1;
                                switch (mapChoice)                      // them dk chi mua  1lan
                                {
                                        case 1:
                                        {
                                                if (bought[0] == 0)
                                                {
                                                        printBoundary();
                                                        printName();
                                                        while (loopMap)
                                                        {
                                                                menuBuyMap(&chooseMap, &loopMap, 200, 1);
                                                                Sleep(150);
                                                        }
                                                        if (chooseMap == 2)
                                                        {
                                                                if (gold < 200)
                                                                {
                                                                        gotoxy(36, 20);
                                                                        printf("No success!");
                                                                        Sleep(300);
                                                                        menu = STORE;
                                                                        loopLV = 0;
                                                                }
                                                                else
                                                                {
                                                                        gotoxy(36, 20);
                                                                        printf("Success!");
                                                                        Sleep(300);
                                                                        LEVEL = mapChoice;
                                                                        loopLV = 1;
                                                                        gold -= 200;
                                                                        bought[0] = 1;
                                                                }
                                                        }
                                                        else if (chooseMap == 1)
                                                        {
                                                                Sleep(300);
                                                               menu = STORE;
                                                                loopLV = 0;
                                                        }
                                                }
                                                else
                                                {
                                                        LEVEL = mapChoice;
                                                        loopLV = 1;
                                                }
                                                break;
                                        }
                                        case 2:
                                        {

                                                if (bought[1] == 0)
                                                {
                                                        printBoundary();
                                                        printName();
                                                        while (loopMap)
                                                        {
                                                                menuBuyMap(&chooseMap, &loopMap, 400, 2);
                                                                Sleep(150);
                                                        }
                                                        if (chooseMap == 2)
                                                        {
                                                                if (gold < 400)
                                                                {
                                                                        gotoxy(36, 20);
                                                                        printf("No success!");
                                                                        Sleep(300);
                                                                        menu = STORE;
                                                                        loopLV = 0;
                                                                }
                                                                else
                                                                {
                                                                        gotoxy(36, 20);
                                                                        printf("Success!");
                                                                        Sleep(300);
                                                                        LEVEL = mapChoice;
                                                                        loopLV = 1;
                                                                        gold -= 400;
                                                                        bought[1] = 1;
                                                                }
                                                        }
                                                        else if (chooseMap == 1)
                                                        {
                                                                Sleep(300);
                                                                menu = STORE;
                                                                loopLV = 0;
                                                        }
                                                }
                                                else
                                                {
                                                        LEVEL = mapChoice;
                                                        loopLV = 1;
                                                }
                                                break;
                                        }
                                        case 3:
                                        {
                                                if (bought[2] == 0)
                                                {
                                                        printBoundary();
                                                        printName();
                                                        while (loopMap)
                                                        {
                                                                menuBuyMap(&chooseMap, &loopMap, 500, 3);
                                                                Sleep(150);
                                                        }
                                                        if (chooseMap == 2)
                                                        {
                                                                if (gold < 500)
                                                                {
                                                                        gotoxy(36, 20);
                                                                        printf("No success!");
                                                                        Sleep(300);
                                                                        menu = STORE;
                                                                        loopLV = 0;
                                                                }
                                                                else
                                                                {
                                                                        gotoxy(36, 20);
                                                                        printf("Success!");
                                                                        Sleep(300);
                                                                        LEVEL = mapChoice;
                                                                        loopLV = 1;
                                                                        gold -= 500;
                                                                        bought[2] = 1;
                                                                }
                                                        }
                                                        else if (chooseMap == 1)
                                                        {
                                                                Sleep(300);
                                                               menu = STORE;
                                                                loopLV = 0;
                                                        }
                                                }
                                                else
                                                {
                                                        LEVEL = mapChoice;
                                                        loopLV = 1;
                                                }
                                                break;
                                        }
                                        case 4:
                                        {
                                                if (bought[3] == 0)
                                                {
                                                        printBoundary();
                                                        printName();
                                                        while (loopMap)
                                                        {
                                                                menuBuyMap(&chooseMap, &loopMap, 500, 4);
                                                                Sleep(150);
                                                        }
                                                        if (chooseMap == 2)
                                                        {
                                                                if (gold < 500)
                                                                {
                                                                        gotoxy(36, 20);
                                                                        printf("No success!");
                                                                        Sleep(300);
                                                                        menu = STORE;
                                                                        loopLV = 0;
                                                                }
                                                                else
                                                                {
                                                                        gotoxy(36, 20);
                                                                        printf("Success!");
                                                                        Sleep(300);
                                                                        LEVEL = mapChoice;
                                                                        loopLV = 1;
                                                                        gold -= 500;
                                                                        bought[3] = 1;
                                                                        recordProfile( IDUser, passUser, &gold, &totalGOLD,&levelMax, bought);
                                                                }
                                                        }
                                                        else if (chooseMap == 1)
                                                        {
                                                                Sleep(300);
                                                                menu = STORE;
                                                                loopLV = 0;
                                                        }
                                                }
                                                else
                                                {
                                                        LEVEL = mapChoice;
                                                        loopLV = 1;
                                                }
                                                break;
                                        }
                                        case 5:
                                        {
                                                if (bought[4] == 0)
                                                {
                                                        printBoundary();
                                                        printName();
                                                        while (loopMap)
                                                        {
                                                                menuBuyMap(&chooseMap, &loopMap, 700, 5);
                                                                Sleep(150);
                                                        }
                                                        if (chooseMap == 2)
                                                        {
                                                                if (gold < 700)
                                                                {
                                                                        gotoxy(36, 20);
                                                                        printf("No success!");
                                                                        Sleep(300);
                                                                        menu = STORE;
                                                                        loopLV = 0;
                                                                }
                                                                else
                                                                {
                                                                        gotoxy(36, 20);
                                                                        printf("Success!");
                                                                        Sleep(300);
                                                                        LEVEL = mapChoice;
                                                                        loopLV = 1;
                                                                        gold -= 700;
                                                                        bought[4] = 1;
                                                                        recordProfile( IDUser, passUser, &gold, &totalGOLD,&levelMax, bought);
                                                                }
                                                        }
                                                        else if (chooseMap == 1)
                                                        {
                                                                Sleep(300);
                                                                menu = STORE;
                                                                loopLV = 0;
                                                        }
                                                }
                                                else
                                                {
                                                        LEVEL = mapChoice;
                                                        loopLV = 1;
                                                }
                                                break;
                                        }
                                        case 6:
                                        {
                                                if (bought[5] == 0)
                                                {
                                                        printBoundary();
                                                        printName();
                                                        while (loopMap)
                                                        {
                                                                menuBuyMap(&chooseMap, &loopMap, 1000, 6);
                                                                Sleep(150);
                                                        }
                                                        if (chooseMap == 2)
                                                        {
                                                                if (gold < 1000)
                                                                {
                                                                        gotoxy(36, 20);
                                                                        printf("No success!");
                                                                        Sleep(300);
                                                                        menu = STORE;
                                                                        loopLV = 0;
                                                                }
                                                                else
                                                                {
                                                                        gotoxy(36, 20);
                                                                        printf("Success!");
                                                                        Sleep(300);
                                                                        LEVEL = mapChoice;
                                                                        loopLV = 1;
                                                                        gold -= 1000;
                                                                        bought[5] = 1;
                                                                        recordProfile( IDUser, passUser, &gold, &totalGOLD,&levelMax, bought);
                                                                }
                                                        }
                                                        else if (chooseMap == 1)
                                                        {
                                                                Sleep(300);
                                                                menu = STORE;
                                                                loopLV = 0;
                                                        }
                                                }
                                                else
                                                {
                                                        LEVEL = mapChoice;
                                                        loopLV = 1;
                                                }
                                                break;
                                        }
                                        case 7:
                                        {
                                                if (bought[6] == 0)
                                                {
                                                        printBoundary();
                                                        printName();
                                                        while (loopMap)
                                                        {
                                                                menuBuyMap(&chooseMap, &loopMap, 1300, 7);
                                                                Sleep(150);
                                                        }
                                                        if (chooseMap == 2)
                                                        {
                                                                if (gold < 1300)
                                                                {
                                                                        gotoxy(36, 20);
                                                                        printf("No success!");
                                                                        Sleep(300);
                                                                        menu = STORE;
                                                                        loopLV = 0;
                                                                }
                                                                else
                                                                {
                                                                        gotoxy(36, 20);
                                                                        printf("Success!");
                                                                        Sleep(300);
                                                                        LEVEL = mapChoice;
                                                                        loopLV = 1;
                                                                        gold -= 1300;
                                                                        bought[6] = 1;
                                                                        recordProfile( IDUser, passUser, &gold, &totalGOLD,&levelMax, bought);
                                                                }
                                                        }
                                                        else if (chooseMap == 1)
                                                        {
                                                                Sleep(300);
                                                                menu = STORE;
                                                                loopLV = 0;
                                                        }
                                                }
                                                else
                                                {
                                                        LEVEL = mapChoice;
                                                        loopLV = 1;
                                                }
                                                break;
                                        }
                                        case 8:
                                        {
                                                if (bought[7] == 0)
                                                {
                                                        printBoundary();
                                                        printName();
                                                        while (loopMap)
                                                        {
                                                                menuBuyMap(&chooseMap, &loopMap, 1500, 8);
                                                                Sleep(150);
                                                        }
                                                        if (chooseMap == 2)
                                                        {
                                                                if (gold < 1500)
                                                                {
                                                                        gotoxy(36, 20);
                                                                        printf("No success!");
                                                                        Sleep(300);
                                                                       menu = STORE;
                                                                        loopLV = 0;
                                                                }
                                                                else
                                                                {
                                                                        gotoxy(36, 20);
                                                                        printf("Success!");
                                                                        Sleep(300);
                                                                        LEVEL = mapChoice;
                                                                        loopLV = 1;
                                                                        gold -= 1500;
                                                                        bought[7] = 1;
                                                                        recordProfile( IDUser, passUser, &gold, &totalGOLD,&levelMax, bought);
                                                                }
                                                        }
                                                        else if (chooseMap == 1)
                                                        {
                                                                Sleep(300);
                                                                menu = STORE;
                                                                loopLV = 0;
                                                        }
                                                }
                                                else
                                                {
                                                        LEVEL = mapChoice;
                                                        loopLV = 1;
                                                }
                                                break;
                                        }
                                        case 9:
                                        {
                                                if (bought[8] == 0)
                                                {
                                                        printBoundary();
                                                        printName();
                                                        while (loopMap)
                                                        {
                                                                menuBuyMap(&chooseMap, &loopMap, 2000, 9);
                                                                Sleep(150);
                                                        }
                                                        if (chooseMap == 2)
                                                        {
                                                                if (gold < 2000)
                                                                {
                                                                        gotoxy(36, 20);
                                                                        printf("No success!");
                                                                        Sleep(300);
                                                                        menu = STORE;
                                                                        loopLV = 0;
                                                                }
                                                                else
                                                                {
                                                                        gotoxy(36, 20);
                                                                        printf("Success!");
                                                                        Sleep(300);
                                                                        LEVEL = mapChoice;
                                                                        loopLV = 1;
                                                                        gold -= 2000;
                                                                        bought[8] = 1;
                                                                        recordProfile( IDUser, passUser, &gold, &totalGOLD,&levelMax, bought);
                                                                }
                                                        }
                                                        else if (chooseMap == 1)
                                                        {
                                                                Sleep(300);
                                                                menu = STORE;
                                                                loopLV = 0;
                                                        }
                                                }
                                                else
                                                {
                                                        LEVEL = mapChoice;
                                                        loopLV = 1;
                                                }
                                                break;
                                        }
                                        case 10:
                                        {
                                                LEVEL = mapChoice;
                                                bought[9] = 1;
                                                recordProfile( IDUser, passUser, &gold, &totalGOLD,&levelMax, bought);
                                                loopLV = 1;
                                        }
                                }
                        }
                        if (loopLV == 1)
                                printBoundaryInGame();

                        toado vitricu;  // xoa vi tri
                        nhanvat nv;

                        for(int j = 0; j < 25; j++){
                            for (int i = 0; i < 72; i++){
                                WALL[j][i].shape = '\0';
                            }
                        }

                        if (LEVEL == 1 && loopLV == 1)
                        {
                                // nhân vật
                                nv.td.x = 2;
                                nv.td.y = 6;
                                nv.tt = STOP;

                                //      MAP
                                level1(WALL);
                                //      MAP
                                changeColor(223);
                                gotoxy(76,4);
                                printf("WAVE 1");
                                resetColor();
                        }
                        else if (LEVEL == 2 && loopLV == 1)
                        {
                                putWall(30, 13, 1, 0, WALL);
                                nv.td.x = 5;
                                nv.td.y = 13;
                                nv.tt = STOP;

                                // MAP
                                level2(WALL);
                                //MAP
                                changeColor(217);
                                gotoxy(76,4);
                                printf("WAVE 2");
                                resetColor();
                        }
                        else if (LEVEL == 3 && loopLV == 1)
                        {
                                nv.td.x = 2;
                                nv.td.y = 2;
                                nv.tt = STOP;

                                // MAP
                                level3(WALL);
                                // MAP
                                changeColor(215);
                                gotoxy(76,4);
                                printf("WAVE 3");
                                resetColor();
                        }
                        else if (LEVEL == 4 && loopLV == 1)
                        {
                                nv.td.x = 60;
                                nv.td.y = 22;
                                nv.tt = STOP;

                                // MAP
                                level4(WALL);
                                // MAP
                                changeColor(94);
                                gotoxy(76,4);
                                printf("WAVE 4");
                                resetColor();
                        }
                        else if (LEVEL == 5 && loopLV == 1)
                        {
                                nv.td.x = 67;
                                nv.td.y = 22;
                                nv.tt = STOP;

                                // MAP
                                level5(WALL);
                                // MAP
                                changeColor(13);
                                gotoxy(76,4);
                                printf("WAVE 5");
                                resetColor();

                        }
                        else if (LEVEL == 6 && loopLV == 1)
                        {
                                nv.td.x = 41;
                                nv.td.y = 3;
                                nv.tt = STOP;

                                // MAP
                                level6(WALL);
                                // MAP
                                changeColor(211);
                                gotoxy(76,4);
                                printf("WAVE 6");
                                resetColor();
                        }
                        else if (LEVEL == 7 && loopLV == 1)
                        {
                                nv.td.x = 18;
                                nv.td.y = 22;
                                nv.tt = STOP;


                                // MAP
                                level7(WALL);
                                //MAP

                                changeColor(219);
                                gotoxy(76,4);
                                printf("WAVE 7");
                                resetColor();
                        }
                        else if (LEVEL == 8 && loopLV == 1)
                        {
                                nv.td.x = 36;
                                nv.td.y = 13;
                                nv.tt = STOP;


                                // MAP
                                level8(WALL);
                                // MAP
                                changeColor(217);
                                gotoxy(76,4);
                                printf("WAVE 8");
                                resetColor();
                        }
                        else if (LEVEL == 9 && loopLV == 1)
                        {
                                nv.td.x = 34;
                                nv.td.y = 11;
                                nv.tt = STOP;


                                // MAP
                                level9(WALL);
                                //MAP

                                changeColor(223);
                                gotoxy(76,4);
                                printf("WAVE 9");
                                resetColor();
                        }
                        else if (LEVEL == 10 && loopLV == 1)
                        {
                                nv.td.x = 27;
                                nv.td.y = 4;
                                nv.tt = STOP;


                                // MAP
                                level10(WALL);
                                //MAP
                                changeColor(218);
                                gotoxy(76,4);
                                printf("WAVE 10");
                                resetColor();
                        }

                                // bien cua lv 2
                        toado dan1;
                                dan1.x = 30;
                                dan1.y = 13;
                        int direction1 = 1;

                        toado dan2;
                                dan2.x = 30;
                                dan2.y = 13;
                        int direction2 = 2;
                                // bien cua lv 2

                                //bien cua lv 3
                        for (int i = 0; i < 10; i++)
                        {
                                appear[i].n = 10000;
                                disappear[i].n = 10000;
                                turn[i].n = 0;
                        }
                                //bien cua lv 3

                                // bien cua lv 4
                        spike delay[70];
                        delay[0].n = 0;
                        delay[1].n = 0;
                        delay[2].n = 0;
                        delay[3].n = 0;

                        nhanvat ghostY[10];

                        ghostY[0].td.x = 38;
                        ghostY[0].td.y = 16;
                        ghostY[0].tt = UP;
                        ghostY[1].td.x = 29;
                        ghostY[1].td.y = 13;
                        ghostY[1].tt = UP;
                        ghostY[2].td.x = 32;
                        ghostY[2].td.y = 3;
                        ghostY[2].tt = DOWN;
                        ghostY[3].td.x = 52;
                        ghostY[3].td.y = 5;
                        ghostY[3].tt = LEFT;
                                // bien cua lv 4

                                // bien cua lv 5            delay va ghost khai bao tren lv 4
                        delay[4].n = 2000;
                        delay[5].n = 2000;
                        delay[6].n = 2000;
                        delay[7].n = 0;
                        delay[8].n = 0;

                        toado dan[70];

                        dan[0].y = 19;
                        dan[1].y = 8;
                        dan[2].y = 4;

                        ghostY[4].td.x = 15;
                        ghostY[4].td.y = 11;
                        ghostY[4].tt = UP;
                        ghostY[5].td.x = 19;
                        ghostY[5].td.y = 9;
                        ghostY[5].tt = DOWN;
                                // bien cua lv 5

                                // bien cua lv6
                        delay[10].n = 2000;
                        delay[9].n = 2000;

                        dan[3].x = 33;
                        dan[4].x = 36;
                                // bien cua lv 6

                                // bien cua lv 7
                        delay[11].n = 2000;
                        delay[12].n = 2000;
                        delay[13].n = 2000;
                        delay[14].n = 2000;
                        delay[15].n = 2000;
                        delay[16].n = 2000;
                        delay[17].n = 2000;
                        delay[18].n = 2000;
                        delay[19].n = 2000;
                        delay[20].n = 2000;
                        delay[21].n = 0;
                        delay[22].n = 0;
                        delay[23].n = 0;

                        dan[5].x = 17;          // dung cho sung
                        dan[6].y = 3;
                        dan[7].y = 19;
                        dan[8].y = 18;
                        dan[9].y = 3;
                        dan[10].y = 3;
                        dan[11].y = 18;
                        dan[12].y = 21;
                        dan[13].y = 4;
                        dan[14].x = 40;

                        ghostY[6].td.x = 45;
                        ghostY[6].td.y = 9;
                        ghostY[6].tt = DOWN;
                        ghostY[7].td.x = 46;
                        ghostY[7].td.y = 9;
                        ghostY[7].tt = DOWN;
                        ghostY[8].td.x = 47;
                        ghostY[8].td.y = 9;
                        ghostY[8].tt = DOWN;
                                // bien cua lv 7

                                // bien cua lv8
                        delay[24].n = 2000;
                        delay[25].n = 2000;
                        delay[26].n = 2000;
                        delay[27].n = 2000;
                        delay[28].n = 2000;
                        delay[29].n = 2000;
                        delay[30].n = 2000;
                        delay[31].n = 2000;
                        delay[32].n = 2000;
                        delay[33].n = 2000;
                        delay[34].n = 2000;

                        dan[15].x = 29;
                        dan[16].y = 15;
                        dan[17].x = 30;
                        dan[18].y = 13;
                        dan[19].x = 42;
                        dan[20].y = 11;
                        dan[21].x = 34;
                        dan[22].x = 37;
                        dan[23].x = 34;
                        dan[24].x = 45;
                        dan[25].y = 11;
                                // bien cua lv 8

                                //bien cua lv9
                        for (int i = 35; i < 70; i++)
                        {
                                delay[i].n = 2000;
                        }


                        dan[26].y = 3;
                        dan[27].x = 27;
                        dan[28].y = 14;
                        dan[29].y = 14;
                        dan[30].y = 14;
                        dan[31].y = 9;
                        dan[32].y = 9;
                        dan[33].y = 9;
                        dan[34].y = 3;
                        dan[35].y = 5;
                        dan[36].y = 14;
                        dan[37].y = 14;
                        dan[38].y = 14;
                        dan[39].x = 49;
                        dan[40].x = 49;
                        dan[41].x = 49;
                        dan[42].x = 52;
                        dan[43].x = 37;
                        dan[44].x = 33;
                                // bien cua lv9

                                // bien cua lv 10
                        dan[45].x = 34;
                        dan[46].x = 31;
                        dan[47].x = 54;
                        dan[48].x = 54;
                        dan[49].x = 55;
                        dan[50].y = 20;
                        dan[51].y = 21;
                        dan[52].y = 21;
                        dan[53].y = 20;
                        dan[54].x = 41;
                        dan[55].x = 41;
                                // bien cua lv 10


                        while (loopLV)
                        {
                                // hien thi
                                changeColor(skin + 2);
                                gotoxy(nv.td.x, nv.td.y);
                                puts("*");
                                resetColor();

                                if (LEVEL == 2)
                                {
                                        arrowTrap1(30, 13, &dan1.x, &dan1.y, &direction1, WALL);
                                        arrowTrap2(30, 13, &dan2.x, &dan2.y, &direction2, WALL);
                                }
                                else if (LEVEL == 3)
                                {
                                        if (steps[5][8].step == '>')
                                                turn[0].n = 1;
                                        if (steps[4][32].step == '>')
                                                turn[1].n = 1;
                                        if (steps[2][7].step == '>')
                                                turn[2].n = 1;
                                        if (steps[5][31].step == '>')
                                                turn[3].n = 1;
                                        if (steps[11][67].step == '>')
                                                turn[5].n = 1;
                                        if (steps[10][9].step == '>')
                                                turn[6].n = 1;

                                        if (turn[0].n == 1)
                                                horizontalSpikeTrap(8, 25, 5, &appear[0].n, &disappear[0].n, &turn[0].n, WALL);
                                        if (turn[1].n == 1)
                                                horizontalSpikeTrap(32, 69, 4, &appear[1].n, &disappear[1].n, &turn[1].n, WALL);
                                        if (turn[2].n == 1)
                                                verticalSpikeTrap(2, 4, 7, &appear[2].n, &disappear[2], &turn[2].n, WALL);
                                        if (turn[3].n == 1)
                                                verticalSpikeTrap(5, 5, 31, &appear[3].n, &disappear[3], &turn[3].n, WALL);
                                        if (turn[5].n == 1)
                                                verticalSpikeTrap(11, 11, 67, &appear[5].n, &disappear[5], &turn[5].n, WALL);
                                        if (turn[6].n == 1)
                                                horizontalSpikeTrap(9, 10, 10, &appear[6].n, &disappear[6], &turn[6].n, WALL);
                                }

                                else if (LEVEL == 4)
                                {
                                        ghostVertical(&ghostY[0].td.x, &ghostY[0].td.y, 15, 22, &ghostY[0].tt, WALL, &delay[0]);
                                        ghostVertical(&ghostY[1].td.x, &ghostY[1].td.y, 13, 22, &ghostY[1].tt, WALL, &delay[1]);
                                        ghostVertical(&ghostY[2].td.x, &ghostY[2].td.y, 2, 6, &ghostY[2].tt, WALL, &delay[2]);
                                        ghostHorizontal(&ghostY[3].td.x, &ghostY[3].td.y, 49, 58, &ghostY[3].tt, WALL, &delay[3]);
                                }
                                else if (LEVEL == 5)
                                {
                                        arrowTrapInovableVersionDOWN(57, 18, &dan[0].y, 21, WALL, &delay[4].n);
                                        arrowTrapInovableVersionUP(67, 9, &dan[1].y, 4, WALL, &delay[5]);
                                        arrowTrapInovableVersionDOWN(65, 3, &dan[2].y, 8, WALL, &delay[6].n);
                                        ghostVertical(&ghostY[4].td.x, &ghostY[4].td.y , 9, 11, &ghostY[4].tt, WALL, &delay[7].n);
                                        ghostVertical(&ghostY[5].td.x, &ghostY[5].td.y , 9, 11, &ghostY[5].tt, WALL, &delay[8].n);

                                        if (steps[8][47].step == '>' || steps[8][48].step == '>')
                                               turn[4].n = 1;
                                        if (turn[4].n == 1)
                                                horizontalSpikeTrap(47, 48, 8, &appear[4].n, &disappear[4].n, &turn[4].n, WALL);               //qua main bo sung

                                        if (steps[10][47].step == '>' || steps[10][48].step == '>')
                                               turn[7].n = 1;
                                        if (turn[7].n == 1)
                                                horizontalSpikeTrap(47, 48, 10, &appear[7].n, &disappear[7].n, &turn[7].n, WALL);

                                        if (steps[9][46].step == '>')
                                               turn[8].n = 1;
                                        if (turn[8].n == 1)
                                                verticalSpikeTrap(9, 9, 46, &appear[8].n, &disappear[8].n, &turn[8].n, WALL);
                                }
                                else if (LEVEL == 6)
                                {
                                        arrowTrapInovableVersionLEFT(34, 13, &dan[3].x, 30, WALL, &delay[9].n);
                                        arrowTrapInovableVersionRIGHT(35, 13, &dan[4].x,42 , WALL, &delay[10].n);
                                        if (steps[2][26].step == '>')
                                                turn[9].n = 1;
                                        if (turn[9].n == 1)
                                                horizontalSpikeTrap(26, 30, 2, &appear[9].n, &disappear[9].n, &turn[9].n, WALL);
                                        if (steps[3][25].step == '>' || steps[5][25].step == '>')
                                                turn[10].n = 1;
                                        if (turn[10].n == 1)
                                                verticalSpikeTrap(3, 5, 25, &appear[10].n, &disappear[10].n, &turn[10].n, WALL);
                                        if (steps[20][32].step == '>')
                                                turn[11].n = 1;
                                        if (turn[11].n == 1)
                                                horizontalSpikeTrap(32, 32, 20, &appear[11].n, &disappear[11].n, &turn[11].n, WALL);
                                        if (steps[22][32].step == '>')
                                                turn[12].n = 1;
                                        if (turn[12].n == 1)
                                                verticalSpikeTrap(22, 22, 32, &appear[12].n, &disappear[12].n, &turn[12].n, WALL);

                                        if (nv.td.x == 37 && nv.td.y == 11)
                                        {
                                                gotoxy(nv.td.x, nv.td.y);
                                                putchar(' ');
                                                nv.td.x = 38;
                                                nv.td.y = 19;
                                        }
                                }
                                else if (LEVEL == 7)
                                {
                                        arrowTrapInovableVersionRIGHT(16, 3, &dan[5].x, 27, WALL, &delay[11].n);
                                        arrowTrapInovableVersionDOWN(21, 2, &dan[6].y, 6, WALL, &delay[12].n);
                                        arrowTrapInovableVersionDOWN(26, 18, &dan[7].y, 22, WALL, &delay[13].n);
                                        arrowTrapInovableVersionDOWN(30, 17, &dan[8].y, 22, WALL, &delay[14].n);
                                        arrowTrapInovableVersionDOWN(33, 2, &dan[9].y, 6, WALL, &delay[15].n);
                                        arrowTrapInovableVersionDOWN(40, 2, &dan[10].y, 7, WALL, &delay[16].n);
                                        arrowTrapInovableVersionUP(47, 19, &dan[11].y, 14, WALL, &delay[17].n);
                                        arrowTrapInovableVersionDOWN(47, 20, &dan[12].y, 22, WALL, &delay[18].n);
                                        arrowTrapInovableVersionDOWN(51, 3, &dan[13].y, 7, WALL, &delay[19].n);
                                        arrowTrapInovableVersionRIGHT(39, 7, &dan[14].x, 42, WALL, &delay[20].n);

                                        ghostVertical(&ghostY[6].td.x, &ghostY[6].td.y , 9, 12, &ghostY[6].tt, WALL, &delay[21].n);
                                        ghostVertical(&ghostY[7].td.x, &ghostY[7].td.y , 9, 12, &ghostY[7].tt, WALL, &delay[22].n);
                                        ghostVertical(&ghostY[8].td.x, &ghostY[8].td.y , 9, 12, &ghostY[8].tt, WALL, &delay[23].n);

                                        if (steps[4][35].step == '>' || steps[5][35].step == '>')
                                                turn[13].n = 1;
                                        if (turn[13].n == 1)
                                                verticalSpikeTrap(4, 5, 35, &appear[13].n, &disappear[13].n, &turn[13].n, WALL);

                                        if (steps[3][36].step == '>')
                                                turn[14].n = 1;
                                        if (turn[14].n == 1)
                                                horizontalSpikeTrap(36, 39, 3, &appear[14].n, &disappear[14].n, &turn[14].n, WALL);

                                        if (steps[18][39].step == '>')
                                                turn[15].n = 1;
                                        if (turn[15].n == 1)
                                                horizontalSpikeTrap(39, 41, 18, &appear[15].n, &disappear[15].n, &turn[15].n, WALL);
                                }
                                else if (LEVEL == 8)
                                {
                                        arrowTrapInovableVersionRIGHT(28, 9, &dan[15].x, 42, WALL, &delay[24].n);
                                        arrowTrapInovableVersionUP(29, 16, &dan[16].y, 9, WALL, &delay[25].n);
                                        arrowTrapInovableVersionRIGHT(29, 18, &dan[17].x, 40, WALL, &delay[26].n);
                                        arrowTrapInovableVersionDOWN(26, 12, &dan[18].y, 18, WALL, &delay[27].n);
                                        arrowTrapInovableVersionLEFT(43, 15, &dan[19].x, 37, WALL, &delay[28].n);
                                        arrowTrapInovableVersionUP(45, 12, &dan[20].y, 7, WALL, &delay[29].n);
                                        arrowTrapInovableVersionLEFT(35, 7, &dan[21].x, 26, WALL, &delay[30]);
                                        arrowTrapInovableVersionRIGHT(36, 7, &dan[22].x, 45, WALL, &delay[31]);
                                        arrowTrapInovableVersionRIGHT(33, 4, &dan[23].x, 42, WALL, &delay[32]);
                                        arrowTrapInovableVersionRIGHT(44, 4, &dan[24].x, 47, WALL, &delay[33]);
                                        arrowTrapInovableVersionDOWN(47, 10, &dan[25].y, 17, WALL, &delay[34].n);
                                }
                                else if (LEVEL == 9)
                                {
                                        arrowTrapInovableVersionDOWN(39, 2, &dan[26].y, 5, WALL, &delay[35].n);
                                        arrowTrapInovableVersionRIGHT(26, 6, &dan[27].x, 32, WALL, &delay[36].n);
                                        arrowTrapInovableVersionDOWN(23, 13, &dan[28].y, 15, WALL, &delay[37].n);
                                        arrowTrapInovableVersionDOWN(24, 13, &dan[29].y, 15, WALL, &delay[38].n);
                                        arrowTrapInovableVersionDOWN(25, 13, &dan[30].y, 15, WALL, &delay[39].n);
                                        arrowTrapInovableVersionUP(18, 10, &dan[31].y, 8, WALL, &delay[40].n);
                                        arrowTrapInovableVersionUP(19, 10, &dan[32].y, 8, WALL, &delay[41].n);
                                        arrowTrapInovableVersionUP(20, 10, &dan[33].y, 8, WALL, &delay[42].n);
                                        arrowTrapInovableVersionDOWN(16, 2, &dan[34].y, 6, WALL, &delay[43].n);
                                        arrowTrapInovableVersionDOWN(18, 4, &dan[35].y, 6, WALL, &delay[44].n);
                                        arrowTrapInovableVersionDOWN(43, 13, &dan[36].y, 15, WALL, &delay[45].n);
                                        arrowTrapInovableVersionDOWN(44, 13, &dan[37].y, 15, WALL, &delay[46].n);
                                        arrowTrapInovableVersionDOWN(45, 13, &dan[38].y, 15, WALL, &delay[47].n);
                                        arrowTrapInovableVersionRIGHT(48, 8, &dan[39].x, 52, WALL, &delay[48].n);
                                        arrowTrapInovableVersionRIGHT(48, 9, &dan[40].x, 52, WALL, &delay[49].n);
                                        arrowTrapInovableVersionRIGHT(48, 10, &dan[41].x, 52, WALL, &delay[50].n);
                                        arrowTrapInovableVersionLEFT(53, 5, &dan[42].x, 48, WALL, &delay[51].n);
                                        arrowTrapInovableVersionLEFT(38, 20, &dan[43].x, 33, WALL, &delay[52].n);
                                        arrowTrapInovableVersionRIGHT(32, 21, &dan[44].x, 37, WALL, &delay[53].n);

                                        if (nv.td.x == 46 && nv.td.y == 2)
                                        {
                                                gotoxy(46, 2);
                                                putchar(' ');
                                                nv.td.x = 42;
                                                nv.td.y = 22;
                                        }
                                }
                                else if (LEVEL == 10)
                                {
                                        arrowTrapInovableVersionRIGHT(33, 12, &dan[45].x, 41, WALL, &delay[54].n);
                                        arrowTrapInovableVersionLEFT(32, 12, &dan[46].x, 23, WALL, &delay[55].n);
                                        arrowTrapInovableVersionLEFT(56, 8, &dan[47].x, 45, WALL, &delay[56].n);
                                        arrowTrapInovableVersionLEFT(56, 9, &dan[48].x, 45, WALL, &delay[57].n);
                                        arrowTrapInovableVersionLEFT(56, 14, &dan[49].x, 24, WALL, &delay[58].n);
                                        arrowTrapInovableVersionDOWN(19, 19, &dan[50].y, 22, WALL, &delay[59].n);
                                        arrowTrapInovableVersionDOWN(20, 20, &dan[51].y, 22, WALL, &delay[60].n);
                                        arrowTrapInovableVersionDOWN(22, 20, &dan[52].y, 22, WALL, &delay[61].n);
                                        arrowTrapInovableVersionDOWN(23, 19, &dan[53].y, 22, WALL, &delay[62].n);
                                        arrowTrapInovableVersionLEFT(42, 21, &dan[54].x, 34, WALL, &delay[63].n);
                                        arrowTrapInovableVersionLEFT(42, 19, &dan[55].x, 35, WALL, &delay[64].n);

                                        if (nv.td.x == 15 && (nv.td.y == 14 || nv.td.y == 6 || nv.td.y == 4))
                                                turn[16].n = 1;
                                        if (turn[16].n == 1)
                                                verticalSpikeTrap(4, 14, 15, &appear[16].n, &disappear[16].n, &turn[16].n, WALL);

                                        if (nv.td.x == 22 && nv.td.y == 14)
                                        {
                                                gotoxy(22, 14);
                                                putchar(' ');
                                                nv.td.x = 22;
                                                nv.td.y = 12;
                                        }
                                        if (nv.td.x == 37 && nv.td.y == 9)
                                        {
                                                gotoxy(37, 9);
                                                putchar(' ');
                                                nv.td.x = 14;
                                                nv.td.y = 22;
                                        }
                                        if (nv.td.x == 14 && nv.td.y == 18)
                                        {
                                                gotoxy(14, 18);
                                                putchar(' ');
                                                nv.td.x = 50;
                                                nv.td.y = 18;
                                        }
                                        if (nv.td.x == 28 && nv.td.y == 18)
                                        {
                                                gotoxy(28, 18);
                                                putchar(' ');
                                                nv.td.x = 34;
                                                nv.td.y = 22;
                                        }
                                        if (nv.td.x == 43 && nv.td.y == 20)
                                        {
                                                gotoxy(43, 20);
                                                putchar(' ');
                                                nv.td.x = 50;
                                                nv.td.y = 18;
                                        }
                                }



                                // gold
                                changeColor(14);
                                if (gold <= 999999)
                                {
                                        if (gold < 100)
                                        {
                                                gotoxy(78, 8);
                                                printf("%d", gold);
                                        }
                                        else if (gold < 10000)
                                        {
                                                gotoxy(77, 8);
                                                printf("%d", gold);
                                        }
                                        else if (gold < 1000000)
                                        {
                                                gotoxy(76, 8);
                                                printf("%d", gold);
                                        }
                                }
                                else
                                {
                                        gotoxy(76, 8);
                                        printf("999999");
                                }
                                resetColor();

                                for (int j = 0; j < 25; j++)
                                        for (int i = 0; i < 70; i++)
                                                steps[j][i].step = '\0';

                                //dieu khien
                                if (kbhit())
                                {
                                        char dieukhien;
                                        dieukhien = getch();
                                        vitricu.x = nv.td.x;
                                        vitricu.y = nv.td.y;
                                        gotoxy(vitricu.x, vitricu.y);
                                        puts(" ");
                                        if (dieukhien == 'W' || dieukhien == 'w')
                                                nv.tt = UP;
                                        else if (dieukhien == 'S' || dieukhien == 's')
                                                nv.tt = DOWN;
                                        else if (dieukhien == 'D' || dieukhien == 'd')
                                                nv.tt = RIGHT;
                                        else if (dieukhien == 'A' || dieukhien == 'a')
                                                nv.tt = LEFT;
                                        else if (dieukhien == 27)
                                        {
                                                /*int loopMenuPause = 1;
                                                int choiceMenuPause = 1;
                                                while (loopMenuPause)
                                                {
                                                        menuPause(&choiceMenuPause, &loopMenuPause);
                                                        Sleep(150);
                                                }*/
                                                menu = PAUSE;
                                                loopLV = 0;
                                        }
                                }

                                // portal
                                if ((LEVEL == 1) && (nv.td.y == 2 && (nv.td.x ==70 || nv.td.x == 66)))
                                {
                                        PlaySound(TEXT("win.wav"), NULL, SND_SYNC);
                                        loopLV = 0;
                                        if (coinWave == 405)
                                        {
                                                if (levelMax == 1)
                                                {
                                                        levelMax += 1;
                                                }
                                                if (mapChoice == 1)
                                                        mapChoice += 1;
                                                menu = WON;
                                        }
                                        else
                                        {
                                                menu = NOLOSE;
                                        }
                                        // xoa rac
                                        for (int j = 0; j < 25; j++)
                                                for (int i = 0; i < 72; i++)
                                                        WALL[j][i].shape = '\0';
                                        recordProfile( IDUser, passUser, &gold, &totalGOLD,&levelMax, bought);
                                }
                                else if ((LEVEL == 2) && (nv.td.x == 58) && (nv.td.y ==12 || nv.td.y == 11))
                                {
                                        PlaySound(TEXT("win.wav"), NULL, SND_SYNC);
                                        loopLV = 0;
                                        if (coinWave == 210)
                                        {
                                                if (levelMax == 2)
                                                {
                                                        levelMax += 1;
                                                }
                                                if (mapChoice == 2)
                                                        mapChoice += 1;
                                                menu = WON;
                                        }
                                        else
                                        {
                                                menu = NOLOSE;
                                        }
                                        for (int j = 0; j < 25; j++)
                                                for (int i = 0; i < 72; i++)
                                                        WALL[j][i].shape = '\0';
                                        recordProfile( IDUser, passUser, &gold, &totalGOLD,&levelMax, bought);
                                }
                                // por tal lv 3
                                else if ((LEVEL == 3) && (nv.td.x == 8) && (nv.td.y == 9))
                                {
                                        PlaySound(TEXT("win.wav"), NULL, SND_SYNC);
                                        loopLV = 0;
                                        if (coinWave == 175)
                                        {
                                                if (levelMax == 3)
                                                {
                                                        levelMax += 1;
                                                }
                                                if (mapChoice == 3)
                                                        mapChoice += 1;
                                                menu = WON;
                                        }
                                        else
                                        {
                                                menu = NOLOSE;
                                        }
                                        for (int j = 0; j < 25; j++)
                                                for (int i = 0; i < 72; i++)
                                                        WALL[j][i].shape = '\0';
                                        recordProfile( IDUser, passUser, &gold, &totalGOLD,&levelMax, bought);
                                }
                                else if ((LEVEL == 4) && (nv.td.x == 46) && (nv.td.y == 2))
                                {
                                        PlaySound(TEXT("win.wav"), NULL, SND_SYNC);
                                        loopLV = 0;
                                        if (coinWave == 155)
                                        {
                                                if (levelMax == 4)
                                                {
                                                        levelMax += 1;
                                                }
                                                if (mapChoice == 4)
                                                        mapChoice += 1;
                                                menu = WON;
                                        }
                                        else
                                        {
                                                menu = NOLOSE;
                                        }
                                        for (int j = 0; j < 25; j++)
                                                for (int i = 0; i < 72; i++)
                                                        WALL[j][i].shape = '\0';
                                        recordProfile( IDUser, passUser, &gold, &totalGOLD,&levelMax, bought);
                                }
                                else if ((LEVEL == 5) && (nv.td.x == 3) && (nv.td.y == 10))
                                {
                                        PlaySound(TEXT("win.wav"), NULL, SND_SYNC);
                                        loopLV = 0;
                                        if (coinWave == 170)
                                        {
                                                if (levelMax == 5)
                                                {
                                                        levelMax += 1;
                                                }
                                                if (mapChoice == 5)
                                                        mapChoice += 1;
                                                menu = WON;
                                        }
                                        else
                                        {
                                                menu = NOLOSE;
                                        }
                                        for (int j = 0; j < 25; j++)
                                                for (int i = 0; i < 72; i++)
                                                        WALL[j][i].shape = '\0';
                                        recordProfile( IDUser, passUser, &gold, &totalGOLD,&levelMax, bought);
                                }
                                else if ((LEVEL == 6) && (nv.td.x == 27) && (nv.td.y == 15))
                                {
                                        PlaySound(TEXT("win.wav"), NULL, SND_SYNC);
                                        loopLV = 0;
                                        if (coinWave == 90)
                                        {
                                                if (levelMax == 6)
                                                {
                                                        levelMax += 1;
                                                }
                                                if (mapChoice == 6)
                                                        mapChoice += 1;
                                                menu = WON;
                                        }
                                        else
                                        {
                                                menu = NOLOSE;
                                        }
                                        for (int j = 0; j < 25; j++)
                                                for (int i = 0; i < 72; i++)
                                                        WALL[j][i].shape = '\0';
                                        recordProfile( IDUser, passUser, &gold, &totalGOLD,&levelMax, bought);
                                }
                                else if ((LEVEL == 7) && (nv.td.x == 16) && (nv.td.y == 12))
                                {
                                        PlaySound(TEXT("win.wav"), NULL, SND_SYNC);
                                        loopLV = 0;
                                        if (coinWave == 210)
                                        {
                                                if (levelMax == 7)
                                                {
                                                        levelMax += 1;
                                                }
                                                if (mapChoice == 7)
                                                        mapChoice += 1;
                                                menu = WON;
                                        }
                                        else
                                        {
                                                menu  = NOLOSE;
                                        }
                                        for (int j = 0; j < 25; j++)
                                                for (int i = 0; i < 72; i++)
                                                        WALL[j][i].shape = '\0';
                                        recordProfile( IDUser, passUser, &gold, &totalGOLD,&levelMax, bought);
                                }
                                else if ((LEVEL == 8) && (nv.td.x == 36) && (nv.td.y == 21))
                                {
                                        PlaySound(TEXT("win.wav"), NULL, SND_SYNC);
                                        loopLV = 0;
                                        if (coinWave == 75)
                                        {
                                                if (levelMax == 8)
                                                {
                                                        levelMax += 1;
                                                }
                                                if (mapChoice == 8)
                                                        mapChoice += 1;
                                                menu = WON;
                                        }
                                        else
                                        {
                                                menu = NOLOSE;
                                        }
                                        for (int j = 0; j < 25; j++)
                                                for (int i = 0; i < 72; i++)
                                                        WALL[j][i].shape = '\0';
                                        recordProfile( IDUser, passUser, &gold, &totalGOLD,&levelMax, bought);
                                }
                                else if ((LEVEL == 9) && (nv.td.x == 34) && (nv.td.y == 13))
                                {
                                        PlaySound(TEXT("win.wav"), NULL, SND_SYNC);
                                        loopLV = 0;
                                        if (coinWave == 135)
                                        {
                                                if (levelMax == 9)
                                                {
                                                        levelMax += 1;
                                                }
                                                if (mapChoice == 9)
                                                        mapChoice += 1;
                                                menu = WON;
                                        }
                                        else
                                        {
                                                menu = NOLOSE;
                                        }
                                        for (int j = 0; j < 25; j++)
                                                for (int i = 0; i < 72; i++)
                                                        WALL[j][i].shape = '\0';
                                        recordProfile( IDUser, passUser, &gold, &totalGOLD,&levelMax, bought);
                                }
                                else if ((LEVEL == 10) && (nv.td.x == 57) && (nv.td.y == 22))
                                {
                                        PlaySound(TEXT("win.wav"), NULL, SND_SYNC);
                                        loopLV = 0;
                                        printBoundary();
                                        printName();
                                        int win = 1;
                                        while (win)
                                        {
                                                gotoxy(36, 16);
                                                changeColor(10);
                                                printf("VICTORY");
                                                resetColor();
                                                gotoxy(28, 19);
                                                printf("Press Enter to return Menu");
                                                if (kbhit())
                                                {
                                                        char enter;
                                                        enter = getch();
                                                        if (enter == 13)
                                                        {
                                                                menu = MAIN;
                                                                win = 0;
                                                        }
                                                }
                                                Sleep(300);
                                        }

                                        for (int j = 0; j < 25; j++)
                                                for (int i = 0; i < 72; i++)
                                                        WALL[j][i].shape = '\0';
                                        recordProfile( IDUser, passUser, &gold, &totalGOLD,&levelMax, bought);
                                }



                                if (nv.tt == UP)
                                {
                                        for (int i = nv.td.y - 1; i >= 1; i--)
                                                if (WALL[i][nv.td.x].shape == '*')
                                                {
                                                        verticalAnimationUp(nv.td.x, nv.td.y, i + 1, steps, &skin);
                                                        nv.td.y = i + 1;
                                                        nv.tt = STOP;
                                                        break;
                                                }
                                                else if (WALL[i][nv.td.x].shape == '$')
                                                {
                                                        if ((LEVEL == 1 && coinWave < 405) || (LEVEL == 2 && coinWave < 210) || (LEVEL == 3 && coinWave < 175) || (LEVEL == 4 && coinWave < 155) || (LEVEL == 5 && coinWave < 170) || (LEVEL == 6 && coinWave < 90) || (LEVEL == 7 && coinWave < 210) || (LEVEL == 8 && coinWave < 75) || (LEVEL == 9 && coinWave < 135))
                                                        {
                                                                coinWave += 1;
                                                        }
                                                        gold += 1;
                                                        totalGOLD += 1;
                                                        WALL[i][nv.td.x].shape == '\0';
                                                }
                                                else if ((WALL[i][nv.td.x].shape == '#'))
                                                {
                                                        PlaySound(TEXT("lose.wav"), NULL, SND_SYNC);
                                                        loopLV = 0;
                                                        menu = LOST;
                                                }
                                }
                                else if (nv.tt == DOWN)
                                {
                                        for (int i = nv.td.y + 1; i <= consoleHeight - 1; i++)
                                                if (WALL[i][nv.td.x].shape == '*')
                                                {
                                                        verticalAnimationDown(nv.td.x, nv.td.y, i - 1, steps, &skin);
                                                        nv.td.y = i - 1;
                                                        nv.tt = STOP;
                                                        break;
                                                }
                                                else if (WALL[i][nv.td.x].shape == '$')
                                                {
                                                        if ((LEVEL == 1 && coinWave < 405) || (LEVEL == 2 && coinWave < 210) || (LEVEL == 3 && coinWave < 175) || (LEVEL == 4 && coinWave < 155) || (LEVEL == 5 && coinWave < 170) || (LEVEL == 6 && coinWave < 90) || (LEVEL == 7 && coinWave < 210) || (LEVEL == 8 && coinWave < 75) || (LEVEL == 9 && coinWave < 135))
                                                        {
                                                                coinWave += 1;
                                                        }
                                                        gold += 1;
                                                        totalGOLD += 1;
                                                        WALL[i][nv.td.x].shape = '\0';
                                                }
                                                else if ((WALL[i][nv.td.x].shape == '#'))
                                                {
                                                        PlaySound(TEXT("lose.wav"), NULL, SND_SYNC);
                                                        loopLV = 0;
                                                        menu = LOST;
                                                }
                                }
                                else if (nv.tt == RIGHT)
                                {
                                        for (int i = nv.td.x + 1; i <= consoleWidth - 12; i++)
                                                if (WALL[nv.td.y][i].shape == '*')
                                                {
                                                        horizontallAnimationRight(nv.td.x, i - 1, nv.td.y, steps, &skin);
                                                        nv.td.x = i - 1;
                                                        nv.tt = STOP;
                                                        break;
                                                }
                                                else if (WALL[nv.td.y][i].shape == '$')
                                                {
                                                        if ((LEVEL == 1 && coinWave < 405) || (LEVEL == 2 && coinWave < 210) || (LEVEL == 3 && coinWave < 175) || (LEVEL == 4 && coinWave < 155) || (LEVEL == 5 && coinWave < 170) || (LEVEL == 6 && coinWave < 90) || (LEVEL == 7 && coinWave < 210) || (LEVEL == 8 && coinWave < 75) || (LEVEL == 9 && coinWave < 135))
                                                        {
                                                                coinWave += 1;
                                                        }
                                                        gold += 1;
                                                        totalGOLD += 1;
                                                        WALL[nv.td.y][i].shape = '\0';
                                                }
                                                 else if ((WALL[nv.td.y][i].shape == '#'))
                                                {
                                                        PlaySound(TEXT("lose.wav"), NULL, SND_SYNC);
                                                        loopLV = 0;
                                                        menu = LOST;
                                                }
                                }
                                else if (nv.tt == LEFT)
                                {
                                        for (int i = nv.td.x - 1; i >= 1; i--)
                                                if (WALL[nv.td.y][i].shape == '*')
                                                {
                                                        horizontallAnimationLeft(nv.td.x, i + 1, nv.td.y, steps, &skin);
                                                        nv.td.x = i + 1;
                                                        nv.tt = STOP;
                                                        break;
                                                }
                                                else if (WALL[nv.td.y][i].shape == '$')
                                                {
                                                        if ((LEVEL == 1 && coinWave < 405) || (LEVEL == 2 && coinWave < 210) || (LEVEL == 3 && coinWave < 175) || (LEVEL == 4 && coinWave < 155) || (LEVEL == 5 && coinWave < 170) || (LEVEL == 6 && coinWave < 90) || (LEVEL == 7 && coinWave < 210) || (LEVEL == 8 && coinWave < 75) || (LEVEL == 9 && coinWave < 135))
                                                        {
                                                                coinWave += 1;
                                                        }
                                                        gold += 1;
                                                        totalGOLD += 1;
                                                        WALL[nv.td.y][i].shape = '\0';
                                                }
                                                else if ((WALL[nv.td.y][i].shape == '#'))
                                                {
                                                        PlaySound(TEXT("lose.wav"), NULL, SND_SYNC);
                                                        loopLV = 0;
                                                        menu = LOST;
                                                }
                                }
                                else if (nv.tt == STOP)
                                {
                                        if (WALL[nv.td.y][nv.td.x].shape == '#')
                                        {
                                                PlaySound(TEXT("lose.wav"), NULL, SND_SYNC);
                                                loopLV = 0;
                                                menu = LOST;
                                        }
                                }
                                if (LEVEL == 1)
                                        Sleep(50);
                                else if (LEVEL == 2)
                                        Sleep(30);
                        }
                }
        }
        while (gameLOOP);
        return 0;
}

                                                                                        // dang nhap game
void passBorder(){
    gotoxy(21, 16);
        printf("PASSWORD");
        for (int i = 35; i < 55; i++)
        {
                gotoxy(i, 15);
                printf("_");
        }
        gotoxy(34, 16);
        printf("|");
        gotoxy(34, 17);
        printf("|");
        gotoxy(55, 16);
        printf("|");
        gotoxy(55, 17);
        printf("|");
        for (int i = 35; i < 55; i++)
        {
                gotoxy(i, 17);
                printf("_");
        }

}

void idBorder (){
    gotoxy(21, 13);
        printf("USERNAME");
        for (int i = 35; i < 55; i++)
        {
                gotoxy(i, 12);
                printf("_");
        }
        gotoxy(34,13);
        printf("|");
        gotoxy(34,14);
        printf("|");
        gotoxy(55,13);
        printf("|");
        gotoxy(55,14);
        printf("|");
        for (int i = 35; i < 55; i++)
        {
                gotoxy(i, 14);
                printf("_");
        }
}

void newPassBorder(){
    gotoxy(20, 16);
        printf("NEW PASS");
        for (int i = 35; i < 55; i++)
        {
                gotoxy(i, 15);
                printf("_");
        }
        gotoxy(34, 16);
        printf("|");
        gotoxy(34, 17);
        printf("|");
        gotoxy(55, 16);
        printf("|");
        gotoxy(55, 17);
        printf("|");
        for (int i = 35; i < 55; i++)
        {
                gotoxy(i, 17);
                printf("_");
        }

}

void currentPassBorder (){
    gotoxy(20, 13);
        printf("CURRENT PASS");
        for (int i = 35; i < 55; i++)
        {
                gotoxy(i, 12);
                printf("_");
        }
        gotoxy(34,13);
        printf("|");
        gotoxy(34,14);
        printf("|");
        gotoxy(55,13);
        printf("|");
        gotoxy(55,14);
        printf("|");
        for (int i = 35; i < 55; i++)
        {
                gotoxy(i, 14);
                printf("_");
        }
}

void pass (char str[], int *loop){
    char key;
        gotoxy(36, 16);
        int j = 36;
        int i = 0;
        do
        {
                key = getch();
                if (key == 8)
                {
                        if (j > 36)
                                j--;
                        if (i == 0)
                        {
                                str[0] = '\0';
                        }
                        else if (i > 0)
                        {
                                i--;
                                str[i] = '\0';
                        }
                        gotoxy(j, 16);
                        printf(" ");

                }
                else
                {
                        if (key != 13 && i <= 16)
                        {
                                gotoxy(j, 16);
                                printf("*");
                                str[i] = key;
                                i++;
                                j++;
                        }
                        else
                                str[i] = '\0';
                }
        }
        while (key != 13);
}

void ID (char str[], int *loop){
    char key;
        gotoxy(36, 13);
        int j = 36;
        int i = 0;
        do
        {
                key = getch();
                if (key == 8)
                {
                        if (j > 36)
                                j--;
                        if (i == 0)
                        {
                                str[0] = '\0';
                        }
                        else if (i > 0)
                        {
                                i--;
                                str[i] = '\0';
                        }
                        gotoxy(j, 13);
                        printf(" ");

                }
                else
                {
                        if (key != 13 && i <= 16)
                        {
                                gotoxy(j, 13);
                                printf("%c", key);
                                str[i] = key;
                                i++;
                                j++;
                        }
                        else
                                str[i] = '\0';
                }
        }
        while (key != 13);
}

void current (char str[], int *loop){
    char key;
        gotoxy(36, 13);
        int j = 36;
        int i = 0;
        do
        {
                key = getch();
                if (key == 8)
                {
                        if (j > 36)
                                j--;
                        if (i == 0)
                        {
                                str[0] = '\0';
                        }
                        else if (i > 0)
                        {
                                i--;
                                str[i] = '\0';
                        }
                        gotoxy(j, 13);
                        printf(" ");

                }
                else
                {
                        if (key != 13 && i <= 16)
                        {
                                gotoxy(j, 13);
                                printf("*");
                                str[i] = key;
                                i++;
                                j++;
                        }
                        else
                                str[i] = '\0';
                }
        }
        while (key != 13);
}



                                                                                        // dang nhap game
// A(1;1); B(consoleWidth -13;1); C(1;ConsoleHeight - 2); D( consoleWidth -13; consoleHeight - 2)
void level1(wall WALL[25][72])
{
        for (int i = 66; i <= 70; i++)
        {
                changeColor(78);
                gotoxy(i, 2);
                putchar(177);
                resetColor();
                // portal
        }
        wall wall;
        putWall(1, 5, 4, 0,  WALL);
        putWall(4, 5, 0, 4,  WALL);
        putWall(4, 9, 9, 0,  WALL);
        putWall(13, 9, 0, 4,  WALL);
        putWall(14, 12, 5, 0,  WALL);
        putWall(18, 12, 0, 5,  WALL);
        putWall(16, 16, 3, 0,  WALL);
        putWall(16, 16 ,0, 5,  WALL);
        putWall(1, 7, 0, 5,  WALL);
        putWall(1, 11, 7, 0,  WALL);
        putWall(8, 11, 0, 3,  WALL);
        putWall(7, 13, 0, 6,  WALL);
        putWall(7, 18, 7, 0,  WALL);
        putWall(11, 18, 0, 2,  WALL);
        putWall(9, 19, 5, 0,  WALL);
        putWall(9, 20, 0, 4,  WALL);
        putWall(9, 23, 12, 0,  WALL);
        putWall(16, 20, 5, 0,  WALL);
        putWall(21, 22, 0, 2,  WALL);
        putWall(21, 22, 3, 0,  WALL);
        putWall(21, 19, 0, 2,  WALL);
        putWall(23, 21, 0, 2,  WALL);
        putWall(23, 21, 13, 0,  WALL);// sua
        putWall(21, 19, 8, 0,  WALL);
        putWall(28, 15, 0, 5,  WALL);
        putWall(22, 15, 6, 0,  WALL);
        putWall(22, 11, 0, 5,  WALL);
        putWall(35, 13, 0, 8,  WALL);
        putWall(28, 13, 7, 0,  WALL);
        putWall(28, 11, 0, 2,  WALL);
        putWall(28, 11, 24, 0,  WALL);
        //putWall(38, 11, 0, 13,  WALL);
        putWall(23, 11, 1, 0,  WALL);
        putWall(23, 9, 0, 3,  WALL);
        putWall(23, 9, 6, 0,  WALL);
        putWall(28, 4, 0, 6,  WALL);
        putWall(28, 4, 25, 0,  WALL);
        putWall(32, 6, 0, 4,  WALL);
        putWall(32, 6, 4, 0,  WALL);
        putWall(35, 6, 0, 2,  WALL);
        putWall(35, 7, 10, 0,  WALL);
        putWall(32, 9, 4, 0,  WALL);
        putWall(35, 8, 0, 1,  WALL);
        putWall(35, 8, 10, 0,  WALL);
        putWall(44, 8, 0, 2,  WALL);
        putWall(44, 9, 4, 0,  WALL);
        putWall(47, 6, 0, 4,  WALL);
        putWall(44, 6, 3, 0,  WALL);
        putWall(51, 10, 1, 0,  WALL);
        putWall(51, 10, 4, 0,  WALL);
        putWall(54, 10, 0, 4,  WALL);
        putWall(42, 13, 12, 0,  WALL);
        putWall(42, 13, 0, 11,  WALL);
        putWall(52, 4, 0, 4,  WALL);
        putWall(52, 7, 8, 0,  WALL);
        putWall(59, 7, 0, 7,  WALL);
        putWall(42, 23, 17, 0,  WALL);
        putWall(59, 14, 2, 0,  WALL);
        putWall(60, 14, 0, 7,  WALL);
        putWall(60, 20, 6, 0,  WALL);
        putWall(56, 17, 0, 4,  WALL);
        putWall(56, 17, 2, 0,  WALL);
        putWall(57, 16, 0, 2,  WALL);
        putWall(49, 16, 9, 0,  WALL);
        putWall(49, 16, 0, 2,  WALL);
        putWall(49, 17, 7, 0,  WALL);
        putWall(55, 17, 0, 4,  WALL);
        putWall(58, 22, 0, 1,  WALL);
        putWall(58, 22, 7, 0,  WALL);
        putWall(39, 5, 2, 0,  WALL);
        putWall(39, 10, 2, 0,  WALL);
        putWall(42, 19, 2, 0,  WALL);
        putWall(50, 13, 0, 2,  WALL);
        putWall(54, 15, 0, 1,  WALL);
        putWall(58, 11, 1, 0,  WALL);
        putWall(34, 17, 1, 0,  WALL);
        putWall(29, 15, 1, 0,  WALL);
        putWall(65, 22, 7, 0,  WALL);
        putWall(71, 1, 0, 21,  WALL);
        putWall(65, 1, 0, 20,  WALL);
        putWall(65, 1, 6, 0,  WALL);
        putWall(1, 6, 1, 0, WALL);
        putWall(68, 4, 0, 4,  WALL);
        putWall(70, 14, 1, 0,  WALL);
        putWall(66, 8, 1, 0,  WALL);
        putWall(67, 4, 3, 0, WALL);
        putWall(68, 16, 0, 4,  WALL);
        putWall(68, 10, 0, 4,  WALL);
        putWall(66, 18, 1, 0,  WALL);
        putWall(54, 18, 1, 0,  WALL);

        // Gold D. Roger
        putGold(2, 7, 0, 4, WALL);
        putGold(3, 6, 0, 5, WALL);
        putGold(4, 10, 9, 0, WALL);
        putGold(10, 13, 6, 0, WALL);
        putGold(9, 11, 0, 7, WALL);
        putGold(8, 14, 0, 4, WALL);
        putGold(10, 15, 6, 0, WALL);
        putGold(12, 11, 0, 7, WALL);
        //putGold(13, 13, 0, 5, WALL);
        putGold(14, 13, 0, 3, WALL);
        putGold(14, 20, 0, 3, WALL);
        putGold(15, 13, 0, 10, WALL);
        putGold(16, 13, 0, 3, WALL);
        putGold(17, 13, 0, 3, WALL);
        putGold(10, 20, 0, 3, WALL);
        putGold(11, 20, 0, 3, WALL);
        putGold(12, 20, 0, 3, WALL);
        putGold(13, 20, 0, 3, WALL);
        putGold(17, 21, 0, 2, WALL);
        putGold(18, 21, 0, 2, WALL);
        putGold(16, 21, 0, 2, WALL);
        putGold(19, 21, 0, 2, WALL);
        putGold(20, 21, 0, 2, WALL);
        putGold(22, 20, 0, 2, WALL);
        putGold(22, 20, 13, 0, WALL);
        putGold(29, 16, 0, 4, WALL);
        //putGold(30, 14, 0, 6, WALL);
        //putGold(31, 14, 0, 6, WALL);
        //putGold(32, 14, 0, 6, WALL);
        //putGold(33, 14, 0, 6, WALL);
        putGold(34, 14, 0, 3, WALL);
        putGold(34, 18, 0, 2, WALL);
        putGold(23, 14, 8, 0, WALL);
        putGold(23, 13, 1, 0, WALL);
        putGold(27, 13, 1, 0, WALL);
        putGold(23, 12, 5, 0, WALL);
        //putGold(24, 11, 4, 0, WALL);
        putGold(24, 10, 8, 0, WALL);
        putGold(31, 14, 4, 0, WALL);
        putGold(29, 5, 0, 6, WALL);
        putGold(31, 10, 9, 0, WALL);
        putGold(36, 9, 8, 0, WALL);
        putGold(36, 6, 8, 0, WALL);
        putGold(32, 5, 7, 0, WALL);
        putGold(41, 10, 10, 0, WALL);
        putGold(41, 5, 11, 0, WALL);
        putGold(50, 5, 0, 6, WALL);
        putGold(51, 5, 0, 5, WALL);
        putGold(29, 5, 3, 0, WALL);
        putGold(52, 9, 7, 0, WALL);
        putGold(48, 6, 0, 4, WALL);
        putGold(52, 8, 7, 0, WALL);
        putGold(58, 10, 1, 0, WALL);
        putGold(55, 10, 0, 6, WALL);
        putGold(58, 12, 0, 10, WALL);
        putGold(59, 15, 0, 7, WALL);
        putGold(43, 14, 0, 5, WALL);
        putGold(43, 20, 0, 3, WALL);
        putGold(44, 14, 0, 9, WALL);
        putGold(45, 14, 5, 0, WALL);
        putGold(49, 15, 5, 0, WALL);
        putGold(56, 15, 4, 0, WALL);
        putGold(43, 21, 28, 0, WALL);
        putGold(43, 22, 15, 0, WALL);
        putGold(43, 20, 12, 0, WALL);
        putGold(44, 19, 11, 0, WALL);
        putGold(67, 5, 0, 17, WALL);
        putGold(69, 5, 0, 17, WALL);
        putGold(24, 11, 1, 0, WALL);
        putGold(27, 11, 1, 0, WALL);
        putGold(21, 21, 1, 0, WALL);
        return;

}

void level2(wall WALL[25][72])
{
    changeColor(1);
        putWall(1, 1, 71, 0, WALL);
        putWall(1, 1, 0, 23, WALL);
        putWall(2, 1, 0, 23, WALL);
        putWall(70, 1, 0, 23, WALL);
        putWall(1, 23, 71, 0, WALL);
        putWall(71, 1, 0, 23, WALL);
        putWall(41, 10, 18, 0, WALL);
        putWall(59, 10, 0, 5, WALL);
        putWall(46, 14, 13, 0, WALL);
        for (int j = 11; j <= 13; j++)
        {
                changeColor(78);
                gotoxy(57, j);
                putchar(177);
                resetColor();
        }
        putWall(46, 18, 0, 5, WALL);
        putWall(58, 20, 8, 0, WALL);
        putWall(65, 16, 0, 4, WALL);
        putWall(64, 16, 0, 4, WALL);
        putWall(7, 4, 0, 5, WALL);
        putWall(8, 4, 0, 5, WALL);
        putWall(7, 4, 8, 0, WALL);
        putWall(47, 15, 1, 0, WALL);
        putWall(40, 5, 25, 0, WALL);
        putWall(29, 6, 0, 2, WALL);
        putWall(31, 20, 0, 3, WALL);
        putWall(30, 13, 1, 0, WALL);
        putWall(57, 13, 1, 0, WALL);
        resetColor();

        // gold D. Roger
        putGold(4, 2, 26, 0, WALL);
        putGold(4, 22, 26, 0, WALL);
        putGold(3, 3, 0, 19, WALL);
        putGold(69, 3, 0, 19, WALL);
        putGold(47, 22, 22, 0, WALL);
        putGold(47, 16, 17, 0, WALL);
        putGold(47, 16, 0, 6, WALL);
        putGold(63, 6, 0, 14, WALL);
        putGold(40, 6, 25, 0, WALL);
        putGold(40, 2, 29, 0, WALL);
        putGold(47, 19, 16, 0, WALL);


}

void level3(wall WALL[25][72])
{
        changeColor(8);
        putWall(1, 1, 8, 0, WALL);
        putWall(1, 1, 0, 5, WALL);
        putWall(8, 1, 0, 4, WALL);
        putWall(1, 6, 25, 0, WALL);
        putWall(8, 4, 19, 0, WALL);
        putWall(27, 4, 0, 2, WALL);
        putWall(25, 6, 0, 2, WALL);
        putWall(26, 7, 6, 0, WALL);
        putWall(28, 5, 3, 0, WALL);
        putWall(30, 3, 0, 3, WALL);
        putWall(32, 5, 0, 3, WALL);
        putWall(30, 3, 40, 0, WALL);
        putWall(32, 5, 38, 0, WALL);
        putWall(69, 1, 0, 2, WALL);
        putWall(69, 1, 3, 0, WALL);
        putWall(71, 1, 0, 9, WALL);
        putWall(69, 6, 0, 2, WALL);
        putWall(7, 8, 3, 0, WALL);
        putWall(7, 9, 1, 0, WALL);
        putWall(9, 9, 1, 0, WALL);
        putWall(1, 9, 6, 0, WALL);
        putWall(1, 9, 0, 6, WALL);
        putWall(10, 9, 2, 0, WALL);
        putWall(11, 9, 0, 2, WALL);
        putWall(2, 14, 7, 0, WALL);
        putWall(9, 12, 0, 3, WALL);
        putWall(4, 12, 3, 0, WALL);
        putWall(9, 12, 27, 0, WALL);    // sua
        putWall(11, 10, 25, 0, WALL);
        putWall(35, 8, 0, 3, WALL);
        putWall(35, 12, 0, 4, WALL);
        putWall(35, 7, 35, 0, WALL);
        putWall(38, 12, 0, 3, WALL);
        putWall(39, 12, 0, 3, WALL);
        putWall(35, 16, 8, 0, WALL);
        putWall(42, 12, 0, 4, WALL);
        putWall(42, 12, 7, 0, WALL);
        putWall(48, 10, 0, 2, WALL);
        putWall(41, 10, 7, 0, WALL);
        putWall(41, 9, 30, 0, WALL);
        resetColor();

        redWell(8, 2, 0, 3, WALL);
        redWell(8, 4, 18, 0, WALL);
        redWell(32, 5, 38, 0, WALL);
        redWell(9, 9, 2, 0, WALL);

        changeColor(78);
        gotoxy(8, 9);
        putchar(177);
        resetColor();

        // gold D. Roger
        putGold(7, 2, 0, 4, WALL);
        putGold(26, 5, 0, 2, WALL);
        putGold(26, 6, 6, 0, WALL);
        putGold(31, 4, 0, 3, WALL);
        putGold(31, 4, 39, 0, WALL);
        putGold(8, 5, 18, 0, WALL);
        putGold(70, 2, 0, 6, WALL);
        putGold(36, 8, 35, 0, WALL);
        putGold(36, 8, 0, 8, WALL);
        putGold(36, 15, 6, 0, WALL);
        putGold(41, 11, 0, 4, WALL);
        putGold(41, 11, 7, 0, WALL);
        putGold(9, 11, 27, 0, WALL);
        putGold(2, 10, 9, 0, WALL);
        putGold(2, 10, 0, 4, WALL);
        putGold(2, 13, 7, 0, WALL);
        putGold(8, 10, 0, 4, WALL);
}

void level4(wall WALL[25][72])
{
        changeColor(94);
        putWall(50, 23, 21, 0, WALL);
        putWall(70, 15, 0, 8, WALL);
        putWall(50, 15, 21, 0, WALL);
        putWall(50, 15, 0, 4, WALL);
        putWall(50, 20, 0, 3, WALL);
        putWall(59, 18, 3, 0, WALL);
        putWall(49, 18, 1, 0, WALL);
        putWall(49, 20, 1, 0, WALL);
        putWall(48, 17, 0, 2, WALL);
        putWall(48, 20, 0, 2, WALL);
        putWall(44, 16, 5, 0, WALL);
        putWall(40, 21, 8, 0, WALL);
        putWall(43, 16, 0, 2, WALL);
        putWall(39, 17, 4, 0, WALL);
        putWall(45, 18, 0, 2, WALL);
        putWall(40, 20, 0, 2, WALL);
        putWall(39, 20, 0, 4, WALL);
        putWall(39, 14, 0, 3, WALL);
        putWall(37, 23, 2, 0, WALL);
        putWall(37, 14, 2, 0, WALL);
        putWall(37, 14, 0, 5, WALL);
        putWall(37, 20, 0, 3, WALL);
        putWall(35, 20, 2, 0, WALL);
        putWall(35, 20, 0, 2, WALL);
        putWall(30, 21, 5, 0, WALL);
        putWall(31, 18, 6, 0, WALL);
        putWall(30, 21, 0, 2, WALL);
        putWall(28, 23, 3, 0, WALL);
        putWall(28, 21, 0, 2, WALL);
        putWall(30, 17, 0, 2, WALL);
        putWall(30, 19, 2, 0, WALL);
        putWall(22, 21, 6, 0, WALL);
        putWall(22, 15, 0, 6, WALL);
        putWall(30, 16, 0, 1, WALL);
        putWall(28, 16, 0, 4, WALL);
        putWall(27, 16, 0, 4, WALL);
        putWall(22, 14, 7, 0, WALL);
        putWall(28, 12, 0, 2, WALL);
        putWall(28, 12, 3, 0, WALL);
        putWall(30, 12, 0, 2, WALL);
        putWall(31, 16, 3, 0, WALL);
        putWall(31, 10, 0, 4, WALL);
        putWall(28, 10, 3, 0, WALL);
        putWall(28, 5, 0, 6, WALL);
        putWall(33, 8, 0, 8, WALL);
        putWall(30, 8, 3, 0, WALL);
        putWall(30, 6, 0, 2, WALL);
        putWall(31, 6, 0, 2, WALL);
        putWall(31, 7, 3, 0, WALL);
        putWall(34, 6, 0, 7, WALL);
        putWall(28, 4, 4, 0, WALL);
        putWall (31, 1, 0, 3, WALL);
        putWall (31, 1, 3, 0, WALL);
        putWall (33, 1, 0, 4, WALL);
        putWall (33, 6, 1, 0, WALL);
        putWall (33, 4, 6, 0, WALL);
        putWall (38, 5, 0, 2, WALL);
        putWall (38, 6, 3, 0, WALL);
        putWall (35, 12, 7, 0, WALL);
        putWall (41, 12, 0, 3, WALL);
        putWall (41, 14, 3, 0, WALL);
        putWall (41, 3, 0, 4, WALL);
        putWall (43, 12, 0, 2, WALL);
        putWall (43, 12, 4, 0, WALL);
        putWall (41, 3, 11, 0, WALL);           // sua
        putWall (46, 8, 0, 4, WALL);
        putWall (43, 7, 4, 0, WALL);
        putWall (43, 5, 0, 2, WALL);
        putWall (43, 5, 6, 0, WALL);
        putWall (49, 5, 0, 4, WALL);
        putWall (51, 4, 6, 0, WALL);
        putWall (49, 9, 8, 0, WALL);
        putWall (56, 10, 3, 0, WALL);
        putWall (58, 1, 0, 10, WALL);
        putWall (45, 1, 14, 0, WALL);
        putWall (45, 2, 1, 0, WALL);
        putWall (51, 3, 6, 0, WALL);
        putWall (51, 6, 6, 0, WALL);
        putWall (51, 7, 6, 0, WALL);
        putWall (39, 18, 5, 0, WALL);
        putWall (38, 8, 2, 0, WALL);
        putWall (43, 9, 2, 0, WALL);
        putWall (43, 10, 2, 0, WALL);
        resetColor();

        putWell(70, 15, 0, 9, WALL);
        putWell(50, 21, 0, 3, WALL);
        putWell(51, 15, 19, 0, WALL);
        putWell(50, 15, 0, 4, WALL);
        //putWell(49, 18, 1, 0, WALL);
        putWell(48, 16, 0, 3, WALL);
        for (int i = 15; i <= 23; i++)
        {
                WALL[i][71].shape = '*';
        }
        for (int i = 51; i <= 69; i++)
        {
                WALL[14][i].shape = '*';
        }
        for (int i = 15; i <= 18; i++)
        {
                WALL[i][49].shape = '*';
        }
        for (int i = 21; i <= 23; i++)
        {
                WALL[i][49].shape = '*';
        }
        putGold(46, 19, 15, 0, WALL);
        putGold(41, 20, 7, 0, WALL);
        putGold(44, 17, 4, 0, WALL);
        putGold(44, 17, 0, 3, WALL);
        putGold(46, 18, 2, 0, WALL);
        putGold(39, 19, 5, 0, WALL);
        putGold(32, 19, 6, 0, WALL);
        putGold(30, 20, 5, 0, WALL);
        putGold(23, 20, 6, 0, WALL);
        putGold(23, 15, 6, 0, WALL);
        putGold(23, 15, 0, 5, WALL);
        putGold(30, 15, 3, 0, WALL);
        putGold(32, 9, 0, 6, WALL);
        putGold(29, 9, 3, 0, WALL);
        putGold(29, 5, 0, 4, WALL);
        putGold(29, 5, 3, 0, WALL);
        putGold(33, 5, 5, 0, WALL);
        putGold(35, 5, 0, 7, WALL);
        putGold(35, 11, 10, 0, WALL);
        putGold(45, 8, 0, 4, WALL);
        putGold(40, 8, 6, 0, WALL);
        putGold(35, 7, 8, 0, WALL);
        putGold(42, 4, 0, 3, WALL);
        putGold(42, 4, 9, 0, WALL);
        putGold(50, 6, 0, 3, WALL);
        putGold(50, 8, 7, 0, WALL);
        putGold(57, 6, 0, 4, WALL);
        putGold(49, 2, 9, 0, WALL);
        putGold(57, 2, 0, 3, WALL);
        putWell(28, 4, 0, 5, WALL);
        for (int i = 4; i <= 8; i++)
        {
                WALL[i][27].shape = '*';
        }
        changeColor(78);
        gotoxy(47, 2);
        putchar(177);
        resetColor();
}

void level5(wall WALL[25][72])
{
        changeColor(13);
        putWall(64, 23, 7, 0, WALL);
        putWall(64, 21, 0, 3, WALL);
        putWall(70, 20, 0, 4, WALL);
        putWall(68, 20, 3, 0, WALL);
        putWall(64, 21, 3, 0, WALL);
        putWall(68, 17, 0, 3, WALL);
        putWall(66, 19, 0, 2, WALL);
        putWall(65, 17, 3, 0, WALL);
        putWall(65, 19, 1, 0, WALL);
        putWall(62, 20, 4, 0, WALL);
        putWall(61, 20, 0, 3, WALL);
        putWall(56, 22, 5, 0, WALL);
        putWall(56, 20, 0, 3, WALL);
        putWall(54, 20, 2, 0, WALL);
        putWall(54, 17, 0, 3, WALL);
        putWall(54, 16, 3, 0, WALL);
        putWall(56, 13, 0, 3, WALL);
        putWall(57, 4, 0, 10, WALL);
        putWall(65, 15, 0, 2, WALL);
        putWall(66, 15, 2, 0, WALL);
        putWall(67, 12, 0, 3, WALL);
        putWall(68, 11, 0, 2, WALL);
        putWall(69, 11, 1, 0, WALL);
        putWall(69, 8, 0, 3, WALL);
        putWall(68, 7, 2, 0, WALL);
        putWall(69, 4, 0, 3, WALL);
        putWall(66, 7, 0, 4, WALL);
        putWall(65, 9, 1, 0, WALL);             // doi
        putWall(58, 15, 0, 6, WALL);
        putWall(59, 15, 0, 6, WALL);
        putWall(60, 18, 2, 0, WALL);
        putWall(62, 16, 2, 0, WALL);
        putWall(63, 13, 0, 3, WALL);
        putWall(63, 13, 3, 0, WALL);
        putWall(60, 13, 3, 0, WALL);
        putWall(62, 13, 0, 3, WALL);
        putWall(60, 9, 0, 4, WALL);
        putWall(61, 9, 3, 0, WALL);
        putWall(65, 12, 1, 0, WALL);
        putWall(64, 11, 0, 2, WALL);
        putWall(63, 10, 0, 2, WALL);
        putWall(66, 3, 4, 0, WALL);
        putWall(64, 2, 3, 0, WALL);
        putWall(64, 2, 0, 6, WALL);
        putWall(60, 7, 4, 0, WALL);
        putWall(60, 6, 2, 0, WALL);
        putWall(61, 3, 0, 3, WALL);
        putWall(58, 4, 2, 0, WALL);
        putWall(52, 11, 0, 4, WALL);
        putWall(52, 11, 2, 0, WALL);
        putWall(54, 8, 0, 4, WALL);
        putWall(52, 7, 3, 0, WALL);
        putWall(52, 5, 0, 2, WALL);
        putWall(50, 4, 7, 0, WALL);
        putWall(47, 14, 5, 0, WALL);
        putWall(49, 6, 0, 7, WALL);
        putWall(50, 6, 0, 7, WALL);
        putWall(51, 9, 2, 0, WALL);
        putWall(48, 2, 14, 0, WALL);
        putWall(48, 2, 0, 3, WALL);
        putWall(47, 11, 0, 3, WALL);
        putWall(47, 4, 0, 3, WALL);
        putWall(45, 11, 2, 0, WALL);
        putWall(45, 9, 0, 2, WALL);
        putWall(46, 6, 0, 2, WALL);
        putWall(30, 9, 15, 0, WALL);
        putWall(32, 7, 14, 0, WALL);
        putWall(32, 6, 5, 0, WALL);
        putWall(30, 5, 0, 4, WALL);
        putWall(36, 3, 0, 3, WALL);
        putWall(29, 5, 0, 6, WALL);
        putWall(27, 3, 10, 0, WALL);
        putWall(21, 11, 9, 0, WALL);
        putWall(14, 12, 8, 0, WALL);
        putWall(2, 11, 13, 0, WALL);
        putWall(2, 9, 0, 3, WALL);
        putWall(2, 9, 12, 0, WALL);
        putWall(12, 8, 9, 0, WALL);
        putWall(20, 9, 8, 0, WALL);
        putWall(27, 4, 0, 5, WALL);
        resetColor();

        putWell(68, 18, 0, 3, WALL);
        WALL[18][69].shape = '*';
        putWell(63, 11, 2, 0, WALL);
        putWell(64, 12, 2, 0, WALL);
        putWell(47, 5, 0, 1, WALL);
        putWell(61, 20, 4, 0, WALL);
        putWell(69, 3, 0, 4, WALL);
        WALL[4][70].shape = '*';
        changeColor(78);
        gotoxy(4, 10);
        putchar(177);
        resetColor();
        redWell(47, 9, 2, 0, WALL);


        // Gold D. Roger
        putGold(67, 18, 0, 4, WALL);
        putGold(62, 18, 5, 0, WALL);
        putGold(60, 17, 5, 0, WALL);
        putGold(60, 14, 0, 4, WALL);
        putGold(61, 14, 0, 4, WALL);
        putGold(57, 14, 0, 4, WALL);
        putGold(55, 17, 3, 0, WALL);
        putGold(55, 17, 0, 3, WALL);
        putGold(58, 21, 3, 0, WALL);
        putGold(60, 19, 0, 2, WALL);
        putGold(60, 19, 5, 0, WALL);
        putGold(64, 14, 0, 3, WALL);
        putGold(65, 14, 2, 0, WALL);
        putGold(66, 11, 0, 4, WALL);
        putGold(68, 8, 0, 3, WALL);
        putGold(67, 10, 0, 2, WALL);
        putGold(58, 8, 6, 0, WALL);
        putGold(58, 5, 0, 10, WALL);
        putGold(58, 5, 3, 0, WALL);
        putGold(60, 3, 0, 2, WALL);
        putGold(49, 3, 12, 0, WALL);
        putGold(49, 3, 0, 3, WALL);
        putGold(49, 5, 3, 0, WALL);
        putGold(51, 6, 0, 3, WALL);
        putGold(51, 8, 3, 0, WALL);
        putGold(53, 9, 0, 2, WALL);
        putGold(51, 10, 2, 0, WALL);
        putGold(51, 11, 0, 3, WALL);
        putGold(48, 13, 3, 0, WALL);
        putGold(48, 10, 0, 3, WALL);
        putGold(46, 10, 3, 0, WALL);
        putGold(46, 8, 3, 0, WALL);
        putGold(46, 8, 0, 2, WALL);
        putGold(48, 5, 0, 3, WALL);
        putGold(31, 8, 15, 0, WALL);
        putGold(31, 4, 0, 4, WALL);
        putGold(31, 4, 5, 0, WALL);
        putGold(35, 4, 0, 2, WALL);
        putGold(32, 5, 3, 0, WALL);
        putGold(28, 4, 3, 0, WALL);
        putGold(28, 4, 0, 6, WALL);
        putGold(20, 10, 9, 0, WALL);
        putGold(6, 10, 9, 0, WALL);
}
void level6(wall WALL[25][72])
{
        changeColor(19);
        putWall(37, 1, 8, 0, WALL);
        putWall(45, 1, 0, 4, WALL);
        putWall(38, 4, 7, 0, WALL);
        putWall(36, 1, 0, 6, WALL);
        putWall(38, 5, 0, 3, WALL);
        putWall(37, 1, 8, 0, WALL);
        putWall(34, 6, 3, 0, WALL);
        putWall(34, 3, 0, 3, WALL);
        putWall(32, 8, 7, 0, WALL);
        putWall(32, 5, 0, 3, WALL);
        putWall(31, 5, 0, 4, WALL);
        putWall(26, 3, 8, 0, WALL);
        putWall(26, 4, 2, 0, WALL);
        putWall(31, 1, 0, 2, WALL);
        putWall(24, 1, 7, 0, WALL);
        putWall(24, 1, 0, 6, WALL);
        putWall(24, 6, 6, 0, WALL);
        putWall(29, 6, 0, 5, WALL);
        putWall(36, 9, 0, 3, WALL);
        putWall(35, 9, 0, 4, WALL);
        putWall(35, 12, 6, 0, WALL);
        putWall(38, 11, 5, 0, WALL);
        putWall(38, 9, 7, 0, WALL);
        putWall(44, 9, 0, 5, WALL);
        putWall(43, 13, 0, 2, WALL);
        putWall(42, 14, 0, 4, WALL);// sua
        putWall(29, 10, 5, 0, WALL);
        putWall(32, 11, 2, 0, WALL);
        putWall(29, 12, 4, 0, WALL);
        putWall(29, 13, 0, 3, WALL);
        putWall(37, 9, 1, 0, WALL);
        putWall(33, 14, 5, 0, WALL);
        putWall(35, 15, 5, 0, WALL);
        putWall(29, 16, 4, 0, WALL);
        putWall(32, 17, 10, 0, WALL);
        putWall(39, 18, 0, 5, WALL);
        putWall(37, 18, 3, 0, WALL);
        putWall(37, 18, 0, 3, WALL);
        putWall(36, 19, 0, 2, WALL);
        putWall(34, 22, 5, 0, WALL);
        putWall(34, 21, 1, 0, WALL);
        putWall(33, 21, 0, 3, WALL);
        putWall(31, 21, 0, 1, WALL);
        putWall(30, 21, 0, 1, WALL);
        putWall(28, 19, 0, 3, WALL);
        putWall(28, 19, 8, 0, WALL);
        putWall(27, 19, 0, 3, WALL);
        putWall(25, 23, 8, 0, WALL);
        putWall(25, 16, 0, 7, WALL);
        putWall(28, 14, 0, 5, WALL);
        putWall(26, 14, 2, 0, WALL);
        putWall(26, 14, 0, 4, WALL);
        resetColor();

        changeColor(126);
        gotoxy(37, 11);
        putchar(176);
        gotoxy(38, 19);
        putchar(176);
        resetColor();
        redWell(26, 1, 6, 0, WALL);
        redWell(24, 3, 0, 3, WALL);
        redWell(32, 19, 1, 0, WALL);
        redWell(33, 22, 1, 0, WALL);
        changeColor(78);
        gotoxy(27, 15);
        putchar(177);
        resetColor();
        // Gold D.Roger
        putGold(37, 4, 0, 4, WALL);
        putGold(33, 7, 5, 0, WALL);
        putGold(33, 4, 0, 4, WALL);
        putGold(28, 4, 6, 0, WALL);
        putGold(25, 5, 6, 0, WALL);
        putGold(25, 2, 0, 4, WALL);
        putGold(25, 2, 6, 0, WALL);
        putGold(30, 6, 0, 4, WALL);
        putGold(30, 9, 5, 0, WALL);
        putGold(34, 9, 0, 4, WALL);
        putGold(33, 12, 2, 0, WALL);
        putGold(30, 14, 0, 2, WALL);
        putGold(30, 15, 5, 0, WALL);
        putGold(33, 16, 8, 0, WALL);
        putGold(41, 14, 0, 3, WALL);
        putGold(41, 12, 3, 0, WALL);
        putGold(37, 10, 7, 0, WALL);
        putGold(43, 11, 1, 0, WALL);
        putGold(38, 20, 0, 2, WALL);
        putGold(35, 21, 4, 0, WALL);
        putGold(29, 20, 7, 0, WALL);
        putGold(32, 21, 0, 2, WALL);
        putGold(29, 21, 0, 2, WALL);
        putGold(26, 22, 6, 0, WALL);
        putGold(26, 18, 0, 4, WALL);
        putGold(27, 16, 0, 3, WALL);
}

void level7(wall WALL[25][72])
{
    changeColor(187);
        putWall(15, 23, 8, 0, WALL);
        putWall(15, 20, 0, 3, WALL);
        putWall(15, 20, 5, 0, WALL);
        putWall(22, 19, 0, 4, WALL);
        putWall(21, 19, 1, 0, WALL);
        putWall(19, 11, 0, 9, WALL);
        putWall(21, 11, 0, 9, WALL);
        putWall(18, 11, 2, 0, WALL);
        putWall(17, 11, 0, 3, WALL);
        putWall(15, 13, 3, 0, WALL);
        putWall(15, 9, 0, 4, WALL);
        putWall(15, 9, 5, 0, WALL);
        putWall(15, 2, 6, 0, WALL);
        putWall(20, 1, 3, 0, WALL);
        putWall(15, 2, 0, 3, WALL);
        putWall(15, 4, 2, 0, WALL);
        putWall(16, 4, 0, 3, WALL);
        putWall(16, 6, 3, 0, WALL);
        putWall(19, 6, 0, 3, WALL);
        putWall(20, 4, 1, 0, WALL);
        putWall(21, 7, 0, 3, WALL);
        putWall(22, 4, 0, 4, WALL);
        putWall(22, 4, 4, 0, WALL);
        putWall(25, 5, 0, 4, WALL);
        putWall(26, 8, 0, 2, WALL);
        putWall(21, 9, 5, 0, WALL);
        // thanh tren
        putWall(22, 2, 7, 0, WALL);
        putWall(28, 3, 0, 3, WALL);
        putWall(27, 5, 1, 0, WALL);
        putWall(27, 6, 2, 0, WALL);
        putWall(28, 7, 0, 3, WALL);
        putWall(21, 11, 6, 0, WALL);
        putWall(26, 11, 0, 7, WALL);
        putWall(25, 17, 0, 2, WALL);
        putWall(24, 18, 0, 6, WALL);
        putWall(24, 23, 4, 0, WALL);
        putWall(28, 21, 0, 3, WALL);
        putWall(29, 21, 0, 3, WALL);


        putWall(28, 11, 0, 7, WALL);
        putWall(29, 16, 0, 2, WALL);
        putWall(29, 16, 3, 0, WALL);
        putWall(31, 16, 0, 6, WALL);
        putWall(30, 23, 4, 0, WALL);
        putWall(32, 17, 0, 5, WALL);
        putWall(34, 19, 0, 5, WALL);
        putWall(33, 11, 0, 7, WALL);
        putWall(35, 11, 0, 9, WALL);
        putWall(28, 9, 6, 0, WALL);
        putWall(32, 1, 3, 0, WALL);
        putWall(32, 2, 0, 5, WALL);
        putWall(32, 7, 2, 0, WALL);
        putWall(33, 7, 0, 2, WALL);
        putWall(35, 6, 0, 4, WALL);
        putWall(36, 4, 0, 3, WALL);
        putWall(36, 4, 4, 0, WALL);
        putWall(34, 4, 1, 0, WALL);
        putWall(34, 2, 6, 0, WALL);
        putWall(39, 1, 3, 0, WALL);
        putWall(41, 2, 0, 4, WALL);
        putWall(39, 5, 0, 2, WALL);
        putWall(38, 6, 0, 2, WALL);
        putWall(41, 6, 4, 0, WALL);
        putWall(43, 6, 0, 3, WALL);
        putWall(44, 6, 0, 3, WALL);

        putWall(45, 8, 3, 0, WALL);
        putWall(47, 6, 0, 2, WALL);
        putWall(48, 4, 0, 3, WALL);
        putWall(47, 2, 0, 3, WALL);
        putWall(37, 7, 0, 3, WALL);
        putWall(37, 9, 2, 0, WALL);

        putWall(38, 11, 0, 5, WALL);
        putWall(38, 15, 4, 0, WALL);
        putWall(41, 16, 0, 1, WALL);
        putWall(38, 17, 4, 0, WALL);
        putWall(38, 18, 0, 4, WALL);
        putWall(48, 13, 0, 10, WALL);

        putWall(41, 11, 0, 3, WALL);
        putWall(40, 11, 0, 3, WALL);
        putWall(43, 13, 6, 0, WALL);
        putWall(43, 11, 0, 2, WALL);
        putWall(43, 15, 0, 3, WALL);
        putWall(43, 15, 3, 0, WALL);
        putWall(46, 15, 0, 3, WALL);
        putWall(43, 17, 3, 0, WALL);
        putWall(43, 19, 4, 0, WALL);
        putWall(43, 20, 4, 0, WALL);

        putWall(48, 22, 4, 0, WALL);
        putWall(41, 23, 8, 0, WALL);

        putWall(38, 8, 4, 0, WALL);
        putWall(55, 8, 0, 2, WALL);
        putWall(47, 1, 11, 0, WALL);
        putWall(57, 1, 0, 23, WALL);
        putWall(49, 23, 8, 0, WALL);
        putWall(49, 19, 0, 4, WALL);
        putWall(50, 19, 3, 0, WALL);
        putWall(55, 11, 0, 11, WALL);
        putWall(53, 21, 2, 0, WALL);
        putWall(53, 11, 0, 9, WALL);

        putWall(49, 9, 7, 0, WALL);

        putWall(55, 3, 0, 5, WALL);
        putWall(49, 8, 4, 0, WALL);
        putWall(43, 15, 0, 3, WALL);
        putWall(52, 3, 0, 5, WALL);
        putWall(52, 3, 4, 0, WALL);
        putWall(32, 20, 0, 1, WALL);
        putWall(38, 22, 4, 0, WALL);
        resetColor();
        redWell(36, 4, 0, 2, WALL);
        redWell(36, 4, 4, 0, WALL);
        redWell(39, 17, 3, 0, WALL);

        changeColor(78);
        gotoxy(16, 12);
        putchar(177);
        resetColor();
        // Gold D. Roger
        putGold(20, 20, 2, 0, WALL);
        putGold(20, 5, 0, 16, WALL);
        putGold(26, 4, 2, 0, WALL);
        putGold(26, 4, 0, 4, WALL);
        putGold(27, 7, 0, 16, WALL);
        putGold(25, 19, 0, 4, WALL);
        putGold(33, 18, 0, 5, WALL);
        putGold(34, 5, 0, 14, WALL);
        putGold(35, 3, 0, 3, WALL);
        putGold(36, 3, 4, 0, WALL);
        putGold(42, 8, 0, 15, WALL);
        putGold(39, 18, 0, 4, WALL);
        putGold(43, 22, 4, 0, WALL);
        putGold(43, 21, 4, 0, WALL);
        putGold(43, 18, 4, 0, WALL);
        putGold(39, 14, 8, 0, WALL);
        putGold(39, 9, 0, 6, WALL);
        putGold(39, 9, 6, 0, WALL);
        putGold(48, 2, 0, 2, WALL);
        putGold(48, 2, 8, 0, WALL);
        putGold(56, 2, 0, 20, WALL);
        putGold(52, 22, 5, 0, WALL);
        putGold(52, 20, 0, 2, WALL);
        putGold(51, 20, 0, 2, WALL);
        putGold(50, 20, 0, 2, WALL);
        putGold(54, 10, 0, 11, WALL);

        putGold(16, 10, 29, 0, WALL);
        putGold(48, 10, 9, 0, WALL);

        putGold(17, 5, 3, 0, WALL);
        putGold(17, 4, 0, 2, WALL);
        putGold(48, 7, 0, 4, WALL);
        putGold(49, 4, 0, 4, WALL);
}

void level8(wall WALL[25][72])
{
        changeColor(161);
        putWall(30, 14, 12, 0, WALL);
        putWall(30, 10, 0, 4, WALL);
        putWall(35, 15, 2, 0, WALL);
        putWall(41, 10, 0, 4, WALL);
        putWall(34, 10, 7, 0, WALL);
        putWall(28, 8, 16, 0, WALL);
        putWall(27, 8, 0, 3, WALL);
        putWall(28, 10, 1, 0, WALL);
        putWall(28, 11, 0, 7, WALL);
        putWall(28, 17, 3, 0, WALL);
        putWall(30, 16, 4, 0, WALL);
        putWall(30, 17, 4, 0, WALL);

        putWall(35, 17, 10, 0, WALL);
        putWall(38, 16, 7, 0, WALL);
        putWall(44, 14, 0, 3, WALL);
        putWall(43, 8, 0, 7, WALL);
        //vong ngoai
        putWall(27, 14, 0, 4, WALL);
        putWall(25, 6, 0, 14, WALL);
        putWall(25, 19, 3, 0, WALL);
        putWall(27, 20, 5, 0, WALL);
        putWall(31, 19, 9, 0, WALL);
        putWall(41, 18, 1, 0, WALL);
        putWall(44, 8, 0, 3, WALL);
        putWall(46, 6, 0, 14, WALL);
        putWall(39, 20, 5, 0, WALL);
        putWall(43, 19, 4, 0, WALL);

        // vong 3
        putWall(35, 5, 12, 0, WALL);     // con sua
        putWall(38, 6, 8, 0, WALL);
        putWall(25, 6, 8, 0, WALL);
        putWall(33, 5, 0, 2, WALL);
        putWall(32, 3, 0, 3, WALL);
        putWall(43, 4, 1, 0, WALL);
        putWall(32, 3, 10, 0, WALL);
        putWall(41, 2, 6, 0, WALL);
        putWall(46, 3, 3, 0, WALL);
        putWall(47, 9, 1, 0, WALL);
        putWall(48, 3, 0, 5, WALL);
        putWall(49, 7, 0, 6, WALL);
        putWall(47, 18, 0, 2, WALL);
        putWall(48, 12, 0, 5, WALL);
        putWall(49, 16, 0, 6, WALL);
        putWall(45, 21, 5, 0, WALL);
        putWall(35, 22, 11, 0, WALL);
        putWall(34, 20, 3, 0, WALL);
        putWall(35, 20, 0, 2, WALL);
        resetColor();

        changeColor(78);
        gotoxy(36, 21);
        putchar(177);
        resetColor();

        // Gold D.Roger
        putGold(42, 10, 0, 5, WALL);
        putGold(34, 16, 4, 0, WALL);
        putGold(30, 15, 5, 0, WALL);
        putGold(26, 8, 0, 4, WALL);
        putGold(27, 11, 0, 3, WALL);
        putGold(27, 18, 2, 0, WALL);
        putGold(28, 19, 3, 0, WALL);
        putGold(40, 19, 3, 0, WALL);
        putGold(42, 18, 4, 0, WALL);
        putGold(45, 13, 0, 5, WALL);
        putGold(44, 11, 0, 3, WALL);
        putGold(34, 6, 4, 0, WALL);
        putGold(34, 5, 1, 0, WALL);
        putGold(42, 3, 4, 0, WALL);
        putGold(47, 5, 0, 4, WALL);
        putGold(48, 8, 0, 4, WALL);
        putGold(48, 17, 0, 4, WALL);
        putGold(44, 20, 4, 0, WALL);
        putGold(38, 21, 7, 0, WALL);

}

void level9(wall WALL[25][72])
{
        changeColor(13);
        putWall(30, 12, 9, 0, WALL);
        putWall(30, 13, 4, 0, WALL);
        putWall(35, 13, 4, 0, WALL);
        changeColor(13);
        putWell(28, 12, 0, 4, WALL);
        putWell(29, 15, 5, 0, WALL);
        putWell(35, 15, 5, 0, WALL);
        putWell(40, 12, 0, 4, WALL);
        putWell(28, 9, 0, 2, WALL);
        putWell(40, 9, 0, 2, WALL);
        putWell(29, 9, 5, 0, WALL);
        putWell(35, 9, 5, 0, WALL);
        changeColor(13);
        putWall(35, 8, 6, 0, WALL);
        putWall(35, 6, 6, 0, WALL);
        putWall(40, 1, 0, 5, WALL);
        putWall(38, 1, 2, 0, WALL);
        putWall(33, 2, 6, 0, WALL);
        putWall(33, 2, 0, 2, WALL);
        changeColor(13);

       putWall(25, 7, 9, 0, WALL);
       putWall(25, 7, 0, 4, WALL);
       putWall(27, 9, 0, 2, WALL);
        changeColor(13);
       putWall(27, 12, 0, 5, WALL);
       putWall(21, 16, 6, 0, WALL);
       putWall(21, 12, 0, 4, WALL);
       putWall(15, 12, 6, 0, WALL);
       putWall(15, 7, 0, 5, WALL);
       putWall(15, 7, 7, 0, WALL);
        changeColor(13);

       putWall(23, 5, 0, 6, WALL);
       putWall(20, 5, 4, 0, WALL);
       putWall(24, 10, 1, 0, WALL);
       putWall(15, 1, 0, 6, WALL);
       putWall(15, 1, 3, 0, WALL);
       putWall(17, 2, 6, 0, WALL);
       putWall(22, 3, 0, 2, WALL);
       putWall(17, 4, 0, 2, WALL);
        changeColor(13);
        putWall(26, 3, 8, 0, WALL);
        putWall(25, 5, 0, 2, WALL);
        putWall(26, 3, 0, 3, WALL);
        putWall(33, 6, 1, 0, WALL);
        putWall(35, 4, 4, 0, WALL);
        putWall(28, 5, 4, 0, WALL);
        changeColor(13);
        putWall(41, 8, 0, 3, WALL);
        putWall(41, 12, 0, 5, WALL);
        putWall(41, 16, 7, 0, WALL);
        changeColor(13);
        putWall(41, 6, 3, 0, WALL);
        putWall(43, 6, 0, 5, WALL);
        putWall(43, 10, 3, 0, WALL);
        putWall(47, 12, 0, 5, WALL);
        putWall(47, 12, 7, 0, WALL);
        putWall(53, 6, 0, 6, WALL);
        putWall(47, 6, 7, 0, WALL);
        putWall(47, 5, 0, 1, WALL);
        putWall(45, 3, 0, 7, WALL);
        putWall(45, 3, 3, 0, WALL);
        putWall(45, 1, 5, 0, WALL);
        putWall(45, 2, 1, 0, WALL);
        putWall(49, 1, 0, 2, WALL);
        putWall(49, 3, 5, 0, WALL);
        putWall(54, 4, 0, 3, WALL);
        putWall(53, 4, 1, 0, WALL);
        changeColor(13);
        putWall(32, 16, 2, 0, WALL);
        putWall(35, 16, 0, 3, WALL);
        putWall(34, 18, 1, 0, WALL);
        putWall(32, 17, 0, 4, WALL);
        putWall(34, 19, 6, 0, WALL);
        putWall(39, 19, 0, 3, WALL);
        putWall(38, 21, 6, 0, WALL);
        putWall(43, 22, 0, 2, WALL);
        putWall(31, 20, 0, 3, WALL);
        putWall(32, 22, 2, 0, WALL);
        putWall(32, 23, 11, 0, WALL);
        resetColor();

        changeColor(78);
        gotoxy(34, 13);
        putchar(177);
        resetColor();
        changeColor(126);
        gotoxy(46, 2);
        putchar(176);

        gotoxy(42, 22);
        putchar(176);
        resetColor();
        // Gold D.Roger
        putGold(34, 3, 0, 7, WALL);
        putGold(35, 3, 4, 0, WALL);
        putGold(32, 5, 7, 0, WALL);
        putGold(27, 4, 7, 0, WALL);
        putGold(27, 4, 0, 2, WALL);
        putGold(35, 7, 7, 0, WALL);
        putGold(42, 7, 0, 9, WALL);
        putGold(26, 8, 8, 0, WALL);
        putGold(26, 8, 0, 8, WALL);
        putGold(16, 11, 13, 0, WALL);
        putGold(22, 6, 0, 10, WALL);
        putGold(16, 8, 0, 4, WALL);
        putGold(17, 3, 5, 0, WALL);
        putGold(19, 4, 3, 0, WALL);
        putGold(19, 4, 0, 3, WALL);
        putGold(19, 6, 3, 0, WALL);
        putGold(46, 4, 0, 12, WALL);
        putGold(47, 4, 6, 0, WALL);
        putGold(48, 2, 0, 2, WALL);
        putGold(34, 22, 7, 0, WALL);
        putGold(34, 16, 0, 2, WALL);
        putGold(33, 17, 0, 3, WALL);

}

void level10(wall WALL[25][72])
{
        changeColor(10);
        //chu f
        putWall(28, 2, 0, 3, WALL);
        putWall(14, 2, 15, 0, WALL);
        putWall(14, 2, 0, 13, WALL);
        putWall(20, 5, 9, 0, WALL);
        putWall(21, 8, 6, 0, WALL);
        putWall(21, 8, 0, 6, WALL);
        putWall(14, 15, 42, 0, WALL);
        putWall(29, 4, 27, 0, WALL);
        putWall(56, 4, 0, 12, WALL);
        putWall(21, 14, 1, 0, WALL);
        putWall(22, 13, 20, 0, WALL);    // net duoi

        // chu c
        putWall(29, 7, 0, 5, WALL);
        putWall(29, 7, 8, 0, WALL);
        putWall(36, 8, 0, 4, WALL);

        // chu d
        putWall(37, 8, 5, 0, WALL);
        putWall(42, 8, 0, 2, WALL);
        putWall(43, 9, 0, 2, WALL);
        putWall(42, 12, 0, 2, WALL);
        putWall(43, 11, 0, 2, WALL);

        // chu e
        putWall(44, 7, 0, 7, WALL);
        putWall(44, 7, 7, 0, WALL);
        putWall(44, 10, 5, 0, WALL);
        putWall(44, 13, 7, 0, WALL);

        // chu m
        putWall(13, 17, 0, 7, WALL);
        putWall(13, 17, 7, 0, WALL);
        putWall(19, 17, 0, 2, WALL);
        putWall(20, 18, 0, 2, WALL);
        putWall(21, 19, 0, 2, WALL);
        putWall(22, 18, 0, 2, WALL);
        putWall(23, 17, 0, 2, WALL);
        putWall(23, 17, 7, 0, WALL);
        putWall(29, 17, 0, 7, WALL);
        putWall(13, 23, 16, 0, WALL);

        // chu d
        putWall(33, 17, 0, 7, WALL);
        putWall(33, 17, 9, 0, WALL);
        putWall(33, 23, 9, 0, WALL);
        putWall(42, 17, 0, 2, WALL);
        putWall(43, 18, 0, 2, WALL);
        putWall(44, 19, 0, 3, WALL);
        putWall(42, 22, 0, 2, WALL);
        putWall(43, 21, 0, 2, WALL);
        putWall(32, 19, 3, 0, WALL);

        // chu l
        putWall(48, 17, 0, 7, WALL);
        putWall(49, 23, 10, 0, WALL);
        putWall(52, 21, 7, 0, WALL);
        putWall(48, 17, 4,0, WALL);
        putWall(52, 17, 0, 4, WALL);
        putWall(58, 22, 1, 0, WALL);

        //bien ngoai
        putWall(57, 7, 0, 4, WALL);
        putWall(57, 13, 0, 3, WALL);

        resetColor();

        putWell(16, 15, 39, 0, WALL);
        putWell(29, 4, 26, 0, WALL);
        putWell(16, 15, 39, 0, WALL);

        changeColor(126);
        gotoxy(22, 14);
        putchar(176);
        gotoxy(22, 12);
        putchar(176);

        gotoxy(37, 9);
        putchar(176);

        gotoxy(14, 22);
        putchar(176);

        gotoxy(14, 18);
        putchar(176);

        gotoxy(28, 18);
        putchar(176);

        gotoxy(43, 20);
        putchar(176);

        gotoxy(34, 22);
        putchar(176);

        gotoxy(50, 18);
        putchar(176);
        resetColor();

        // por tal
        changeColor(78);
        gotoxy(57, 22);
        putchar(177);
        resetColor();

        redWell(14, 4, 0, 11, WALL);
}

void putWell(int toadoX, int toadoY, int soluongNgang, int soluongDoc, wall WALL[25][72])               // Well trap
{
        changeColor(26);
        for (int i = 0; i < soluongNgang; i++)
        {
                gotoxy(toadoX + i, toadoY);
                WALL[toadoY][toadoX + i].shape = '#';
                putchar(222);
        }
        for (int i = 0; i < soluongDoc; i++)
        {
                gotoxy(toadoX, toadoY + i);
                WALL[toadoY + i][toadoX].shape = '#';
                putchar(223);
        }
        resetColor();
        return;
}
void putWall(int toadoX, int toadoY, int soluongNgang, int soluongDoc, wall WALL[25][72])       // vi tri x,y dat n 'tuong'
{
        for (int i = 0; i < soluongNgang; i++)
        {
                gotoxy(toadoX + i, toadoY);
                WALL[toadoY][toadoX + i].shape = '*';
                putchar(219);
        }
        for (int i = 0; i < soluongDoc; i++)
        {
                gotoxy(toadoX, toadoY + i);
                WALL[toadoY + i][toadoX].shape = '*';
                putchar(219);
        }
        return;
}
void putGold(int toadoX, int toadoY, int soluongNgang, int soluongDoc, wall WALL[25][72])
{
        changeColor(270);
        for (int i = 0; i < soluongNgang; i++)
        {
                gotoxy(toadoX + i, toadoY);
                WALL[toadoY][toadoX + i].shape = '$';
                putchar(248);
        }
        for (int i = 0; i < soluongDoc; i++)
        {
                gotoxy(toadoX, toadoY + i);
                WALL[toadoY + i][toadoX].shape = '$';
                putchar(248);
        }
        resetColor();
        return;
}
void redWell(int toadoX, int toadoY, int soluongNgang, int soluongDoc, wall WALL[25][72])               // Well trap
{
        changeColor(25);
        for (int i = 0; i < soluongNgang; i++)
        {
                gotoxy(toadoX + i, toadoY);
                WALL[toadoY][toadoX + i].shape = '*';
                putchar(222);
        }
        for (int i = 0; i < soluongDoc; i++)
        {
                gotoxy(toadoX, toadoY + i);
                WALL[toadoY + i][toadoX].shape = '*';
                putchar(222);
        }
        resetColor();
        return;
}

void ghostHorizontal (int *x, int *y, int leftBorder, int rigthBorder, stat *ghost, wall WALL[25][72], int *delay){                     // ma
    // x và y là vị trí con ma sẽ xuất hiện
    // leftBoder: vị trí biên trái; rightBorder: vị trí biên phải
        if (*delay == 0)
        {
                gotoxy(*x, *y);
                printf("%c", 157);
                WALL[*y][*x].shape = '#';
        }
        *delay += 1;
        if (*delay == 300)
        {
                //Sleep(50);
                gotoxy(*x, *y);
                printf(" ");
                WALL[*y][*x].shape = '\0';
                *delay = -300;
                if (*x == leftBorder + 1)
                        *ghost = RIGHT;
                else if (*x == rigthBorder - 1)
                        *ghost = LEFT;
                if (*ghost == RIGHT)
                {
                        *x += 1;
                }
                else if (*ghost == LEFT)
                {
                        *x -= 1;
                }
        }


}

void ghostVertical (int *x, int *y, int upBorder, int downBorder, stat *ghost, wall WALL[25][72], int *delay)
{
        if (*delay == 0)
        {
                gotoxy(*x, *y);
                printf("%c", 157);
                WALL[*y][*x].shape = '#';
        }
        *delay += 1;
        if (*delay == 300)
        {
                gotoxy(*x, *y);
                printf(" ");
                WALL[*y][*x].shape = '\0';
                *delay = -300;
                if (*y == upBorder)
                        *ghost = DOWN;
                else if (*y == downBorder )
                        *ghost = UP;
                if (*ghost == UP)
                        *y -= 1;
                else if (*ghost == DOWN)
                        *y += 1;
        }

}

void arrowTrap1(int trap1X, int trap1Y, int *dan1X, int *dan1Y, int *direction1, wall WALL[25][72])         // tao toado dan.
{
        //gotoxy(trap1X, trap1Y);
        //printf("%c", 219);
        WALL[13][30].shape = '*';
         // 1 up - 2 down - 3 left - 4 right
        if ((*direction1 == 1 || *direction1 == 2) && (*dan1Y > 22 || *dan1Y < 2))
        {
                Beep(92.49860567790861, 150);
                *direction1 = rand() % 4 + 1;
                *dan1X = trap1X;
                *dan1Y = trap1Y;
                WALL[22][30].shape = '\0';
                WALL[2][30].shape = '\0';
                WALL[13][55].shape = '\0';
                WALL[13][5].shape = '\0';
        }
        else if ((*direction1 == 3 || *direction1 == 4) && (*dan1X < 3 || *dan1X > 57))
        {
                Beep(92.49860567790861, 150);
                *direction1 = rand() % 4 + 1;
                *dan1X = trap1X;
                *dan1Y = trap1Y;
                WALL[22][30].shape = '\0';
                WALL[2][30].shape = '\0';
                WALL[13][55].shape = '\0';
                WALL[13][5].shape = '\0';
        }
        else
        {
                if (*direction1 == 1)             // up
                {
                        if (*dan1Y == trap1Y)
                                *dan1Y -= 1;
                        else
                        {
                                gotoxy(*dan1X, *dan1Y);
                                printf("%c", 254);
                                WALL[*dan1Y][*dan1X].shape = '#';
                                Sleep(50);
                                gotoxy(*dan1X, *dan1Y);
                                printf(" ");
                                WALL[*dan1Y + 1][*dan1X].shape = '\0';
                                *dan1Y -= 1;

                        }
                }
                else if (*direction1 == 2)        // down
                {
                        if (*dan1Y == trap1Y)
                                *dan1Y += 1;
                        else
                        {
                                gotoxy(*dan1X, *dan1Y);
                                printf("%c", 254);
                                WALL[*dan1Y][*dan1X].shape = '#';
                                Sleep(50);
                                gotoxy(*dan1X, *dan1Y);
                                printf(" ");
                                WALL[*dan1Y -1][*dan1X].shape = '\0';
                                *dan1Y += 1;
                        }
                }
                else if (*direction1 == 3)        // left
                {
                        if (*dan1X == trap1X)
                                *dan1X -= 1;
                        else
                        {
                                gotoxy(*dan1X, *dan1Y);
                                printf("%c", 254);
                                WALL[*dan1Y][*dan1X].shape = '#';
                                Sleep(50);
                                gotoxy(*dan1X, *dan1Y);
                                printf(" ");
                                WALL[*dan1Y][*dan1X + 3].shape = '\0';
                                *dan1X -= 3;

                        }

                }
                else if (*direction1 == 4)        // right
                {
                        if (*dan1X == trap1X)
                                *dan1X += 1;
                        else
                        {
                                gotoxy(*dan1X, *dan1Y);
                                printf("%c", 254);
                                WALL[*dan1Y][*dan1X].shape = '#';
                                Sleep(50);
                                gotoxy(*dan1X, *dan1Y);
                                printf(" ");
                                WALL[*dan1Y][*dan1X - 3].shape = '\0';
                                *dan1X += 3;
                        }
                }
        }
        changeColor(13);
        putWall(30, 13, 1, 0, WALL);
        resetColor();
}

void arrowTrap2(int trap2X, int trap2Y, int *dan2X, int *dan2Y, int *direction2, wall WALL[25][72])         // tao toado dan.
{
        //gotoxy(trap2X, trap2Y);
        //printf("%c", 219);
        WALL[13][30].shape = '*';
         // 1 up - 2 down - 3 left - 4 right
        if ((*direction2 == 1 || *direction2 == 2) && (*dan2Y > 22 || *dan2Y < 2))
        {
                Beep(92.49860567790861, 150);
                *direction2 = rand() % 4 + 1;
                *dan2X = trap2X;
                *dan2Y = trap2Y;
                WALL[22][30].shape = '\0';
                WALL[2][30].shape = '\0';
                WALL[13][55].shape = '\0';
                WALL[13][5].shape = '\0';
        }
        else if ((*direction2 == 3 || *direction2 == 4) && (*dan2X < 3 || *dan2X > 57))
        {
                Beep(92.49860567790861, 150);
                *direction2 = rand() % 4 + 1;
                *dan2X = trap2X;
                *dan2Y = trap2Y;
                WALL[22][30].shape = '\0';
                WALL[2][30].shape = '\0';
                WALL[13][55].shape = '\0';
                WALL[13][5].shape = '\0';
        }
        else
        {
                if (*direction2 == 1)             // up
                {
                        if (*dan2Y == trap2Y)
                                *dan2Y -= 1;
                        else
                        {
                                gotoxy(*dan2X, *dan2Y);
                                printf("%c", 254);
                                WALL[*dan2Y][*dan2X].shape = '#';
                                Sleep(50);
                                gotoxy(*dan2X, *dan2Y);
                                printf(" ");
                                WALL[*dan2Y + 1][*dan2X].shape = '\0';
                                *dan2Y -= 1;

                        }
                }
                else if (*direction2 == 2)        // down
                {
                        if (*dan2Y == trap2Y)
                                *dan2Y += 1;
                        else
                        {
                                gotoxy(*dan2X, *dan2Y);
                                printf("%c", 254);
                                WALL[*dan2Y][*dan2X].shape = '#';
                                Sleep(50);
                                gotoxy(*dan2X, *dan2Y);
                                printf(" ");
                                WALL[*dan2Y - 1][*dan2X].shape = '\0';
                                *dan2Y += 1;
                        }
                }
                else if (*direction2 == 3)        // left
                {
                        if (*dan2X == trap2X)
                                *dan2X -= 1;
                        else
                        {
                                gotoxy(*dan2X, *dan2Y);
                                printf("%c", 254);
                                WALL[*dan2Y][*dan2X].shape = '#';
                                Sleep(50);
                                gotoxy(*dan2X, *dan2Y);
                                printf(" ");
                                WALL[*dan2Y][*dan2X + 3].shape = '\0';
                                *dan2X -= 3;

                        }

                }
                else if (*direction2 == 4)        // right
                {
                        if (*dan2X == trap2X)
                                *dan2X += 1;
                        else
                        {
                                gotoxy(*dan2X, *dan2Y);
                                printf("%c", 254);
                                WALL[*dan2Y][*dan2X].shape = '#';
                                Sleep(50);
                                gotoxy(*dan2X, *dan2Y);
                                printf(" ");
                                WALL[*dan2Y][*dan2X - 3].shape = '\0';
                                *dan2X += 3;
                        }
                }
        }
        changeColor(13);
        putWall(30, 13, 1, 0, WALL);
        resetColor();
}

                                                                // ANIMATON
void verticalAnimationDown(int toadoX, int fromY, int toY, movement steps[25][72], int *skin)
{

        changeColor(*skin + 2);
        for (int i = fromY; i <= toY - 1; i++)
        {
                for (int j = 0; j <= 100000; j++);

        gotoxy(toadoX, i);
        steps[i][toadoX].step = '>';
        printf("*");
        }

        steps[toY][toadoX].step = '>';
//        Sleep(50);
        Beep(150, 150);
        resetColor();
        gotoxy(toadoX, fromY);
        for (int i = fromY; i <= toY - 1; i++)
        {
                for (int j = 0; j <= 1000000; j++);

        gotoxy(toadoX, i);
        printf(" ");
        }
//        PlaySound(TEXT("move.wav"), NULL, SND_SYNC);
}

void verticalAnimationUp(int toadoX, int fromY, int toY, movement steps[25][72], int *skin)
{
        changeColor(*skin + 2);
        for (int i = fromY; i >= toY + 1; i--)
        {
                for (int j = 0; j <= 100000; j++);

        gotoxy(toadoX, i);
        steps[i][toadoX].step = '>';
        printf("^");
        }

        steps[toY][toadoX].step = '>';
//        Sleep(50);
        Beep(150, 150);
        resetColor();
        gotoxy(toadoX, fromY);
       for (int i = fromY; i >= toY + 1; i--)
        {
                for (int j = 0; j <= 1000000; j++);

        gotoxy(toadoX, i);
        printf(" ");
        }
//        PlaySound(TEXT("move.wav"), NULL, SND_SYNC);
}

void horizontallAnimationRight(int fromX, int toX, int toadoY, movement steps[25][72], int *skin)
{
        changeColor(*skin + 2);
        for (int i = fromX; i <= toX - 1; i++)
        {
                for (int j = 0; j <= 100000; j++);

        gotoxy(i, toadoY);
        steps[toadoY][i].step = '>';
        printf("%c", 175);
        }
        steps[toadoY][toX].step = '>';
//        Sleep(50);
        Beep(150, 150);
        resetColor();
        for (int i = fromX; i <= toX - 1; i++)
        {
                for (int j = 0; j <= 100000; j++);

        gotoxy(i, toadoY);
        printf(" ");
        }
//        PlaySound(TEXT("move.wav"), NULL, SND_SYNC);
}
void horizontallAnimationLeft(int fromX, int toX, int toadoY, movement steps[25][72], int *skin)
{
        changeColor(*skin + 2);
        for (int i = fromX; i >= toX + 1; i--)
        {
                for (int j = 0; j <= 100000; j++);

        gotoxy(i, toadoY);
        steps[toadoY][i].step = '>';
        printf("%c", 174);
        }
        steps[toadoY][toX].step = '>';
//        Sleep(50);
        Beep(150, 150);
        resetColor();
        for (int i = fromX; i >= toX + 1; i--)
        {
                for (int j = 0; j <= 100000; j++);

        gotoxy(i, toadoY);
        printf(" ");
        }
//        PlaySound(TEXT("move.wav"), NULL, SND_SYNC);
}

                        // trap map 3
void horizontalSpikeTrap(int fromX, int toX, int toadoY, int *delayAppear, int *delayDisappear, int *turn, wall WALL[25][72])
{
        if (*delayAppear == 10000 && *delayDisappear == 10000)
        {
                *delayAppear = fromX - 700;
                *delayDisappear = fromX - 2000;
        }
        if (*delayAppear < fromX)
                *delayAppear += 1;
        else
        {
                if (*delayAppear == fromX)
                {
                        Beep(130.8127826502993, 700);
                }
                if (*delayAppear <= toX)
                {
                        gotoxy(*delayAppear, toadoY);
                        printf("'");                                    // thang la dau -, ngang la dau '
                        if (*delayAppear > 0)
                                WALL[toadoY][*delayAppear].shape = '#';
                        Sleep(5);
                        *delayAppear += 1;
                }
        }
        if (*delayDisappear < fromX)
                *delayDisappear += 1;
        else
        {
                if (*delayDisappear <= toX)
                {
                        gotoxy(*delayDisappear, toadoY);
                        if (*delayDisappear > 0)
                                WALL[toadoY][*delayDisappear].shape = '\0';
                        printf(" ");
                        Sleep(5);
                        *delayDisappear += 1;
                }
                else
                {
                        *turn = 0;
                        *delayAppear = fromX - 700;
                        *delayDisappear = fromX - 2000;
                }
        }
}


void verticalSpikeTrap(int fromY, int toY, int toadoX, int *delayAppear, int *delayDisappear, int *turn, wall WALL[25][72])
{
        if (*delayAppear == 10000 && *delayDisappear == 10000)
        {
                *delayAppear = fromY - 700;
                *delayDisappear = fromY - 2000;
        }
        if (*delayAppear < fromY)
                *delayAppear += 1;
        else
        {
                if (*delayAppear == fromY)
                {
                        Beep(130.8127826502993, 700);
                }
                if (*delayAppear <= toY)
                {
                        gotoxy(toadoX, *delayAppear);
                        printf("-");                                    // thang la dau -, ngang la dau '
                        if (*delayAppear > 0)
                                WALL[*delayAppear][toadoX].shape = '#';
                        Sleep(5);
                        *delayAppear += 1;
                }
        }
        if (*delayDisappear < fromY)
                *delayDisappear += 1;
        else
        {
                if (*delayDisappear <= toY)
                {
                        gotoxy(toadoX, *delayDisappear);
                        if (*delayDisappear > 0)
                                WALL[*delayDisappear][toadoX].shape = '\0';
                        printf(" ");
                        Sleep(5);
                        *delayDisappear += 1;
                }
                else
                {
                        *turn = 0;
                        *delayAppear = fromY - 700;
                        *delayDisappear = fromY - 2000;
                }
        }
}


//
// arrowTrapInnovation
void arrowTrapInovableVersionUP(int trapX, int trapY, int *danFromY, int dantoY, wall WALL[25][72], int *delay)         // tao toado dan.
{
        if (*delay == 2000)
        {
                *delay = -60;
        }
        changeColor(4);
        gotoxy(trapX, trapY);
        printf("%c", 219);
        resetColor();
        changeColor(8);
        // y tang

        if (*delay == 0)
        {
                gotoxy(trapX, *danFromY);
                WALL[*danFromY][trapX].shape = '#';
                putchar(254);
        }
        else if (*delay == 60)
        {
                gotoxy(trapX, *danFromY);
                WALL[*danFromY][trapX].shape = '\0';
                putchar(' ');
                if (*danFromY > dantoY)
                {
                        *danFromY -= 1;
                        *delay = 1999;
                }
                else
                {
//                        Beep(92.49860567790861, 150);
                        *danFromY = trapY - 1;
                        *delay = -601;
                }
        }
        resetColor();
        *delay += 1;
        WALL[trapY][trapX].shape = '*';
}
void arrowTrapInovableVersionDOWN(int trapX, int trapY, int *danFromY, int dantoY, wall WALL[25][72], int *delay)
{
        if (*delay == 2000)
        {
                *delay = -60;
        }
        changeColor(4);
        gotoxy(trapX, trapY);
        printf("%c", 219);
        resetColor();
        changeColor(8);
        // y tang

        if (*delay == 0)
        {
                gotoxy(trapX, *danFromY);
                WALL[*danFromY][trapX].shape = '#';
                putchar(254);
        }
        else if (*delay == 60)
        {
                gotoxy(trapX, *danFromY);
                WALL[*danFromY][trapX].shape = '\0';
                putchar(' ');
                if (*danFromY < dantoY)
                {
                        *danFromY += 1;
                        *delay = 1999;
                }
                else
                {
//                        Beep(92.49860567790861, 150);
                        *danFromY = trapY + 1;
                        *delay = -601;
                }
        }
        resetColor();
        *delay += 1;
        WALL[trapY][trapX].shape = '*';
}
void arrowTrapInovableVersionLEFT(int trapX, int trapY, int *danFromX,int dantoX, wall WALL[25][72], int *delay)
{
        if (*delay == 2000)
        {
                *delay = -60;
        }
        changeColor(4);
        gotoxy(trapX, trapY);
        printf("%c", 219);
        resetColor();
        changeColor(8);
        // X GIAM

        if (*delay == 0)
        {
                gotoxy(*danFromX, trapY);
                WALL[trapY][*danFromX].shape = '#';
                putchar(254);
        }
        else if (*delay == 60)
        {
                gotoxy(*danFromX, trapY);
                WALL[trapY][*danFromX].shape = '\0';
                putchar(' ');
                if (*danFromX > dantoX)
                {
                        *danFromX -= 1;
                        *delay = 1999;
                }
                else
                {
//                        Beep(92.49860567790861, 150);
                        *danFromX = trapX - 1;
                        *delay = -601;
        }
}
        resetColor();
        *delay += 1;
        WALL[trapY][trapX].shape = '*';
}
void arrowTrapInovableVersionRIGHT(int trapX, int trapY, int *danFromX,int dantoX, wall WALL[25][72], int *delay)
{
        if (*delay == 2000)
        {
                *delay = -60;
        }
        changeColor(4);
        gotoxy(trapX, trapY);
        printf("%c", 219);
        resetColor();

        changeColor(8);
        // x tang

        if (*delay == 0)
        {
                gotoxy(*danFromX, trapY);
                WALL[trapY][*danFromX].shape = '#';
                putchar(254);
        }
        else if (*delay == 60)
        {
                gotoxy(*danFromX, trapY);
                WALL[trapY][*danFromX].shape = '\0';
                putchar(' ');
                if (*danFromX < dantoX)
                {
                        *danFromX += 1;
                        *delay = 1999;
                }
                else
                {
//                        Beep(92.49860567790861, 150);
                        *danFromX = trapX + 1;
                        *delay = -601;
                }
        }
        resetColor();
        *delay += 1;
        WALL[trapY][trapX].shape = '*';
}

void recordProfile(char id[], char passW[], int *gold, int *totalGOLD, int *LEVEL, int bought[])
{
        char chuoiRac[25];
        char rac;
        char profileName[25];
        sprintf(profileName, "%s.dm", id);
        FILE *profile = fopen(profileName, "w+");
        fprintf(profile, "%s\n", passW);
        fprintf(profile, "%d/%d\n", *gold, *totalGOLD);
        fprintf(profile, "%d\n", *LEVEL);
        for (int i = 0; i < 10; i++)
        {
                fprintf(profile, "%d ", bought[i]);
        }
        fclose(profile);
        FILE *PROFILE = fopen(profileName, "r");
        fscanf(PROFILE, "%s%c%d%c%d%c%d%c%d%c%d%c%d%c%d%c%d%c%d%c%d%c%d%c%d%c%d%c", chuoiRac, &rac, gold, &rac, totalGOLD, &rac, LEVEL, &rac, &bought[0], &rac, &bought[1], &rac, &bought[2], &rac, &bought[3], &rac, &bought[4], &rac, &bought[5], &rac, &bought[6], &rac, &bought[7], &rac, &bought[8], &rac, &bought[9], &rac);
        fclose(PROFILE);
}
int checkID_checkPass (char userID[], char userPass[]){
        char chuoiTestTK[20], userProfile[25], chuoiTestMK[20];
        int test;
        FILE *acc = fopen("tk_mk.dm", "r");
        int loopTestTK = 1;
        loopLogin = 1;

        sprintf(userProfile, "%s.dm", userID);

        if (strlen(userID) == 0 || strlen(userPass) == 0)
        {
                gotoxy(36, 20);
                printf("No success\n");
                fclose(acc);
                return 0;
        }
        if(acc != NULL)
        {
                while (loopTestTK)
                {
                        if (fgets(chuoiTestTK, 20, acc) != NULL)
                        {
                                test = 1;
                                for (int i = 0; i < strlen(userID); i++)
                                {
                                        if (userID[i] != chuoiTestTK[i])
                                        {
                                                test = 0;
                                                break;
                                        }
                                }
                                if(test == 1)
                                {
                                        loopTestTK = 0;
                                        FILE *checkMK = fopen(userProfile, "r");
                                        fscanf(checkMK, "%s", chuoiTestMK);
                                        fclose(checkMK);
                                        for (int i = 0; i < strlen(userPass); i++)
                                        {
                                                if (userPass[i] != chuoiTestMK[i])
                                                {
                                                        test = 0;
                                                        break;
                                                }
                                        }
                                        if (test == 1)
                                        {
                                                gotoxy(36, 20);
                                                printf("Success\n");
                                                loopLogin = 0;
                                                fclose(acc);
                                                return 1;
                                        }
                                        else if (test == 0)
                                        {
                                                gotoxy(36, 20);
                                                printf("No success\n");
                                                fclose(acc);
                                                return 0;
                                        }
                                }
                        }
                        else
                        {
                                loopTestTK = 0;
                                gotoxy(36, 20);
                                printf("No success\n");
                                fclose(acc);
                                return 0;
                        }
                }
        }
}


void signUp (char userID[], char userPass[]){
    FILE *acc = fopen("tk_mk.dm", "a");

    fprintf(acc, "%s\n", userID);

    creatingAcc(userID, userPass);

    fclose(acc);
}
void creatingAcc(char userID[], char userPass[]){
    FILE *user;
    char userFile[25];

    sprintf(userFile, "%s.dm", userID);

    user = fopen(userFile, "w");

    fprintf(user, "%s\n", userPass);
    fprintf(user, "0/0\n");       //gold  & total Gold
    fprintf(user, "1\n" );
    fprintf(user, "1 1 1 0 0 0 0 0 0 1 \n" );

    fclose(user);
}
int checkIDExisted (char userID[], char userPass[]){
        char chuoiTestTK[20], userProfile[25];
        int test;
        FILE *acc = fopen("tk_mk.dm", "r");
        int loopTestTK = 1;
        loopLogin = 1;

        sprintf(userProfile, "%s.dm", userID);

        if (strlen(userID) == 0 || strlen(userPass) == 0)
        {
                gotoxy(30, 20);
                printf("Invalid Username or Passwork\n");
                fclose(acc);
                return 0;
        }
        else if (strlen(userID) > 16 || strlen(userPass) > 16)
        {
                gotoxy(30, 20);
                printf("Invalid Username or Passwork\n");
                fclose(acc);
                return 0;
        }
        test = 0;
        if(acc != NULL)
        {
                while (loopTestTK)
                {
                        if (fgets(chuoiTestTK, 20, acc) != NULL)        // dau vong lap test = 1; neu id thu nhap vao khac voi dong 1 thi test = 0; break
                        {
                                test = 1;
                                for (int i = 0; i < strlen(userID); i++)
                                {
                                        if (userID[i] != chuoiTestTK[i])
                                        {
                                                test = 0;
                                                break;
                                        }
                                }
                                if (test == 1)
                                {
                                        gotoxy(30, 20);
                                        printf("This account has already existed!\n");
                                        fclose(acc);
                                        return 0;
                                }
                        }
                        else
                        {
                                loopTestTK = 0;
                        }
                }
                if (test == 0)
                {
                        gotoxy(36, 20);
                        printf("Success\n");
                        loopLogin = 0;
                        fclose(acc);
                        return 1;
                }
        }
}
void topGold(score top[])
{
        char middeStr[20];
        int middle;
        for (int i = 0; i < 9; i++)
        {
                for (int j = 0; j < i; j++)
                {
                        if (top[j].n < top[i].n)
                        {
                                middle = top[j].n;
                                top[j].n = top[i].n;
                                top[i].n = middle;
                                for (int m = 0; m <= 20; m++)
                                {
                                        middeStr[m] = top[j].str[m];
                                        top[j].str[m] = top[i].str[m];
                                        top[i].str[m] = top[j].str[m];

                                }
                        }
                }
        }
}
