# ES-STM32-ILI9341
Embedded System Projekt Schachbrett bewegenden Ball 

## Entwickler
Anna I.,<br />
Jens K.,<br />
Nadine W.<br />

## Erklärung
In diesem Projekt arbeiten wir mit dem Microcontroller STM32F429 Discovery von<br />
STMicroelectronics. Dieser besitzt ein ILI9341 LCD-Display, auf dem wir zwei Layer<br />
erstellen.<br />

Auf dem ersten Layer wird ein grün/rotes Schachbrett Muster erstellt und auf dem<br />
zweiten Layer ein hellblauer durchsichtiger Kreis, der auf dem Display kontinuierlich<br />
von links nach rechts wandert.<br />

Für dieses Projekt durften nur in der Vorlesung bereitgestellte Dateien, mit dem Grundcode,<br />
und die IDE μVision 5 von Keil verwendet werden.<br />
Zum Anfang wird der SPI initialisiert, um Befehle senden und das Display ansteuern<br />
zu können.<br />

Sobald dies erledigt ist, wird der LTDC initialisiert, der eine schnellere Verbindung<br />
gewährleistet und über diesen die Layer für das Display aufgebaut werden können.<br />
Danach werden die Formen für die verschiedenen Layer vom DMA2D gezeichnet<br />
und über den SDRam geladen. Die Bewegung des Kreises wird ermöglicht durch<br />
das Verschieben des oberen Layers.<br />

![](https://github.com/Isyaam/Images/blob/main/skizze.PNG)<br />

![](https://github.com/Isyaam/Images/blob/main/STM.PNG)<br />
