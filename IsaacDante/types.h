#ifdef __TYPES__
#define __TYPES__

//máquina de estados
#define	NOTHING		0
#define	HIT			1
#define	SHOT		2
#define	LEFT		3

// 	NPCS E CENÁRIO
#define FOE		0
#define	OBJECT	1
#define FAMILIAR 2

typedef struct game_t{
	Lista *lista;
	int game_time;
	// 1 = direita -1 = esquerda 0 = parado 2=cima -2=baixo
	int	moves;
}Game;

typedef struct draw_t{
	int x,y
	char *i;
} Draw;

typedef struct sprite_t{
	Draw *draw;
	int HP;
	int	strength;
	int	speed;
	int	luck;
	int color;
	int state;
	int type;
	int begin_time;
	int	where_begin;
	void (*move)(Game *g, struct sprite_t *spr);
}Sprite;

typedef struct config_t{
	Draw *draw;
	int game_time;
	int type;
	int x;
	int y;
	int HP;
	int strength;
	int speed;
	int luck;
	int color;
	void ()
}Config;

#endif