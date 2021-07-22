/*
SmartWatch
https://github.com/theRealc2c2/SmartWatch

Based on Bahn-for-Watchy
https://github.com/BraininaBowl/Bahn-for-Watchy

Face for Watchy watch
https://watchy.sqfmi.com
*/

#include <Watchy.h> //include the Watchy library
#include "Teko_Regular12pt7b.h"
#include "Teko_Regular50pt7b.h"
#include "icons.h"

class WatchFace : public Watchy { //inherit and extend Watchy class
  public:
    void drawWatchFace() { //override this method to customize how the watch face looks
      
      int16_t  x1, y1;
      uint16_t w, h;
      String textstring;
      bool light = true; // left this here if someone wanted to tweak for dark

      //resets step counter at midnight everyday
      if(currentTime.Hour == 00 && currentTime.Minute == 00) {
        sensor.resetStepCounter();
      }

      // ** DRAW **

      //drawbg
      display.fillScreen(light ? GxEPD_WHITE : GxEPD_BLACK);  
      display.setFont(&Teko_Regular50pt7b);
      display.setTextColor(light ? GxEPD_BLACK : GxEPD_WHITE);
      display.setTextWrap(false);

      //draw image
      display.drawBitmap(16,159, epd_bitmap_icons, 168, 41, GxEPD_BLACK);

      //draw time
      textstring = currentTime.Hour;
      textstring += ":";
      if (currentTime.Minute < 10) {
        textstring += "0";
      } else {
        textstring += "";
      }
      textstring += currentTime.Minute;
      display.getTextBounds(textstring, 0, 0, &x1, &y1, &w, &h);
      display.setCursor(100-w/2, 110);
      display.print(textstring);

      // draw battery
      display.fillRoundRect(16,16,34,12,4,light ? GxEPD_BLACK : GxEPD_WHITE);
      display.fillRoundRect(49,20,3,4,2,light ? GxEPD_BLACK : GxEPD_WHITE);
      display.fillRoundRect(18,18,30,8,3,light ? GxEPD_WHITE : GxEPD_BLACK);
      float batt = (getBatteryVoltage()-3.3)/0.9;
      if (batt > 0) {
       display.fillRoundRect(20,20,26*batt,4,2,light ? GxEPD_BLACK : GxEPD_WHITE);
      }										

      display.setFont(&Teko_Regular12pt7b);

      //draw steps
      textstring = sensor.getCounter();
      textstring += " steps";
      display.getTextBounds(textstring, 0, 0, &x1, &y1, &w, &h);
      display.setCursor(155-w/2, 145);
      display.setTextColor(light ? GxEPD_BLACK: GxEPD_WHITE);
      display.print(textstring);

      // draw date
      textstring = monthShortStr(currentTime.Month);
      textstring += " ";
      textstring += currentTime.Day;
      textstring += " ";
      textstring += currentTime.Year + 1970;
      display.getTextBounds(textstring, 0, 0, &x1, &y1, &w, &h);
      display.setCursor(50-w/2, 145);
      display.print(textstring);

    }

};


WatchFace m; //instantiate your watchface

void setup() {
  m.init(); //call init in setup
}

void loop() {
  // this should never run, Watchy deep sleeps after init();
}
