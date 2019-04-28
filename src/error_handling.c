/*
** EPITECH PROJECT, 2018
** NWP_mychap_2018
** File description:
** error_handling.c
*/
/** \file error_handling.c
  * \brief errors handling file
  * \author Janote J;
*/
#include <stdio.h>
#include <stdlib.h>

/*
** PURPOSE : Prints the error given in parameter and exit the program
** PARAMS  : char *str
** RETURNS : None
*/
void error(char *str)
{
    printf("%s", str);
    exit(84);
}
