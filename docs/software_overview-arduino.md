---
icon: simple/arduino
---

!!! tip
	For first-time users, who have never programmed before and are looking to use the Arduino IDE, we recommend beginning with the [SparkFun Inventor's Kit (SIK)](https://www.sparkfun.com/products/15631), which is designed to help users get started programming with the Arduino IDE.

Most users should already be familiar with the Arduino IDE and its use. However, for those of you who have never heard the name *Arduino* before, feel free to check out the [Arduino website](https://www.arduino.cc/en/Guide/HomePage). To get started with using the Arduino IDE, check out our tutorials below:


<div class="grid cards" markdown align="center">

-   <a href="https://learn.sparkfun.com/tutorials/50">
	<figure markdown>
	![What is an Arduino?](https://cdn.sparkfun.com/c/264-148/assets/3/b/6/e/b/512e66bece395f492b000000.jpg)
	</figure>

	---

	**What is an Arduino?**</a>

-   <a href="https://learn.sparkfun.com/tutorials/61">
	<figure markdown>
	![Installing the Arduino IDE](https://cdn.sparkfun.com/c/264-148/assets/learn_tutorials/6/1/arduinoThumb.jpg)
	</figure>

	---

	**Installing the Arduino IDE**</a>

-   <a href="https://learn.sparkfun.com/tutorials/1265">
	<figure markdown>
	![Installing Board Definitions in the Arduino IDE](https://cdn.sparkfun.com/c/264-148/assets/learn_tutorials/1/2/6/5/sparkfun_boards.PNG)
	</figure>

	---

	**Installing Board Definitions in the Arduino IDE**</a>

-   <a href="https://learn.sparkfun.com/tutorials/15">
	<figure markdown>
	![Installing an Arduino Library](https://cdn.sparkfun.com/c/264-148/assets/b/e/4/b/2/50f04b99ce395fd95e000001.jpg)
	</figure>

	---

	**Installing an Arduino Library**</a>

</div>


## Arduino Core
!!! success "Temporary Instructions"
	In order to program the RA6M5 Thing Plus in the Arduino IDE, users will need to install the **Renesas-Arduino core**. However, until the RA6M5 Thing Plus is officially adopted into the [Renesas-Arduino core](https://github.com/arduino/ArduinoCore-renesas), users need to utilize [our port of the **Renesas-Arduino core**](./assets/SFE-Renesas-Arduino_core.zip).

	1. Before users can install our ported version of the Renesas-Arduino core, they should first install the [*official* Renesas-Arduino core](https://github.com/arduino/ArduinoCore-renesas) in the Arduino IDE.
		- This will ensure that any required compilation and upload tools are installed for the Arduino core.
	2. Once installed, users will need to locate the `packages` directory for for the Arduino cores in the Arduino IDE:

		<div class="grid cards" markdown>

		-   **Windows**

			---

			On Windows, the directory location may vary based on whether the Arduino IDE was installed for an individual user or all users:

			- The user's `AppData` directory:

					C:\Users\{==<insert username>==}\AppData\Local\Arduino15\packages

			- The `Program Files` or `Program Files(x86)` directories:

					C:\Program Files{++(x86)++}\Arduino IDE


		-   **MacOS**

			---

			With Mac OS, users should check the `Applications` and `Library` directories:

			- `Applications` directory:

					/Applications/Arduino.app/

			- `Library` directory:

					~/Library/Arduino15/packages/


		-   **Linux**

			---

			For Linux, this may be located in the following directories:

			- Local:

					/home/$USER/Arduino

			- Downloaded:

					/home/$USER/.arduino15/packages


		</div>

	3. After the `packages` directory has been located, users will need to navigate to the Renesas Arduino core. It is usually located in the `./arduino/hardware/{==renesas_portenta==}/{++<version number>++}/` directory of the `packages` folder.
	4. The Arduino core is followed by a directory, named after the Arduino core's release `{++<version number>++}`. From there, users will need to create a new directory/folder in the `renesas_portenta` directory with the `version number` bumped up.
		- *For example, if the current version is `1.1.0`, users can name the new directory `1.2.0`.*
	4. Next, users will need to download and extract the files from [our ported version of the Renesas-Arduino core](./assets/SFE-Renesas-Arduino_core.zip):
		<center>
		[:material-download:{ .heart }&nbsp;&nbsp;Download our Renesas-Arduino Core *(Ported)*](./assets/SFE-Renesas-Arduino_core.zip "Click to download the ported Arduino core"){ .md-button .md-button--primary }
		</center>
	4. Once extracted, users will need to copy over the files from [our ported version of the Renesas-Arduino core](./assets/SFE-Renesas-Arduino_core.zip)into the new directory that was created earlier:
		<figure markdown>
		[![Extracted files](./assets/img/hookup_guide/arduino-extracted_files.png){ width=500 }](./assets/img/hookup_guide/arduino-extracted_files.png "Click to enlarge")
		<figcaption markdown>The files extracted from [our ported version of the Renesas-Arduino core](./assets/SFE-Renesas-Arduino_core.zip).</figcaption>
		</figure>


	??? warning "Bootloader - Initial Release"
		For the initial release of the RA6M5 Thing Plus, we were unable to provide a signed USB driver for the bootloader. In the meantime, we are utilizing the `VID` and `PID` for the Arduino Portenta C33.

		This is not a major issue for the board functionality. However, once the RA6M5 Thing Plus is adopted into the Renesas-Arduino core and when users begin to utilize the [*official* Renesas-Arduino core](https://github.com/arduino/ArduinoCore-renesas), the board will be recognized as the `Arduino Portenta C33` in the Arduino IDE. This is based on the `VID` and `PID` in the bootloader; therefore, to update this information, users would need to update the bootloader for the RA6M5.


	!!! info
		This information is accurate as of April 2024; however, it may become irrelevant in the future *(once the RA6M5 Thing Plus is included in the Renesas-Arduino core)*. At which point, users may disregard this note and/or request for this information to be updated by [filing an issue](../github/file_issue).


??? failure "Invalid - Do Not Use"
	{--

	In order to program the RA6M5 Thing Plus in the Arduino IDE, users will need to install the [Renesas-Arduino core](https://github.com/arduino/ArduinoCore-renesas). The Arduino core can be found by searching for `Arduino Renesas Portenta Boards` in the **Board Manager** of the Arduino IDE. Once installed, the RA6M5 Thing Plus will become available in the **Board Manager**.

		Arduino Renesas Portenta Boards

	<div class="grid" markdown>

	<div markdown>

	For users who are unfamiliar with this process, please check out our tutorial on [installing an Arduino core](https://learn.sparkfun.com/tutorials/installing-board-definitions-in-the-arduino-ide/installing-an-arduino-board-definition).

	<div class="grid cards" markdown align="center">

	-   <a href="https://learn.sparkfun.com/tutorials/1265">
		<figure markdown>
		![Installing Board Definitions in the Arduino IDE](https://cdn.sparkfun.com/c/264-148/assets/learn_tutorials/1/2/6/5/sparkfun_boards.PNG)
		</figure>

		---

		**Installing Board Definitions in the Arduino IDE**</a>

	</div>

	</div>

	<div markdown>

	<figure markdown>
	[![Install the Renesas-Arduino Core](./assets/img/hookup_guide/arduino-renesas_core.png){ width="400" }](./assets/img/hookup_guide/arduino-renesas_core.png "Click to enlarge")
	<figcaption markdown>Installing the [Renesas-Arduino core](https://github.com/arduino/ArduinoCore-renesas) in the Arduino IDE.</figcaption>
	</figure>

	</div>

	</div>

	--}




## Arduino Libraries
In order to utilize some of the peripherals of the RA6M5 Thing Plus with the Arduino IDE, users will need to [install Arduino libraries](https://learn.sparkfun.com/tutorials/15) for the peripheral devices/interfaces. For users who are unfamiliar with this process, please check out our tutorial below:

<div class="grid cards" markdown align="center">

-   <a href="https://learn.sparkfun.com/tutorials/15">
	<figure markdown>
	![Installing an Arduino Library](https://cdn.sparkfun.com/c/264-148/assets/b/e/4/b/2/50f04b99ce395fd95e000001.jpg)
	</figure>

	---

	**Installing an Arduino Library**</a>

</div>

<!-- 
### SD Card
The [SD library for Arduino](https://github.com/arduino-libraries/SD) can be installed from the library manager in the Arduino IDE by searching for:

	SD library for Arduino

<figure markdown>
[![](./assets/img/hookup_guide/arduino_library-SD.png "Click to enlarge"){ width="400" }](./assets/img/hookup_guide/arduino_library-SD.png)
<figcaption markdown>SD library for Arduino in the library manager of the Arduino IDE.</figcaption>
</figure>

??? tip "Manually Downloading the Arduino Library"
	For users who would like to manually download and install the library, the `*.zip` file can be accessed from the [GitHub repository](https://github.com/arduino-libraries/SD) or downloaded by clicking the button below.

	<center>
	[:octicons-download-16:{ .heart } Download the Arduino Library](https://github.com/arduino-libraries/SD/archive/refs/heads/master.zip){ .md-button .md-button--primary }
	</center>
 -->


### WS2812 RGB LED
While users are free to choose any Arduino library that provides support for WS2812 LEDs, we recommend the [FastLED Arduino library](https://github.com/FastLED/FastLED/); as it has been tested and verified to work with the RGB LED on the RA6M5 Thing Plus. The [FastLED Arduino library](https://github.com/FastLED/FastLED/) can be installed from the **Library Manager** in the Arduino IDE by searching for:

	FastLED Arduino Library


<div class="grid" markdown>

<div markdown>

<figure markdown>
[![](./assets/img/hookup_guide/arduino-FastLED_library.png "Click to enlarge"){ width="400" }](./assets/img/hookup_guide/arduino-FastLED_library.png)
<figcaption markdown>FastLED Arduino library in the library manager of the Arduino IDE.</figcaption>
</figure>

</div>

<div markdown>

!!! tip "Manually Downloading the Arduino Library"
	For users who would like to manually download and install the library, the `*.zip` file can be accessed from the [GitHub repository](https://github.com/FastLED/FastLED/) or downloaded by clicking the button below.

	<center>
	[:octicons-download-16:{ .heart } Download the Arduino Library](https://github.com/FastLED/FastLED/archive/refs/heads/master.zip){ .md-button .md-button--primary }
	</center>

</div>

</div>

!!! warning "Note - Support Modification"
	While support for the Renesas Arduino boards has been added to FastLED, it is not available in the latest release. For the meantime, users will need to follow the [porting instructions](https://github.com/FastLED/FastLED/blob/master/PORTING.md) to enable support for the RA6M5 Thing Plus, in order to utilize this library.

	Below, are the modifications necessary to utilize the [FastLED Arduino library](https://github.com/FastLED/FastLED/) for the WS2812 LED on the RA6M5 Thing PLus:

	- Provide a linker to `cstdint` at the beginning of the sketch: `#include <cstdint>`
	- Followed by defining the `_FL_DEFPIN( DATA_PIN, BSP_IO_PORT_01_PIN_05, R_PORT1_BASE );`

	!!! info
		This information is accurate as of April 2024; however, it may become irrelevant in the future *(once a release is published, with support for the Renesas Arduino boards)*. At which point, users may disregard this note and/or request for this information to be removed by [filing an issue](../github/file_issue).


### MAX17048 Fuel Gauge
While users are free to choose any Arduino library that provides support for MAX17048 fuel gauge, we recommend the [SparkFun MAX1704x Arduino library](https://github.com/sparkfun/SparkFun_MAX1704x_Fuel_Gauge_Arduino_Library); as it has been tested and verified to work with the MAX17048 on the RA6M5 Thing Plus. The [SparkFun MAX1704x Fuel Gauge Arduino library](https://github.com/sparkfun/SparkFun_MAX1704x_Fuel_Gauge_Arduino_Library) can be installed from the **Library Manager** in the Arduino IDE by searching for:

	SparkFun MAX1704x Fuel Gauge Arduino Library


<div class="grid" markdown>

<div markdown>

<figure markdown>
[![](./assets/img/hookup_guide/arduino-MAX1704x_library.png "Click to enlarge"){ width="400" }](./assets/img/hookup_guide/arduino-MAX1704x_library.png)<figcaption markdown>SparkFun MAX1704x Fuel Gauge Arduino library in the library manager of the Arduino IDE.</figcaption>
</figure>

</div>

<div markdown>

!!! tip "Manually Downloading the Arduino Library"
	For users who would like to manually download and install the library, the `*.zip` file can be accessed from the [GitHub repository](https://github.com/sparkfun/MAX1704x_Fuel_Gauge_Arduino_Library) or downloaded by clicking the button below.

	<center>
	[:octicons-download-16:{ .heart } Download the Arduino Library](https://github.com/sparkfun/SparkFun_MAX1704x_Fuel_Gauge_Arduino_Library/archive/refs/heads/main.zip){ .md-button .md-button--primary }
	</center>

</div>

</div>
