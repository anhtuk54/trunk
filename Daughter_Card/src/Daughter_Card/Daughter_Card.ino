#include "SPISlave.h"
#include "circular_buffer.h"
#include <SPI.h>


enum CMD {
  CMD_ECHO   = 0x00,
  CMD_WR_PIN = 0x01,
  CMD_RD_PIN = 0x02,
  CMD_WR_PWM = 0x03,
  CMD_MAX=0x09
};

#define TEST

#ifdef TEST
CircularBuffer<uint16_t> cBuf;
#endif

union uSpiPayload
{
  uint16_t raw;
  struct sSpiPayload {
    uint8_t cmd   :3;
    uint8_t pin   :6;
    uint8_t value :7;
  } st __packed;
};

void write_to_io(const uint32_t &pin,const uint32_t &val)
{
  digitalWrite(pin,val);
}

uint32_t read_from_io(const uint32_t &pin)
{
  return digitalRead(pin);
}

void xfer_to_master(const uint16_t data)
{
  // load data to transmit register
  REG_SPI0_TDR = data;
  
  // trigger interrupt to notify read
}

void handler()
{ 
  uSpiPayload payload;
  payload.raw  = REG_SPI0_RDR;

#ifdef TEST
  // hooking data for printing later
  cBuf.put2(payload.raw);
#endif
  // processing data
  if (payload.st.cmd==CMD_WR_PIN) {
    write_to_io((uint32_t)(payload.st.pin), (uint32_t)(payload.st.value));
  }
  else if (payload.st.cmd == CMD_RD_PIN) {
  }
}

void setup()
{
  // Setup Serial for logging
  Serial.begin(115200);
  Serial.println("Setting up SPI...");

  pinMode(13,OUTPUT);
  digitalWrite(13,HIGH);
  SPISlave.begin(&handler);

	Serial.println("Done");
}

void loop() {
  // put your main code here, to run repeatedly:
  // show if error

  // should do nothing, interrupt will handle all things.
#ifdef TEST
  if ( !cBuf.empty()) {
    // Serial.print("Data: ");
    uSpiPayload payload;
    payload.raw = cBuf.get();
    Serial.println( payload.raw,HEX);
    Serial.println( payload.st.cmd,BIN);
    Serial.println( payload.st.pin,BIN);
    Serial.println( payload.st.value,BIN);
    // Serial.print(" ");
  }
#endif
}
