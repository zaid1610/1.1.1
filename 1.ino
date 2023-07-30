const int numParkingSpaces = 4;  // Define the number of parking spaces
const int triggerPin[numParkingSpaces] = {2, 4, 6, 8}; // Trigger pins for the ultrasonic sensors
const int echoPin[numParkingSpaces] = {3, 5, 7, 9};    // Echo pins for the ultrasonic sensors
const int ledPin[numParkingSpaces] = {10, 11, 12, 13}; // LED pins to indicate parking space status

const int vacantDistanceThreshold = 30; // Adjust this threshold based on your setup
bool parkingSpaceStatus[numParkingSpaces] = {false}; // Array to store parking space status (true for occupied, false for vacant)
void setup() {
  Serial.begin(9600);

  for (int i = 0; i < numParkingSpaces; i++) {
    pinMode(triggerPin[i], OUTPUT);
    pinMode(echoPin[i], INPUT);
    pinMode(ledPin[i], OUTPUT);
    digitalWrite(ledPin[i], LOW); // Turn off all LEDs initially
  }
}
float getDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  float distance = duration * 0.034 / 2;

  return distance;
}
void updateParkingStatus() {
  for (int i = 0; i < numParkingSpaces; i++) {
    float distance = getDistance(triggerPin[i], echoPin[i]);
    bool isOccupied = (distance < vacantDistanceThreshold);

    if (isOccupied != parkingSpaceStatus[i]) {
      parkingSpaceStatus[i] = isOccupied;
      digitalWrite(ledPin[i], isOccupied ? HIGH : LOW); // Turn on LED if parking space is occupied, otherwise turn it off
      Serial.print("Parking Space ");
      Serial.print(i + 1);
      Serial.println(isOccupied ? " Occupied" : " Vacant");
    }
  }
}
void loop() {
  updateParkingStatus();
  delay(1000); // Add a delay to avoid rapid status changes due to sensor noise
}
