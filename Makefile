C_THIRDPARTY := json/json.c
C_HTTP := game/g_network.c
C_UI := game/ui/ui.c game/ui/draw.c game/ui/speech_box.c game/ui/sprite.c game/ui/textbox.c
C_WORLD := game/world/world.c game/world/world_gen.c random/perlin.c
C_ENTITY := game/world/entity/player.c game/g_entity.c  game/world/entity/entity_brain.c
C_GAME := game/game.c game/log.c game/time.c game/g_prompt.c $(C_WORLD) $(C_ENTITY) $(C_UI) $(C_HTTP) $(C_THIRDPARTY)
LIBS := -lcurl -lpthread -lm

builddir:
	mkdir -p build

build: builddir
	cp -r data/ build/data
	gcc main.c $(C_GAME) -o build/main $(LIBS) -DJSON_SKIP_WHITESPACE

run: build
	./build/main

test/build: builddir
	gcc tests/test_http.c $(C_HTTP) -o build/test_http $(LIBS)
	# gcc tests/test_ent_brain.c $(C_GAME) -o build/test_ent_brain $(LIBS)
	gcc tests/test_prompts.c $(C_GAME) -o build/test_prompts $(LIBS)

test: test/build
	cp -r data/ build/data
	./build/test_http
	 # ./build/test_ent_brain
	./build/test_prompts

