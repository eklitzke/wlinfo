#include <stdio.h>
#include <string.h>

#include <wayland-client.h>

int display = 0;

static void
output_handle_geometry(void *data, struct wl_output *wl_output,
		       int32_t x, int32_t y,
		       int32_t physical_width, int32_t physical_height,
		       int32_t subpixel,
		       const char *make, const char *model,
		       int32_t output_transform)
{
  printf("x: %d\n", x);
  printf("y: %d\n", y);
  printf("physical_width: %d\n", physical_width);
  printf("physical_height: %d\n", physical_height);
  printf("subpixel: %d\n", subpixel);
  printf("make: %s\n", make);
  printf("model: %s\n", model);
  printf("output_transform: %d\n", output_transform);
}

static void output_handle_mode(void *data, struct wl_output *wl_output,
		   uint32_t flags, int32_t width, int32_t height,
		   int32_t refresh) {
  printf(" - width: %d\n", width);
  printf(" - height: %d\n", height);
}

static void output_handle_done(void *data, struct wl_output *wl_output) {
}

static void output_handle_scale(void *data, struct wl_output *wl_output,
		    int32_t scale)
{
  printf(" - scale: %d\n", scale);
}

static const struct wl_output_listener output_listener = {
	output_handle_geometry,
	output_handle_mode,
	output_handle_done,
	output_handle_scale,
};


static void
global_registry_handler(void *data, struct wl_registry *registry, uint32_t id,
	       const char *interface, uint32_t version) {
    if (!strcmp(interface, "wl_output")) {
      struct wl_output *output = output = wl_registry_bind(registry, id,
                                        &wl_output_interface, version);
      wl_output_add_listener(output, &output_listener, output);
    }
}

static void
global_registry_remover(void *data, struct wl_registry *registry, uint32_t id) {}

static const struct wl_registry_listener registry_listener = {
    global_registry_handler,
    global_registry_remover
};

int main(int argc, char **argv) {
  struct wl_display *display = wl_display_connect(NULL);
  if (display == NULL) {
    fprintf(stderr, "wl_display_connect() failed\n");
    return 1;
  }
  struct wl_registry *registry = wl_display_get_registry(display);
  wl_registry_add_listener(registry, &registry_listener, NULL);

  wl_display_dispatch(display);
  wl_display_roundtrip(display);

  return 0;
}
