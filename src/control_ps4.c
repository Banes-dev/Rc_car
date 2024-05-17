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

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

int main()
{
	printf("\n\033[35mRc car Project by \033[33mBanes\033[0m\n\033[35m-------------------\n(Personnal Project)\n-------------------\n");
	printf("\nCopyright \033[33mBanes\033[0m \033[35mand \033[36mReltik Studio\033[0m\n\n");   // ©️

	hid_device *controller;
	unsigned char buffer[1024];
	int res;
	int i;

	// Init library HIDAPI
	if (hid_init())
	{
		printf("\033[31mFailed to initialize HIDAPI.\033[0m\n");
		return (-1);
    }
	// Search to connect ps4 controller
	controller = hid_open(0x054C, 0x05C4, NULL); // Identifiants USB pour la manette PS4
    if (controller == NULL)
	{
		perror("hid_open");
        printf("\033[31mFailed to open PS4 controller. %d\033[0m\n");
		hid_exit();
        return (-1);
    }
	else
	{
		// Read the PS4 controller
		while (1)
		{
			res = hid_read(controller, buffer, sizeof(buffer));
			if (res < 0)
			{
				printf("\033[31mError of readinf controller.\033[0m\n");
				break;
			}
			i = 0;
			while (buffer[i] != '\0')
			{
				ft_putchar(buffer[i]);
				i++;
			}
			
			// lire les boutons
		}
	}

	hid_close(controller);
	hid_exit();
}
