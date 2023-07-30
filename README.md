# Elite Security - IoT Smart Shop Security System

Embedded System Image

![Elite Security](https://github.com/tejaspalyekar/Elite-Security/raw/main/images/elite_security.png)

Android App Image(Only Main Control Panel)

![Elite Security](https://github.com/tejaspalyekar/Elite-Security/raw/main/images/mobile_ui.png)
## Table of Contents

- [Project Description](#project-description)
- [Features](#features)
- [Getting Started](#getting-started)
- [Hardware Requirements](#hardware-requirements)
- [Software Requirements](#software-requirements)
- [Installation](#installation)
- [Usage](#usage)
- [Contributing](#contributing)
- [License](#license)

## Project Description

Elite Security is an innovative IoT-based Smart Shop Security System developed to address the rising instances of theft and robbery in small-scale businesses, especially during the pandemic. The project aims to provide affordable and advanced security solutions for small businesses to protect their assets and prevent robbery.

The system is designed to continuously monitor the shop premises and employs real-time alert mechanisms to immediately notify the shop owner or security personnel in case of any unauthorized access or suspicious activities. The alert notifications are sent to a mobile application built using Android Studio, ensuring that the shop owner can be informed about the situation from anywhere.

The core components of the Elite Security system include ESP8266 (a Wi-Fi enabled microcontroller), various sensors (e.g., motion sensors, door/window sensors), and alarms. These components work together to detect and respond to potential security breaches effectively.

The project provides a cost-effective and scalable solution, making it accessible to small businesses with limited budgets. It emphasizes simplicity in both hardware and software to ensure easy implementation and management for users.

## Features

- Real-time monitoring of the shop premises
- Mobile application with alert notifications, User Authentication, Helpline Support and user Profil
- Integration of ESP8266, sensors, and alarms for security detection
- Cost-effective and scalable solution
- Seamless hardware-to-app updates for continuous security coverage

## Getting Started

To get started with Elite Security, follow the installation instructions provided in the next section. You will need to gather the required hardware and software components before setting up the system.

## Hardware Requirements

1. ESP8266 (NodeMCU) microcontroller
2. Motion sensors (PIR sensors)
3. Door/window sensors (reed switches)
4. Buzzer or alarm
5. Wi-Fi connection for the ESP8266

## Software Requirements

1. Arduino IDE
2. Android Studio (for mobile application)

## Installation

1. Clone this GitHub repository to your local machine using the following command:

   ```bash
   git clone https://github.com/tejaspalyekar/Elite-Security.git
   ```

2. Set up the Arduino IDE and open the code provided in the `arduino` directory.

3. Connect the ESP8266 and sensors according to the wiring instructions provided in the Arduino code comments.

4. Upload the code to the ESP8266 using the Arduino IDE.

5. Open the Android Studio and import the mobile application project from the `android_app` directory.

6. Build and install the mobile application on your Android device.

## Usage

1. Power up the ESP8266 and sensors.

2. Launch the mobile application on your Android device.

3. The system will start monitoring the shop premises.

4. If any suspicious activity is detected, the mobile application will receive an alert notification.

5. Take appropriate actions based on the received alerts.

## Contributing

Thank you for considering contributing to the Elite Security project! If you have any suggestions, bug reports, or feature requests, please feel free to open an issue on the GitHub repository. We welcome any contributions that can enhance the project and make it even more reliable and secure.

## License

This project is licensed under the [MIT License](https://opensource.org/licenses/MIT). You are free to use, modify, and distribute the code as long as you retain the original license text.
