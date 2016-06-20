#include <gtest/gtest.h>
#include <bridge/NativeObject.h>
#include <component/Container.h>
#include <bridge/Context.h>
#include <component/view/Visibility.h>

TEST(ComponentTest, testNullObjects_crashTest)
{
	//Test for crash ;)
	Context context;
	NativeObject nativeObject{"MyFunnyObject", &context};
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
