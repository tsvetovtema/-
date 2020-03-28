#include "gtest.h"
#include"../mp2-lab-Polinom/TList.h"




TEST(THeadList, can_create_list)
{
	ASSERT_NO_THROW(THeadList<int> l);
}

TEST(THeadList, can_insfirst)
{
	THeadList<int> l;
	ASSERT_NO_THROW(l.InsFirst(5));
	ASSERT_NO_THROW(l.Reset());
	EXPECT_EQ(l.GetCurrEl(), 5);
}


TEST(THeadList, stop)
{
	system("pause");
}