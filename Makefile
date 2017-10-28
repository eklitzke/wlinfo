wlinfo: wlinfo.c
	$(CC) $(shell pkg-config --cflags --libs wayland-client) $< -o $@
