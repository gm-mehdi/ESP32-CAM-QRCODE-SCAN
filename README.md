# Arduino QR Code Reader

This Arduino sketch utilizes an ESP32 board to read QR codes and perform actions based on the decoded data.

## Description

This code is an Arduino sketch that uses an ESP32 board to read QR codes and interact with a server to check and change the status of the QR codes. The sketch utilizes the ESP32QRCodeReader library for reading QR codes and the WiFi and HTTPClient libraries for network connectivity. The code continuously scans for QR codes, connects to a Wi-Fi network, and sends HTTP requests to the server for processing.

## Code Breakdown

The code is organized into the following sections:

1. Libraries: Lists the libraries used in the sketch.
2. Constant Definitions: Defines the constant values used in the code, including Wi-Fi credentials and server URLs.
3. QRCodeData Structure and Variables: Describes the structure and variables used for storing QR code data.
4. connectWifi() Function: Explains the function for establishing a Wi-Fi connection.
5. callWebhook() Function: Passing the reservation number as a string parameter. An HTTP GET request is made to the CHECK_STATUS URL with the reservation number as a query parameter.
6. If the statut is "true", indicating that the reservation exists, the code prints "OK" and proceeds to send another HTTP GET request to the CHANGE_STATUS URL with the reservation number.
7. setup() Function: Describes the setup function that initializes the sketch.
8. loop() Function: Explains the main loop function that continuously scans for QR codes and performs actions based on the decoded data.


## Importing Required Files

To import the required files, follow these steps:

1. Visit the [ESP32QRCodeReader GitHub repository](https://github.com/alvarowolfx/ESP32QRCodeReader/tree/master/include).
2. Download the `ESP32QRCodeReader.h` and `ESP32CameraPins.h` files from the repository.
3. Place the downloaded files in your Arduino project folder or in the appropriate include directory of your development environment.

## Usage

To use this code, follow these steps:

1. Set up your Arduino development environment and ensure you have the necessary ESP32 board.
2. Install the required libraries mentioned in the code.
3. Update the Wi-Fi credentials and server URLs in the Constant Definitions section.
4. Upload the sketch to your ESP32 board.
5. Open the serial monitor to view the QR code data and status messages.

Please note that the specific actions performed based on the QR code data are not described in the provided code snippet. You will need to refer to the server-side code or API documentation to understand the complete functionality and configure the necessary server endpoints and responses.

## License

This project is licensed under the [MIT License](LICENSE).
