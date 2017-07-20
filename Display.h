#ifndef _DISPLAY_H_
#define _DISPLAY_H_

// LED definitions
#include "Arduino.h"
#include "LEDMatrix64.h"
#include "Queuer.h"

#define PREWIDTH  8
#define WIDTH   64
#define HEIGHT  32

#define RowA A0
#define RowB A1
#define RowC A2
#define RowD A3
#define STB 6
#define CLK 7
#define OE 8
#define Red 9
#define Green 10

class Display{
public:
  Display();
  void Init();
  void Refresh();
  void LoadMsg(int row, String msg);
  void ScrollMatrix();

private:
  void Scan();
  void AddNumbersToBuffer();
  void AddQueueToScreen(int row);

  bool IsInterval(uint32_t lastCountTime);
  int SCROLLDELAY;
  
  LEDMatrix64* matrix;

  Queuer* GetQueuer(int row);
  
  Queuer* row1;
  Queuer* row2;
  Queuer* row3;
  Queuer* row4;
};

#endif
