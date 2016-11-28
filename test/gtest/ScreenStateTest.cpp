#include <gtest/gtest.h>
#include <screen/Screen.h>
#include "screen/StateManager.h"

typedef Screen::State State;

class TestScreen : public Screen
{

public:
	TestScreen(const std::string& screenName)
			: Screen(screenName)
	{
	}

	virtual void onCreate() override
	{
	}

	virtual void onResume() override
	{
	}

	virtual void onPause() override
	{
	}

	virtual void onDestroy() override
	{
	}
};

TEST(ScreenStateTest, simple)
{
	TestScreen testScreen("test");
	EXPECT_EQ(Screen::State::EXIT, testScreen.getState());

	StateManager::onEnter(&testScreen);
	EXPECT_EQ(Screen::State::ENTER, testScreen.getState());

	StateManager::onCreate(&testScreen);
	EXPECT_EQ(Screen::State::CREATE, testScreen.getState());

	StateManager::onResume(&testScreen);
	EXPECT_EQ(Screen::State::RESUME, testScreen.getState());

	StateManager::onPause(&testScreen);
	EXPECT_EQ(Screen::State::PAUSE, testScreen.getState());

	StateManager::onDestroy(&testScreen);
	EXPECT_EQ(Screen::State::DESTROY, testScreen.getState());

	StateManager::onExit(&testScreen);
	EXPECT_EQ(Screen::State::EXIT, testScreen.getState());
}

TEST(ScreenStateTest, multipleCalls)
{
	TestScreen testScreen("test");
	EXPECT_EQ(Screen::State::EXIT, testScreen.getState());

	EXPECT_TRUE(StateManager::onEnter(&testScreen));
	EXPECT_FALSE(StateManager::onEnter(&testScreen));
	EXPECT_EQ(Screen::State::ENTER, testScreen.getState());

	EXPECT_TRUE(StateManager::onCreate(&testScreen));
	EXPECT_FALSE(StateManager::onCreate(&testScreen));
	EXPECT_EQ(Screen::State::CREATE, testScreen.getState());

	EXPECT_TRUE(StateManager::onResume(&testScreen));
	EXPECT_FALSE(StateManager::onResume(&testScreen));
	EXPECT_FALSE(StateManager::onResume(&testScreen));
	EXPECT_FALSE(StateManager::onResume(&testScreen));
	EXPECT_EQ(Screen::State::RESUME, testScreen.getState());

	EXPECT_TRUE(StateManager::onPause(&testScreen));
	EXPECT_FALSE(StateManager::onPause(&testScreen));
	EXPECT_EQ(Screen::State::PAUSE, testScreen.getState());

	EXPECT_TRUE(StateManager::onDestroy(&testScreen));
	EXPECT_FALSE(StateManager::onDestroy(&testScreen));
	EXPECT_FALSE(StateManager::onDestroy(&testScreen));
	EXPECT_EQ(Screen::State::DESTROY, testScreen.getState());

	EXPECT_TRUE(StateManager::onExit(&testScreen));
	EXPECT_FALSE(StateManager::onExit(&testScreen));
	EXPECT_FALSE(StateManager::onExit(&testScreen));
	EXPECT_FALSE(StateManager::onExit(&testScreen));
	EXPECT_FALSE(StateManager::onExit(&testScreen));
	EXPECT_EQ(Screen::State::EXIT, testScreen.getState());
}

TEST(ScreenStateTest, checkEnterToCreate)
{
	TestScreen testScreen("test");

	EXPECT_TRUE(StateManager::onEnter(&testScreen));
	EXPECT_EQ(Screen::State::ENTER, testScreen.getState());
	//-----------------------------------------------

	EXPECT_FALSE(StateManager::onResume(&testScreen));
	EXPECT_EQ(Screen::State::ENTER, testScreen.getState());

	EXPECT_FALSE(StateManager::onPause(&testScreen));
	EXPECT_EQ(Screen::State::ENTER, testScreen.getState());

	EXPECT_FALSE(StateManager::onPause(&testScreen));
	EXPECT_EQ(Screen::State::ENTER, testScreen.getState());

	EXPECT_TRUE(StateManager::onCreate(&testScreen));
	EXPECT_EQ(Screen::State::CREATE, testScreen.getState());
}

TEST(ScreenStateTest, checkEnterToExit)
{
	TestScreen testScreen("test");

	EXPECT_TRUE(StateManager::onEnter(&testScreen));
	EXPECT_EQ(Screen::State::ENTER, testScreen.getState());
	//-----------------------------------------------

	EXPECT_FALSE(StateManager::onResume(&testScreen));
	EXPECT_EQ(Screen::State::ENTER, testScreen.getState());

	EXPECT_FALSE(StateManager::onPause(&testScreen));
	EXPECT_EQ(Screen::State::ENTER, testScreen.getState());

	EXPECT_FALSE(StateManager::onPause(&testScreen));
	EXPECT_EQ(Screen::State::ENTER, testScreen.getState());

	EXPECT_TRUE(StateManager::onExit(&testScreen));
	EXPECT_EQ(Screen::State::EXIT, testScreen.getState());
}

TEST(ScreenStateTest, checkCreateToResume)
{
	TestScreen testScreen("test");

	EXPECT_TRUE(StateManager::onEnter(&testScreen));
	EXPECT_EQ(Screen::State::ENTER, testScreen.getState());

	EXPECT_TRUE(StateManager::onCreate(&testScreen));
	EXPECT_EQ(Screen::State::CREATE, testScreen.getState());
	//-----------------------------------------------

	EXPECT_FALSE(StateManager::onEnter(&testScreen));
	EXPECT_EQ(Screen::State::CREATE, testScreen.getState());

	EXPECT_FALSE(StateManager::onPause(&testScreen));
	EXPECT_EQ(Screen::State::CREATE, testScreen.getState());

	EXPECT_FALSE(StateManager::onExit(&testScreen));
	EXPECT_EQ(Screen::State::CREATE, testScreen.getState());

	EXPECT_TRUE(StateManager::onResume(&testScreen));
	EXPECT_EQ(Screen::State::RESUME, testScreen.getState());
}

TEST(ScreenStateTest, checkCreateToDestroy)
{
	TestScreen testScreen("test");

	EXPECT_TRUE(StateManager::onEnter(&testScreen));
	EXPECT_EQ(Screen::State::ENTER, testScreen.getState());

	EXPECT_TRUE(StateManager::onCreate(&testScreen));
	EXPECT_EQ(Screen::State::CREATE, testScreen.getState());
	//-----------------------------------------------

	EXPECT_FALSE(StateManager::onEnter(&testScreen));
	EXPECT_EQ(Screen::State::CREATE, testScreen.getState());

	EXPECT_FALSE(StateManager::onPause(&testScreen));
	EXPECT_EQ(Screen::State::CREATE, testScreen.getState());

	EXPECT_FALSE(StateManager::onExit(&testScreen));
	EXPECT_EQ(Screen::State::CREATE, testScreen.getState());

	EXPECT_TRUE(StateManager::onDestroy(&testScreen));
	EXPECT_EQ(Screen::State::DESTROY, testScreen.getState());
}

TEST(ScreenStateTest, checkResumeToPause)
{
	TestScreen testScreen("test");

	EXPECT_TRUE(StateManager::onEnter(&testScreen));
	EXPECT_EQ(Screen::State::ENTER, testScreen.getState());

	EXPECT_TRUE(StateManager::onCreate(&testScreen));
	EXPECT_EQ(Screen::State::CREATE, testScreen.getState());

	EXPECT_TRUE(StateManager::onResume(&testScreen));
	EXPECT_EQ(Screen::State::RESUME, testScreen.getState());
	//-----------------------------------------------

	EXPECT_FALSE(StateManager::onEnter(&testScreen));
	EXPECT_EQ(Screen::State::RESUME, testScreen.getState());

	EXPECT_FALSE(StateManager::onCreate(&testScreen));
	EXPECT_EQ(Screen::State::RESUME, testScreen.getState());

	EXPECT_FALSE(StateManager::onDestroy(&testScreen));
	EXPECT_EQ(Screen::State::RESUME, testScreen.getState());

	EXPECT_FALSE(StateManager::onExit(&testScreen));
	EXPECT_EQ(Screen::State::RESUME, testScreen.getState());

	EXPECT_TRUE(StateManager::onPause(&testScreen));
	EXPECT_EQ(Screen::State::PAUSE, testScreen.getState());
}

TEST(ScreenStateTest, checkPauseToResume)
{
	TestScreen testScreen("test");

	EXPECT_TRUE(StateManager::onEnter(&testScreen));
	EXPECT_EQ(Screen::State::ENTER, testScreen.getState());

	EXPECT_TRUE(StateManager::onCreate(&testScreen));
	EXPECT_EQ(Screen::State::CREATE, testScreen.getState());

	EXPECT_TRUE(StateManager::onResume(&testScreen));
	EXPECT_EQ(Screen::State::RESUME, testScreen.getState());

	EXPECT_TRUE(StateManager::onPause(&testScreen));
	EXPECT_EQ(Screen::State::PAUSE, testScreen.getState());
	//-----------------------------------------------

	EXPECT_FALSE(StateManager::onEnter(&testScreen));
	EXPECT_EQ(Screen::State::PAUSE, testScreen.getState());

	EXPECT_FALSE(StateManager::onCreate(&testScreen));
	EXPECT_EQ(Screen::State::PAUSE, testScreen.getState());

	EXPECT_FALSE(StateManager::onExit(&testScreen));
	EXPECT_EQ(Screen::State::PAUSE, testScreen.getState());

	EXPECT_TRUE(StateManager::onResume(&testScreen));
	EXPECT_EQ(Screen::State::RESUME, testScreen.getState());
}

TEST(ScreenStateTest, checkPauseToDestroy)
{
	TestScreen testScreen("test");

	EXPECT_TRUE(StateManager::onEnter(&testScreen));
	EXPECT_EQ(Screen::State::ENTER, testScreen.getState());

	EXPECT_TRUE(StateManager::onCreate(&testScreen));
	EXPECT_EQ(Screen::State::CREATE, testScreen.getState());

	EXPECT_TRUE(StateManager::onResume(&testScreen));
	EXPECT_EQ(Screen::State::RESUME, testScreen.getState());

	EXPECT_TRUE(StateManager::onPause(&testScreen));
	EXPECT_EQ(Screen::State::PAUSE, testScreen.getState());
	//-----------------------------------------------

	EXPECT_FALSE(StateManager::onEnter(&testScreen));
	EXPECT_EQ(Screen::State::PAUSE, testScreen.getState());

	EXPECT_FALSE(StateManager::onCreate(&testScreen));
	EXPECT_EQ(Screen::State::PAUSE, testScreen.getState());

	EXPECT_FALSE(StateManager::onExit(&testScreen));
	EXPECT_EQ(Screen::State::PAUSE, testScreen.getState());

	EXPECT_TRUE(StateManager::onDestroy(&testScreen));
	EXPECT_EQ(Screen::State::DESTROY, testScreen.getState());
}

TEST(ScreenStateTest, checkDestroyToCreate)
{
	TestScreen testScreen("test");

	EXPECT_TRUE(StateManager::onEnter(&testScreen));
	EXPECT_EQ(Screen::State::ENTER, testScreen.getState());

	EXPECT_TRUE(StateManager::onCreate(&testScreen));
	EXPECT_EQ(Screen::State::CREATE, testScreen.getState());

	EXPECT_TRUE(StateManager::onResume(&testScreen));
	EXPECT_EQ(Screen::State::RESUME, testScreen.getState());

	EXPECT_TRUE(StateManager::onPause(&testScreen));
	EXPECT_EQ(Screen::State::PAUSE, testScreen.getState());

	EXPECT_TRUE(StateManager::onDestroy(&testScreen));
	EXPECT_EQ(Screen::State::DESTROY, testScreen.getState());
	//-----------------------------------------------

	EXPECT_FALSE(StateManager::onEnter(&testScreen));
	EXPECT_EQ(Screen::State::DESTROY, testScreen.getState());

	EXPECT_FALSE(StateManager::onResume(&testScreen));
	EXPECT_EQ(Screen::State::DESTROY, testScreen.getState());

	EXPECT_FALSE(StateManager::onPause(&testScreen));
	EXPECT_EQ(Screen::State::DESTROY, testScreen.getState());

	EXPECT_TRUE(StateManager::onCreate(&testScreen));
	EXPECT_EQ(Screen::State::CREATE, testScreen.getState());
}

TEST(ScreenStateTest, checkDestroyToExit)
{
	TestScreen testScreen("test");

	EXPECT_TRUE(StateManager::onEnter(&testScreen));
	EXPECT_EQ(Screen::State::ENTER, testScreen.getState());

	EXPECT_TRUE(StateManager::onCreate(&testScreen));
	EXPECT_EQ(Screen::State::CREATE, testScreen.getState());

	EXPECT_TRUE(StateManager::onResume(&testScreen));
	EXPECT_EQ(Screen::State::RESUME, testScreen.getState());

	EXPECT_TRUE(StateManager::onPause(&testScreen));
	EXPECT_EQ(Screen::State::PAUSE, testScreen.getState());

	EXPECT_TRUE(StateManager::onDestroy(&testScreen));
	EXPECT_EQ(Screen::State::DESTROY, testScreen.getState());
	//-----------------------------------------------

	EXPECT_FALSE(StateManager::onEnter(&testScreen));
	EXPECT_EQ(Screen::State::DESTROY, testScreen.getState());

	EXPECT_FALSE(StateManager::onResume(&testScreen));
	EXPECT_EQ(Screen::State::DESTROY, testScreen.getState());

	EXPECT_FALSE(StateManager::onPause(&testScreen));
	EXPECT_EQ(Screen::State::DESTROY, testScreen.getState());

	EXPECT_TRUE(StateManager::onExit(&testScreen));
	EXPECT_EQ(Screen::State::EXIT, testScreen.getState());
}

TEST(ScreenStateTest, checkExitToEnter)
{
	TestScreen testScreen("test");

	EXPECT_TRUE(StateManager::onEnter(&testScreen));
	EXPECT_EQ(Screen::State::ENTER, testScreen.getState());

	EXPECT_TRUE(StateManager::onCreate(&testScreen));
	EXPECT_EQ(Screen::State::CREATE, testScreen.getState());

	EXPECT_TRUE(StateManager::onResume(&testScreen));
	EXPECT_EQ(Screen::State::RESUME, testScreen.getState());

	EXPECT_TRUE(StateManager::onPause(&testScreen));
	EXPECT_EQ(Screen::State::PAUSE, testScreen.getState());

	EXPECT_TRUE(StateManager::onDestroy(&testScreen));
	EXPECT_EQ(Screen::State::DESTROY, testScreen.getState());

	EXPECT_TRUE(StateManager::onExit(&testScreen));
	EXPECT_EQ(Screen::State::EXIT, testScreen.getState());
	//-----------------------------------------------

	EXPECT_FALSE(StateManager::onCreate(&testScreen));
	EXPECT_EQ(Screen::State::EXIT, testScreen.getState());

	EXPECT_FALSE(StateManager::onResume(&testScreen));
	EXPECT_EQ(Screen::State::EXIT, testScreen.getState());

	EXPECT_FALSE(StateManager::onPause(&testScreen));
	EXPECT_EQ(Screen::State::EXIT, testScreen.getState());

	EXPECT_FALSE(StateManager::onDestroy(&testScreen));
	EXPECT_EQ(Screen::State::EXIT, testScreen.getState());

	EXPECT_TRUE(StateManager::onEnter(&testScreen));
	EXPECT_EQ(Screen::State::ENTER, testScreen.getState());
}
