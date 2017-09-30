#include <iostream>
using namespace std;

int led_list[4];
int button_list[4];

const size_t size_of_led = sizeof(led_list) / sizeof(led_list[0]);
const size_t size_of_button = sizeof(button_list) / sizeof(button_list[0]);

const int led_one = 2;
const int led_two = 3;
const int led_three = 4;
const int led_four = 5;

const int button_one = 8;
const int button_two = 9;
const int button_three = 10;
const int button_four = 11;

const int led_button[4][2]{
  
    {led_one, button_one},
    {led_two, button_two},
    {led_three, button_three},
    {led_four, button_four}
  
};

int find_index(const int list[4][2], int size, int value){

  int index = 0;

  while (index < size && list[index][0] != value) index++;
    
  return (index == size ? -1 : index);
  
}

int main(){
    
    for (int i = 0; i < size_of_led; i++){
        led_list[i] = led_button[i][0];
    }
    
    for (int j = 0; j < size_of_button; j++){
        button_list[j] = led_button[find_index(led_button, size_of_led, led_list[j])][1];
    }
    
    for (int k = 0; k < size_of_led; k++){
        
        cout << led_list[k];
        cout << button_list[k];
    }
    
    return 0;
}

void button_debug(){

    for (int l = 0; l < size_of_button; l++){
        pinMode(button_list[l], OUTPUT);
    }
    
    for (int j = 0; j < size_of_button; j++){
        digitalWrite(button_list[j], HIGH);
        delay(500);
        digitalWrite(button_list[j], LOW);
    }
    
}