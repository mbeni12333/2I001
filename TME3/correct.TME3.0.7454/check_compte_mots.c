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


START_TEST (test_compte_mots_segv)
{
	// vérif si seg fault ou pas
	char **tab_mot;
	tab_mot = (char **)malloc(sizeof(char *)*3); 
	tab_mot[0] = (char *)malloc(sizeof(char)*10);
	strcpy(tab_mot[0], "bla");
	tab_mot[1] = (char *)malloc(sizeof(char)*10);
	strcpy(tab_mot[1], "bla");
	tab_mot[2] = NULL;
	compte_mots(tab_mot);                                                                         
	free(tab_mot[1]);
	free(tab_mot[0]);
	free(tab_mot);

}
END_TEST

START_TEST (test_compte_mots)
{
	
	char **tab_mot;
	tab_mot = (char **)malloc(sizeof(char *)*5); 
	tab_mot[0] = (char *)malloc(sizeof(char)*4);
	strcpy(tab_mot[0],"bla");
	tab_mot[1] = (char *)malloc(sizeof(char)*4);
	strcpy(tab_mot[1],"bla");
	tab_mot[2] = NULL;
	int x=compte_mots(tab_mot);    
	fail_unless (x == 2,
	       "erreur sur le comptage de mots");                                                                     

	tab_mot[2] = (char *)malloc(sizeof(char)*4);
	strcpy(tab_mot[2],"bla");
	tab_mot[3] = (char *)malloc(sizeof(char)*4);
	strcpy(tab_mot[3],"bla");
	tab_mot[4]=NULL;
	x=compte_mots(tab_mot);
	fail_unless (x == 4,
	       "erreur sur le comptage de mots");                                                                     
	
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
  Suite *s = suite_create ("Compte mots");

  /* Compte_mots */
  TCase *tc_cptmots = tcase_create ("Compte mots");
  tcase_add_test (tc_cptmots, test_compte_mots_segv);
  tcase_add_test (tc_cptmots, test_compte_mots);
  tcase_add_test (tc_cptmots, test_compte_mots);
  tcase_add_test (tc_cptmots, test_compte_mots);
  tcase_add_test (tc_cptmots, test_compte_mots);
  tcase_add_test (tc_cptmots, test_compte_mots);
  tcase_add_test (tc_cptmots, test_compte_mots);
  suite_add_tcase (s, tc_cptmots);

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
