/*
 *  check_TME1.c
 *  
 *
 *  Created by Stéphane Doncieux on 29/01/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include <stdlib.h>
#include <check.h>
#include <stdio.h>
#include "csvl.h"

void
setup (void)
{

}

void
teardown (void)
{

}


START_TEST (test_compose_chaine_segv)
{
	// vérif si seg fault ou pas
	char **tab_mot;
	tab_mot = (char **)malloc(sizeof(char *)*5); 
	tab_mot[0] = (char *)malloc(sizeof(char)*10);
	strcpy(tab_mot[0],"bonjour");
	tab_mot[1] = (char *)malloc(sizeof(char)*10);
	strcpy(tab_mot[1],"le");
	tab_mot[2] = (char *)malloc(sizeof(char)*10);
	strcpy(tab_mot[2],"monde");
	tab_mot[3] = (char *)malloc(sizeof(char)*10);
	strcpy(tab_mot[3],"!!!!!");
	tab_mot[4]=NULL;
	compose_chaine(tab_mot);                                                                        
}
END_TEST

START_TEST (test_compose_chaine)
{

	char **tab_mot;
	tab_mot = (char **)malloc(sizeof(char *)*5); 
	tab_mot[0] = (char *)malloc(sizeof(char)*10);
	strcpy(tab_mot[0],"bonjour");
	tab_mot[1] = (char *)malloc(sizeof(char)*10);
	strcpy(tab_mot[1],"le");
	tab_mot[2] = (char *)malloc(sizeof(char)*10);
	strcpy(tab_mot[2],"monde");
	tab_mot[3] = (char *)malloc(sizeof(char)*10);
	strcpy(tab_mot[3],"!!!!!");
	tab_mot[4]=NULL;
	char *ch=compose_chaine(tab_mot); 
	//printf ("chaine composee: %s\n",ch);                                                                       
	fail_unless (strncmp(ch,"bonjour le monde !!!!!",22)==0, // il peut y avoir des espaces a la fin de la chaine
	       "erreur sur la composition de chaine");                                                                     
	free(tab_mot[3]);
	free(tab_mot[2]);
	free(tab_mot[1]);
	free(tab_mot[0]);
	free(tab_mot);

}
END_TEST

Suite *
ma_suite (void)
{
  Suite *s = suite_create ("compose chaine");

  TCase *tc = tcase_create ("compose chaine");
  tcase_add_test (tc, test_compose_chaine_segv);
  tcase_add_test (tc, test_compose_chaine);
  tcase_add_test (tc, test_compose_chaine);
  tcase_add_test (tc, test_compose_chaine);
  tcase_add_test (tc, test_compose_chaine);
  tcase_add_test (tc, test_compose_chaine);
  tcase_add_test (tc, test_compose_chaine);
  suite_add_tcase (s, tc);

  return s;
}

int
main (void)
{
  int number_failed, number_total;
  Suite *s = ma_suite ();
  SRunner *sr = srunner_create (s);
  srunner_run_all (sr, CK_VERBOSE);
  number_failed = srunner_ntests_failed (sr);
  number_total =  srunner_ntests_run (sr);
  printf("Note %d/%d\n",number_total-number_failed,number_total);
  srunner_free (sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
