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
  switch(row) {
    case 1: row1->push(msg); break;
    case 2: row2->push(msg); break;
    case 3: row3->push(msg); break;
    case 4: row4->push(msg); break;
  }
}

bool Display::IsInterval(uint32_t lastCountTime) {
  return (millis() - lastCountTime) > SCROLLDELAY * 6;
}

void Display::AddNumbersToBuffer() {
  static uint32_t lastCountTime = millis() + 1000;
  if (IsInterval(lastCountTime)) {
    lastCountTime = millis();
    CallQueueMethods();
  }
}

// Adds a number to the prebuffer, which is off screen
void Display::CallQueueMethods() {
  if (row1->hasInQueue())
    matrix->printCharInBuffer(0, row1->rowNumber, row1->popQueueChar() - 32);
  if (row2->hasInQueue())
    matrix->printCharInBuffer(0, row2->rowNumber, row2->popQueueChar() - 32);
  if (row3->hasInQueue())
    matrix->printCharInBuffer(0, row3->rowNumber, row3->popQueueChar() - 32);
  if (row4->hasInQueue())
    matrix->printCharInBuffer(0, row4->rowNumber, row4->popQueueChar() - 32);
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


