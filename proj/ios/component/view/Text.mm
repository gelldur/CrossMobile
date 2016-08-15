//
// Created by Dawid Drozd aka Gelldur on 6/15/16.
//

#include <component/view/Text.h>

#include <platform/Context.h>
#include <log.h>
#include <ColorUtils.h>
#include <Utils.h>
#include <acme/text/AttributedText.h>
#include <platform/ContextHelper.h>

#import <UIKit/UIKit.h>

void Text::setText(const char* text)
{
	auto context = getContext();

	UILabel* label = ContextHelper::getNative(context);
	label.text = [NSString stringWithUTF8String:text];
}

void Text::setText(const std::string& text)
{
	setText(text.c_str());
}

void Text::setTextColor(int color)
{
	auto context = getContext();

	UILabel* label = ContextHelper::getNative(context);
	label.textColor = UIColorFromRGB(color);
}

void Text::setTextAttributed(const AttributedText& attributedText)
{
	NSMutableAttributedString* attributedString= [[NSMutableAttributedString alloc] initWithString:@""];

	for(auto& element : attributedText.getElements())
	{
		NSAttributedString* attachmentString;
		if(element.type == AttributedText::ElementType::IMAGE_LOCAL)
		{
			//TODO http://stackoverflow.com/questions/26105803/center-nstextattachment-image-next-to-single-line-uilabel
			NSTextAttachment* attachment = [[NSTextAttachment alloc] init];
            attachment.image = [UIImage imageNamed:stringConvert(element.value)];
            attachmentString = [NSAttributedString attributedStringWithAttachment:attachment];
		}
		else
		{
			attachmentString = [[NSAttributedString alloc] initWithString:stringConvert(element.value)];
		}

		[attributedString appendAttributedString:attachmentString];
	}

	auto context = getContext();

	UILabel* label = ContextHelper::getNative(context);
	label.attributedText = attributedString;
}
