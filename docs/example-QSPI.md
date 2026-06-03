---
icon: simple/arduino
---

## MX25L12833F
The Renesas-Arduino core includes a built-in [FATFileSystem library](https://github.com/arduino/ArduinoCore-renesas/tree/main/libraries/FATFilesystem) to control the QSPI flash memory. This example code demonstrates how to initialize the flash memory, a file is written, and data is read from the file. *Users can also find other example sketches in the **File** > **Examples** > **Storage** drop-down menu.*

??? code "`QSPI_Flash_FileSystem_Test.ino`"
	--8<-- "https://raw.githubusercontent.com/arduino/docs-content/main/content/hardware/04.pro/boards/portenta-c33/tutorials/user-manual/content.md:1365:1450"


--8<-- "https://raw.githubusercontent.com/arduino/docs-content/main/content/hardware/04.pro/boards/portenta-c33/tutorials/user-manual/content.md:1454:1454"

	??? code
		```cpp
		--8<-- "https://raw.githubusercontent.com/arduino/docs-content/main/content/hardware/04.pro/boards/portenta-c33/tutorials/user-manual/content.md:1401:1411"
		```

--8<-- "https://raw.githubusercontent.com/arduino/docs-content/main/content/hardware/04.pro/boards/portenta-c33/tutorials/user-manual/content.md:1455:1455"

	??? code
		```cpp
		--8<-- "https://raw.githubusercontent.com/arduino/docs-content/main/content/hardware/04.pro/boards/portenta-c33/tutorials/user-manual/content.md:1414:1428"
		```

--8<-- "https://raw.githubusercontent.com/arduino/docs-content/main/content/hardware/04.pro/boards/portenta-c33/tutorials/user-manual/content.md:1456:1456"

	??? code
		```cpp
		--8<-- "https://raw.githubusercontent.com/arduino/docs-content/main/content/hardware/04.pro/boards/portenta-c33/tutorials/user-manual/content.md:1430:1446"
		```
