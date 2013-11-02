#include <stdio.h>
#include <stdlib.h>
#include <check.h>
#include "../src/mypstree.h"

START_TEST (testInsertNeighbour1)
{
	Dirstruct temp1 = {24,"24",NULL,NULL};
	Dirstruct temp2 = {25,"25",NULL,NULL};
	Dirstruct temp3 = {26,"26",NULL,NULL};
	insertNeighbour(&temp2,&temp1);
	insertNeighbour(&temp3,&temp1);
	ck_assert(temp1.next == &temp3);
	ck_assert(temp3.next == &temp2);
}
END_TEST

START_TEST (testInsertChild1)
{
	Dirstruct temp1 = {24,"24",NULL,NULL};
	Dirstruct temp2 = {25,"25",NULL,NULL};
	Dirstruct temp3 = {26,"26",NULL,NULL};
	insertChild(&temp1,&temp2);
	insertChild(&temp3,&temp1);
	ck_assert(temp2.child == &temp1);
	ck_assert(temp1.child == &temp3);
}
END_TEST

START_TEST (testInsertChild2)
{
	Dirstruct temp1 = {24,"24",NULL,NULL};
	Dirstruct temp2 = {25,"25",NULL,NULL};
	Dirstruct temp3 = {26,"26",NULL,NULL};
	insertChild(&temp2,&temp1);
	insertChild(&temp3,&temp1);
	ck_assert(temp1.child == &temp3);
	ck_assert(temp3.next == &temp2);
}
END_TEST

START_TEST (testInsertChildByPPid1) 
{
	head = &(Dirstruct) {0,"0",NULL,NULL};
	Dirstruct temp1 = {24,"24",NULL,NULL};
	Dirstruct temp2 = {25,"25",NULL,NULL};
	Dirstruct temp3 = {26,"26",NULL,NULL};
	insertChildByPPid(&temp1,23);
	insertChildByPPid(&temp2,24);
	insertChildByPPid(&temp3,23);
	ck_assert(head->child->pid == 23);
	ck_assert(head->child->child == &temp3);
	ck_assert(temp1.child == &temp2);
	ck_assert(temp3.next == &temp1);

}
END_TEST

START_TEST (testInsertChildByPPid2) 
{
	head = &(Dirstruct) {0,"0",NULL,NULL};
	Dirstruct temp1 = {24,"24",NULL,NULL};
	Dirstruct temp2 = {25,"25",NULL,NULL};
	Dirstruct temp3 = {26,"26",NULL,NULL};
	insertChildByPPid(&temp1,23);
	insertChildByPPid(&temp2,23);
	insertChildByPPid(&temp3,20);
	ck_assert(head->child->pid == 20);
	ck_assert(head->child->next->pid ==23);
	ck_assert(head->child->next->child == &temp2);
	ck_assert(head->child->next->child->next == &temp1);
}
END_TEST

START_TEST (testRemoveHeadLink1) 
{
	head = &(Dirstruct) {0,"0",NULL,NULL};
	Dirstruct temp1 = {24,"24",NULL,NULL};
	Dirstruct temp2 = {25,"25",NULL,NULL};
	Dirstruct temp3 = {26,"26",NULL,NULL};
	head->child = &temp1;
	temp1.next = &temp2;
	removeHeadLink(&temp1);
	ck_assert(head->child==&temp2);
}
END_TEST

START_TEST (testSearchByPid1) 
{
	head = &(Dirstruct) {0,"0",NULL,NULL};
	Dirstruct temp1 = {24,"24",NULL,NULL};
	Dirstruct temp2 = {25,"25",NULL,NULL};
	Dirstruct temp3 = {26,"26",NULL,NULL};
	insertChild(&temp1, head);
	insertChild(&temp2, head);
	insertChild(&temp3, &temp1);
	ck_assert(searchByPid(head, 25)->next == &temp1);
	ck_assert(searchByPid(head, 26)->next == NULL);
	ck_assert(searchByPid(head, 24)->child == &temp3);
	ck_assert(searchByPid(head, 21) == NULL);
	ck_assert(searchByPid(&temp1, 26)->pid == 26);
	ck_assert(searchByPid(&temp1, 25) == NULL);
}
END_TEST
Suite* mypstree_suite(void)
{
	Suite* s = suite_create("Mypstree");

	TCase* tc_InsertNeighbour = tcase_create("InsertNeighbour");
	TCase* tc_InsertChild = tcase_create("InsertChild");
	TCase* tc_InsertChildByPPid = tcase_create("InsertChildByPPid");
	TCase* tc_RemoveHeadLink = tcase_create("RemoveHeadLink");
	TCase* tc_SearchByPid = tcase_create("SearchByPid");

	tcase_add_test(tc_InsertNeighbour, testInsertNeighbour1);
	tcase_add_test(tc_InsertChild, testInsertChild1);
	tcase_add_test(tc_InsertChild, testInsertChild2);
	tcase_add_test(tc_InsertChildByPPid, testInsertChildByPPid1);
	tcase_add_test(tc_InsertChildByPPid, testInsertChildByPPid2);
	tcase_add_test(tc_RemoveHeadLink, testRemoveHeadLink1);
	tcase_add_test(tc_SearchByPid, testSearchByPid1);

	suite_add_tcase(s, tc_InsertNeighbour);
	suite_add_tcase(s, tc_InsertChild);
	suite_add_tcase(s, tc_InsertChildByPPid);
	suite_add_tcase(s, tc_RemoveHeadLink);
	suite_add_tcase(s, tc_SearchByPid);

	return s;
}

int main(void) {
	int number_failed;
	Suite* s = mypstree_suite();
	SRunner* sr = srunner_create(s);
	srunner_run_all(sr, CK_NORMAL);
	number_failed = srunner_ntests_failed(sr);
	srunner_free(sr);
	return (number_failed == 0)?EXIT_SUCCESS:EXIT_FAILURE;
}
