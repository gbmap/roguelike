
build: 
	gcc main.c entity.c world/world.c world/world_gen.c random/perlin.c -o main

run: build
	./main


