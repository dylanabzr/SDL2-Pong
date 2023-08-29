build:
	gcc ./src/*.c -o pong -lSDL2
run:
	./pong
clean:
	rm pong
