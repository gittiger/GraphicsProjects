#include "Image.h"
#include <algorithm>

Image::Image()
{
}

Image::Image(string fullPath, int order)
{
	string base_filename = fullPath.substr(fullPath.find_last_of("/\\") + 1);
	std::size_t pos = fullPath.find(base_filename);
	string filename_path = fullPath.substr(0, pos);
	string format = base_filename.substr(base_filename.find_last_of('.')+1);
	std::transform(format.begin(), format.end(), format.begin(), ::toupper);
	setName(base_filename);
	setPath(filename_path);
	IMAGE_TYPE formatType;
	if (format.compare("PNG") == 0)
		formatType = PNG;

	setFormat(formatType);
	setOrder(order);
}

string Image::getName() const
{
	return m_name;
}

void Image::setName(string name)
{
	m_name = name;
}

string Image::getPath() const
{
	return m_path;
}

void Image::setPath(string path)
{
	m_path = path;
}

IMAGE_TYPE Image::getFormat() const
{
	return m_format;
}

void Image::setFormat(IMAGE_TYPE format)
{
	m_format = format;
}

int Image::getOrder() const
{
	return m_order;
}

void Image::setOrder(int order)
{
	m_order = order;
}