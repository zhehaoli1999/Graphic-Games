// My_Test.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<conio.h>
#include<cstdlib>
#include<graphics.h>
#include"function.h"


////class Hero
class Hero {
	Position  position;           //当前坐标   #注意# 内嵌struct要实例化!
	Size  size;   //人物图片的大小
	IMAGE hero_img;

	void image_clear() {
		clearrectangle(position.x, position.y, position.x + size.x, position.y + size.y);
	}
	void image_put(int x = 0, int y = 0) {
		putimage(x, y, &hero_img);
	}

public:
	Hero(int size_x, int size_y, int birth_x, int birth_y);
	~Hero();

	bool move(int stride);
	bool ismonster();
	bool iswall(char key);
	void get_position();
	friend void draw(const Hero& hero, IMAGE* stone, IMAGE* star,IMAGE* monster);
	friend void clear(const Hero& hero);
};

//创造一个hero
Hero::Hero(int size_x = HERO_SIZE, int size_y = HERO_SIZE, int birth_x = STONE_SIZE, int birth_y = STONE_SIZE){
	//位置与图片大小
	size.x= size_x;
	size.y = size_y;
	position.x = birth_x;
	position.y = birth_y;
	//
	loadimage(&hero_img, L"..\\images\\hero.bmp", size_x, size_y);    //以size_x *size_y的大小loadimage
	image_put(birth_x, birth_y);
	printf("This is just a beginning!\n");
}

//析构hero
Hero::~Hero(){
	printf("Your hero is dead.");
	image_clear();
}

//移动
bool Hero::move(int stride = HERO_STRIDE) {    //key:指令，stride:步长
	if (maze[Hero::position.y / STONE_SIZE][Hero::position.x / STONE_SIZE] == -1) {
		printf("You Win!!!");//待优化！！！放张图片！
		return 1;
	}
	if (_kbhit()) {
		char key = _getch();            //直接读取键盘输入
		if (key == 'q') return 1;
		if (key == 'p') {
			Hero::get_position();
			return 1;
		}

		if (key == 'w'&&Hero::iswall(key)) {
			image_clear();
			image_put(position.x, position.y -= stride);
			return 1;
		}
		if (key == 's'&&Hero::iswall(key)) {
			image_clear();
			image_put(position.x, position.y += stride);
			return 1;
		}
		if (key == 'a'&&Hero::iswall(key)) {
			image_clear();
			image_put(position.x -= stride, position.y);
			return 1;
		}
		if (key == 'd'&&Hero::iswall(key)) {
			image_clear();
			image_put(position.x += stride, position.y);
			return 1;
		}
	}
}

bool Hero::iswall(char key) {
	switch (key) {
		case 'w': {
			//调试用：printf("x==%d,y==%d\n", -1 + Hero::position.y / STONE_SIZE, Hero::position.x / STONE_SIZE);
			if (maze[-1 + Hero::position.y / STONE_SIZE][Hero::position.x / STONE_SIZE]<=0)return 1;
			else return 0;
			break;
			//#注意# -1 的原因是矩阵下标是从0开始的！
		}
		case 's': {
			if (maze[1+Hero::position.y / STONE_SIZE][Hero::position.x / STONE_SIZE]<=0)return 1;
			else return 0;
			break;
		}
		case 'a': {
			if (maze[Hero::position.y / STONE_SIZE][-1 + Hero::position.x / STONE_SIZE]<=0)return 1;
			else return 0;
			break;
		}
		case 'd': {
			if (maze[Hero::position.y / STONE_SIZE] [1+Hero::position.x / STONE_SIZE]<=0)return 1;
			else return 0;
			break;
		}

	}
}

bool Hero::ismonster() {
	if (Hero::position.x == MONSTER_BIRTH_x && Hero::position.y == MONSTER_BIRTH_y) { 
		Hero::~Hero();
		return 1; }
	else return 0;
}
void Hero::get_position() {
	printf("x=%d,y=%d\n", Hero::position.x, Hero::position.y);
}

////class Hero2
class Hero2 :virtual public Hero {

public:
	void move(int stride = HERO_STRIDE); 
};    


/*
////class Monster
class Monster{
	Position position;
	Size size;
	IMAGE  monster_img;
	void image_clear() {
		clearrectangle(position.x, position.y, position.x + size.x, position.y + size.y);
	}
	void image_put(int x = 0, int y = 0) {
		putimage(x, y, &monster_img);
	}
public:
	Monster(int size_x, int size_y, int birth_x, int birth_y);
	~Monster();
	void attack();
	//void move(int stride);
};

Monster::Monster(int size_x= MONSTER_SIZE, int size_y= MONSTER_SIZE, int birth_x= MONSTER_BIRTH_x, int birth_y= MONSTER_BIRTH_y)
{
	size.x = size_x;
	size.y = size_y;
	position.x = birth_x;
	position.y = birth_y;

	loadimage(&monster_img, L"D:\\monster1.bmp", size_x, size_y);
	image_put(birth_x, birth_y);
	printf("Watch Out!There is something strange in this maze...\n");
}

Monster::~Monster(){}

void Monster::move(int stride = MONSTER_STRIDE) {
	if (_kbhit()) {
		char key = _getch();            //直接读取键盘输入
		if (key == 'u'&&Monster::iswall(key)) {
			image_clear();
			image_put(position.x, position.y -= stride);
		}
		if (key == 'j'&&Monster::iswall(key)) {
			hero_clear();
			hero_put(position.x, position.y += stride);
		}
		if (key == 'h'&&Monster::iswall(key)) {
			hero_clear();
			hero_put(position.x -= stride, position.y);
		}
		if (key == 'k'&&Monster::iswall(key)) {
			hero_clear();
			hero_put(position.x += stride, position.y);
		}
	}
}

void Monster::attack() {

}
*/

void draw(const Hero& hero,IMAGE* stone,IMAGE* star,IMAGE* monster) {
	for (int i = hero.position.y /HERO_SIZE - 1; i <= hero.position.y / HERO_SIZE + 1; i++) {
		for (int j = hero.position.x / HERO_SIZE - 1; j <= hero.position.x / HERO_SIZE + 1; j++) {
			if (maze[i][j] == 1) {
				putimage(j*STONE_SIZE, i*STONE_SIZE, stone);
				continue;
			}
			if (maze[i][j] == 2) {
				putimage(j*STONE_SIZE, i*STONE_SIZE, monster);
			}
			if (maze[i][j] == -1)
				putimage(j*STONE_SIZE, i*STONE_SIZE, star);
		}
	}
}
void clear(const Hero& hero){
	clearrectangle(hero.position.x-HERO_SIZE, hero.position.y - HERO_SIZE, hero.position.x +HERO_SIZE, hero.position.y + HERO_SIZE);
}
int main()
{
	initgraph(WIDTH, HEIGHT, SHOWCONSOLE);

	Hero man;
	//Monster octopus;

	IMAGE stone;	
	IMAGE star;
	IMAGE monster1;

	loadimage(&stone, L"..\\images\\stone.bmp", STONE_SIZE, STONE_SIZE);
	loadimage(&star, L"..\\images\\star.bmp", STONE_SIZE, STONE_SIZE);
	loadimage(&monster1, L"..\\images\\fireghost.bmp", MONSTER_SIZE, MONSTER_SIZE);

	man.move();
	draw(man, &stone, &star,&monster1);
	//putimage(21 * STONE_SIZE, 6 * STONE_SIZE, &monster1);
	//char pause1 = _getch();
	while (1) {
		if (man.move()) {
			draw(man, &stone, &star,&monster1);
			//clear(man);
		}
	}
	//初始化图形界面
	/*
	for (int i = 0; i <= HEIGHT /STONE_SIZE; i ++) {
		for (int j = 0; j <= WIDTH/STONE_SIZE ; j ++){
			if (maze[i][j] == 1) {
				putimage(j*STONE_SIZE, i*STONE_SIZE, &stone);
				continue; 
			}
			if(maze[i][j]==-1)
				putimage(j*STONE_SIZE, i*STONE_SIZE, &star);
		}
	}*/

	//放置monster
	
	man.move();
	getchar();
	closegraph();
}