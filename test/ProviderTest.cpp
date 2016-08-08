#include <gtest/gtest.h>
#include <data/provider/Provider.h>

TEST(ProviderTest, cancelBug)
{
	Provider provider;

	EXPECT_EQ(true, provider.isReady());
	provider.cancel();
	EXPECT_EQ(true, provider.isReady());
}
