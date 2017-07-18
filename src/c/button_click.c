#include <pebble.h>

static Window *window;
static TextLayer *text_layer_intro;
static TextLayer *text_layer_emelia;
static TextLayer *text_layer_hunter;

static void up_click_handler(ClickRecognizerRef recognizer, void *context) {
  text_layer_set_text(text_layer_intro, "Up");
}

static void down_click_handler(ClickRecognizerRef recognizer, void *context) {
  text_layer_set_text(text_layer_intro, "Down");
}

static void click_config_provider(void *context) {
  window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
}

static void window_load(Window *window) {
    Layer *window_layer = window_get_root_layer(window);
    GRect bounds = layer_get_bounds(window_layer);

    text_layer_intro = text_layer_create(GRect(0, 72, bounds.size.w, 20));
    text_layer_emelia = text_layer_create(GRect(0, 72, bounds.size.w, 20));
    text_layer_hunter = text_layer_create(GRect(0, 72, bounds.size.w, 20));
  
    text_layer_set_text(text_layer_intro, "Who are you?");
    text_layer_set_text(text_layer_emelia, "Emelia");
    text_layer_set_text(text_layer_hunter, "Hunter");
    
    text_layer_set_text_alignment(text_layer_intro, GTextAlignmentCenter);
    text_layer_set_text_alignment(text_layer_emelia, GTextAlignmentCenter);
    text_layer_set_text_alignment(text_layer_hunter, GTextAlignmentCenter);
    
    layer_add_child(window_layer, text_layer_get_layer(text_layer_intro));
    layer_add_child(window_layer, text_layer_get_layer(text_layer_emelia));
    layer_add_child(window_layer, text_layer_get_layer(text_layer_hunter));
}

static void window_unload(Window *window) {
    text_layer_destroy(text_layer_intro);
    text_layer_destroy(text_layer_emelia);
    text_layer_destroy(text_layer_hunter);
}

static void init(void) {
  window = window_create();
  window_set_click_config_provider(window, click_config_provider);
  window_set_window_handlers(window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload,
  });
  const bool animated = true;
  window_stack_push(window, animated);
}

static void deinit(void) {
  window_destroy(window);
}

int main(void) {
  init();

  APP_LOG(APP_LOG_LEVEL_DEBUG, "Done initializing, pushed window: %p", window);

  app_event_loop();
  deinit();
}