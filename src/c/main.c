#include <pebble.h>

static Window *window;
static TextLayer *text_layer_intro;
static TextLayer *text_layer_emelia;
static TextLayer *text_layer_hunter;

static TextLayer *text_layer_welcome;
static TextLayer *text_layer_rate;
static TextLayer *text_layer_wages;
static TextLayer *text_layer_time;



bool roundPebble;
char user;

#if defined(PBL_ROUND)
    bool roundPebble = true;       
#else
    bool roundPebble = false;
#endif

//Hunter
static void up_click_handler(ClickRecognizerRef recognizer, void *context) {
  // text_layer_set_text(text_layer_intro, "Up");
    layer_set_hidden((Layer *)text_layer_intro, true);
    layer_set_hidden((Layer *)text_layer_hunter, true);
    layer_set_hidden((Layer *)text_layer_emelia, true);
    
    //char user = "h";
    
    text_layer_set_text(text_layer_welcome, "Welcome, Hunter!");
    text_layer_set_text(text_layer_rate, "Rate: $10/hour");
    text_layer_set_text(text_layer_wages, "Current Wages: $5.06");
    
    layer_set_hidden((Layer *)text_layer_welcome, false);
    layer_set_hidden((Layer *)text_layer_rate, false);
    layer_set_hidden((Layer *)text_layer_time, false);
    layer_set_hidden((Layer *)text_layer_wages, false);
    
 

}

//Emelia
static void down_click_handler(ClickRecognizerRef recognizer, void *context) {
  // text_layer_set_text(text_layer_intro, "Down");
    layer_set_hidden((Layer *)text_layer_intro, true);
    layer_set_hidden((Layer *)text_layer_hunter, true);
    layer_set_hidden((Layer *)text_layer_emelia, true);
    
    //char user = "e";
}

static void back_click_handler(ClickRecognizerRef recognizer, void *context) {
    layer_set_hidden((Layer *)text_layer_intro, false);
    layer_set_hidden((Layer *)text_layer_hunter, false);
    layer_set_hidden((Layer *)text_layer_emelia, false);
    
    //char user = "e";
    
    layer_set_hidden((Layer *)text_layer_welcome, true);
    layer_set_hidden((Layer *)text_layer_rate, true);
    layer_set_hidden((Layer *)text_layer_time, true);
    layer_set_hidden((Layer *)text_layer_wages, true);
    
}

static void click_config_provider(void *context) {
    window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
    window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
    window_single_click_subscribe(BUTTON_ID_BACK, back_click_handler);
}

static void window_load(Window *window) {
    Layer *window_layer = window_get_root_layer(window);
    GRect bounds = layer_get_bounds(window_layer);
                                                // K so this is left/right, then down/up. Lower # is higher up.
    text_layer_hunter = text_layer_create(GRect(0, 10, (bounds.size.w-10), 20));
    text_layer_intro = text_layer_create(GRect(0, 72, bounds.size.w, 20));
    text_layer_emelia = text_layer_create(GRect(0, 140, (bounds.size.w-10), 20));
    
    text_layer_welcome = text_layer_create(GRect(0, 10, (bounds.size.w-10), 20));
    text_layer_wages = text_layer_create(GRect(0, 30, (bounds.size.w-10), 20));
    text_layer_rate = text_layer_create(GRect(0, 50, (bounds.size.w-10), 20));
    text_layer_time = text_layer_create(GRect(0, 70, (bounds.size.w-10), 20));
    
    text_layer_set_text_alignment(text_layer_welcome, GTextAlignmentCenter);     
    text_layer_set_text_alignment(text_layer_rate, GTextAlignmentCenter);     
    text_layer_set_text_alignment(text_layer_wages, GTextAlignmentCenter);     
    text_layer_set_text_alignment(text_layer_time, GTextAlignmentCenter);     
    
    
    text_layer_set_text(text_layer_intro, "Who are you?");
    text_layer_set_text(text_layer_emelia, "Emelia");
    text_layer_set_text(text_layer_hunter, "Hunter");
    
    text_layer_set_text(text_layer_time, "Time Placeholder");
    

    
    #if defined(PBL_ROUND)
        text_layer_set_text_alignment(text_layer_emelia, GTextAlignmentCenter);
           
    #else
        text_layer_set_text_alignment(text_layer_emelia, GTextAlignmentRight);
        text_layer_set_text_alignment(text_layer_hunter, GTextAlignmentRight);
    #endif

    text_layer_set_text_alignment(text_layer_intro, GTextAlignmentCenter);
    
    layer_add_child(window_layer, text_layer_get_layer(text_layer_intro));
    layer_add_child(window_layer, text_layer_get_layer(text_layer_emelia));
    layer_add_child(window_layer, text_layer_get_layer(text_layer_hunter));
    
    layer_add_child(window_layer, text_layer_get_layer(text_layer_welcome));
    layer_add_child(window_layer, text_layer_get_layer(text_layer_rate));
    layer_add_child(window_layer, text_layer_get_layer(text_layer_wages));
    layer_add_child(window_layer, text_layer_get_layer(text_layer_time));
    
    layer_set_hidden((Layer *)text_layer_welcome, true);
    layer_set_hidden((Layer *)text_layer_rate, true);
    layer_set_hidden((Layer *)text_layer_time, true);
    layer_set_hidden((Layer *)text_layer_wages, true);
    
}

static void window_unload(Window *window) {
    text_layer_destroy(text_layer_intro);
    text_layer_destroy(text_layer_emelia);
    text_layer_destroy(text_layer_hunter);
    
    text_layer_destroy(text_layer_welcome);
    text_layer_destroy(text_layer_rate);
    text_layer_destroy(text_layer_wages);
    text_layer_destroy(text_layer_time);
    
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