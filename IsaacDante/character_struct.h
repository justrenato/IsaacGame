#ifndef STRUCT_H
#define STRUCT_H 
/*-----------------------------------------personagem----------------------------------------*/

typedef struct character_t{	
	int hp;
	int strength;
	int speed;
	int luck;

	
} character;

/*-----------------------------------------bosses-------------------------------------------*/

typedef struct boss_t{
	int hp;
	int speed;
	int strength;
} boss;

/*-----------------------------------------monstros------------------------------------------*/

typedef struct monster_t{
	int hp;
	int speed;
	int strength;	
	
} monster;

#endif