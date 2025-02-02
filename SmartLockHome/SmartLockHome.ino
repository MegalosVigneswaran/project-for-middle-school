#include <Keypad.h>
#include <LiquidCrystal.h>
#include <Servo.h>

// Define the password
const String correctPassword = "1899";
String enteredPassword = "";

// Define keypad rows and columns
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {7, 6, 5, 4}; // Connect to the row pins of the keypad
byte colPins[COLS] = {3, 2, A4, A5}; // Connect to the column pins of the keypad

// Create Keypad instance
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// Define LCD pins
int attempt = 0;
const int rs = 12, en = 11, d4 = A0, d5 = A1, d6 = A2, d7 = A3;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Create Servo objects
Servo servo1;
Servo servo2;

// Function to display centered text on the LCD
void displayCenteredText(const String& text, int row) {
  lcd.clear();
  int padding = (16 - text.length()) / 2; // Calculate padding for centering
  lcd.setCursor(padding, row);
  lcd.print(text);
}

void setup() {
  // Initialize serial monitor for monitoring
  Serial.begin(9600);
  
  // Initialize LCD
  lcd.begin(16, 2);
  displayCenteredText("Enter Password:", 0);

  // Attach servos to pins
  servo1.attach(10);
  servo2.attach(13);

  // Set initial servo positions
  servo1.write(0);
  servo2.write(90);
  
  // Monitor initial states on Serial
  Serial.println("System Initialized");
  Serial.println("Waiting for Password...");
}

void loop() {
  char key = keypad.getKey();

  if (key) {
    if (key == '#') { // '#' to submit the password
      lcd.clear();
      Serial.print("Entered Password: ");
      Serial.println(enteredPassword); // Print entered password to Serial Monitor

      if (enteredPassword == correctPassword) {
        displayCenteredText("Unlocked", 0);
        Serial.println("Password correct. Unlocking...");

        // Move servos
        servo1.write(90);
        servo2.write(0);
        delay(2000); // Wait for 2 seconds

        // Reset servo positions
        servo1.write(0);
        servo2.write(90);
        enteredPassword = ""; // Clear only after successful unlock

        Serial.println("Servos reset to initial positions.");
      } else {
        if(attempt = 3){
          enteredPassword = "";
          lcd.clear();
          displayCenteredText("3 Times Entered ", 0);
          displayCenteredText("Wrong Paddword", 1);
          for(int i = 30; i > 0 ; i--){
            lcd.clear();
            displayCenteredText("Wait "+String(i)+" seconds", 0);
            displayCenteredText("Enter Password:", 0);
            delay(1000);
          }
        }else{
          enteredPassword = "";
          attempt = attempt+1;
          displayCenteredText("Wrong Password", 0);
          Serial.println("Wrong password entered.");
          delay(2000); // Show error for 2 seconds
          lcd.clear();
          displayCenteredText("Enter Password:", 0);
        }
      }
    } else if (key == '*') { // '*' to clear the input
      enteredPassword = "";
      lcd.clear();
      displayCenteredText("Enter Password:", 0);
      Serial.println("Password input cleared.");
    } else { // Add key to the entered password
      enteredPassword += key;
      lcd.setCursor(0, 1);

      // Mask input with '*' and center it dynamically
      String maskedPassword = "";
      for (int i = 0; i < enteredPassword.length(); i++) {
        maskedPassword += "*"; // Append '*' for each character
      }

      int padding = (16 - maskedPassword.length()) / 2;
      lcd.setCursor(padding, 1);
      lcd.print(maskedPassword);
    }
  }
}
