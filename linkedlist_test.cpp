#include <unittest++/UnitTest++.h>
#include "linkedlist.h"

struct test_struct_t {
	int var;
	ListNode_t node;
};

TEST(ListInitialize)
{
	test_struct_t a;
	a.var = 1;
	ListInitialize(&a.node);	
	CHECK_EQUAL(a.node.nextp,&a.node);
	CHECK_EQUAL(a.node.prevp,&a.node);

	CHECK_EQUAL(LINKEDLIST_IS_EMPTY(a.node),1);
}
TEST(ListAddEnd2) {
	test_struct_t a,b;
	a.var = 1;
	b.var = 2;
	ListInitialize(&a.node);	
	ListAddEnd(&a.node, &b.node);
	CHECK_EQUAL(a.node.nextp,&b.node);
	CHECK_EQUAL(a.node.prevp,&b.node);
	CHECK_EQUAL(b.node.nextp,&a.node);
	CHECK_EQUAL(b.node.prevp,&a.node);
	CHECK_EQUAL(LINKEDLIST_IS_EMPTY(a.node),0);
}

TEST(ListAddEnd3) {
	test_struct_t a,b,c;
	a.var = 1;
	b.var = 2;
	c.var = 3;
	ListInitialize(&a.node);	
	ListAddEnd(&a.node, &b.node);
	ListAddEnd(&a.node, &c.node);
	CHECK_EQUAL(a.node.nextp,&b.node);
	CHECK_EQUAL(a.node.prevp,&c.node);
	CHECK_EQUAL(b.node.nextp,&c.node);
	CHECK_EQUAL(b.node.prevp,&a.node);
	CHECK_EQUAL(c.node.nextp,&a.node);
	CHECK_EQUAL(c.node.prevp,&b.node);
	CHECK_EQUAL(LINKEDLIST_FIRST(a.node),&b.node);
	CHECK_EQUAL(LINKEDLIST_LAST(a.node),&c.node);

}
TEST(ListMove3) {
	test_struct_t a,b,c;
	ListNode_t linkedList, *cur_nodep;
	
	a.var = 1;
	b.var = 2;
	c.var = 3;
	ListInitialize(&linkedList);	
	ListAddEnd(&linkedList, &a.node);
	ListAddEnd(&linkedList, &b.node);
	ListAddEnd(&linkedList, &c.node);
	int expected_num=1;
	cur_nodep =linkedList.nextp;
	while (&linkedList != cur_nodep) {
		test_struct_t *cur = NODE_TO_ENTRY(test_struct_t,node, cur_nodep);
		CHECK_EQUAL(expected_num,cur->var);
		cur_nodep= cur_nodep->nextp;
		expected_num++;
	}
	CHECK_EQUAL(expected_num,4);
}

TEST(ListMove1) {
	test_struct_t a;
	ListNode_t *cur_nodep;
	a.var = 1;
	ListInitialize(&a.node);	
	int expected_num=1;
	cur_nodep =&a.node;
	do {
		test_struct_t *cur = NODE_TO_ENTRY(test_struct_t,node, cur_nodep);
		CHECK_EQUAL(expected_num,cur->var);
		cur_nodep= cur_nodep->nextp;
		expected_num++;
	} while (&a.node != cur_nodep);
	CHECK_EQUAL(expected_num,2);

}

TEST(ListAddEnd2_move) {
	test_struct_t a,*cur;
	a.var = 1;
	ListInitialize(&a.node);	
	cur = NODE_TO_ENTRY(test_struct_t,node, &a.node);
	CHECK_EQUAL(cur,&a);
	CHECK_EQUAL(cur->var,a.var);
}
TEST(ListLength) {
	ListNode_t linkedList;
	ListInitialize(&linkedList);	
	CHECK_EQUAL(ListLength(&linkedList),0);
	test_struct_t a;
	a.var = 1;
	ListAddEnd(&linkedList, &a.node);
	CHECK_EQUAL(ListLength(&linkedList),1);
	test_struct_t b;
	b.var = 1;
	ListAddEnd(&linkedList, &b.node);
	CHECK_EQUAL(ListLength(&linkedList),2);
}

TEST(ListRemoveA) {
	test_struct_t a,b,c,d;
	ListNode_t linkedList;
	a.var = 1;
	b.var = 2;
	c.var = 3;
	d.var = 4;
	ListInitialize(&linkedList);	
	ListAddEnd(&linkedList, &a.node);
	ListAddEnd(&linkedList, &b.node);
	ListAddEnd(&linkedList, &c.node);
	CHECK_EQUAL(ListLength(&linkedList),3);
	ListRemove (&b.node);
	CHECK_EQUAL(ListLength(&linkedList),2);
	ListRemove (&c.node);
	CHECK_EQUAL(ListLength(&linkedList),1);
	ListRemove (&a.node);
	CHECK_EQUAL(ListLength(&linkedList),0);
	CHECK_EQUAL(LINKEDLIST_IS_EMPTY(linkedList),1);
	ListAddEnd(&linkedList, &d.node);
	CHECK_EQUAL(ListLength(&linkedList),1);
	ListAddEnd(&linkedList, &b.node);
	test_struct_t *cur = NODE_TO_ENTRY(test_struct_t,node, linkedList.nextp);;
	CHECK_EQUAL(cur->var,4);
	cur = NODE_TO_ENTRY(test_struct_t,node, cur->node.nextp);
	CHECK_EQUAL(cur->var,2);
}


static void sumList(ListNode_t * nodep, void * datap) {
	test_struct_t *cur = NODE_TO_ENTRY(test_struct_t,node, nodep);
	(*(int *) datap) += cur->var;

}

TEST(ListApplyAllSum) {
	test_struct_t a,b,c,d;
	ListNode_t linkedList;
	int sum=0;
	a.var = 1;
	b.var = 2;
	c.var = 3;
	d.var = 4;
	ListInitialize(&linkedList);	
	ListAddEnd(&linkedList, &a.node);
	ListAddEnd(&linkedList, &b.node);
	ListAddEnd(&linkedList, &c.node);
	ListAddEnd(&linkedList, &d.node);

	ListApplyAll(&linkedList, sumList, &sum);
	CHECK_EQUAL(10, sum);

}

TEST(ListAddFirst) {
	test_struct_t a,b,c,d;
	ListNode_t linkedList;
	int sum =0 ;
	a.var = 1;
	b.var = 2;
	c.var = 3;
	d.var = 4;
	ListInitialize(&linkedList);	
	ListAddEnd(&linkedList, &a.node);
	ListAddEnd(&linkedList, &b.node);
	ListAddEnd(&linkedList, &c.node);
	ListAddBegin(&linkedList, &d.node);
	test_struct_t *cur = NODE_TO_ENTRY(test_struct_t,node, linkedList.nextp);;
	CHECK_EQUAL(cur->var,4);
	ListApplyAll(&linkedList, sumList, &sum);
	CHECK_EQUAL(10, sum);
}
static int  isMatch(ListNode_t * nodep, void * datap) {
	int number = (intptr_t) datap;
	test_struct_t *cur = NODE_TO_ENTRY(test_struct_t,node, nodep);
	if (number == cur->var) 
		return 1;
	return 0;
}


TEST(ListFindFound) {
	test_struct_t a,b,c,d;
	ListNode_t linkedList;
	a.var = 1;
	b.var = 2;
	c.var = 3;
	d.var = 4;
	ListInitialize(&linkedList);	
	ListAddEnd(&linkedList, &a.node);
	ListAddEnd(&linkedList, &b.node);
	ListAddEnd(&linkedList, &c.node);
	ListAddBegin(&linkedList, &d.node);
	ListNode_t * node = ListFind(&linkedList, isMatch,(void *) (intptr_t)3);
	CHECK_EQUAL(&c.node, node);
	node = ListFind(&linkedList, isMatch,(void *) (intptr_t)10);
	CHECK(NULL== node);
}

static int ts_compare(ListNode_t * ap,ListNode_t * bp, UNUSED void * datap) {
	test_struct_t *cur_a = NODE_TO_ENTRY(test_struct_t,node, ap);
	test_struct_t *cur_b = NODE_TO_ENTRY(test_struct_t,node, bp);
	return cur_b->var - cur_a->var;
}

TEST(ListSort) {
	test_struct_t a,b,c,d;
	ListNode_t linkedList;
	a.var = 1;
	b.var = 2;
	c.var = 3;
	d.var = 4;
	ListInitialize(&linkedList);	
	ListAddBegin(&linkedList, &a.node);
	ListAddBegin(&linkedList, &b.node);
	ListAddBegin(&linkedList, &c.node);
	ListAddBegin(&linkedList, &d.node);
	ListSort(&linkedList, ts_compare, NULL);
	test_struct_t *cur = NODE_TO_ENTRY(test_struct_t,node, linkedList.nextp);;
	CHECK_EQUAL(cur->var,1);
	cur = NODE_TO_ENTRY(test_struct_t,node, linkedList.nextp->nextp);
	CHECK_EQUAL(cur->var,2);
	cur = NODE_TO_ENTRY(test_struct_t,node, linkedList.nextp->nextp->nextp);
	CHECK_EQUAL(cur->var,3);
	cur = NODE_TO_ENTRY(test_struct_t,node, linkedList.nextp->nextp->nextp->nextp);
	CHECK_EQUAL(cur->var,4);
}
TEST(ListSort2) {
	test_struct_t a,b,c,d;
	ListNode_t linkedList;
	a.var = 4;
	b.var = 3;
	c.var = 2;
	d.var = 1;
	ListInitialize(&linkedList);	
	ListAddBegin(&linkedList, &a.node);
	ListAddBegin(&linkedList, &b.node);
	ListAddBegin(&linkedList, &c.node);
	ListAddBegin(&linkedList, &d.node);
	ListSort(&linkedList, ts_compare, NULL);
	test_struct_t *cur = NODE_TO_ENTRY(test_struct_t,node, linkedList.nextp);;
	CHECK_EQUAL(cur->var,1);
	cur = NODE_TO_ENTRY(test_struct_t,node, linkedList.nextp->nextp);
	CHECK_EQUAL(cur->var,2);
	cur = NODE_TO_ENTRY(test_struct_t,node, linkedList.nextp->nextp->nextp);
	CHECK_EQUAL(cur->var,3);
	cur = NODE_TO_ENTRY(test_struct_t,node, linkedList.nextp->nextp->nextp->nextp);
	CHECK_EQUAL(cur->var,4);
}


TEST(ListSort3) {
	test_struct_t a,b,c,d;
	ListNode_t linkedList;
	a.var = 4;
	b.var = 3;
	c.var = 2;
	d.var = 1;
	ListInitialize(&linkedList);	
	ListAddBegin(&linkedList, &a.node);
	ListAddBegin(&linkedList, &b.node);
	ListAddBegin(&linkedList, &c.node);
	ListAddEnd(&linkedList, &d.node);
	ListSort(&linkedList, ts_compare, NULL);
	test_struct_t *cur = NODE_TO_ENTRY(test_struct_t,node, linkedList.nextp);;
	CHECK_EQUAL(cur->var,1);
	cur = NODE_TO_ENTRY(test_struct_t,node, linkedList.nextp->nextp);
	CHECK_EQUAL(cur->var,2);
	cur = NODE_TO_ENTRY(test_struct_t,node, linkedList.nextp->nextp->nextp);
	CHECK_EQUAL(cur->var,3);
	cur = NODE_TO_ENTRY(test_struct_t,node, linkedList.nextp->nextp->nextp->nextp);
	CHECK_EQUAL(cur->var,4);
}

TEST(ListAddSorted) {
	test_struct_t a,b,c,d;
	ListNode_t linkedList;
	a.var = 4;
	b.var = 3;
	c.var = 2;
	d.var = 1;
	ListInitialize(&linkedList);	
	ListAddSorted(&linkedList, &a.node,ts_compare, NULL);
	ListAddSorted(&linkedList, &c.node,ts_compare, NULL);
	ListAddSorted(&linkedList, &b.node,ts_compare, NULL);
	ListAddSorted(&linkedList, &d.node,ts_compare, NULL);
	test_struct_t *cur = NODE_TO_ENTRY(test_struct_t,node, linkedList.nextp);;
	CHECK_EQUAL(1, cur->var);
	cur = NODE_TO_ENTRY(test_struct_t,node, linkedList.nextp->nextp);
	CHECK_EQUAL(2, cur->var);
	cur = NODE_TO_ENTRY(test_struct_t,node, linkedList.nextp->nextp->nextp);
	CHECK_EQUAL(3,cur->var);
	cur = NODE_TO_ENTRY(test_struct_t,node, linkedList.nextp->nextp->nextp->nextp);
	CHECK_EQUAL(4, cur->var);
}

TEST(ListFind) {
	test_struct_t a,b,c,d, findNode;
	ListNode_t linkedList;
	a.var = 4;
	b.var = 3;
	c.var = 2;
	d.var = 1;
	ListInitialize(&linkedList);	
	ListAddSorted(&linkedList, &a.node,ts_compare, NULL);
	ListAddSorted(&linkedList, &c.node,ts_compare, NULL);
	ListAddSorted(&linkedList, &b.node,ts_compare, NULL);
	ListAddSorted(&linkedList, &d.node,ts_compare, NULL);
	findNode.var= 4;
	CHECK_EQUAL(&a.node, ListFind (&linkedList,&findNode.node, ts_compare,  NULL));
}
static int ts_compare_rev(ListNode_t * ap,ListNode_t * bp, UNUSED void * datap) {
	test_struct_t *cur_a = NODE_TO_ENTRY(test_struct_t,node, ap);
	test_struct_t *cur_b = NODE_TO_ENTRY(test_struct_t,node, bp);
	return cur_a->var - cur_b->var;
}

TEST(ListFindLastGE) {
	test_struct_t a,b,d, findNode;
	ListNode_t linkedList;
	a.var = 4;
	b.var = 3;
	d.var = 1;
	ListInitialize(&linkedList);	
	ListAddSorted(&linkedList, &a.node,ts_compare_rev, NULL);
	ListAddSorted(&linkedList, &b.node,ts_compare_rev, NULL);
	ListAddSorted(&linkedList, &d.node,ts_compare_rev, NULL);
	findNode.var= 2;
	CHECK_EQUAL(&a.node,linkedList.nextp);
	CHECK_EQUAL(&b.node, ListFindLastGE (&linkedList,&findNode.node, ts_compare_rev,  NULL));
	CHECK_EQUAL(&a.node,b.node.prevp);

}

int main()
{
	return UnitTest::RunAllTests();
}


