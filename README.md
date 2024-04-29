# Embed

Embed is a tool designed to generate a server from a dropped folder (which will be the root directory for the server) that will serve the requested files to the client.
This application was made specifically to generate C++ code for ESP32(or any other microcontroller that can use WiFi) projects to simplify creating a server. The files are embeded in the server.

## Features

- Drag and drop a folder onto the application window to generate a server.

- Automatically embed files from the dropped folder into the generated server.

- Export the generated server files to a specified directory.

## Getting Started

To get started with Embed:

    Clone the repository to your local machine.

    Build the project using CMake.

    Run the built executable to launch the Embed application.

> **_NOTE:_**  Or you can use pre-built binaries for your system in [Releases](https://github.com/Byte-White/Embed/releases).

![draganddrop](https://github.com/Byte-White/Embed/assets/51212450/22e453ed-a5a3-4da1-8168-1f0e426f2645)

![export](https://github.com/Byte-White/Embed/assets/51212450/99567722-64e1-4516-85b3-978746726085)

Create your arduino project and use the generated server:

```C++
#include "EmbedServer.h"

const char* ssid = "";
const char* password = "";
const int port = 80;

EmbedServer server(port); 

void setup() 
{
  Serial.begin(115200);
  Serial.print("Connecting to ");
  Serial.println(ssid);

  // Connect to Wi-Fi network with SSID and password
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  server.begin();
}

void loop() 
{
  server.handleClient();
}
```

*This application is powered by Magma.*
