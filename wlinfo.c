#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <wayland-client.h>

struct ctx {
  struct wl_list outputs;
  int need_newline;
};

struct output_t {
  int id;
  int size;
  struct ctx *ctx;
  struct wl_output *output;
  struct wl_list link;
};

static void output_handle_geometry(void *data, struct wl_output *wl_output,
                                   int32_t x, int32_t y, int32_t physical_width,
                                   int32_t physical_height, int32_t subpixel,
                                   const char *make, const char *model,
                                   int32_t output_transform) {
  struct output_t *out = (struct output_t *)data;
  if (out->ctx->need_newline) {
    putchar('\n');
  } else {
    out->ctx->need_newline = 1;
  }
  out->size = physical_width * physical_height;
  printf("output %d\n---------\n", out->id);

  printf("x: %d\n", x);
  printf("y: %d\n", y);
  printf("physical_width: %d\n", physical_width);
  printf("physical_height: %d\n", physical_height);
  printf("subpixel: %d\n", subpixel);
  printf("make: %s\n", make);
  printf("model: %s\n", model);
}

static void output_handle_mode(void *data, struct wl_output *wl_output,
                               uint32_t flags, int32_t width, int32_t height,
                               int32_t refresh) {
  printf("width: %d\n", width);
  printf("height: %d\n", height);
  double dots = width * height;
  double dots_per_mm = dots / ((struct output_t *)data)->size;
  double dots_per_in = dots_per_mm / 0.155;
  printf("dpi: %.1f\n", dots_per_in);
}

static void output_handle_done(void *data, struct wl_output *wl_output) {}

static void output_handle_scale(void *data, struct wl_output *wl_output,
                                int32_t scale) {
  printf("scale: %d\n", scale);
}

static const struct wl_output_listener output_listener = {
    output_handle_geometry, output_handle_mode, output_handle_done,
    output_handle_scale,
};

static void global_registry_handler(void *data, struct wl_registry *registry,
                                    uint32_t id, const char *interface,
                                    uint32_t version) {
  if (!strcmp(interface, "wl_output")) {
    struct ctx *ctx = (struct ctx *)data;
    struct output_t *output = malloc(sizeof(struct output_t));
    output->ctx = ctx;
    output->id = id;
    output->output =
        wl_registry_bind(registry, id, &wl_output_interface, version);
    wl_list_insert(&ctx->outputs, &output->link);
    wl_output_add_listener(output->output, &output_listener, output);
  }
}

static void global_registry_remover(void *data, struct wl_registry *registry,
                                    uint32_t id) {}

static const struct wl_registry_listener registry_listener = {
    global_registry_handler, global_registry_remover};

int main(int argc, char **argv) {
  struct wl_display *display = wl_display_connect(NULL);
  if (display == NULL) {
    fprintf(stderr, "wl_display_connect() failed\n");
    return 1;
  }

  struct ctx ctx;
  ctx.need_newline = 0;
  wl_list_init(&ctx.outputs);
  struct wl_registry *registry = wl_display_get_registry(display);

  wl_registry_add_listener(registry, &registry_listener, &ctx);

  wl_display_dispatch(display);
  wl_display_roundtrip(display);

  struct output_t *out, *tmp;
  wl_list_for_each_safe(out, tmp, &ctx.outputs, link) {
    wl_output_destroy(out->output);
    wl_list_remove(&out->link);
    free(out);
  }
  wl_registry_destroy(registry);
  wl_display_disconnect(display);
  return 0;
}
