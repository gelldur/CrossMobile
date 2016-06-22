#include <gtest/gtest.h>
#include <bridge/NativeObject.h>
#include <component/Container.h>
#include <bridge/Context.h>
#include <component/view/Visibility.h>
#include <bridge/NativeObjectBuilder.h>

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

class TestComponent : public Component
{
public:
	Context* getContextHidden()
	{
		return getContext();
	}

	COMPONENT_TO_STRING(TestComponent);

	static TestComponent& getNullObject()
	{
		static TestComponent nullObject;
		return nullObject;
	}

};

TEST(ComponentTest, bugFixMoveComponents)
{
	auto object = NativeObjectBuilder::create("MyFunnyObject", std::make_shared<Context>())
			.addComponent<TestComponent>()
			.build();
	auto movedObject = std::move(object);
	EXPECT_TRUE(movedObject.getContext() != nullptr);
	EXPECT_FALSE(movedObject.getComponent<TestComponent>().isNullObject());
	EXPECT_TRUE(movedObject.getComponent<TestComponent>().getContextHidden() != nullptr);//previously crash
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
