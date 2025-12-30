build:
	cc -g -fsanitize=address mumble.c test.c -o mumblelinktest
