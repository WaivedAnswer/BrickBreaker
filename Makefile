CC = g++
INC_DIR = include
SRC_DIR = src
OBJ_DIR = bin
CFLAGS = -std=c++11 -I $(INC_DIR)
LFLAGS = -lSDL2 -lSDL2_ttf -lSDL2_image


_DEPS = GameObject.h Actor.h common.h commonSDL.h Ball.h Wall.h StandardWall.h DeathWall.h Brick.h ObjectVisitor.h Collider.h RectCollider.h CircleCollider.h PhysicsBody.h World.h Player.h BrickRemover.h GameEngine.h GameState.h PlayState.h MenuState.h Menu.h MenuNode.h CompositeNode.h ActionNode.h LTexture.h Command.h NullCommand.h NewGameCommand.h

DEPS = $(patsubst %, $(INC_DIR)/%, $(_DEPS))

_SRC = Actor.cpp Ball.cpp Wall.cpp StandardWall.cpp DeathWall.cpp Brick.cpp RectCollider.cpp CircleCollider.cpp PhysicsBody.cpp common.cpp World.cpp Player.cpp BrickRemover.cpp GameEngine.cpp PlayState.cpp MenuState.cpp Menu.cpp CompositeNode.cpp ActionNode.cpp LTexture.cpp NewGameCommand.cpp bricks.cpp
SRC = $(patsubst %, $(SRC_DIR)/%, $(_SRC))

_OBJ = Actor.o Ball.o Wall.o StandardWall.o DeathWall.o Brick.o RectCollider.o CircleCollider.o PhysicsBody.o common.o World.o Player.o BrickRemover.o GameEngine.o PlayState.o MenuState.o Menu.o CompositeNode.o ActionNode.o LTexture.o NewGameCommand.o bricks.o
OBJ = $(patsubst %, $(OBJ_DIR)/%, $(_OBJ))


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) $(LFLAGS)

bricks: $(OBJ) 
	$(CC) -o $@ $^ $(CFLAGS) $(LFLAGS)

clean:
	rm -f $(OBJ_DIR)/*.o bricks phystest
