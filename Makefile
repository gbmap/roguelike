C_THIRDPARTY := json/json.c
C_HTTP := game/g_network.c
C_UI := game/ui/ui.c game/ui/draw.c game/ui/speech_box.c game/ui/sprite.c game/ui/textbox.c
C_WORLD := game/world/world.c game/world/world_gen.c random/perlin.c
C_ENTITY := game/world/entity/player.c game/world/entity/entity.c  game/world/entity/entity_brain.c
C_GAME := game/game.c game/log.c game/time.c $(C_WORLD) $(C_ENTITY) $(C_UI) $(C_HTTP) $(C_THIRDPARTY)
LIBS := -lcurl -lpthread -lm

build: 
	gcc main.c $(C_GAME) -o main $(LIBS) -DJSON_SKIP_WHITESPACE

run: build
	./main

test/build:
	gcc tests/test_http.c $(C_HTTP) -o test_http $(LIBS)
	gcc tests/test_ent_brain.c $(C_GAME) -o test_ent_brain $(LIBS)

test: test/build
	 ./test_http && rm ./test_http
	 ./test_ent_brain && rm ./test_ent_brain

