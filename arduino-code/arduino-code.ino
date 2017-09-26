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

typedef struct {
  int led;
  int button;
} led_button_struct;

const led_button_struct led_button[] {
  {led_one, button_one},
  {led_two, button_two},
  {led_three, button_three},
  {led_four, button_four}
};

void setup() {

  for(int i = 0; i < sizeof(led_button)/sizeof(led_button_struct); ++i) {
    Serial.println(led_button[i].led);
  }

}
