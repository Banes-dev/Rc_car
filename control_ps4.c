/* ******************************************* */
/*               Rc-car project                */
/*                                             */
/*   File : control_ps4.c                      */
/*                                             */
/*   Created: 2023/11/06 23:56:20 by Banes     */
/*   Updated: 2023/11/06 23:56:20 by Banes     */
/*                                             */
/* ******************************************* */

#include "lib_rc_car.h"
// #include <stdio.h>          		 // printf
// #include "include/hidapi.h"          // Interaction avec dispositifs USB et Bluetooth HID (Human Interface Device)

int main()
{
	printf("\nRc car Project by Banes\n-------------------\n(Personnal Project)\n-------------------\n");
	printf("\nCopyright Banes and Reltik Studio\n\n");   // ©️

	// Init library HIDAPI
	if (hid_init()) {
		printf("Failed to initialize HIDAPI.\n");
		return (-1);
    }
	// Search to connect ps4 controller
	// hid_device *controller = hid_open(0x054C, 0x05C4, NULL); // Identifiants USB pour la manette PS4
    // if (!controller) {
    //     printf("Failed to open PS4 controller.\n");
    //     return (-1);
    // }
}