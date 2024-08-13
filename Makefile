C_THIRDPARTY := json/json.c
C_UTILS := game/u_str.c game/u_rand.c game/u_network.c game/u_time.c
C_UI := game/ui/ui.c game/ui/draw.c game/ui/speech_box.c game/ui/sprite.c game/ui/textbox.c
C_WORLD := game/g_world.c
C_ENTITY := game/g_player.c game/g_entity.c  game/world/entity/entity_brain.c
C_GAME := game/game.c game/u_log.c game/g_prompt.c game/g_cmd.c game/c_cmd.c $(C_WORLD) $(C_ENTITY) $(C_UI) $(C_HTTP) $(C_UTILS) $(C_THIRDPARTY)
LIBS := -lcurl -lpthread -lm
COMPILE_FLAGS := -g

builddir:
	mkdir -p build

build: builddir
	cp -r data/ build/data
	gcc main.c $(C_GAME) -o build/main $(LIBS) -DJSON_SKIP_WHITESPACE

run: build
	./build/main

test/build: builddir
	gcc tests/test_http.c $(C_HTTP) -o build/test_http $(COMPILE_FLAGS) $(LIBS)
	# gcc tests/test_ent_brain.c $(C_GAME) -o build/test_ent_brain $(LIBS)
	gcc tests/test_prompts.c $(C_GAME) -o build/test_prompts -g $(COMPILE_FLAGS) $(LIBS)
	gcc tests/test_cmdbuffer.c $(C_GAME) -o build/test_cmdbuffer -g $(COMPILE_FLAGS) $(LIBS)

test: test/build
	cp -r data/ build/data
	./build/test_http
	 # ./build/test_ent_brain
	./build/test_prompts
	./build/test_cmdbuffer

