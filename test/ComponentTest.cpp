#include <gtest/gtest.h>
#include <component/Nodect.h>
#include <component/view/Visibility.h>
#include <component/NodectBuilder.h>
#include <component/view/Image.h>

void* const nativeContext = nullptr;

class Context //for tests
{
public:
	Context(void* pointer)
	{
	}
};

TEST(ComponentTest, testNullObjects_crashTest)
{
	//Test for crash ;)
	Nodect nodect{"MyFunnyObject", std::make_shared<Context>(nativeContext)};
	{
		auto& nullVisibility = nodect.getComponent<Visibility>();
		nullVisibility.setVisibility(Visibility::GONE);
	}

	auto& nullContainer = nodect.getComponent<Container>();
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
	auto object = NodectBuilder::create("MyFunnyObject", std::make_shared<Context>(nativeContext))
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
	Nodect nodect{"MyFunnyObject", std::make_shared<Context>(nativeContext)};
	{
		nodect.addComponent<Container>();
	}

	auto& notNull = nodect.getComponent<Container>();
	EXPECT_FALSE(notNull.isNullObject());
}

TEST(ComponentTest, testOfBuilders)
{
	auto myNative = NodectBuilder::create("HelloBuilder", nativeContext).build();
	EXPECT_TRUE(myNative.getContext() != nullptr);
	EXPECT_EQ("HelloBuilder", myNative.getTag());
}
