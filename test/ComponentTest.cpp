#include <gtest/gtest.h>
#include <bridge/NativeObject.h>
#include <component/Container.h>
#include <bridge/Context.h>
#include <component/view/Visibility.h>

TEST(ComponentTest, testNullObjects_crashTest)
{
	//Test for crash ;)
	NativeObject nativeObject{"MyFunnyObject", std::make_shared<Context>()};
	{
		auto& nullVisibility = nativeObject.getComponent<Visibility>();
		nullVisibility.setVisibility(Visibility::GONE);
	}

	auto& nullContainer = nativeObject.getComponent<Container>();
	auto& nullNativeObject = nullContainer.get("myTag");
	{
		auto& nullVisibility = nullNativeObject.getComponent<Visibility>();
		nullVisibility.setVisibility(Visibility::GONE);
	}
}

TEST(ComponentTest, testAddComponent)
{
	//Test for crash ;)
	NativeObject nativeObject{"MyFunnyObject", std::make_shared<Context>()};
	{
		nativeObject.addComponent<Container>();
	}

	auto& notNull = nativeObject.getComponent<Container>();
	EXPECT_FALSE(notNull.isNullObject());
}
