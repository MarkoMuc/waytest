#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <wayland-client.h>

struct our_state {
  struct wl_compositor *compositor;
};

static void registry_handle_global(void *data, struct wl_registry *registry,
                                   uint32_t name, const char *interface,
                                   uint32_t version) {
  struct our_state *state = data;
  if (strcmp(interface, wl_compositor_interface.name) == 0) {
    state->compositor =
        wl_registry_bind(registry, name, &wl_compositor_interface, 4);
  }
}

static void registry_handle_global_remove(void *data,
                                          struct wl_registry *registry,
                                          uint32_t name) {
  // This space deliberately left blank
}

static const struct wl_registry_listener registry_listener = {
    .global = registry_handle_global,
    .global_remove = registry_handle_global_remove,
};

int main(int argc, char *argv[]) {
  struct our_state state = {0};
  struct wl_display *display = wl_display_connect(NULL);
  struct wl_registry *registry = wl_display_get_registry(display);
  wl_registry_add_listener(registry, &registry_listener, &state);
  wl_display_roundtrip(display);

  struct wl_surface *surface = wl_compositor_create_surface(state.compositor);
  return 0;
}
