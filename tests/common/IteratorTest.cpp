/**
 * IteratorTest.cpp
 */
#include <assert.h>
extern "C"
{
#include "common/types.h"
#include "common/Iterator.h"
}

#include "CppUTest/TestHarness.h"

TEST_GROUP(Iterator)
{
	/* test target */
	Iterator* target;
	int* itest;

	void setup()
	{
		itest = (int*)malloc(sizeof(int));
		assert(itest);
		*itest = 30;
		target = new_Iterator(itest);
	}

	void teardown()
	{
		delete_Iterator(&target);
		free(itest);
	}
};

/**
 * Check object create
 */
TEST(Iterator, new)
{
	CHECK(NULL != target);
}

/**
 * Check object delete
 */
TEST(Iterator, delete)
{
	delete_Iterator(&target);

	/* check delete */
	POINTERS_EQUAL(NULL, target);
}

/**
 * Check prev method
 */
TEST(Iterator, prev)
{
	POINTERS_EQUAL(NULL, target->prev(target));
}

/**
 * Check next method
 */
TEST(Iterator, next)
{
	POINTERS_EQUAL(NULL, target->next(target));
}

/**
 * Check data method
 */
TEST(Iterator, data)
{
	int *i;
	i = (int*)target->data(target);
	CHECK(NULL != i);
	LONGS_EQUAL(30, *i);
}

/**
 * Check insert method
 */
TEST(Iterator, insert)
{
	int *ins;
	int *chk;
	Iterator* prev;
	Iterator* ppre;
	
	ins = (int*)malloc(sizeof(int));
	assert(ins);
	*ins = 100;

	target->insert(target, ins);
	prev = target->prev(target);

	CHECK(NULL != prev);
	chk = (int*)prev->data(prev);
	LONGS_EQUAL(100, (*chk));

	
	ins = (int*)malloc(sizeof(int));
	assert(ins);
	*ins = 999;

	target->insert(target, ins);
	ppre = target->prev(target);

	CHECK(NULL != ppre);
	chk = (int*)ppre->data(ppre);
	LONGS_EQUAL(999, (*chk));

	free(prev->data(prev));
	free(ppre->data(ppre));
	delete_Iterator(&prev);
	delete_Iterator(&ppre);
}

/**
 * Check remove method
 */
TEST(Iterator, remove)
{
	/* TODO: implement this test if implement remove method */
	target->remove(target, true);
}
