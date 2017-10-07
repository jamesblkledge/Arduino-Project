/*

                  _       _               __  __                                    _____
    /\           | |     (_)             |  \/  |                                  / ____|
   /  \   _ __ __| |_   _ _ _ __   ___   | \  / | ___ _ __ ___   ___  _ __ _   _  | |  __  __ _ _ __ ___   ___
  / /\ \ | '__/ _` | | | | | '_ \ / _ \  | |\/| |/ _ \ '_ ` _ \ / _ \| '__| | | | | | |_ |/ _` | '_ ` _ \ / _ \
 / ____ \| | | (_| | |_| | | | | | (_) | | |  | |  __/ | | | | | (_) | |  | |_| | | |__| | (_| | | | | | |  __/
/_/    \_\_|  \__,_|\__,_|_|_| |_|\___/  |_|  |_|\___|_| |_| |_|\___/|_|   \__, |  \_____|\__,_|_| |_| |_|\___|
                                                                           |___/|


                                       CODE WRITTEN BY JAMES BLACKLEDGE.
                                   ADA, NATIONAL COLLEGE FOR DIGITAL SKILLS.


*/

/* VARIABLE DECLARATION */

int led_list[4];
int button_list[4];
int check_list[4];

int flash_rate = 750;

int button_count = 0;
int cycle_count = 0;
int flash_count = 0;
int correct_count = 0;

const size_t size_of_led = sizeof(led_list) / sizeof(led_list[0]);
const size_t size_of_button = sizeof(button_list) / sizeof(button_list[0]);

/* VARIABLE DECLARATION */

// 2D ARRAY - TO MAP EACH LED PIN TO ITS CORRESPONDING BUTTON PIN //

const int led_button[4][2] {

  {2, 8}, {3, 9}, {4, 10}, {5, 11}

};

// 2D ARRAY - TO MAP EACH BUTTON PIN TO ITS CORRESPONDING STATE AND LAST STATE //

int button_state_map[4][3] {

  {8, 0, 0}, {9, 0, 0}, {10, 0, 0}, {11, 0, 0}

};

int process_button() {

  // READING THE BUTTON STATE FROM THE DESIRED PIN //

  for (int i = 0; i < size_of_button; i++) {
    button_state_map[i][1] = digitalRead(button_state_map[i][0]);
  }

  // DEPENDING ON WHAT BUTTON IS PRESSED, APPEND THAT BUTTON TO THE ARRAY 'check_list' //

  if (button_state_map[0][1] != button_state_map[0][2]) {
    if (button_state_map[0][1] == HIGH) {
      check_list[button_count] = button_state_map[0][0]; button_count++;
    }
    delay(50);
  }
  button_state_map[0][2] = button_state_map[0][1];

  if (button_state_map[1][1] != button_state_map[1][2]) {
    if (button_state_map[1][1] == HIGH) {
      check_list[button_count] = button_state_map[1][0]; button_count++;
    }
    delay(50);
  }
  button_state_map[1][2] = button_state_map[1][1];

  if (button_state_map[2][1] != button_state_map[2][2]) {
    if (button_state_map[2][1] == HIGH) {
      check_list[button_count] = button_state_map[2][0]; button_count++;
    }
    delay(50);
  }
  button_state_map[2][2] = button_state_map[2][1];

  if (button_state_map[3][1] != button_state_map[3][2]) {
    if (button_state_map[3][1] == HIGH) {
      check_list[button_count] = button_state_map[3][0]; button_count++;
    }
    delay(50);
  }
  button_state_map[3][2] = button_state_map[3][1];

}

// FUNCTION TO FIND LIST INDEX GIVEN A VALUE - TO MAP LED TO BUTTON //

int find_index_led(const int list[4][2], int size, int value) {

  int index = 0;

  while (index < size && list[index][0] != value) index++;
  return (index == size ? -1 : index);

}

// FUNCTION TO SHUFFLE THE LED LIST - MAKE THE LEDs FLASH IN A RANDOM ORDER //

int shuffle_led_list() {

  for (size_t i = 0; i < size_of_led; i++) {
    size_t j = random(0, size_of_led);

    int k = led_list[i];
    led_list[i] = led_list[j];
    led_list[j] = k;

    randomSeed(analogRead(0));
  }

}

void setup() {

  // INITIALISE SERIAL BAUD RATE //

  Serial.begin(9600);

  // POPULATE 'led_list' AND 'button_list' WITH PIN NUMBERS. SET ALL BUTTON PINS AS AN INPUT //

  for (int i = 0; i < size_of_led; i++) {
    led_list[i] = led_button[i][0];

    button_list[i] = led_button[i][1];
    pinMode(button_list[i], INPUT);
  }

}

void loop() {

  while (flash_count == 0) {

    // CALL THE 'shuffle_led_list' FUNCTION //

    shuffle_led_list();

    // POPULATE 'button_list' WITH PIN NUMBERS, RESPECTIVE TO THE ORDER IN WHICH THE LEDs FLASHED. SET ALL LED PINS AS AN OUTPUT //

    for (int i = 0; i < size_of_button; i++) {
      button_list[i] = led_button[find_index_led(led_button, size_of_led, led_list[i])][1];

      pinMode(led_list[i], OUTPUT);
    }

    // WAIT 1 SECOND //

    delay(1000);

    // FLASH THE LEDs //

    for (int j = 0; j < size_of_led; j++) {
      digitalWrite(led_list[j], HIGH);
      delay(flash_rate);
      digitalWrite(led_list[j], LOW);
    }

    flash_count++;

  }

  // CALL THE 'process_button' FUNCTION //

  process_button();

  while (button_count == size_of_button) {

    // IF THE LIST INDEXES ARE EQUAL FOR BOTH LISTS, INCREMENT 'cycle_count' //

    for (int k = 0; k < size_of_button; k++) {
      if (button_list[k] == check_list[k]) {
        cycle_count++;
      }
    }

    // IF PLAYER INPUTTED WRONG COMBONATION, FLASH LAST LED 3 TIMES AND DISPLAY THE SCORE (IN THE SERIAL MONITOR) //

    if (cycle_count < size_of_button) {
      for (int l = 0; l < 3; l++) {
        digitalWrite(led_button[3][0], HIGH);
        delay(200);
        digitalWrite(led_button[3][0], LOW);
        delay(200);
      }

      Serial.print("\nFINAL SCORE >> " + String(correct_count)); delay(1000);
      exit(0);
    }

    correct_count++;

    // IF PLAYER INPUTTED CORRECT COMBONATION, FLASH ALL LEDs //

    for (int m = 0; m < size_of_led; m++) {
      digitalWrite(led_button[m][0], HIGH);
    }

    Serial.print("CURRENT SCORE >> " + String(correct_count) + "\n"); delay(1000);

    for (int n = 0; n < size_of_led; n++) {
      digitalWrite(led_button[n][0], LOW);
    }

    // DECREMENT 'flash_rate' BY 75 EVERY SECOND CYCLE WHILE 'flash_rate' > 150 //

    if (correct_count > 1) {
      if (flash_rate > 150 && (correct_count & 1) != 0) {
        flash_rate -= 75;
      }
    }

    // RESET KEY VARIABLES //

    button_count -= button_count; cycle_count -= cycle_count; flash_count -= flash_count;

  }

}
