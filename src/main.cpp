#include <lvgl.h>
#include "ui.h"

#include <TFT_eSPI.h>
#include <Preferences.h>
#include <XPT2046_Touchscreen.h>
#include "actions.h"
#include <time.h>

// #include "BluetoothSerial.h"

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

// BluetoothSerial SerialBT;
bool isConnected = false;

Preferences preferences;
char projname1[50] = "Boot";
char projname2[50] = "Flieger";
char projname3[50] = "Zug";
char projname4[50] = "Auto";
void setup()
{

  delay(100);
  // Some basic info on the Serial console
  String LVGL_Arduino = "LVGL demo ";
  LVGL_Arduino += String('V') + lv_version_major() + "." + lv_version_minor() + "." + lv_version_patch();
  Serial.begin(115200);
  Serial.println(LVGL_Arduino);

  // Initialise the touchscreen
  touchscreenSpi.begin(XPT2046_CLK, XPT2046_MISO, XPT2046_MOSI, XPT2046_CS); /* Start second SPI bus for touchscreen */
  touchscreen.begin(touchscreenSpi);                                         /* Touchscreen init */
  touchscreen.setRotation(2);                                                /* Inverted landscape orientation to match screen */

  preferences.begin("projects", false); // Namespace "projects", lesend & schreibend

  // Gespeicherte Namen laden (Standardwert: "Default")
  String loadedName1 = preferences.getString("projname1", "Default1");
  loadedName1.toCharArray(projname1, sizeof(projname1));
  String loadedName2 = preferences.getString("projname2", "Default2");
  loadedName2.toCharArray(projname2, sizeof(projname2));
  String loadedName3 = preferences.getString("projname3", "Default3");
  loadedName3.toCharArray(projname3, sizeof(projname3));
  String loadedName4 = preferences.getString("projname4", "Default4");
  loadedName4.toCharArray(projname4, sizeof(projname4));

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
#define BTN_ACTIVE_COLOR lv_color_make(0, 0, 255)        // Blau
#define BTN_INACTIVE_COLOR lv_color_make(100, 149, 237)  // Kräftiges Hellblau
extern lv_event_t g_eez_event;
extern bool g_eez_event_is_available;
static int Valbtn1 = 650;
static int Valbtn2 = 1880;
static int Valbtn3 = 2520;
static int Valbtn4 = 1230;
static int valfluk = 20;
static int intPotValPrev = 1; // Get an initial baseline value.

static bool t1activ = false;
static bool t2activ = false;
static bool t3activ = false;
static bool t4activ = false;
int t1 = 0;
int t2 = 0;
int t3 = 0;
int t4 = 0;

bool pstart = false;

// Variablen für Echtzeit-Tracking
unsigned long lastTimeT1 = 0;
unsigned long lastTimeT2 = 0;
unsigned long lastTimeT3 = 0;
unsigned long lastTimeT4 = 0;

void loop()
{
  lv_tick_inc(millis() - lastTick);
  lastTick = millis();
  lv_timer_handler();
  delay(10);
  ui_tick();
  if (pstart == false)
  {
    lv_label_set_text(objects.btn1l, projname1);
    lv_label_set_text(objects.btn2l, projname2);
    lv_label_set_text(objects.btn3l, projname3);
    lv_label_set_text(objects.btn4l, projname4);
    pstart = true;
  }
  // Echtzeit-Update für Variablen
  unsigned long currentTime = millis();

  if (t1activ)
  {
    t1 += (currentTime - lastTimeT1); // Add elapsed time in ms
    lastTimeT1 = currentTime;         // Update last timestamp
  }
  else
  {
    lastTimeT1 = currentTime; // Reset timestamp if not active
  }

  if (t2activ)
  {
    t2 += (currentTime - lastTimeT2); // Add elapsed time in ms (scaled by factor)
    lastTimeT2 = currentTime;
  }
  else
  {
    lastTimeT2 = currentTime;
  }

  if (t3activ)
  {
    t3 += (currentTime - lastTimeT3);
    lastTimeT3 = currentTime;
  }
  else
  {
    lastTimeT3 = currentTime;
  }

  if (t4activ)
  {
    t4 += (currentTime - lastTimeT4);
    lastTimeT4 = currentTime;
  }
  else
  {
    lastTimeT4 = currentTime;
  }

  // Labels aktualisieren
  auto formatTime = [](unsigned long ms) -> String
  {
    unsigned long seconds = ms / 1000;
    unsigned long minutes = seconds / 60;
    unsigned long hours = minutes / 60;
    seconds %= 60;
    minutes %= 60;
    char buffer[12];
    sprintf(buffer, "%02lu:%02lu:%02lu", hours, minutes, seconds);
    return String(buffer);
  };

  lv_label_set_text(objects.lbl1, formatTime(t1).c_str());
  lv_label_set_text(objects.lbl2, formatTime(t2).c_str());
  lv_label_set_text(objects.lbl3, formatTime(t3).c_str());
  lv_label_set_text(objects.lbl4, formatTime(t4).c_str());
  if (t1activ)
{
    lv_obj_set_style_bg_color(objects.btn1, BTN_ACTIVE_COLOR, LV_PART_MAIN);
    lv_obj_set_style_bg_color(objects.btn2, BTN_INACTIVE_COLOR, LV_PART_MAIN);
    lv_obj_set_style_bg_color(objects.btn3, BTN_INACTIVE_COLOR, LV_PART_MAIN);
    lv_obj_set_style_bg_color(objects.btn4, BTN_INACTIVE_COLOR, LV_PART_MAIN);
}
else if (t2activ)
{
    lv_obj_set_style_bg_color(objects.btn1, BTN_INACTIVE_COLOR, LV_PART_MAIN);
    lv_obj_set_style_bg_color(objects.btn2, BTN_ACTIVE_COLOR, LV_PART_MAIN);
    lv_obj_set_style_bg_color(objects.btn3, BTN_INACTIVE_COLOR, LV_PART_MAIN);
    lv_obj_set_style_bg_color(objects.btn4, BTN_INACTIVE_COLOR, LV_PART_MAIN);
}
else if (t3activ)
{
    lv_obj_set_style_bg_color(objects.btn1, BTN_INACTIVE_COLOR, LV_PART_MAIN);
    lv_obj_set_style_bg_color(objects.btn2, BTN_INACTIVE_COLOR, LV_PART_MAIN);
    lv_obj_set_style_bg_color(objects.btn3, BTN_ACTIVE_COLOR, LV_PART_MAIN);
    lv_obj_set_style_bg_color(objects.btn4, BTN_INACTIVE_COLOR, LV_PART_MAIN);
}
else if (t4activ)
{
    lv_obj_set_style_bg_color(objects.btn1, BTN_INACTIVE_COLOR, LV_PART_MAIN);
    lv_obj_set_style_bg_color(objects.btn2, BTN_INACTIVE_COLOR, LV_PART_MAIN);
    lv_obj_set_style_bg_color(objects.btn3, BTN_INACTIVE_COLOR, LV_PART_MAIN);
    lv_obj_set_style_bg_color(objects.btn4, BTN_ACTIVE_COLOR, LV_PART_MAIN);
}
else
{
    // Falls kein Timer aktiv ist, alle Buttons auf inaktive Farbe setzen
    lv_obj_set_style_bg_color(objects.btn1, BTN_INACTIVE_COLOR, LV_PART_MAIN);
    lv_obj_set_style_bg_color(objects.btn2, BTN_INACTIVE_COLOR, LV_PART_MAIN);
    lv_obj_set_style_bg_color(objects.btn3, BTN_INACTIVE_COLOR, LV_PART_MAIN);
    lv_obj_set_style_bg_color(objects.btn4, BTN_INACTIVE_COLOR, LV_PART_MAIN);
}

  if (g_eez_event_is_available == true)
  {
    lv_obj_t *obj = lv_event_get_target_obj(&g_eez_event);
    Serial.printf("Received event from obj: %u\n", obj);
    g_eez_event_is_available = false;

    if (obj == objects.btn1)
    {
      t1activ = !t1activ;
      t2activ = t3activ = t4activ = false;
    }
    if (obj == objects.btn2)
    {
      t2activ = !t2activ;
      t1activ = t3activ = t4activ = false;
    }
    if (obj == objects.btn3)
    {
      t3activ = !t3activ;
      t1activ = t2activ = t4activ = false;
    }
    if (obj == objects.btn4)
    {
      t4activ = !t4activ;
      t1activ = t2activ = t3activ = false;
    }
    if (obj == objects.btns1)
    {
      lv_scr_load(objects.scrch1);
      delay(100);
    }
    if (obj == objects.btnexit)
    {
      lv_scr_load(objects.main);
      delay(100);
    }

    if (obj == objects.txt1)
    {

      const char *text = lv_textarea_get_text(objects.txtfeld);

      preferences.putString("projname1", text);

      lv_label_set_text(objects.btn1l, text);
      lv_scr_load(objects.main);
      delay(100);
    }
    if (obj == objects.txt2)
    {

      const char *text = lv_textarea_get_text(objects.txtfeld);
      preferences.putString("projname2", text);
      lv_label_set_text(objects.btn2l, text);
      lv_scr_load(objects.main);
      delay(100);
    }
    if (obj == objects.txt3)
    {

      const char *text = lv_textarea_get_text(objects.txtfeld);
      preferences.putString("projname3", text);
      lv_label_set_text(objects.btn3l, text);
      lv_scr_load(objects.main);
      delay(100);
    }
    if (obj == objects.txt4)
    {

      const char *text = lv_textarea_get_text(objects.txtfeld);
      preferences.putString("projname4", text);
      lv_label_set_text(objects.btn4l, text);
      preferences.putString(text, projname1);
      lv_scr_load(objects.main);
      delay(100);
    }
  }

  if (lv_screen_active() == objects.main)
  {
    int potValCur = analogRead(ANALOG_PIN_0); // Get the current raw value.
    if (potValCur == 0)
    {

      intPotValPrev = potValCur;
    }

    else if (abs(potValCur - Valbtn1) < valfluk && (abs(potValCur - intPotValPrev) > valfluk))
    {

      // Serial.printf("BT1: %ld\n", potValCur);

      t1activ = !t1activ;
      t2activ = t3activ = t4activ = false;

      intPotValPrev = potValCur;
    }
    else if (abs(potValCur - Valbtn2) < valfluk && (abs(potValCur - intPotValPrev) > valfluk))
    {

      // Serial.printf("BT2: %ld\n", potValCur);

      t2activ = !t2activ;
      t1activ = t3activ = t4activ = false;
      intPotValPrev = potValCur;
    }
    else if (abs(potValCur - Valbtn3) < valfluk && (abs(potValCur - intPotValPrev) > valfluk))
    {

      //  Serial.printf("BTN3: %ld\n", potValCur);

      t3activ = !t3activ;
      t1activ = t2activ = t4activ = false;
      intPotValPrev = potValCur;
    }
    else if (abs(potValCur - Valbtn4) < valfluk && (abs(potValCur - intPotValPrev) > valfluk))
    {

      // Serial.printf("BTN4: %ld\n", potValCur);
      t4activ = !t4activ;
      t2activ = t3activ = t1activ = false;

      intPotValPrev = potValCur;
    }

  } // ========== ADC input END   ==========
}