int led_list[4];

const int led_one = 1;
const int led_two = 2;
const int led_three = 3;
const int led_four = 4;

const int button_one = 1;
const int button_two = 2;
const int button_three = 3;
const int button_four = 4;

typedef struct {

  int led;
  int button;
  
} led_button_map;

const led_button_map led_button[] {

  {led_one, button_one},
  {led_two, button_two},
  {led_three, button_three},
  {led_four, button_four}
  
};

void setup() {

  for (int i = 0; i <= 4; i++) {

    led_list[i] = led_button[i].led;
    
  }

  for (int j = 0; j <= 4; j++) {

    pinMode(led_list[j], OUTPUT);
    
  }
  
}

void loop() {

  for (int k = 0; k <= 4; k++) {

    digitalWrite(led_list[k], HIGH);
    
  }
  
}

