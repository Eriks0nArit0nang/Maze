# Project: Maze
# Makefile created by Dev-C++ 4.9.9.2

CPP  = g++ 
CC   = gcc

OBJ  = Main.o Character.o WeaponProperties.o Weapon.o Gun.o AbstractGun.o AbstractGunDecorator.o WideShot.o ExplodingShot.o Grenade.o Bomb.o Nuke.o WallBreaker.o Player.o StandardEnemy.o Map.o Input.o Interaction.o EnemyWeapon.o Display.o Game.o Enemy.o EnemyFactory.o FloatingEnemy.o ShootingEnemy.o SurvivalGame.o Button.o ButtonManager.o MainMenu.o UpgradeMenu.o
DEPENDS = ${OBJ:.o=.d}
LDFLAGS =  -lallegro -lallegro_primitives -lallegro_font -lallegro_image -lallegro_main

DEBUGFLAGS = -g -ggdb3
BIN  = Maze
CXXFLAGS = -O3
RM = rm -f

.PHONY: all clean

all: ${BIN}

clean:
	${RM} $(OBJ) $(BIN)

$(BIN): $(OBJ)
	$(CPP) $(OBJ) ${CXXFLAGS} ${LDFLAGS} -o ${BIN}

