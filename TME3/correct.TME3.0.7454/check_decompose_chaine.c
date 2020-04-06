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


START_TEST (test_decompose_chaine_segv)
{
	// vérif si seg fault ou pas
	decompose_chaine("ceci est une chaine de caractère!");                                                                        
}
END_TEST

START_TEST (test_decompose_chaine)
{

  char ch[]="ceci est une chaine de caractere!";
	char **tab_mot=decompose_chaine(ch);                                                                        
	fail_unless (strcmp(tab_mot[0],"ceci")==0,
	       "erreur sur la decomposition de chaine");                                                                     
	fail_unless (strcmp(tab_mot[1],"est")==0,
	       "erreur sur la decomposition de chaine");                                                                     
	fail_unless (strcmp(tab_mot[2],"une")==0,
	       "erreur sur la decomposition de chaine");                                                                     
	fail_unless (strcmp(tab_mot[3],"chaine")==0,
	       "erreur sur la decomposition de chaine");                                                                     
	fail_unless (strcmp(tab_mot[4],"de")==0,
	       "erreur sur la decomposition de chaine");                                                                     
	fail_unless (strcmp(tab_mot[5],"caractere!")==0,
	       "erreur sur la decomposition de chaine");                                                                     
	fail_unless (tab_mot[6]==NULL,
	       "erreur sur la decomposition de chaine");                                                                     

	free(tab_mot[5]);
	free(tab_mot[4]);
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
  Suite *s = suite_create ("Decompose chaine");

  TCase *tc = tcase_create ("Decompose chaine");
  tcase_add_test (tc, test_decompose_chaine_segv);
  tcase_add_test (tc, test_decompose_chaine);
  tcase_add_test (tc, test_decompose_chaine);
  tcase_add_test (tc, test_decompose_chaine);
  tcase_add_test (tc, test_decompose_chaine);
  tcase_add_test (tc, test_decompose_chaine);
  tcase_add_test (tc, test_decompose_chaine);
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
