#include <lvgl.h>
#include "ui.h"

#include <TFT_eSPI.h>

#include <XPT2046_Touchscreen.h>

// A library for interfacing with the touch screen
//
// Can be installed from the library manager (Search for "XPT2046")
// https://github.com/PaulStoffregen/XPT2046_Touchscreen
// ----------------------------
// Touch Screen pins
// ----------------------------

// The CYD touch uses some non default
// SPI pins
#define ANALOG_PIN_0 27
#define XPT2046_IRQ 36
#define XPT2046_MOSI 32
#define XPT2046_MISO 39
#define XPT2046_CLK 25
#define XPT2046_CS 33
SPIClass touchscreenSpi = SPIClass(VSPI);
XPT2046_Touchscreen touchscreen(XPT2046_CS, XPT2046_IRQ);
uint16_t touchScreenMinimumX = 200, touchScreenMaximumX = 3700, touchScreenMinimumY = 240, touchScreenMaximumY = 3800;

/*Set to your screen resolution*/
#define TFT_HOR_RES 240
#define TFT_VER_RES 320

/*LVGL draw into this buffer, 1/10 screen size usually works well. The size is in bytes*/
#define DRAW_BUF_SIZE (TFT_HOR_RES * TFT_VER_RES / 10 * (LV_COLOR_DEPTH / 8))

#if LV_USE_LOG != 0
void my_print(lv_log_level_t level, const char *buf)
{
  LV_UNUSED(level);
  Serial.println(buf);
  Serial.flush();
}
#endif

/* LVGL calls it when a rendered image needs to copied to the display*/
void my_disp_flush(lv_display_t *disp, const lv_area_t *area, uint8_t *px_map)
{
  /*Call it to tell LVGL you are ready*/
  lv_disp_flush_ready(disp);
}

/*Read the touchpad*/
void my_touchpad_read(lv_indev_t *indev, lv_indev_data_t *data)
{
  if (touchscreen.touched())
  {
    TS_Point p = touchscreen.getPoint();
    // Some very basic auto calibration so it doesn't go out of range
    if (p.x < touchScreenMinimumX)
      touchScreenMinimumX = p.x;
    if (p.x > touchScreenMaximumX)
      touchScreenMaximumX = p.x;
    if (p.y < touchScreenMinimumY)
      touchScreenMinimumY = p.y;
    if (p.y > touchScreenMaximumY)
      touchScreenMaximumY = p.y;
    // Map this to the pixel position
    data->point.x = map(p.x, touchScreenMinimumX, touchScreenMaximumX, 1, TFT_HOR_RES); /* Touchscreen X calibration */
    data->point.y = map(p.y, touchScreenMinimumY, touchScreenMaximumY, 1, TFT_VER_RES); /* Touchscreen Y calibration */
    data->state = LV_INDEV_STATE_PRESSED;
    /*
    Serial.print("Touch x ");
    Serial.print(data->point.x);
    Serial.print(" y ");
    Serial.println(data->point.y);
    */
  }
  else
  {
    data->state = LV_INDEV_STATE_RELEASED;
  }
}

lv_indev_t *indev;     // Touchscreen input device
uint8_t *draw_buf;     // draw_buf is allocated on heap otherwise the static area is too big on ESP32 at compile
uint32_t lastTick = 0; // Used to track the tick timer

void setup()
{

  // Some basic info on the Serial console
  String LVGL_Arduino = "LVGL demo ";
  LVGL_Arduino += String('V') + lv_version_major() + "." + lv_version_minor() + "." + lv_version_patch();
  Serial.begin(115200);
  Serial.println(LVGL_Arduino);

  // Initialise the touchscreen
  touchscreenSpi.begin(XPT2046_CLK, XPT2046_MISO, XPT2046_MOSI, XPT2046_CS); /* Start second SPI bus for touchscreen */
  touchscreen.begin(touchscreenSpi);                                         /* Touchscreen init */
  touchscreen.setRotation(2);                                                /* Inverted landscape orientation to match screen */

  // Initialise LVGL GUI
  lv_init();

  draw_buf = new uint8_t[DRAW_BUF_SIZE];
  lv_display_t *disp;
  disp = lv_tft_espi_create(TFT_HOR_RES, TFT_VER_RES, draw_buf, DRAW_BUF_SIZE);
  lv_display_set_rotation(disp, LV_DISPLAY_ROTATION_90);

  // Initialize the XPT2046 input device driver
  indev = lv_indev_create();
  lv_indev_set_type(indev, LV_INDEV_TYPE_POINTER);
  lv_indev_set_read_cb(indev, my_touchpad_read);

  // Done
  Serial.println("LVGL Setup done");

  // Integrate EEZ Studio GUI
  ui_init();
}
extern lv_event_t g_eez_event;
extern bool g_eez_event_is_available;
static int Valbtn1 = 650;
static int Valbtn2 = 1880;
static int Valbtn3 = 2520;
static int Valbtn4 = 1230;
static int valfluk = 20;
static int intPotValPrev = 1; // Get an initial baseline value.

void loop()
{
  lv_tick_inc(millis() - lastTick); // Update the tick timer. Tick is new for LVGL 9
  lastTick = millis();
  lv_timer_handler(); // Update the UI
  delay(10);
  ui_tick();


  int potValCur = analogRead(ANALOG_PIN_0); // Get the current raw value.
  if (potValCur == 0)
  {

    intPotValPrev = potValCur;
  }

  else if (abs(potValCur - Valbtn1) < valfluk && (abs(potValCur - intPotValPrev) > valfluk)) 
  {
    
    
      Serial.printf("BT1: %ld\n", potValCur);
     
      intPotValPrev = potValCur;
    
  }
  else if (abs(potValCur - Valbtn2) < valfluk && (abs(potValCur - intPotValPrev) > valfluk))
  {

    Serial.printf("BT2: %ld\n", potValCur);
    intPotValPrev = potValCur;

  }
  else if (abs(potValCur - Valbtn3) < valfluk && (abs(potValCur - intPotValPrev) > valfluk))
  {
    
    Serial.printf("BTN3: %ld\n", potValCur);
    intPotValPrev = potValCur;
    
  }
  else if (abs(potValCur - Valbtn4) < valfluk  && (abs(potValCur - intPotValPrev) > valfluk))
  {
    
   Serial.printf("BTN4: %ld\n", potValCur);
   intPotValPrev = potValCur;
    
  }
  // ========== ADC input END   ==========
}