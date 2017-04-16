/*
 ============================================================================
 Name        : Jinux.c
 Author      : JunGeGe
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <test.h>




int main(void)
{
	puts("!!!Hello JunGeGe!!!"); /* prints !!!Hello World!!! */

	puts("!!!__DO_WHITEBOX_TEST!!!");
	__DO_WHITEBOX_TEST();

	puts("!!!Hello end!!!");

	return EXIT_SUCCESS;
}
