//
// Created by dawid on 10/29/15.
//

#include "TestExtractingTags.h"
#include "gtest/gtest.h"
#include "Functions.h"

TEST(ExtractingTags, Simple)
{
	const char* text = "sdf";
	auto tags = processTags(text);

	EXPECT_EQ(1, tags.size());
	EXPECT_EQ("sdf", tags[0]);
}

TEST(ExtractingTags, Empty)
{
	const char* text = "";
	auto tags = processTags(text);

	EXPECT_EQ(0, tags.size());
}

TEST(ExtractingTags, FewElements)
{
	const char* text = "aa bb cc zzz";
	auto tags = processTags(text);

	EXPECT_EQ(4, tags.size());
	EXPECT_EQ("aa", tags[0]);
	EXPECT_EQ("bb", tags[1]);
	EXPECT_EQ("cc", tags[2]);
	EXPECT_EQ("zzz", tags[3]);
}

TEST(ExtractingTags, TrickyTest)
{
	const char* text = ",, ,, , ,,, ,,,   bb, , ,, , , , , aa    ,,, , z, , ,,";
	auto tags = processTags(text);

	EXPECT_EQ(2, tags.size());
	EXPECT_EQ("bb", tags[0]);
	EXPECT_EQ("aa", tags[1]);
}

TEST(ExtractingTags, TrickyTest2)
{
	const char* text = ",Text,";
	auto tags = processTags(text);

	EXPECT_EQ(1, tags.size());
	EXPECT_EQ("text", tags[0]);
}

TEST(ExtractingTags, TrickyTest3)
{
	const char* text = ", ,";
	auto tags = processTags(text);

	EXPECT_EQ(0, tags.size());
}

TEST(ExtractingTags, Uppercase)
{
	const char* text = ",ASDF QwEr ,";
	auto tags = processTags(text);

	EXPECT_EQ(2, tags.size());
	EXPECT_EQ("asdf", tags[0]);
	EXPECT_EQ("qwer", tags[1]);
}

TEST(ExtractingTags, Diacarts)
{
	const char* text = "ąę";
	auto tags = processTags(text);

	EXPECT_EQ(1, tags.size());
	EXPECT_EQ("ae", tags[0]);
}

TEST(ExtractingTags, Diacarts2)
{
	const char* text = "ĄęŹ";
	auto tags = processTags(text);

	EXPECT_EQ(1, tags.size());
	EXPECT_EQ("aez", tags[0]);
}

TEST(ExtractingTags, Diacarts3)
{
	const char* text = "¿ĘÐ¿Ð ĄęŹ ¿ŒĘ®¿£Æ¿££";
	auto tags = processTags(text);

	EXPECT_EQ(1, tags.size());
	EXPECT_EQ("aez", tags[0]);
}

TEST(ExtractingTags, Diacarts4)
{
	const char* text = "¿ĘasÐ¿Ð ĄęŹ ¿ŒĘ®¿£Æ¿£ÓĄl£";
	auto tags = processTags(text);

	EXPECT_EQ(3, tags.size());
	EXPECT_EQ("eas", tags[0]);
	EXPECT_EQ("aez", tags[1]);
	EXPECT_EQ("oal", tags[2]);
}

TEST(ExtractingTagsWithHtml, Simple)
{
	const char* text = "<Tag>Text</Tag>";
	auto tags = processTagsStripHtml(text);

	EXPECT_EQ(1, tags.size());
	EXPECT_EQ("text", tags[0]);
}

TEST(ExtractingTagsWithHtml, NoTags)
{
	const char* text = "Text";
	auto tags = processTagsStripHtml(text);

	EXPECT_EQ(1, tags.size());
	EXPECT_EQ("text", tags[0]);
}

TEST(ExtractingTagsWithHtml, Empty)
{
	const char* text = "<Tag></Tag>";
	auto tags = processTagsStripHtml(text);

	EXPECT_EQ(0, tags.size());
}

TEST(ExtractingTagsWithHtml, Empty2)
{
	const char* text = "<Tag>";
	auto tags = processTagsStripHtml(text);

	EXPECT_EQ(0, tags.size());
}

TEST(ExtractingTagsWithHtml, LastWord)
{
	const char* text = "<Tag>aa";
	auto tags = processTagsStripHtml(text);

	EXPECT_EQ(1, tags.size());
	EXPECT_EQ("aa", tags[0]);
}

TEST(ExtractingTagsWithHtml, FirstWord)
{
	const char* text = "aa<Tag>";
	auto tags = processTagsStripHtml(text);

	EXPECT_EQ(1, tags.size());
	EXPECT_EQ("aa", tags[0]);
}

TEST(ExtractingTagsWithHtml, MultipleWord)
{
	const char* text = "aa<Tag>bb<>aa";
	auto tags = processTagsStripHtml(text);

	EXPECT_EQ(3, tags.size());
	EXPECT_EQ("aa", tags[0]);
	EXPECT_EQ("bb", tags[1]);
	EXPECT_EQ("aa", tags[2]);
}

TEST(ExtractingTagsWithHtml, FailTag)
{
	const char* text = "<aa";
	auto tags = processTagsStripHtml(text);

	EXPECT_EQ(1, tags.size());
	EXPECT_EQ("<aa", tags[0]);
}

TEST(ExtractingTagsWithHtml, OnlyTag)
{
	const char* text = "<aa,>";
	auto tags = processTagsStripHtml(text);

	EXPECT_EQ(0, tags.size());
}

TEST(ExtractingTagsWithHtml, AmpersandSpace)
{
	const char* text = "<aa>promocje&nbsp;od&nbsp;1<>";
	auto tags = processTagsStripHtml(text);

	EXPECT_EQ(2, tags.size());
	EXPECT_EQ("promocje", tags[0]);
	EXPECT_EQ("od", tags[1]);
}

TEST(ExtractingTagsWithHtml, AmpersandSpaceTricky)
{
	const char* text = "<aa>promocję&nbsp;od&nbsp1<>";
	auto tags = processTagsStripHtml(text);

	EXPECT_EQ(2, tags.size());
	EXPECT_EQ("promocje", tags[0]);
	EXPECT_EQ("od&nbsp1", tags[1]);
}
