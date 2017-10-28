wlinfo: wlinfo.c
	$(CC) -g -Wall $(shell pkg-config --cflags --libs wayland-client) $< -o $@
