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
  char tab_mots[]="abc def ghi";
  compte_mots_chaine(tab_mots);                                                                         

}
END_TEST

START_TEST (test_compte_mots)
{

  char tab_mots[]="abc def ghi";
  char tab_mots2[]="abc def ghi jkl";
  int res=compte_mots_chaine(tab_mots);                                                                         
	
	fail_unless (res == 3,
	       "erreur sur le comptage de mots");                                                                     

    res=compte_mots_chaine(tab_mots2);                                                                         

	fail_unless (res == 4,
	       "erreur sur le comptage de mots");                                                                     


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
