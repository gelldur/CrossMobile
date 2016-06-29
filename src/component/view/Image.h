//
// Created by Dawid Drozd aka Gelldur on 6/22/16.
//

#pragma once

#include <component/Component.h>

/**
 * Implementation is environment specific
 */
class Image : public Component
{
	using inherited = Component;
public:
	virtual void loadImage(const std::string& url);
	virtual void image(const std::string& name);

	COMPONENT_TO_STRING(Image)

	static Image& getNullObject();
};

class NullImage : public Image
{
public:
	virtual void loadImage(const std::string& url) override;
	virtual void image(const std::string& name) override;
};
