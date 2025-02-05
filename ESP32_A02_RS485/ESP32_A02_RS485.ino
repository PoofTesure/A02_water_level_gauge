#define RX_PIN      16        //RX2 
#define TX_PIN      17        //TX2 
// #define LED_BUILTIN 25
/* macro definition -----------------------------------------------------------------------*/
#define SOFT_VERSION "MB-211123-A0"  //Software version

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <ModbusRTU.h>

LiquidCrystal_I2C lcd(0x27,20,4);
ModbusRTU mb;

class A02{
  public:
      A02(ModbusRTU &mb, uint8_t address){
        _mb = &mb;
        _address = address;
      }
      uint16_t readRange(){
        uint16_t value[1];
        uint16_t regAddress = 0x0101; 
        _mb->readHreg(_address,regAddress,value,1);
        while(_mb->slave()){
          _mb->task();
          delay(10);
        }
        return value[0];
      }
      bool setAddress(uint16_t after){
        uint16_t value = after;
        uint16_t regAddress = 0x0200; 
        _mb->writeHreg(_address,regAddress,value);
        while(_mb->slave()){
          _mb->task();
          //if(value == after) break;
          delay(10);
        }
        return value;
      }
  private:
    uint8_t _address;
    ModbusRTU *_mb;
};

A02 sensor_1(mb,0x01);
A02 sensor_2(mb,0x02);
A02 sensor_3(mb,0x03);
A02 sensor_4(mb,0x04);
A02 sensor_5(mb,0x05);

void setup()
{
    // put your setup code here, to run once:
    // pinMode( LED_BUILTIN, OUTPUT );
    Serial.begin( 9600 );
    Serial2.begin(9600, SERIAL_8N1, RX_PIN, TX_PIN);
    Serial.println( SOFT_VERSION );
    Wire.begin();
    lcd.init();                      // initialize the lcd 
    // Print a message to the LCD.
    lcd.backlight();
    mb.begin(&Serial2,5,false);
    mb.master();
    //sensor_1.setAddress(0x05);
}

void loop()
{

  uint16_t sensor_read = sensor_1.readRange()/10;
  uint16_t sensor2_read = sensor_2.readRange()/10;
  uint16_t sensor3_read = sensor_3.readRange()/10;
  uint16_t sensor4_read = sensor_4.readRange()/10;
  uint16_t sensor5_read = sensor_5.readRange()/10;
  Serial.print("Sensor 1 : ");
  Serial.println(sensor_read);
  Serial.print("Sensor 2 : ");
  Serial.println(sensor2_read);
  Serial.print("Sensor 3 : ");
  Serial.println(sensor3_read);
  Serial.print("Sensor 4 : ");
  Serial.println(sensor4_read);
  Serial.print("Sensor 5 : ");
  Serial.println(sensor5_read);

  lcd.clear();
  //lcd.setCursor(0,0);
  lcd.printf("F1: %dcm   F5: %dcm",sensor_read,sensor5_read);
  //delay(10);
  lcd.setCursor(0,1);
  lcd.printf("F2: %dcm",sensor2_read);
  //delay(10);
  lcd.setCursor(0,2);
  lcd.printf("F3: %dcm",sensor3_read);
  //delay(10);
  lcd.setCursor(0,3);
  lcd.printf("F4: %dcm",sensor4_read);

  //Serial.println(mb.slave());
  //mb.task();
  //Serial2.println("test");
  delay(500);
  
}
