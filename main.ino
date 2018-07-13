/*
 * Morse code in arduino.
 */

int light = 13; //Pin with the light

int durationTime = 250; //Duration of pulses

void setup() {
  Serial.begin(9600);
  pinMode(light, OUTPUT);
  while(!Serial) { }
}

void loop() {
  if(Serial.available() > 0) {
    String message = Serial.readString();
    if(testMessage(message))
      messageParser(message);
    else
      Serial.println("Message can't be sent, there is invalid characters!");
  }
}

bool testMessage(String message) {
  int pos = 0;
  bool isOk = true;
  do {
    switch(message.charAt(pos)) {
      case 'A': case 'a': case 'B': case 'b': case 'C': case 'c':
      case 'D': case 'd': case 'E': case 'e': case 'F': case 'f':
      case 'G': case 'g': case 'H': case 'h': case 'I': case 'i':
      case 'J': case 'j': case 'K': case 'k': case 'L': case 'l':
      case 'M': case 'm': case 'N': case 'n': case 'O': case 'o':
      case 'P': case 'p': case 'Q': case 'q': case 'R': case 'r':
      case 'S': case 's': case 'T': case 't': case 'U': case 'u':
      case 'V': case 'v': case 'X': case 'x': case 'Y': case 'y':
      case 'W': case 'w': case 'Z': case 'z': case '1': case '2':
      case '3': case '4': case '5': case '6': case '7': case '8':
      case '9': case '0': case '.': case ',': case '?': case '\'':
      case '!': case '/': case '(': case ')': case '&': case ':':
      case ';': case '=': case '-': case '_': case '$': case '@':
      case ' ': break;
      default: isOk = false;
    }
    pos++;
  } while(pos < message.length());
  return isOk;
}

void messageParser(String message) {
  Serial.println("Message to be sent: " + message);
  int pos = 0;
  do {
    morseCode(message.charAt(pos));
    delay(3*durationTime);
    pos++;
  } while(pos < message.length());
  Serial.print("End of Message");
  luminousMessage(".-.-.");
}

void morseCode(char letter) {
  Serial.print("Sending letter ");
  Serial.print(letter);
  switch(letter) {
    case 'A': case 'a': luminousMessage(".-"); break;
    case 'B': case 'b': luminousMessage("-..."); break;
    case 'C': case 'c': luminousMessage("-.-."); break;
    case 'D': case 'd': luminousMessage("-.."); break;
    case 'E': case 'e': luminousMessage("."); break;
    case 'F': case 'f': luminousMessage("..-."); break;
    case 'G': case 'g': luminousMessage("--."); break;
    case 'H': case 'h': luminousMessage("...."); break;
    case 'I': case 'i': luminousMessage(".."); break;
    case 'J': case 'j': luminousMessage(".---"); break;
    case 'K': case 'k': luminousMessage("-.-"); break;
    case 'L': case 'l': luminousMessage(".-.."); break;
    case 'M': case 'm': luminousMessage("--"); break;
    case 'N': case 'n': luminousMessage("-."); break;
    case 'O': case 'o': luminousMessage("---"); break;
    case 'P': case 'p': luminousMessage(".--."); break;
    case 'Q': case 'q': luminousMessage("--.-"); break;
    case 'R': case 'r': luminousMessage(".-."); break;
    case 'S': case 's': luminousMessage("..."); break;
    case 'T': case 't': luminousMessage("-"); break;
    case 'U': case 'u': luminousMessage("..-"); break;
    case 'V': case 'v': luminousMessage("...-"); break;
    case 'X': case 'x': luminousMessage("-..-"); break;
    case 'Y': case 'y': luminousMessage("-.--"); break;
    case 'Z': case 'z': luminousMessage("--.."); break;
    case 'W': case 'w': luminousMessage(".--"); break;
    case '1': luminousMessage(".----"); break;
    case '2': luminousMessage("..---"); break;
    case '3': luminousMessage("...--"); break;
    case '4': luminousMessage("....-"); break;
    case '5': luminousMessage("....."); break;
    case '6': luminousMessage("-...."); break;
    case '7': luminousMessage("--..."); break;
    case '8': luminousMessage("---.."); break;
    case '9': luminousMessage("----."); break;
    case '0': luminousMessage("-----"); break;
    case '.': luminousMessage(".-.-.-"); break;
    case ',': luminousMessage("--..--"); break;
    case '?': luminousMessage("..--.."); break;
    case '\'': luminousMessage(".----."); break;
    case '!': luminousMessage("-.-.--"); break;
    case '/': luminousMessage("-..-."); break;
    case '(': luminousMessage("-.--."); break;
    case ')': luminousMessage("-.--.-"); break;
    case '&': luminousMessage(".-..."); break;
    case ':': luminousMessage("---..."); break;
    case ';': luminousMessage("-.-.-."); break;
    case '=': luminousMessage("-...-"); break;
    case '-': luminousMessage("-....-"); break;
    case '_': luminousMessage("..--.-"); break;
    case '"': luminousMessage(".-..-."); break;
    case '$': luminousMessage("...-..-"); break;
    case '@': luminousMessage(".--.-."); break;
    case ' ': delay(7*durationTime); Serial.println(); break;
  }
  
}

void luminousMessage(String code) {
  int pos = 0;
  Serial.println(" - Code: " + code);
  do {
    if(code.charAt(pos) == '.') {
      digitalWrite(light, HIGH);
      delay(durationTime);
    } else if(code.charAt(pos) == '-') {
      digitalWrite(light, HIGH);
      delay(3*durationTime);
    }
    digitalWrite(light, LOW);
    delay(durationTime);
    pos++;
  } while(pos < code.length());
}
