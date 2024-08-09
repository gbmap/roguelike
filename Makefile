C_HTTP := game/http/http.c game/http/http_thread.c
C_UI := game/ui/draw.c game/ui/speech_box.c game/ui/sprite.c
C_WORLD := game/world/world.c game/world/world_gen.c random/perlin.c
C_ENTITY := game/world/entity/entity.c game/world/entity/player.c
C_GAME := game/game.c game/log.c game/time.c $(C_WORLD) $(C_ENTITY) $(C_UI) $(C_HTTP)
LIBS := -lcurl -lpthread

build: 
	gcc main.c $(C_GAME) -o main $(LIBS)

run: build
	./main

test/build:
	gcc tests/test_http.c $(C_HTTP) -o test_http $(LIBS)

test: test/build
	 ./test_http && rm ./test_http

