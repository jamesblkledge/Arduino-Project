import random, time

led_flash = []
cor_button = []

led_one = 'a'
led_two = 'b'
led_three = 'c'
led_four = 'd'

button_one = 'w'
button_two = 'x'
button_three = 'y'
button_four = 'z'

user_difficulty = 0
flash_rate = 0

correct = 0
wrong = 0

led_button = {
    
    led_one: button_one, led_two: button_two, led_three: button_three, led_four: button_four
    
}

user_difficulty_map = {'1': 1, '2': 0.75, '3': 0.5, '4': 0.25}
user_difficulty = input('DIFFICULTY ({}) >> '.format(', '.join(list(level for level in user_difficulty_map.keys()))))

flash_rate = user_difficulty_map[user_difficulty]

led_list = list(led_button.keys())
random.shuffle(led_list)

shuffled_map = [(led, led_button[led]) for led in led_list]

for each_tuple in shuffled_map:

    led_flash.append(each_tuple[0])
    cor_button.append(each_tuple[1])

for each_led in led_flash:

    print('{}'.format(each_led))
    time.sleep(flash_rate)

while wrong != 3 and correct != 4:

    button_sequence = input('INPUT BUTTONS ({}) >> '.format(', '.join(button for button in sorted(cor_button))))

    button_sequence_list = button_sequence.split()

    for led_button_match in range(0, 4):
        
        if button_sequence_list[led_button_match] == cor_button[led_button_match]:
            correct += 1

    if correct == 4:
        print('\nGOOD\n')
        
    else:
        wrong += 1 ; correct -= correct

print('GAME FINISHED')