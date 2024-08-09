

C_FILES := random/perlin.c game/http.c game/time.c game/log.c game/game.c game/world/world.c game/world/entity/entity.c  game/world/entity/player.c game/world/world_gen.c game/ui/speech_box.c game/ui/draw.c

build: 
	gcc main.c $(C_FILES) -o main -lcurl

run: build
	./main

test:
	gcc tests/test_http.c $(C_FILES) -o test_http -lcurl && ./test_http && rm ./test_http

