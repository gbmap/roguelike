
build: 
	gcc main.c \
		random/perlin.c  \
		game/time.c \
		game/log.c \
		game/game.c \
		game/world/world.c \
		game/world/entity/entity.c  \
		game/world/entity/player.c \
		game/world/world_gen.c game/ui/speech_box.c \
		game/ui/draw.c \
		-o main

run: build
	./main


