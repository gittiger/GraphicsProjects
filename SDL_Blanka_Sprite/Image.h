#pragma once
#include <string>
using namespace std;

enum IMAGE_TYPE { PNG, JPG, JPEG, BMP, };

class Image
{
#pragma region Properties

private:
	string m_name;
	string m_path;
	IMAGE_TYPE m_format;
	int m_order;
#pragma endregion

#pragma region Methods
public:
	Image();
	Image(string fullPath, int order = 0);
	string getName() const;
	void setName(string name);
	string getPath() const;
	void setPath(string path);
	IMAGE_TYPE getFormat() const;
	void setFormat(IMAGE_TYPE format);
	int getOrder() const;
	void setOrder(int order);
#pragma endregion

};
