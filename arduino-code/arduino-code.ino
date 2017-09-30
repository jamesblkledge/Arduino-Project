int led_list[4];
int button_list[4];
int check_button[4];

int flash_rate = 700;
int button_count, cycle_count, state_one, state_two, state_three, state_four = 0;

const size_t size_of_led = sizeof(led_list) / sizeof(led_list[0]);
const size_t size_of_button = sizeof(button_list) / sizeof(button_list[0]);

const int led_one = 2; const int button_one = 8;
const int led_two = 3; const int button_two = 9;
const int led_three = 4; const int button_three = 10;
const int led_four = 5; const int button_four = 11;

const int led_button[4][2]{

  {led_one, button_one},
  {led_two, button_two},
  {led_three, button_three},
  {led_four, button_four}

};

int button_state_map[4][2]{

  {button_one, state_one},
  {button_two, state_two},
  {button_three, state_three},
  {button_four, state_four}

};

int find_index_led(const int list[4][2], int size, int value){

  int index = 0;

  while (index < size && list[index][0] != value) index++;
  return (index == size ? -1 : index);

}

int shuffle_led_list(){

  for (size_t i = 0; i < size_of_led; i++){
    size_t j = random(0, size_of_led);

    int r = led_list[i];
    led_list[i] = led_list[j];
    led_list[j] = r;

    randomSeed(analogRead(0));
  }

}

void setup() {

  Serial.begin(115200);

  for (int i = 0; i < size_of_led; i++){
    led_list[i] = led_button[i][0];

    button_list[i] = led_button[i][1];
    pinMode(button_list[i], INPUT);
  }

}

void loop() {

  delay(2500);
  
  shuffle_led_list();

  for (int i = 0; i < size_of_button; i++){
    button_list[i] = led_button[find_index_led(led_button, size_of_led, led_list[i])][1];

    button_state_map[i][1] = digitalRead(button_state_map[i][0]);

    pinMode(led_list[i], OUTPUT);
  }

  for (int j = 0; j < size_of_led; j++){
    digitalWrite(led_list[j], HIGH);
    delay(flash_rate);
    digitalWrite(led_list[j], LOW);
  }

  while (button_count < size_of_button){
    for (int k = 0; k < size_of_button; k++){
      if (button_state_map[k][0] == HIGH){
        check_button[k] = button_state_map[k][0];
        button_count++;
      }
    }
  }

  while (cycle_count < size_of_button){
    for (int l = 0; l < size_of_button; l++){
      if (button_list[l] == check_button[l]){
        cycle_count++; flash_rate -= 50;
      }
    }
    if (cycle_count != size_of_button){
      Serial.println("GAME OVER"); exit(0);
    }
  }

  for (int m = 0; m < size_of_led; m++){
    digitalWrite(led_button[m][0], HIGH);
  }

  delay(1000);

  for (int n = 0; n < size_of_led; n++){
    digitalWrite(led_button[n][0], LOW);
  }
  
}
