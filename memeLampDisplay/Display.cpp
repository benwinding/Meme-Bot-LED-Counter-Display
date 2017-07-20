#include "Display.h"

Display::Display() {
  this->SCROLLDELAY = 100;
  this->matrix = new LEDMatrix64(RowA, RowB, RowC, RowD, OE, Red, Green, STB, CLK);

  this->row1 = new Queuer(0);
  this->row2 = new Queuer(8);
  this->row3 = new Queuer(16);
  this->row4 = new Queuer(24);
}

void Display::Init() {
  matrix->begin();
  matrix->clear();
  matrix->reverse();
}

void Display::Refresh() {
  Scan();
  AddNumbersToBuffer();
}

void Display::Scan() {
  matrix->scan();
}

void Display::LoadMsg(int row, String msg) {
  GetQueuer(row)->push(msg);
}

Queuer* Display::GetQueuer(int row) {
  switch(row) {
    case 1: return row1;
    case 2: return row2;
    case 3: return row3;
    default: return row4;
  }
}

bool Display::IsInterval(uint32_t lastCountTime) {
  return (millis() - lastCountTime) > SCROLLDELAY * 6;
}

void Display::AddNumbersToBuffer() {
  static uint32_t lastCountTime = millis() + 1000;
  if (IsInterval(lastCountTime)) {
    lastCountTime = millis();
    AddQueueToScreen(1);
    AddQueueToScreen(2);
    AddQueueToScreen(3);
    AddQueueToScreen(4);
  }
}

// Adds a number to the prebuffer, which is off screen
void Display::AddQueueToScreen(int row) {
  Queuer* q = GetQueuer(row);
  if (q->hasInQueue())
    matrix->printCharInBuffer(0, q->rowNumber, q->popQueueChar() - 32);
}

// Scroll the matrix accross the screen and pull in from the prebuffer
void Display::ScrollMatrix() {
  static uint32_t lastCountTime = 0;

  // Run every 100 milliseconds
  if ((millis() - lastCountTime) > SCROLLDELAY) {
    lastCountTime = millis();
    matrix->shiftMatrixLeft();
  }
}


