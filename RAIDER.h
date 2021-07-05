#ifndef TOTM_H_INCLUDED
#define TOTM_H_INCLUDED

#include <windows.h>
#include <MMsystem.h>

#define consoleWidth 85
#define consoleHeight 25

typedef struct toado toado;
typedef enum stat stat;
typedef struct nhanvat nhanvat; // nhân vật
typedef struct hinhdang hinhdang; // hình dáng
typedef struct wall wall;
typedef enum menuGame menuGame;
typedef struct movement movement;
typedef struct spike spike;
typedef struct  score score;

struct toado
{
        char letter;
        int y, x;
};

/*
struct hinhdang {
    char a[2][2];
};*/


void hidecursor()
{
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = FALSE;
   SetConsoleCursorInfo(consoleHandle, &info);
}
void cursor()
{
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 1;
   info.bVisible =TRUE;
   SetConsoleCursorInfo(consoleHandle, &info);
}

void gotoxy(int x, int y)
{
        COORD coord;
        coord.X = x;
        coord.Y = y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void clrscr(void){


    system("cls");
}
void changeColor(int color){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void resetColor(){
    changeColor(15);
}

void printBoarder(){
    // xoá màn hình
    // các góc
    gotoxy(1,1); printf("%c", 201);
    gotoxy(80,1); printf("%c", 187);
    gotoxy(1,26); printf("%c", 200);
    gotoxy(80,26); printf("%c", 188);


    for (int i = 1 + 1; i < 80; i++){

        gotoxy(i,1); printf("%c", 205);
        gotoxy(i,26); printf("%c", 205);
    }

    for (int i = 1 + 1; i < 26; i++){

        gotoxy(1,i); printf("%c", 186);
        gotoxy(80,i); printf("%c", 186);
    }
}

void loadingBar(){


    int length = strlen("Loading...");
    int x = (consoleWidth - length) / 2;
    gotoxy(x, 13);
    printf("Loading...");
    gotoxy(x - 6, 14);
    for (int i = 1; i <= 10; i++){
        for (int j = 0; j <= 100000000; j++);

    printf("%c ", 254);
    }
    Sleep(2000);

    length = strlen("Press any key to continue");
    x = (consoleWidth - length) / 2;
    gotoxy(x, 15);
    printf("Press any key to continue");
        getch();

            PlaySound(TEXT("clicking.wav"), NULL, SND_SYNC);
    clrscr();
}

void printMenu(){
    int length = strlen("Play");
    int x = (consoleWidth - length) / 2;

    printBoarder();

    gotoxy(x, consoleHeight / 2 + 5);
    printf("Play\n");

    length = strlen("Setting");
    x = (consoleWidth - length) / 2;
    gotoxy(x, consoleHeight / 2 + 6);
    printf("Setting\n");

    length = strlen("High Score");
    x = (consoleWidth - length) / 2;
    gotoxy(x, consoleHeight / 2 + 7);
    printf("High Score\n");

    length = strlen("Exit");
    x = (consoleWidth - length) / 2;
    gotoxy(x, consoleHeight / 2 + 8);
    printf("Exit");
}

void printBoundary()
{
        resetColor();
        toado character;
        for (character.y = 0; character.y < consoleHeight; character.y++)
        {
                for (character.x = 0; character.x < consoleWidth; character.x++)
                        if (character.y == 0 || character.y == consoleHeight - 1)
                        {
                                if (character.x == 0 || character.x == consoleWidth - 1)
                                {
                                        gotoxy(character.x, character.y);
                                        putchar(206);
                                }
                                else
                                {
                                        gotoxy(character.x, character.y);
                                        putchar(205);
                                }
                        }
                        else
                        {
                                if (character.x == 0 || character.x == consoleWidth - 1)
                                {
                                        gotoxy(character.x, character.y);
                                        putchar(186);
                                }
                                else
                                {
                                        gotoxy(character.x, character.y);
                                        putchar(' ');
                                }
                        }
        }

}

void printBoundaryInGame(){

        toado character;
        for (character.y = 0; character.y < consoleHeight; character.y++)
        {
                for (character.x = 0; character.x < consoleWidth; character.x++)
                        if (character.y == 0 || character.y == consoleHeight - 1)
                        {
                                if (character.x == 0 || character.x == consoleWidth - 1)
                                {
                                        gotoxy(character.x, character.y);
                                        putchar(206);
                                }
                                else if (character.x == consoleWidth - 12)
                                {
                                        if (character.y == 0)
                                        {
                                                gotoxy(character.x, character.y);
                                                putchar(203);
                                        }
                                        else
                                        {
                                                gotoxy(character.x, character.y);
                                                putchar(202);
                                        }
                                }
                                else
                                {
                                        gotoxy(character.x, character.y);
                                        putchar(205);
                                }
                        }
                        else
                        {
                                if (character.x == 0 || character.x == consoleWidth - 1 || character.x == consoleWidth - 12)
                                {
                                        gotoxy(character.x, character.y);
                                        putchar(186);
                                }
                                else
                                {
                                        gotoxy(character.x, character.y);
                                        putchar(' ');
                                }
                        }
        }
        gotoxy(75, 7);
        printf("________");
        gotoxy(74, 8);
        printf("|");
        gotoxy(83, 8);
        printf("|");
        gotoxy(74, 9);
        printf("|________|");
        changeColor(14);
        gotoxy(77,6);
        printf("COIN");
        resetColor();
         changeColor(12);
        gotoxy(consoleWidth - 11, 11);
        printf("ESC = STOP");
        resetColor();

}

void printChooseResume (){
    gotoxy(36,13);
    changeColor(10);
    printf(" %c PLAY", 249);
    resetColor();
}


void printNotChooseResume (){
    gotoxy(36,13);
    puts("  PLAY ");
}

void printChoosePlay (){
        changeColor(10);
        gotoxy(31,15);
        printf(" %c Change Password", 249);
        resetColor();
}

void printNotChoosePlay (){
    gotoxy(31,15);
    puts("  Change Password ");
}

void printChooseRank (){
        changeColor(10);
        gotoxy(37,17);
        printf(" %c Rank", 249);
        resetColor();
}

void printNotChooseRank (){
        gotoxy(37,17);
        puts("  Rank ");
}

void printChooseQuit (){
        changeColor(14);
        gotoxy(35,21);
        printf(" %c Log out", 249);
        resetColor();
}

void printNotChooseQuit (){
    gotoxy(35,21);
    puts("  Log out ");
}

void printChooseInstruction(){
    changeColor(10);
    gotoxy(33,19);
    printf(" %c Instruction", 249);
    resetColor();
}

void printNotChooseInstruction (){
    gotoxy(33,19);
    puts("  Instruction ");
}

#endif // MAIN_H_INCLUDED

// choice
int chooseMenu(int *choice, int *loopMenu)
{
        char key;
        if (kbhit())
        {
                key = getch();
                if ((key == 'W' || key == 'w') && (*choice > 1 && *choice <= 5))
                {
                        *choice -= 1;
                        PlaySound(TEXT("option.wav"), NULL, SND_SYNC);
                }
                else if ((key == 'S' || key == 's') && (*choice >= 1 && *choice < 5))
                {
                        *choice += 1;
                        PlaySound(TEXT("option.wav"), NULL, SND_SYNC);
                }
                else if (key == 13)
                {
                        PlaySound(TEXT("clicking.wav"), NULL, SND_SYNC);

                        *loopMenu = 0;
                        clrscr();
                        return *choice;
                }
        }
        // choose resume



        if (*choice == 1 )
        {
                printChooseResume();
        }
        else
        {
                printNotChooseResume();
        }

        // choose PLAY
        if (*choice == 2)
        {
                printChoosePlay();
        }
        else
        {
                printNotChoosePlay();
        }

        // choose ranked
        if (*choice == 3)
        {
                printChooseRank();
        }
        else
        {
                printNotChooseRank();
        }

        // choose Instruction
        if (*choice == 4){

                printChooseInstruction();
        } else{
                printNotChooseInstruction();
        }

        // choose quit
        if (*choice == 5 )
        {
                printChooseQuit();
        }
        else
        {
                printNotChooseQuit();
        }
}


void printInstruct (){
    int length = strlen("*****Instruction*****");
    int x = (consoleWidth - length) / 2;
    int y =  consoleHeight - 22;

    char key;
    gotoxy(x, y);

    printf("*****Instruction*****\n");


    gotoxy(consoleWidth - 80, y + 3);

    printf("-> Press \"W\" for up, \"S\" for down, \"A\" for left and \"D\" for right.\n");
    gotoxy(consoleWidth - 80, y + 4);

    printf("-> Press \"ESC\" to pause.\n");

    gotoxy(consoleWidth - 80, y + 6);

    printf("Your main goal is to get the gold along the map and reach the end of the map.\n");
    gotoxy(consoleWidth - 80, y + 6);

    printf("If you get hit by an enemy you will lose and return to menu.\n");
    gotoxy(consoleWidth - 77, y + 8);


    printf(" Press \"ESC\" to return to menu...");


    do {
       key = getch();
    }while(key != 27);

}

// menu pause and win game
int menuPause (int *choice, int *loopMenu, int *coins){                                             // menu win, pau dùng chung lost
        int length = strlen("You win!");
        int x = (consoleWidth - length) / 2;
        int y = consoleHeight / 2;

        gotoxy(x,y);
        changeColor(10);
        puts("You win!");
        resetColor();
        changeColor(14);
        gotoxy(x - 1, y + 1);
        printf("+ %d coins", *coins);
        resetColor();

        char key;
        if (kbhit())
        {
                key = getch();
                if ((key == 'W' || key == 'w') && (*choice > 1 && *choice <= 3))
                {
                        *choice -= 1;
                        PlaySound(TEXT("option.wav"), NULL, SND_SYNC);
                }
                else if ((key == 'S' || key == 's') && (*choice >= 1 && *choice < 3))
                {
                        *choice += 1;
                        PlaySound(TEXT("option.wav"), NULL, SND_SYNC);
                }
                else if ((key == 'A' || key =='a') && (*choice == 3))
                {
                        *choice -= 1;
                        PlaySound(TEXT("option.wav"), NULL, SND_SYNC);
                }
                else if ((key == 'D' || key =='d') && (*choice == 2))
                {
                        *choice += 1;
                        PlaySound(TEXT("option.wav"), NULL, SND_SYNC);
                }
                else if (key == 13)
                {
                        PlaySound(TEXT("clicking.wav"), NULL, SND_SYNC);

                        *loopMenu = 0;
                        clrscr();
                        *coins = 0;
                        return *choice;
                }
        }


        if (*choice == 1){
                printChooseCont();
        } else {
                printNotChooseCont();
        }

        if (*choice == 2)
                printChooseRTM();
        else
                printNotChooseRTM();

        if (*choice == 3)
                printChoosePA();
        else
                printNotChoosePA();
}


// menu lost

int menuLost (int *choice, int *loopMenu, int *coins){
        int length = strlen("You lost!");
        int x = (consoleWidth - length) / 2;
        int y = consoleHeight / 2;

        gotoxy(x,y);
        changeColor(4);
        puts("You lost!");
        resetColor();
        changeColor(14);
        gotoxy(x - 1, y + 1);
        printf("+ %d coins", *coins);
        resetColor();
        char key;
        if (kbhit())
        {
                key = getch();
                if ((key == 'A' || key =='a') && (*choice == 2))
                {
                        *choice -= 1;
                        PlaySound(TEXT("option.wav"), NULL, SND_SYNC);
                }
                else if ((key == 'D' || key =='d') && (*choice == 1))
                {
                        *choice += 1;
                        PlaySound(TEXT("option.wav"), NULL, SND_SYNC);
                }
                else if (key == 13)
                {
                        PlaySound(TEXT("clicking.wav"), NULL, SND_SYNC);

                        *coins  = 0;
                        *loopMenu = 0;
                        clrscr();
                        return *choice;
                }
        }
        if (*choice == 1)
                printChooseRTM();
        else
                printNotChooseRTM();

        if (*choice == 2)
                printChoosePA();
        else
                printNotChoosePA();
}

void printChooseCont (){ // continue
    int length = strlen("> Continue <");
    int x = (consoleWidth - length) / 2;
    int y = consoleHeight / 2;
    gotoxy(x, y + 2);
    printf("%c Continue", 249);
}

void printNotChooseCont (){  // continue
    int length = strlen("  Continue  ");
    int x = (consoleWidth - length) / 2;
    int y = consoleHeight / 2;
    gotoxy(x, y + 2);
    puts("  Continue");
}

void printNotChooseRTM (){ // return to menu
    int length = strlen("  Menu  ");
    int x = (consoleWidth - length) / 2;
    int y = consoleHeight / 2;
    gotoxy(x - 9, y + 4);
    puts("  Menu");
}

void printChooseRTM (){ // return to menu
    int length = strlen("> Menu <");
    int x = (consoleWidth - length) / 2;
    int y = consoleHeight / 2;
    gotoxy(x - 9, y + 4);
    printf("%c Menu", 249);
}

void printChoosePA (){ // play again
    int length = strlen("> Play again <");
    int x = (consoleWidth - length) / 2;
    int y = consoleHeight / 2;
    gotoxy(x + 10, y + 4);
    printf("%c Play again", 249);
}

void printNotChoosePA (){ // not play again
    int length = strlen("  Play again  ");
    int x = (consoleWidth - length) / 2;
    int y = consoleHeight / 2;
    gotoxy(x + 10, y + 4);
    puts("  Play again");
}


void printName (){
        gotoxy(10,3);
        printf("	   (`-')  (`-')  _   _     _(`-')    (`-')  _   (`-')");
        gotoxy(10,4);
	printf("	<-.(OO )  (OO ).-/  (_)   ( (OO ).-> ( OO).-/<-.(OO )");
	gotoxy(10,5);
	printf("	,------,) / ,---.   ,-(`-')\\    .'_ (,------.,------,)");
	gotoxy(10,6);
	printf("	|   /`. ' | \\ /`.\\  | ( OO)'`'-..__) |  .---'|   /`. '");
	gotoxy(10,7);
	printf("	|  |_.' | '-'|_.' | |  |  )|  |  ' |(|  '--. |  |_.' |");
	gotoxy(10,8);
	printf("	|  .   .'(|  .-.  |(|  |_/ |  |  / : |  .--' |  .   .'");
	gotoxy(10, 9);
	printf("	|  |\\  \\  |  | |  | |  |'->|  '-'  / |  `---.|  |\\  \\ ");
	gotoxy(10, 10);
	printf("	`--' '--' `--' `--' `--'   `------'  `------'`--' '--'");

}

int menuBuyMap(int *choice, int *loopMenu, int cost, int man){
        gotoxy(23, 13);
        printf("Do you want to use %d to buy MAP%d ?", cost, man);
        char key;
        if (kbhit())
        {
                key = getch();
                if ((key == 'A' || key =='a') && (*choice == 2))
                {
                        *choice -= 1;
                        PlaySound(TEXT("option.wav"), NULL, SND_SYNC);
                }
                else if ((key == 'D' || key =='d') && (*choice == 1))
                {
                        *choice += 1;
                        PlaySound(TEXT("option.wav"), NULL, SND_SYNC);
                }
                else if (key == 13)
                {
                        PlaySound(TEXT("clicking.wav"), NULL, SND_SYNC);
                        *loopMenu = 0;
                        //clrscr();
                        return *choice;
                }
        }
        if (*choice == 1)
                printChooseNo();
        else
                printNotChooseNo();

        if (*choice == 2)
                printChooseYes();
        else
                printNotChooseYes();
}

/*
33. !
34. "
35. #
36. $
37. %
38. &
39. '
40. (
41. )
42. *
43. +
44. ,
45. -
46. .
47. /
48. 0
49. 1
50. 2
51. 3
52. 4
53. 5
54. 6
55. 7
56. 8
57. 9
58. :
59. ;
60. <
61. =
62. >
63. ?
64. @
65. A
66. B
67. C
68. D
69. E
70. F
71. G
72. H
73. I
74. J
75. K
76. L
77. M
78. N
79. O
80. P
81. Q
82. R
83. S
84. T
85. U
86. V
87. W
88. X
89. Y
90. Z
91. [
92. \
93. ]
94. ^
95. _
96. `
97. a
98. b
99. c
100. d
101. e
102. f
103. g
104. h
105. i
106. j
107. k
108. l
109. m
110. n
111. o
112. p
113. q
114. r
115. s
116. t
117. u
118. v
119. w
120. x
121. y
122. z
123. {
124. |
125. }
126. ~
127.
128. Ç
129. ü
130. é
131. â
132. ä
133. à
134. å
135. ç
136. ê
137. ë
138. è
139. ï
140. î
141. ì
142. Ä
143. Å
144. É
145. æ
146. Æ
147. ô
148. ö
149. ò
150. û
151. ù
152. ÿ
153. Ö
154. Ü
155. ¢
156. £
157. ¥
158. ₧
159. ƒ
160. á
161. í
162. ó
163. ú
164. ñ
165. Ñ
166. ª
167. º
168. ¿
169. ⌐
170. ¬
171. ½
172. ¼
173. ¡
174. «
175. »
176. ░
177. ▒
178. ▓
179. │
180. ┤
181. ╡
182. ╢
183. ╖
184. ╕
185. ╣
186. ║
187. ╗
188. ╝
189. ╜
190. ╛
191. ┐
192. └
193. ┴
194. ┬
195. ├
196. ─
197. ┼
198. ╞
199. ╟
200. ╚
201. ╔
202. ╩
203. ╦
204. ╠
205. ═
206. ╬
207. ╧
208. ╨
209. ╤
210. ╥
211. ╙
212. ╘
213. ╒
214. ╓
215. ╫
216. ╪
217. ┘
218. ┌
219. █
220. ▄
221. ▌
222. ▐
223. ▀
224. α
225. ß
226. Γ
227. π
228. Σ
229. σ
230. µ
231. τ
232. Φ
233. Θ
234. Ω
235. δ
236. ∞
237. φ
238. ε
239. ∩
240. ≡
241. ±
242. ≥
243. ≤
244. ⌠
245. ⌡
246. ÷
247. ≈
248. °
249. ∙
250. ·
251. √
252. ⁿ
253. ²
254. ■
255.
*/
int menuCrAccount (int *choice, int *loopMenu){
        gotoxy(27, 13);
        printf("Do you have an account yet?");
        char key;
        if (kbhit())
        {
                key = getch();
                if ((key == 'A' || key =='a') && (*choice == 2))
                {
                        *choice -= 1;
                        PlaySound(TEXT("option.wav"), NULL, SND_SYNC);
                }
                else if ((key == 'D' || key =='d') && (*choice == 1))
                {
                        *choice += 1;
                        PlaySound(TEXT("option.wav"), NULL, SND_SYNC);
                }
                else if (key == 13)
                {
                        PlaySound(TEXT("clicking.wav"), NULL, SND_SYNC);

                        *loopMenu = 0;
                        clrscr();
                        return *choice;
                }
        }
        if (*choice == 1)
                printChooseNo();
        else
                printNotChooseNo();

        if (*choice == 2)
                printChooseYes();
        else
                printNotChooseYes();
}
int menuChangePass (int *choice, int *loopMenu){
        gotoxy(27, 13);
        printf("Do you want to change Password?");
        char key;
        if (kbhit())
        {
                key = getch();
                if ((key == 'A' || key =='a') && (*choice == 2))
                {
                        *choice -= 1;
                        PlaySound(TEXT("option.wav"), NULL, SND_SYNC);
                }
                else if ((key == 'D' || key =='d') && (*choice == 1))
                {
                        *choice += 1;
                        PlaySound(TEXT("option.wav"), NULL, SND_SYNC);
                }
                else if (key == 13)
                {
                        PlaySound(TEXT("clicking.wav"), NULL, SND_SYNC);

                        *loopMenu = 0;
                        clrscr();
                        return *choice;
                }
        }
        if (*choice == 1)
                printChooseNo();
        else
                printNotChooseNo();

        if (*choice == 2)
                printChooseYes();
        else
                printNotChooseYes();
}

int menuLogOut (int *choice, int *loopMenu){
        gotoxy(27, 13);
        printf("Do you want to Log Out?");
        char key;
        if (kbhit())
        {
                key = getch();
                if ((key == 'A' || key =='a') && (*choice == 2))
                {
                        *choice -= 1;
                        PlaySound(TEXT("option.wav"), NULL, SND_SYNC);
                }
                else if ((key == 'D' || key =='d') && (*choice == 1))
                {
                        *choice += 1;
                        PlaySound(TEXT("option.wav"), NULL, SND_SYNC);
                }
                else if (key == 13)
                {
                        PlaySound(TEXT("clicking.wav"), NULL, SND_SYNC);

                        *loopMenu = 0;
                        clrscr();
                        return *choice;
                }
        }
        if (*choice == 1)
                printChooseNo();
        else
                printNotChooseNo();

        if (*choice == 2)
                printChooseYes();
        else
                printNotChooseYes();
}

void printNotChooseNo (){ // return to menu
    int length = strlen("  No  ");
    int x = (consoleWidth - length) / 2;
    int y = consoleHeight / 2;
    gotoxy(x - 12, y + 4);
//    resetColor();
    puts("  NO");
}

void printChooseNo (){ // return to menu
    int length = strlen("> No <");
    int x = (consoleWidth - length) / 2;
    int y = consoleHeight / 2;
    gotoxy(x - 12, y + 4);
    changeColor(12);
    printf("%c NO", 249);
    resetColor();
}

void printChooseYes (){ // play again
    int length = strlen("> Yes <");
    int x = (consoleWidth - length) / 2;
    int y = consoleHeight / 2;
    gotoxy(x + 7, y + 4);
    changeColor(10);
    printf("%c YES", 249);
    resetColor();

}

void printNotChooseYes (){ // not play again
    int length = strlen("  Yes  ");
    int x = (consoleWidth - length) / 2;
    int y = consoleHeight / 2;
    gotoxy(x + 7, y + 4);
    resetColor();
    puts("  YES");
}

int menuStore(int *choice, int *loopMenu, int *mapChoice, int *levelMax, int bought[10], int *skin)
{
        char key;
        if (kbhit())
        {
                key = getch();
                if ((key == 'W' || key == 'w') && (*choice > 1 && *choice <= 3))
                {
                        *choice -= 1;
                        PlaySound(TEXT("option.wav"), NULL, SND_SYNC);
                }
                else if ((key == 'S' || key == 's') && (*choice >= 1 && *choice < 3))
                {
                        *choice += 1;
                        PlaySound(TEXT("option.wav"), NULL, SND_SYNC);
                }
                else if ((key == 'A' || key == 'a') && (*mapChoice > 1 && *mapChoice <= *levelMax && *choice == 1))
                {
                        *mapChoice -= 1;
                        PlaySound(TEXT("option.wav"), NULL, SND_SYNC);
                }
                else if ((key == 'D' || key == 'd') && (*mapChoice >= 1 && *mapChoice < *levelMax && *choice == 1))
                {
                        *mapChoice += 1;
                        PlaySound(TEXT("option.wav"), NULL, SND_SYNC);
                }
                else if ((key == 'A' || key == 'a') && (*skin > 1 && *skin <= 10 && *choice == 2))
                {
                        *skin -= 1;
                        PlaySound(TEXT("option.wav"), NULL, SND_SYNC);
                }
                else if ((key == 'D' || key == 'd') && (*skin >= 1 && *skin < 10 && *choice == 2))
                {
                        *skin += 1;
                        PlaySound(TEXT("option.wav"), NULL, SND_SYNC);
                }
                else if (key == 13)
                {
                        PlaySound(TEXT("clicking.wav"), NULL, SND_SYNC);

                        *loopMenu = 0;
                        clrscr();
                        return *choice;
                }
        }
                if (*skin == 1)
                {
                        gotoxy(37, 17);
                        printf("       >");
                        gotoxy(41, 17);
                        changeColor(*skin + 2);
                        printf("*");
                        resetColor();
                }
                else if (*skin == 2)
                {
                        gotoxy(37, 17);
                        printf(" <     >");
                        changeColor(*skin + 2);
                        gotoxy(41, 17);
                        printf("*");
                        resetColor();
                }
                else if (*skin == 3)
                {
                        gotoxy(37, 17);
                        printf(" <     >");
                        changeColor(*skin + 2);
                        gotoxy(41, 17);
                        printf("*");
                        resetColor();
                }

                else if (*skin == 4)
                {
                        gotoxy(37, 17);
                        printf(" <     >");
                        changeColor(*skin + 2);
                        gotoxy(41, 17);
                        printf("*");
                        resetColor();
                }

                else if (*skin == 5)
                {
                        gotoxy(37, 17);
                        printf(" <     >");
                        changeColor(*skin + 2);
                        gotoxy(41, 17);
                        printf("*");
                        resetColor();
                }

                else if (*skin == 6)
                {
                        gotoxy(37, 17);
                        printf(" <     >");
                        changeColor(*skin + 2);
                        gotoxy(41, 17);
                        printf("*");
                        resetColor();
                }

                else if (*skin == 7)
                {
                        gotoxy(37, 17);
                        printf(" <     >");
                        changeColor(*skin + 2);
                        gotoxy(41, 17);
                        printf("*");
                        resetColor();
                }

                else if (*skin == 8)
                {
                        gotoxy(37, 17);
                        printf(" <     >");
                        changeColor(*skin + 2);
                        gotoxy(41, 17);
                        printf("*");
                        resetColor();
                }

                else if (*skin == 9)
                {
                        gotoxy(37, 17);
                        printf(" <     >");
                        changeColor(*skin + 2);
                        gotoxy(41, 17);
                        printf("*");
                        resetColor();
                }
                else if(*skin == 10)
                {
                        gotoxy(37, 17);
                        printf(" <       ");
                        gotoxy(41, 17);
                        changeColor(*skin + 2);
                        printf("*");
                        resetColor();
                }

                        // choose map
        if (*choice == 1 )
        {
                changeColor(10);
                gotoxy(18, 15);
                printf("%c  MAPS", 249);
                resetColor();
                if (bought[*mapChoice - 1] == 1)
                        printUnlocked();
                else if (bought[*mapChoice - 1] == 0)
                        printLocked();
                if (*mapChoice == 1)
                {
                        gotoxy(37, 15);
                        printf("    1  >");
                }
                else if (*mapChoice == 2)
                {
                        gotoxy(37, 15);
                        printf(" <  2  >");
                }
                else if (*mapChoice == 3)
                {
                        gotoxy(37, 15);
                        printf(" <  3  >");
                }

                else if (*mapChoice == 4)
                {
                        gotoxy(37, 15);
                        printf(" <  4  >");
                }

                else if (*mapChoice == 5)
                {
                        gotoxy(37, 15);
                        printf(" <  5  >");
                }

                else if (*mapChoice == 6)
                {
                        gotoxy(37, 15);
                        printf(" <  6  >");
                }

                else if (*mapChoice == 7)
                {
                        gotoxy(37, 15);
                        printf(" <  7  >");
                }

                else if (*mapChoice == 8)
                {
                        gotoxy(37, 15);
                        printf(" <  8  >");
                }

                else if (*mapChoice == 9)
                {
                        gotoxy(37, 15);
                        printf(" <  9  >");
                }

                else if(*mapChoice == 10)
                {
                        gotoxy(37, 15);
                        printf("<  10      ");
                }
        }
        else
        {
                gotoxy(18, 15);
                printf("  MAPS ");
        }

        // choose Skin
        if (*choice == 2)
        {
                changeColor(10);
                gotoxy(18, 17);
                printf("%c  Skins", 249);
                resetColor();
                if (*skin == 1)
                {
                        gotoxy(37, 17);
                        printf("       >");
                        gotoxy(41, 17);
                        changeColor(*skin + 2);
                        printf("*");
                        resetColor();
                }
                else if (*skin == 2)
                {
                        gotoxy(37, 17);
                        printf(" <     >");
                        changeColor(*skin + 2);
                        gotoxy(41, 17);
                        printf("*");
                        resetColor();
                }
                else if (*skin == 3)
                {
                        gotoxy(37, 17);
                        printf(" <     >");
                        changeColor(*skin + 2);
                        gotoxy(41, 17);
                        printf("*");
                        resetColor();
                }

                else if (*skin == 4)
                {
                        gotoxy(37, 17);
                        printf(" <     >");
                        changeColor(*skin + 2);
                        gotoxy(41, 17);
                        printf("*");
                        resetColor();
                }

                else if (*skin == 5)
                {
                        gotoxy(37, 17);
                        printf(" <     >");
                        changeColor(*skin + 2);
                        gotoxy(41, 17);
                        printf("*");
                        resetColor();
                }

                else if (*skin == 6)
                {
                        gotoxy(37, 17);
                        printf(" <     >");
                        changeColor(*skin + 2);
                        gotoxy(41, 17);
                        printf("*");
                        resetColor();
                }

                else if (*skin == 7)
                {
                        gotoxy(37, 17);
                        printf(" <     >");
                        changeColor(*skin + 2);
                        gotoxy(41, 17);
                        printf("*");
                        resetColor();
                }

                else if (*skin == 8)
                {
                        gotoxy(37, 17);
                        printf(" <     >");
                        changeColor(*skin + 2);
                        gotoxy(41, 17);
                        printf("*");
                        resetColor();
                }

                else if (*skin == 9)
                {
                        gotoxy(37, 17);
                        printf(" <     >");
                        changeColor(*skin + 2);
                        gotoxy(41, 17);
                        printf("*");
                        resetColor();
                }
                else if(*skin == 10)
                {
                        gotoxy(37, 17);
                        printf(" <       ");
                        gotoxy(41, 17);
                        changeColor(*skin + 2);
                        printf("*");
                        resetColor();
                }
        }
        else
        {
                gotoxy(18, 17);
                printf("  Skins ");
        }
        // back to menu
        if (*choice == 3)
        {
                changeColor(14);
                gotoxy(18, 19);
                printf("%c  Back to MENU", 249);
                resetColor();
        }
        else
        {
                gotoxy(18, 19);
                printf("  Back to MENU ");
        }
}
void printLocked()
{
        changeColor(12);
        gotoxy(51, 15);
        printf("Locked");
        resetColor();
        gotoxy(59, 15);
        printf("/  Unlocked");
}
void printUnlocked()
{
        changeColor(10);
        gotoxy(62, 15);
        printf("Unlocked");
        resetColor();
        gotoxy(51, 15);
        printf("Locked  /");
}
void printRank(){
    gotoxy(20, 2);
    for (int i = 1; i <= 51; i++){
        if (i == 1)
            printf("%c", 218);
        else if (i == 51)
            printf("%c", 191);
        else if (i == 25)
            printf("%c", 194);
        else printf("%c", 196);
    }
    //printf("\n");

    for (int i = 2; i <= 20; i ++){
        gotoxy(20, i + 1);
        for (int j = 1; j <= 51; j++){
            if (i == 3){
                if (j == 1) printf("%c", 195);
                else if (j == 25) printf("%c", 197);
                else if (j == 51) printf("%c", 180);
                else printf("%c", 196);
            } else
                if (j == 1 || j == 25 || j == 51)
                    printf("%c", 179);
                else printf(" ");
        }
        printf("\n");
    }

    gotoxy(20, 22);
    for (int i = 1; i <= 51; i++){
        if (i == 1) printf("%c", 192);
        else if (i == 25) printf("%c", 193);
        else if (i == 51) printf("%c", 217);
        else printf("%c", 196);
    }

    changeColor(11);
    gotoxy(28, 3);
    printf("Username");
    resetColor();
    changeColor(6);
    gotoxy(28 + 27, 3);
    printf("Coins");
    resetColor();

}
int menuThangNhungDelChoQuaMan (int *choice, int *loopMenu, int *coins){
        int length = strlen("You Win!");
        int x = (consoleWidth - length) / 2;
        int y = consoleHeight / 2;

        gotoxy(x,y);
        changeColor(9);
        puts("You Win!");
        resetColor();
        changeColor(14);
        gotoxy(x - 1, y + 1);
        printf("+ %d coins", *coins);
        resetColor();

        gotoxy(20, 18);
        changeColor(13);
        printf("Collect all coins in wave to unlock next level!");
        resetColor();
        char key;
        if (kbhit())
        {
                key = getch();
                if ((key == 'A' || key =='a') && (*choice == 2))
                {
                        *choice -= 1;
                        PlaySound(TEXT("option.wav"), NULL, SND_SYNC);
                }
                else if ((key == 'D' || key =='d') && (*choice == 1))
                {
                        *choice += 1;
                        PlaySound(TEXT("option.wav"), NULL, SND_SYNC);
                }
                else if (key == 13)
                {
                        PlaySound(TEXT("clicking.wav"), NULL, SND_SYNC);

                        *coins  = 0;
                        *loopMenu = 0;
                        clrscr();
                        return *choice;
                }
        }
        if (*choice == 1)
                printChooseRTM();
        else
                printNotChooseRTM();

        if (*choice == 2)
                printChoosePA();
        else
                printNotChoosePA();
}
