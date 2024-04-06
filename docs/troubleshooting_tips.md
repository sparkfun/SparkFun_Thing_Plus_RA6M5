---
icon: sfe-logo
---

!!! warning "Need Help?"
	If you need technical assistance or more information on a product that is not working as you expected, we recommend heading over to the [SparkFun Technical Assistance](https://www.sparkfun.com/technical_assistance) page for some initial troubleshooting.

	<center>
	[SparkFun Technical Assistance Page](https://www.sparkfun.com/technical_assistance){ .md-button .md-button--primary }
	</center>

	If you can't find what you need there, the [SparkFun GNSS Forum](https://forum.sparkfun.com/viewforum.php?f=116) is a great place to ask questions.

	!!! info "Account Registration Required"
		If this is your first visit to our forum, you'll need to create a [Forum Account](https://forum.sparkfun.com/ucp.php?mode=register) to post questions.


### &micro;SD Card
Make sure that the &micro;SD card is compatible with the Arduino library being used for it.   For example, the default [SD Arduino library](https://www.arduino.cc/reference/en/libraries/sd/) is only compatible with `FAT16` or `FAT32` file systems; therefore, the card capacity is limited to **16GB** or **32GB** and smaller. Another consideration is that the library was also written to only handle [short 8.3 names for files](https://en.wikipedia.org/wiki/8.3_filename).
