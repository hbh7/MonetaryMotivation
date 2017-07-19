#include <pebble.h>

static Window *mainWindow;
static Window *hunterWindow;
static Window *emeliaWindow;
static TextLayer *text_layer_intro;
static TextLayer *text_layer_emelia;
static TextLayer *text_layer_hunter;

static TextLayer *text_layer_welcome;
static TextLayer *text_layer_rate;
static TextLayer *text_layer_time;
static TextLayer *text_layer_wages;
static TextLayer *text_layer_wages_2;


bool roundPebble;

#if defined(PBL_ROUND)
    bool roundPebble = true;       
#else
    bool roundPebble = false;
#endif

//Hunter
static void up_click_handler(ClickRecognizerRef recognizer, void *context) {
    /* 
    layer_set_hidden((Layer *)text_layer_intro, true);
    layer_set_hidden((Layer *)text_layer_hunter, true);
    layer_set_hidden((Layer *)text_layer_emelia, true);
    
    text_layer_set_text(text_layer_welcome, "Welcome, Hunter!");
    text_layer_set_text(text_layer_rate, "Rate: $12/hour");
    text_layer_set_text(text_layer_wages, "Current Wages:");
    text_layer_set_text(text_layer_wages_2, "$0.00");
    
    layer_set_hidden((Layer *)text_layer_welcome, false);
    layer_set_hidden((Layer *)text_layer_rate, false);
    layer_set_hidden((Layer *)text_layer_time, false);
    layer_set_hidden((Layer *)text_layer_wages, false);
    layer_set_hidden((Layer *)text_layer_wages_2, false);
    
    */
    APP_LOG(APP_LOG_LEVEL_DEBUG, "Pushed Up");
    window_stack_push(hunterWindow, true);
    
}

//Emelia
static void down_click_handler(ClickRecognizerRef recognizer, void *context) {

    layer_set_hidden((Layer *)text_layer_intro, true);
    layer_set_hidden((Layer *)text_layer_hunter, true);
    layer_set_hidden((Layer *)text_layer_emelia, true);
    
    text_layer_set_text(text_layer_welcome, "Welcome, Emelia!");
    text_layer_set_text(text_layer_rate, "Rate: $10.10/hour");
    text_layer_set_text(text_layer_wages, "Current Wages:");
    text_layer_set_text(text_layer_wages_2, "$0.00");
    
    layer_set_hidden((Layer *)text_layer_welcome, false);
    layer_set_hidden((Layer *)text_layer_rate, false);
    layer_set_hidden((Layer *)text_layer_time, false);
    layer_set_hidden((Layer *)text_layer_wages, false);
    layer_set_hidden((Layer *)text_layer_wages_2, false);

}
/*
static void back_click_handler(ClickRecognizerRef recognizer, void *context) {
    layer_set_hidden((Layer *)text_layer_intro, false);
    layer_set_hidden((Layer *)text_layer_hunter, false);
    layer_set_hidden((Layer *)text_layer_emelia, false);
    
    layer_set_hidden((Layer *)text_layer_welcome, true);
    layer_set_hidden((Layer *)text_layer_rate, true);
    layer_set_hidden((Layer *)text_layer_time, true);
    layer_set_hidden((Layer *)text_layer_wages, true);
    layer_set_hidden((Layer *)text_layer_wages_2, true);
    
    window_pop_all()
}
*/
static void click_config_provider(void *context) {
    window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
    window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
//    window_single_click_subscribe(BUTTON_ID_BACK, back_click_handler);
}

static void mainWindow_load(Window *window) {
    APP_LOG(APP_LOG_LEVEL_DEBUG, "Pushing mainWindow");
    
    Layer *window_layer = window_get_root_layer(window);
    GRect bounds = layer_get_bounds(window_layer);
    
    // Pebble Time: 144 × 168
    // Pebble Round: 180 x 180
    
    if (roundPebble == true) {  // K so this is left/right, then down/up. Lower # is higher up.
        text_layer_hunter = text_layer_create(GRect(0, 15, (bounds.size.w), 20));
        text_layer_emelia = text_layer_create(GRect(0, 140, (bounds.size.w), 20));
        text_layer_intro = text_layer_create(GRect(0, 80, bounds.size.w, 20));
        
        text_layer_welcome = text_layer_create(GRect(0, 30, (bounds.size.w), 20));
        text_layer_rate = text_layer_create(GRect(0, 50, (bounds.size.w), 20));
        text_layer_time = text_layer_create(GRect(0, 90, (bounds.size.w), 20));
        text_layer_wages = text_layer_create(GRect(0, 130, (bounds.size.w), 20));
        text_layer_wages_2 = text_layer_create(GRect(0, 150, (bounds.size.w), 20));
    } else {                    // K so this is left/right, then down/up. Lower # is higher up.
        text_layer_hunter = text_layer_create(GRect(0, 10, (bounds.size.w-10), 20));
        text_layer_emelia = text_layer_create(GRect(0, 140, (bounds.size.w-10), 20));
        text_layer_intro = text_layer_create(GRect(0, 72, bounds.size.w, 20));
        
        text_layer_welcome = text_layer_create(GRect(0, 30, (bounds.size.w-10), 20));
        text_layer_rate = text_layer_create(GRect(0, 50, (bounds.size.w-10), 20));
        text_layer_time = text_layer_create(GRect(0, 90, (bounds.size.w-10), 20));
        text_layer_wages = text_layer_create(GRect(0, 150, (bounds.size.w-10), 20));
        text_layer_wages_2 = text_layer_create(GRect(0, 150, (bounds.size.w), 20));
    }
    
    
    
    text_layer_set_text_alignment(text_layer_welcome, GTextAlignmentCenter);     
    text_layer_set_text_alignment(text_layer_rate, GTextAlignmentCenter);     
    text_layer_set_text_alignment(text_layer_time, GTextAlignmentCenter);     
    text_layer_set_text_alignment(text_layer_wages, GTextAlignmentCenter);     
    text_layer_set_text_alignment(text_layer_wages_2, GTextAlignmentCenter);     
    
    
    text_layer_set_text(text_layer_intro, "Who are you?");
    text_layer_set_text(text_layer_emelia, "Emelia");
    text_layer_set_text(text_layer_hunter, "Hunter");
    
    text_layer_set_text(text_layer_time, "Time Placeholder");
    

    
    if (roundPebble == true) {
        text_layer_set_text_alignment(text_layer_emelia, GTextAlignmentCenter);
        text_layer_set_text_alignment(text_layer_hunter, GTextAlignmentCenter);
    } else {
        text_layer_set_text_alignment(text_layer_emelia, GTextAlignmentRight);
        text_layer_set_text_alignment(text_layer_hunter, GTextAlignmentRight);
    }

    text_layer_set_text_alignment(text_layer_intro, GTextAlignmentCenter);
    
    layer_add_child(window_layer, text_layer_get_layer(text_layer_intro));
    layer_add_child(window_layer, text_layer_get_layer(text_layer_emelia));
    layer_add_child(window_layer, text_layer_get_layer(text_layer_hunter));
    
    layer_add_child(window_layer, text_layer_get_layer(text_layer_welcome));
    layer_add_child(window_layer, text_layer_get_layer(text_layer_rate));
    layer_add_child(window_layer, text_layer_get_layer(text_layer_time));
    layer_add_child(window_layer, text_layer_get_layer(text_layer_wages));
    layer_add_child(window_layer, text_layer_get_layer(text_layer_wages_2));
    
    layer_set_hidden((Layer *)text_layer_welcome, true);
    layer_set_hidden((Layer *)text_layer_rate, true);
    layer_set_hidden((Layer *)text_layer_time, true);
    layer_set_hidden((Layer *)text_layer_wages, true);
    layer_set_hidden((Layer *)text_layer_wages_2, true);
    
}

static void mainWindow_unload(Window *window) {
    text_layer_destroy(text_layer_intro);
    text_layer_destroy(text_layer_emelia);
    text_layer_destroy(text_layer_hunter);    
}

static void hunterWindow_load(Window *window) {
    APP_LOG(APP_LOG_LEVEL_DEBUG, "Pushing hunterWindow");
    
    Layer *hunter_window_layer = window_get_root_layer(hunterWindow);
    GRect bounds = layer_get_bounds(hunter_window_layer);
    
    // Pebble Time: 144 × 168
    // Pebble Round: 180 x 180
    
    if ( roundPebble == true ) {  // K so this is left/right, then down/up. Lower # is higher up.
        text_layer_welcome = text_layer_create(GRect(0, 30, (bounds.size.w), 20));
        text_layer_rate = text_layer_create(GRect(0, 50, (bounds.size.w), 20));
        text_layer_time = text_layer_create(GRect(0, 90, (bounds.size.w), 20));
        text_layer_wages = text_layer_create(GRect(0, 130, (bounds.size.w), 20));
        text_layer_wages_2 = text_layer_create(GRect(0, 150, (bounds.size.w), 20));
    } else {                    // K so this is left/right, then down/up. Lower # is higher up. 
        text_layer_welcome = text_layer_create(GRect(0, 30, (bounds.size.w-10), 20));
        text_layer_rate = text_layer_create(GRect(0, 50, (bounds.size.w-10), 20));
        text_layer_time = text_layer_create(GRect(0, 90, (bounds.size.w-10), 20));
        text_layer_wages = text_layer_create(GRect(0, 150, (bounds.size.w-10), 20));
        text_layer_wages_2 = text_layer_create(GRect(0, 150, (bounds.size.w), 20));
    }
    
    text_layer_set_text_alignment(text_layer_welcome, GTextAlignmentCenter);     
    text_layer_set_text_alignment(text_layer_rate, GTextAlignmentCenter);     
    text_layer_set_text_alignment(text_layer_time, GTextAlignmentCenter);     
    text_layer_set_text_alignment(text_layer_wages, GTextAlignmentCenter);     
    text_layer_set_text_alignment(text_layer_wages_2, GTextAlignmentCenter);     
   
    
    text_layer_set_text(text_layer_time, "Time Placeholder");
    
    layer_add_child(hunter_window_layer, text_layer_get_layer(text_layer_welcome));
    layer_add_child(hunter_window_layer, text_layer_get_layer(text_layer_rate));
    layer_add_child(hunter_window_layer, text_layer_get_layer(text_layer_time));
    layer_add_child(hunter_window_layer, text_layer_get_layer(text_layer_wages));
    layer_add_child(hunter_window_layer, text_layer_get_layer(text_layer_wages_2));
    
}

static void hunterWindow_unload(Window *window) {
    
    text_layer_destroy(text_layer_welcome);
    text_layer_destroy(text_layer_rate);
    text_layer_destroy(text_layer_time);
    text_layer_destroy(text_layer_wages);
    text_layer_destroy(text_layer_wages_2);
    
}

static void emeliaWindow_load(Window *window) {
    Layer *window_layer = window_get_root_layer(window);
    GRect bounds = layer_get_bounds(window_layer);
    
    // Pebble Time: 144 × 168
    // Pebble Round: 180 x 180
    
    if (roundPebble == true) {  // K so this is left/right, then down/up. Lower # is higher up.
        text_layer_hunter = text_layer_create(GRect(0, 15, (bounds.size.w), 20));
        text_layer_emelia = text_layer_create(GRect(0, 140, (bounds.size.w), 20));
        text_layer_intro = text_layer_create(GRect(0, 80, bounds.size.w, 20));
        
        text_layer_welcome = text_layer_create(GRect(0, 30, (bounds.size.w), 20));
        text_layer_rate = text_layer_create(GRect(0, 50, (bounds.size.w), 20));
        text_layer_time = text_layer_create(GRect(0, 90, (bounds.size.w), 20));
        text_layer_wages = text_layer_create(GRect(0, 130, (bounds.size.w), 20));
        text_layer_wages_2 = text_layer_create(GRect(0, 150, (bounds.size.w), 20));
    } else {                    // K so this is left/right, then down/up. Lower # is higher up.
        text_layer_hunter = text_layer_create(GRect(0, 10, (bounds.size.w-10), 20));
        text_layer_emelia = text_layer_create(GRect(0, 140, (bounds.size.w-10), 20));
        text_layer_intro = text_layer_create(GRect(0, 72, bounds.size.w, 20));
        
        text_layer_welcome = text_layer_create(GRect(0, 30, (bounds.size.w-10), 20));
        text_layer_rate = text_layer_create(GRect(0, 50, (bounds.size.w-10), 20));
        text_layer_time = text_layer_create(GRect(0, 90, (bounds.size.w-10), 20));
        text_layer_wages = text_layer_create(GRect(0, 150, (bounds.size.w-10), 20));
        text_layer_wages_2 = text_layer_create(GRect(0, 150, (bounds.size.w), 20));
    }
    
    
    
    text_layer_set_text_alignment(text_layer_welcome, GTextAlignmentCenter);     
    text_layer_set_text_alignment(text_layer_rate, GTextAlignmentCenter);     
    text_layer_set_text_alignment(text_layer_time, GTextAlignmentCenter);     
    text_layer_set_text_alignment(text_layer_wages, GTextAlignmentCenter);     
    text_layer_set_text_alignment(text_layer_wages_2, GTextAlignmentCenter);     
    
    
    text_layer_set_text(text_layer_intro, "Who are you?");
    text_layer_set_text(text_layer_emelia, "Emelia");
    text_layer_set_text(text_layer_hunter, "Hunter");
    
    text_layer_set_text(text_layer_time, "Time Placeholder");
    

    
    if (roundPebble == true) {
        text_layer_set_text_alignment(text_layer_emelia, GTextAlignmentCenter);
        text_layer_set_text_alignment(text_layer_hunter, GTextAlignmentCenter);
    } else {
        text_layer_set_text_alignment(text_layer_emelia, GTextAlignmentRight);
        text_layer_set_text_alignment(text_layer_hunter, GTextAlignmentRight);
    }

    text_layer_set_text_alignment(text_layer_intro, GTextAlignmentCenter);
    
    layer_add_child(window_layer, text_layer_get_layer(text_layer_intro));
    layer_add_child(window_layer, text_layer_get_layer(text_layer_emelia));
    layer_add_child(window_layer, text_layer_get_layer(text_layer_hunter));
    
    layer_add_child(window_layer, text_layer_get_layer(text_layer_welcome));
    layer_add_child(window_layer, text_layer_get_layer(text_layer_rate));
    layer_add_child(window_layer, text_layer_get_layer(text_layer_time));
    layer_add_child(window_layer, text_layer_get_layer(text_layer_wages));
    layer_add_child(window_layer, text_layer_get_layer(text_layer_wages_2));
    
    layer_set_hidden((Layer *)text_layer_welcome, true);
    layer_set_hidden((Layer *)text_layer_rate, true);
    layer_set_hidden((Layer *)text_layer_time, true);
    layer_set_hidden((Layer *)text_layer_wages, true);
    layer_set_hidden((Layer *)text_layer_wages_2, true);
    
}

static void emeliaWindow_unload(Window *window) {
    
    text_layer_destroy(text_layer_welcome);
    text_layer_destroy(text_layer_rate);
    text_layer_destroy(text_layer_time);
    text_layer_destroy(text_layer_wages);
    text_layer_destroy(text_layer_wages_2);
    
}

static void init(void) {
    APP_LOG(APP_LOG_LEVEL_DEBUG, "Starting Init");
    mainWindow = window_create();
    window_set_click_config_provider(mainWindow, click_config_provider);
    window_set_window_handlers(mainWindow, (WindowHandlers) {
      .load = mainWindow_load,
      .unload = mainWindow_unload,
    });
    APP_LOG(APP_LOG_LEVEL_DEBUG, "Created mainWindow");
    hunterWindow = window_create();
    window_set_window_handlers(hunterWindow, (WindowHandlers) {
      .load = hunterWindow_load,
      .unload = hunterWindow_unload,
    });
    APP_LOG(APP_LOG_LEVEL_DEBUG, "Created hunterWindow");
    emeliaWindow = window_create();
    window_set_window_handlers(emeliaWindow, (WindowHandlers) {
      .load = emeliaWindow_load,
      .unload = emeliaWindow_unload,
    });
  const bool animated = true;
  window_stack_push(mainWindow, animated);
}

static void deinit(void) {
    window_destroy(mainWindow);
    window_destroy(hunterWindow);
    window_destroy(emeliaWindow);
}

int main(void) {
  init();

  APP_LOG(APP_LOG_LEVEL_DEBUG, "Done initializing, pushed window: mainWindow");

  app_event_loop();
  deinit();
}