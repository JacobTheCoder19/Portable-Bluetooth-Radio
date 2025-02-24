<h2><em>💎 Key Features 💎</em></h2>
<div>
  🟩 <strong>Bluetooth Communication</strong><br>
  &emsp;🔸 The ESP32 is equipped with Bluetooth capabilities, allowing wireless communication with other devices.<br><br>
</div>
<div>
  🟩 <strong>Radio Control</strong><br>
  &emsp;🔸 The Arduino Mega controls a TEA5767 radio module, enabling users to tune into FM radio frequencies.<br><br>
</div>
<div>
  🟩 <strong>Rotary Encoder Input</strong><br>
  &emsp;🔸 Users can adjust the radio frequency using a rotary encoder, providing a tactile interface for frequency selection.<br><br>
</div>
<div>
  🟩 <strong>Sound Sensor Activation</strong><br>
  &emsp;🔸 The system can be toggled on and off using a sound sensor, allowing users to control the radio with a clap.<br><br>
</div>
<div>
  🟩 <strong>LCD Display</strong><br>
  &emsp;🔸 An LCD screen displays the current frequency, providing real-time feedback to the user.<br><br>
</div>

<h2><em>✨ Purpose / Inspiration ✨</em></h2>
&emsp;This project was inspired by me wanting to learn how to use the radio module I got as a gift. I also thought it would be cool to see if I could build my own smart radio from scratch. This project was awesome and I use it to listen to the radio all the time, especially since I can plug my headphones or speaker into it.

<h2><em>⚙️ How It Works ⚙️</em></h2>
&emsp;The project consists of two main components: the ESP32 and the Arduino Mega. The ESP32 handles Bluetooth communication, allowing users to send commands to the Arduino Mega. The Arduino Mega is responsible for controlling the TEA5767 radio module, which tunes into FM radio frequencies.

&emsp;In the ESP32 code, the BluetoothSerial library is used to establish a Bluetooth connection, and any received characters are sent to the Arduino Mega via Serial2. The Arduino Mega code initializes the radio and LCD display, and it continuously checks for input from the rotary encoder and sound sensor.

&emsp;When the rotary encoder is turned, the frequency is adjusted accordingly, and the new frequency is displayed on the LCD. The sound sensor allows users to toggle the radio on and off with a clap, adding an interactive element to the project. Additionally, the system can receive frequency commands via Bluetooth, enabling users to set the radio to specific frequencies wirelessly.
