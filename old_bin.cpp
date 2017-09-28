#include <HashMap.h>

int led_flash[] = {};
int cor_button[] = {};

const int led_one = 1;
const int led_two = 2;
const int led_three = 3;
const int led_four = 4;

const int button_one = 5;
const int button_two = 6;
const int button_three = 7;
const int button_four = 8;

int button_state = 0;

int user_difficulty = 0;
int flash_rate = 0;

int correct = 0;
int wrong = 0;

const byte HASH_SIZE = 4;
HashType<int, int> hashRawArray[HASH_SIZE];
HashMap<int, int> led_button = HashMap<int, int>(hashRawArray, HASH_SIZE);

void setup() {

  led_button[0](led_one, button_one);
  led_button[1](led_two, button_two);
  led_button[2](led_three, button_three);
  led_button[3](led_four, button_four);

  pinMode(led_button, OUTPUT);
  
  led_button.debug();
}

void loop() {

  digitalWrite(led_button.getIndexOf(0), HIGH);
  
}
