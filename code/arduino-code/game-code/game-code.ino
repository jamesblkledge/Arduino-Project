int led_list[4];
int button_list[4];
int check_list[4];

int flash_rate = 800;

int button_count, cycle_count, flash_count, correct_count = 0;
int state_one, last_one, state_two, last_two, state_three, last_three, state_four, last_four = 0;

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

int button_state_map[4][3]{

  {button_one, state_one, last_one},
  {button_two, state_two, last_two},
  {button_three, state_three, last_three},
  {button_four, state_four, last_four}

};

int process_button(){

  button_state_map[0][1] = digitalRead(button_state_map[0][0]);
  button_state_map[1][1] = digitalRead(button_state_map[1][0]);
  button_state_map[2][1] = digitalRead(button_state_map[2][0]);
  button_state_map[3][1] = digitalRead(button_state_map[3][0]);

  if (button_state_map[0][1] != button_state_map[0][2]){
    if (button_state_map[0][1] == HIGH){
      check_list[button_count] = button_state_map[0][0]; button_count++;
    }
    delay(50);
  }
  button_state_map[0][2] = button_state_map[0][1];

  if (button_state_map[1][1] != button_state_map[1][2]){
    if (button_state_map[1][1] == HIGH){
      check_list[button_count] = button_state_map[1][0]; button_count++;
    }
    delay(50);
  }
  button_state_map[1][2] = button_state_map[1][1];

  if (button_state_map[2][1] != button_state_map[2][2]){
    if (button_state_map[2][1] == HIGH){
      check_list[button_count] = button_state_map[2][0]; button_count++;
    }
    delay(50);
  }
  button_state_map[2][2] = button_state_map[2][1];

  if (button_state_map[3][1] != button_state_map[3][2]){
    if (button_state_map[3][1] == HIGH){
      check_list[button_count] = button_state_map[3][0]; button_count++;
    }
    delay(50);
  }
  button_state_map[3][2] = button_state_map[3][1];

}

int find_index_led(const int list[2][2], int size, int value){

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

  while (flash_count == 0){ 

    shuffle_led_list();

    for (int i = 0; i < size_of_button; i++){
      button_list[i] = led_button[find_index_led(led_button, size_of_led, led_list[i])][1];

      pinMode(led_list[i], OUTPUT);
    }

    delay(1000);

    for (int j = 0; j < size_of_led; j++){
      digitalWrite(led_list[j], HIGH);
      delay(flash_rate);
      digitalWrite(led_list[j], LOW);
    }

    flash_count++;

  }

  process_button();

  while (button_count == size_of_button){

    for (int i = 0; i < size_of_button; i++){
      if (button_list[i] == check_list[i]){
        cycle_count++;
      }
    }

    if (cycle_count < size_of_button){
      Serial.println(correct_count); exit(0);
    }

    correct_count++;

    for (int j = 0; j < size_of_led; j++){
      digitalWrite(led_button[j][0], HIGH);
    }

    delay(1000);

    for (int k = 0; k < size_of_led; k++){
      digitalWrite(led_button[k][0], LOW);
    }

    if (flash_rate > 150 && (correct_count & 1) != 0){
      flash_rate -= 100;
    }

    button_count -= button_count; cycle_count -= cycle_count; flash_count -= flash_count;

  }

}
