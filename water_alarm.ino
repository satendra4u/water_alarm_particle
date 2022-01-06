//
// Water Alarm
// By Nic Jansma
// http://nicj.net
// http://github.com/nicjansma/spark-water-alarm
//
//
// Constants
//
// pins
#define WATER_SENSOR D0
#define LED D5
#define TouchPin D4
//
// Config
//
// How long to wait before noting that the alarm has switched states -- this
// helps stop a super-sensitive sensor from ping-ponging back and forth a lot.
#define DEBOUNCE_SECONDS 5
#define Grove_Piezo_Buzzer D5
#define DEBOUNCE_SECONDS_TOUCH 10
//
// Vars
//
// the alarm state: 0 = off, 1 = on
int alarmState = 0;
// the last tiem we switched alarm states (ms since Unix epoch)
int lastStateSwitchTime = 0;
int lastStateSwitchTimeTouch = 0;

int  i = 0;//
// Functions
//
// Spark setup
void setup()
{
                // initialize our pins I/O
                pins_init();
                // tell the world we're online
                Spark.publish("online");

                pinMode(TouchPin, INPUT);
                // publish the alarm state variable
                Spark.variable("alarmState", &alarmState, INT);
                Spark.variable("i", &i, INT);
                pinMode(LED, OUTPUT);    //The Piezo Buzzer is an Output
}

// Spark loop
void loop()
    {



        if(isExposedToWater()) {

                if (alarmState == 0) {
                    // only alarm if we're past the debounce interval
                            int now = Time.now();
                            if (now - lastStateSwitchTime > DEBOUNCE_SECONDS) {
                                        alarmState = 1;
                                        lastStateSwitchTime = now;
                                        //digitalWrite(LED, HIGH);
                                        Spark.publish("alarm", "on", 60, PRIVATE);
                                        digitalWrite(Grove_Piezo_Buzzer, HIGH);
                                        //delay(2);
                                        //digitalWrite(Grove_Piezo_Buzzer, LOW);
                                        //delay(40);
                            }
                }

        }
        else {

                        if (alarmState == 1) {
                                    // only alarm if we're past the debounce interval
                                    int now = Time.now();
                                    if (now - lastStateSwitchTime > DEBOUNCE_SECONDS) {
                                            alarmState = 0;
                                            lastStateSwitchTime = now;
                                           // digitalWrite(LED, LOW);
                                            Spark.publish("alarm", "off", 60, PRIVATE);
                                            digitalWrite(Grove_Piezo_Buzzer, LOW);
                                    }
                        }

            }
    }

// initialize our pins
void pins_init()
{
  //      pinMode(LED, OUTPUT);
        pinMode(WATER_SENSOR, INPUT);
}


// determine if we're exposed to water or not
boolean isExposedToWater()
{
    if (digitalRead(WATER_SENSOR) == LOW) {

            i = 1;
            return true;
    }
    else
    {
            i = 0;
            return false;
    }
}
