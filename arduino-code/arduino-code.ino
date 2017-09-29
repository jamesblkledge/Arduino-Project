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

const led_button_map led_button[]{
  {led_one, button_one},
  {led_two, button_two},
  {led_three, button_three},
  {led_four, button_four}
};

int randomizeList() {

  unsigned char chosen[sizeof(led_list)];
  unsigned char i, j;

  for (i = 0; i < sizeof(led_list); i++){
    chosen[i] = 0;
  }

  randomSeed(analogRead(A0));

  for (i = 0; i < sizeof(led_list); i++){
    int r = random(sizeof(led_list) - i);
    for (j = 0; j <= r; j++){
      r += chosen[j];
    }
    chosen[r] = 1;
    led_list[i] = r;
  }
  
}

void setup() {
  
  for (int i = 0; i <= sizeof(led_list); i++){
    led_list[i] = led_button[i].led;
  }

  randomizeList();

  for (int j = 0; j <= sizeof(led_list); j++){
    pinMode(led_list[j], OUTPUT);
  }
  
}

void loop() {
  
  for (int i = 0; i <= sizeof(led_list); i++){
    digitalWrite(led_list[i], HIGH);
    delay(500);
    digitalWrite(led_list[i], LOW);
  }

  delay(1000000000);
}

