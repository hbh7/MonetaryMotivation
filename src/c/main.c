#include <pebble.h>

// Helpful Info:
// Created by hbh7
//
// Pebble Time: 144 × 168
// Pebble Round: 180 x 180

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
bool emelia;

#if defined(PBL_ROUND)
    bool roundPebble = true;       
#else
    bool roundPebble = false;
#endif

char* floatToString(char* buffer, int bufferSize, double number) {
    char decimalBuffer[5];

    snprintf(buffer, bufferSize, "%d", (int)number);
    strcat(buffer, ".");

    snprintf(decimalBuffer, 5, "%02d", (int)((double)(number - (int)number) * (double)100));
    strcat(buffer, decimalBuffer);

    return buffer;
}

// Runs when the time changes
static void update_time() {
    // Get a tm structure
    time_t temp = time(NULL);
    struct tm *tick_time = localtime(&temp);

    // Write the current hours, minutes, and seconds into a buffer
    static char time_buffer[12];
    strftime(time_buffer, sizeof(time_buffer), clock_is_24h_style() ?
                                          "%H:%M:%S" : "%I:%M:%S", tick_time);
    // Write those to a bunch of buffers
    static char wages_hour_buffer[8];
    static char wages_minute_buffer[8];
    static char wages_second_buffer[8];
    strftime(wages_hour_buffer, sizeof(wages_hour_buffer), true ?
                                          "%H" : "%H", tick_time);
    strftime(wages_minute_buffer, sizeof(wages_minute_buffer), true ?
                                          "%M" : "%M", tick_time);
    strftime(wages_second_buffer, sizeof(wages_second_buffer), true ?
                                          "%S" : "%S", tick_time);
    
    int wages_hour = atof(wages_hour_buffer);
    int wages_minute = atof(wages_minute_buffer);
    int wages_second = atof(wages_second_buffer);
    /*
    APP_LOG(APP_LOG_LEVEL_DEBUG, "Hour: %d", wages_hour);
    APP_LOG(APP_LOG_LEVEL_DEBUG, "Minute: %d", wages_minute);
    APP_LOG(APP_LOG_LEVEL_DEBUG, "Second: %d", wages_second);
    */
    
    // Display this time on the TextLayer
    text_layer_set_text(text_layer_time, time_buffer);
    //APP_LOG(APP_LOG_LEVEL_DEBUG, "Ticking the time %p", time_buffer);
    
    // Logic for the counter
    double wages_total_amount;
    double wages_hour_amount;
    double wages_minute_amount;
    double wages_second_amount;

    // Manual override for after hours
    //wages_hour = 20;
    
    //APP_LOG(APP_LOG_LEVEL_DEBUG, "Starting Wages Hour: %d", wages_hour);   
    if (wages_hour > 17) {
        // Its past 5, set an amount
        if (emelia == false) {
            wages_total_amount = 96;
        }
        else {
           wages_total_amount = 80;
        }
    } else {
        // Its work time
        wages_hour = wages_hour-8;
        if (emelia == false) {
            wages_hour_amount = wages_hour*12;
            wages_minute_amount = wages_minute*0.2;
            wages_second_amount = wages_second*0.003;
            wages_total_amount = wages_hour_amount+wages_minute_amount+wages_second_amount;
        }
        else {
            wages_hour_amount = wages_hour*10.10;
            wages_minute_amount = wages_minute*0.168;
            wages_second_amount = wages_second*0.0028;
            wages_total_amount = wages_hour_amount+wages_minute_amount+wages_second_amount;
        }
    }
    //APP_LOG(APP_LOG_LEVEL_DEBUG, "Adjusted Wages Hour: %d", wages_hour);   

    static char wages_string[7];
    char wages_string_2[7] = "$";
    strcpy(wages_string, floatToString(wages_string, 5, wages_total_amount));
    strcat(wages_string_2, wages_string);
    text_layer_set_text(text_layer_wages_2, wages_string_2);
    APP_LOG(APP_LOG_LEVEL_DEBUG, "Total Wages: %s", wages_string_2);
}

// Handles time update
static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
    update_time();
}

// Handle the up/Hunter button
static void up_click_handler(ClickRecognizerRef recognizer, void *context) {
    APP_LOG(APP_LOG_LEVEL_DEBUG, "Pushed Up");
    emelia = false;
    window_stack_push(hunterWindow, true);
}

// Handle the down/Emelia button
static void down_click_handler(ClickRecognizerRef recognizer, void *context) {
    APP_LOG(APP_LOG_LEVEL_DEBUG, "Pushed Down");
    emelia = true;
    window_stack_push(emeliaWindow, true);
}

// Listen for button presses
static void click_config_provider(void *context) {
    window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
    window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
}

static void mainWindow_load(Window *window) {
    APP_LOG(APP_LOG_LEVEL_DEBUG, "Pushing mainWindow");
    
    Layer *window_layer = window_get_root_layer(window);
    GRect bounds = layer_get_bounds(window_layer);
    
    // Pebble Time: 144 × 168
    // Pebble Round: 180 x 180
    
    if (roundPebble == true) {  // K so this is left/right, then down/up. Lower # is higher up.
        text_layer_hunter = text_layer_create(GRect(0, 15, (bounds.size.w), 40));
        text_layer_emelia = text_layer_create(GRect(0, 140, (bounds.size.w), 40));
        text_layer_intro = text_layer_create(GRect(0, 70, bounds.size.w, 60));
        
        text_layer_welcome = text_layer_create(GRect(0, 30, (bounds.size.w), 20));
        text_layer_rate = text_layer_create(GRect(0, 50, (bounds.size.w), 20));
        text_layer_time = text_layer_create(GRect(0, 90, (bounds.size.w), 20));
        text_layer_wages = text_layer_create(GRect(0, 130, (bounds.size.w), 20));
        text_layer_wages_2 = text_layer_create(GRect(0, 150, (bounds.size.w), 20));
    } else {                    // K so this is left/right, then down/up. Lower # is higher up.
        text_layer_hunter = text_layer_create(GRect(0, 1, (bounds.size.w-10), 40));
        text_layer_emelia = text_layer_create(GRect(0, 135, (bounds.size.w-10), 40));
        text_layer_intro = text_layer_create(GRect(0, 65, bounds.size.w, 60));
        
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
    
    text_layer_set_font(text_layer_intro, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
    text_layer_set_font(text_layer_emelia, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
    text_layer_set_font(text_layer_hunter, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
    
    text_layer_set_background_color(text_layer_intro, GColorBlack);
    text_layer_set_background_color(text_layer_hunter, GColorBlack);
    text_layer_set_background_color(text_layer_emelia, GColorBlack);
    text_layer_set_background_color(text_layer_time, GColorBlack);
    
    text_layer_set_text_color(text_layer_intro, GColorWhite);
    text_layer_set_text_color(text_layer_hunter, GColorWhite);
    text_layer_set_text_color(text_layer_emelia, GColorWhite);
    text_layer_set_text_color(text_layer_time, GColorWhite);
    
    
    
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
    
}

static void mainWindow_unload(Window *window) {
    text_layer_destroy(text_layer_intro);
    text_layer_destroy(text_layer_emelia);
    text_layer_destroy(text_layer_hunter);    
}

static void hunterWindow_load(Window *window) {
    APP_LOG(APP_LOG_LEVEL_DEBUG, "Pushing hunterWindow");
    
    Layer *hunterWindow_layer = window_get_root_layer(hunterWindow);
    GRect bounds = layer_get_bounds(hunterWindow_layer);
    
    if ( roundPebble == true ) {  // K so this is left/right, then down/up. Lower # is higher up.
        text_layer_welcome = text_layer_create(GRect(0, 30, (bounds.size.w), 20));
        text_layer_rate = text_layer_create(GRect(0, 50, (bounds.size.w), 20));
        text_layer_time = text_layer_create(GRect(0, 80, (bounds.size.w), 38));
        text_layer_wages = text_layer_create(GRect(0, 130, (bounds.size.w), 20));
        text_layer_wages_2 = text_layer_create(GRect(0, 145, (bounds.size.w), 21));
    } else {                    // K so this is left/right, then down/up. Lower # is higher up. 
        text_layer_welcome = text_layer_create(GRect(0, 10, (bounds.size.w), 20));
        text_layer_rate = text_layer_create(GRect(0, 30, (bounds.size.w), 20));
        text_layer_time = text_layer_create(GRect(0, 60, (bounds.size.w), 38));
        text_layer_wages = text_layer_create(GRect(0, 120, (bounds.size.w), 20));
        text_layer_wages_2 = text_layer_create(GRect(0, 135, (bounds.size.w), 21));
    }
    
    text_layer_set_text_alignment(text_layer_welcome, GTextAlignmentCenter);     
    text_layer_set_text_alignment(text_layer_rate, GTextAlignmentCenter);     
    text_layer_set_text_alignment(text_layer_time, GTextAlignmentCenter);     
    text_layer_set_text_alignment(text_layer_wages, GTextAlignmentCenter);     
    text_layer_set_text_alignment(text_layer_wages_2, GTextAlignmentCenter);     
   
    text_layer_set_text(text_layer_welcome, "Welcome, Hunter!");
    text_layer_set_text(text_layer_rate, "Rate: $12/hour");
    text_layer_set_text(text_layer_time, "Loading...");
    text_layer_set_text(text_layer_wages, "Current Wages:");
    text_layer_set_text(text_layer_wages_2, "$0.00");
    
    text_layer_set_background_color(text_layer_welcome, GColorOrange);
    text_layer_set_background_color(text_layer_rate, GColorOrange);
    text_layer_set_background_color(text_layer_time, GColorChromeYellow);
    text_layer_set_background_color(text_layer_wages, GColorOrange);
    text_layer_set_background_color(text_layer_wages_2, GColorOrange);
    
    text_layer_set_text_color(text_layer_welcome, GColorWhite);
    text_layer_set_text_color(text_layer_rate, GColorWhite);
    text_layer_set_text_color(text_layer_time, GColorWhite);
    text_layer_set_text_color(text_layer_wages, GColorWhite);
    text_layer_set_text_color(text_layer_wages_2, GColorWhite);
    
    text_layer_set_font(text_layer_time, fonts_get_system_font(FONT_KEY_DROID_SERIF_28_BOLD));
    text_layer_set_font(text_layer_wages_2, fonts_get_system_font(FONT_KEY_ROBOTO_CONDENSED_21));
    
    layer_add_child(hunterWindow_layer, text_layer_get_layer(text_layer_welcome));
    layer_add_child(hunterWindow_layer, text_layer_get_layer(text_layer_rate));
    layer_add_child(hunterWindow_layer, text_layer_get_layer(text_layer_time));
    layer_add_child(hunterWindow_layer, text_layer_get_layer(text_layer_wages));
    layer_add_child(hunterWindow_layer, text_layer_get_layer(text_layer_wages_2));
}

static void hunterWindow_unload(Window *window) {
    text_layer_destroy(text_layer_welcome);
    text_layer_destroy(text_layer_rate);
    text_layer_destroy(text_layer_time);
    text_layer_destroy(text_layer_wages);
    text_layer_destroy(text_layer_wages_2);
}

static void emeliaWindow_load(Window *window) {
    Layer *emeliaWindow_layer = window_get_root_layer(emeliaWindow);
    GRect bounds = layer_get_bounds(emeliaWindow_layer);
    
    // Pebble Time: 144 × 168
    // Pebble Round: 180 x 180
    
    if ( roundPebble == true ) {  // K so this is left/right, then down/up. Lower # is higher up.
        text_layer_welcome = text_layer_create(GRect(0, 30, (bounds.size.w), 20));
        text_layer_rate = text_layer_create(GRect(0, 50, (bounds.size.w), 20));
        text_layer_time = text_layer_create(GRect(0, 80, (bounds.size.w), 38));
        text_layer_wages = text_layer_create(GRect(0, 130, (bounds.size.w), 20));
        text_layer_wages_2 = text_layer_create(GRect(0, 145, (bounds.size.w), 21));
    } else {                    // K so this is left/right, then down/up. Lower # is higher up. 
        text_layer_welcome = text_layer_create(GRect(0, 10, (bounds.size.w), 20));
        text_layer_rate = text_layer_create(GRect(0, 30, (bounds.size.w), 20));
        text_layer_time = text_layer_create(GRect(0, 60, (bounds.size.w), 38));
        text_layer_wages = text_layer_create(GRect(0, 120, (bounds.size.w), 20));
        text_layer_wages_2 = text_layer_create(GRect(0, 135, (bounds.size.w), 21));
    }
    
    text_layer_set_text_alignment(text_layer_welcome, GTextAlignmentCenter);     
    text_layer_set_text_alignment(text_layer_rate, GTextAlignmentCenter);     
    text_layer_set_text_alignment(text_layer_time, GTextAlignmentCenter);     
    text_layer_set_text_alignment(text_layer_wages, GTextAlignmentCenter);     
    text_layer_set_text_alignment(text_layer_wages_2, GTextAlignmentCenter);     
   
    text_layer_set_text(text_layer_welcome, "Welcome, Emelia!");
    text_layer_set_text(text_layer_rate, "Rate: $10.10/hour");
    text_layer_set_text(text_layer_time, "Loading...");
    text_layer_set_text(text_layer_wages, "Current Wages:");
    text_layer_set_text(text_layer_wages_2, "$0.00");
    
    text_layer_set_background_color(text_layer_welcome, GColorIndigo);
    text_layer_set_background_color(text_layer_rate, GColorIndigo);
    text_layer_set_background_color(text_layer_time, GColorIndigo);
    text_layer_set_background_color(text_layer_wages, GColorIndigo);
    text_layer_set_background_color(text_layer_wages_2, GColorIndigo);
    
    text_layer_set_text_color(text_layer_welcome, GColorWhite);
    text_layer_set_text_color(text_layer_rate, GColorWhite);
    text_layer_set_text_color(text_layer_time, GColorWhite);
    text_layer_set_text_color(text_layer_wages, GColorWhite);
    text_layer_set_text_color(text_layer_wages_2, GColorWhite);

    text_layer_set_font(text_layer_time, fonts_get_system_font(FONT_KEY_DROID_SERIF_28_BOLD));
    text_layer_set_font(text_layer_wages_2, fonts_get_system_font(FONT_KEY_ROBOTO_CONDENSED_21));
    
    layer_add_child(emeliaWindow_layer, text_layer_get_layer(text_layer_welcome));
    layer_add_child(emeliaWindow_layer, text_layer_get_layer(text_layer_rate));
    layer_add_child(emeliaWindow_layer, text_layer_get_layer(text_layer_time));
    layer_add_child(emeliaWindow_layer, text_layer_get_layer(text_layer_wages));
    layer_add_child(emeliaWindow_layer, text_layer_get_layer(text_layer_wages_2));
    
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
    
    // Register with TickTimerService
    tick_timer_service_subscribe(SECOND_UNIT, tick_handler);
    
    
    mainWindow = window_create();
        window_set_click_config_provider(mainWindow, click_config_provider);
        window_set_window_handlers(mainWindow, (WindowHandlers) {
          .load = mainWindow_load,
          .unload = mainWindow_unload,
        });
        window_set_background_color(mainWindow, GColorBlack);
    APP_LOG(APP_LOG_LEVEL_DEBUG, "Created mainWindow");
    
    hunterWindow = window_create();
        window_set_window_handlers(hunterWindow, (WindowHandlers) {
          .load = hunterWindow_load,
          .unload = hunterWindow_unload,
        });
        window_set_background_color(hunterWindow, GColorOrange);
    APP_LOG(APP_LOG_LEVEL_DEBUG, "Created hunterWindow");
    
    emeliaWindow = window_create();
        window_set_window_handlers(emeliaWindow, (WindowHandlers) {
          .load = emeliaWindow_load,
          .unload = emeliaWindow_unload,
        });
        window_set_background_color(emeliaWindow, GColorIndigo);
    APP_LOG(APP_LOG_LEVEL_DEBUG, "Created emeliaWindow");
    
    // Display the main window/screen
    const bool animated = true;
    window_stack_push(mainWindow, animated);
    
    // Make sure the time is displayed from the start
    update_time();
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