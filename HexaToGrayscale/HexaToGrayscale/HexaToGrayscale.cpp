#include <iostream> 
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <ctime>
using namespace std;
#define bMin (0)

struct RGB {
	unsigned char r, g, b;
};

int POW(int value, int power) {
	int poweredValue = 1;
	while (power != 0) {
		poweredValue *= value;
		--power;
	}
	return poweredValue;
}
RGB ColorConverter(int* hexValue) {
	RGB rgbColor;
	rgbColor.r = ((*hexValue >> 16) & 0xFF);
	rgbColor.g = ((*hexValue >> 8) & 0xFF);
	rgbColor.b = (*hexValue & 0xFF);
	std::cout << std::dec << "R:" << (short)rgbColor.r << " G:" << (short)rgbColor.g << " B:" << (short)rgbColor.b << std::endl;

	return rgbColor;
}
int RGBToGrayScale(RGB& color) {
	unsigned char grayHexColor = (color.r + color.b + color.g) / 3;//Average grayscale without lightweight
	unsigned int grayColor = grayHexColor + (short)grayHexColor * POW(16, 2) + (short)grayHexColor * POW(16, 4);
	return grayColor;
}
int GenerateRandomHex()
{
	int	new_color = ((rand() % (0x00FFFFFF + 1 - bMin)) + bMin);
	return new_color;
}
void ConvertIntoGreyScale(int** pImage, int SizeX, int SizeY) {
	for (int x = 0; x < SizeX; ++x)
	{
		for (int y = 0; y < SizeY; ++y) {
			std::cout << "P(" << x << "," << y << ") >> " << std::hex << (pImage[x][y]) << std::endl;
			RGB rgbColor = ColorConverter(&pImage[x][y]);
			int grayColor = RGBToGrayScale(rgbColor);
			pImage[x][y] = grayColor;
			std::cout << "GrayHex(" << x << "," << y << ")=" << std::hex << (pImage[x][y]) << std::endl;
		}
	}
}
void Delete2DArray(int** _array, int SizeX) {
	for (int x = SizeX - 1; x > 0; --x)
	{
		delete[] _array[x];
	}
	delete[] _array;
}
int main()
{
	srand(time(NULL));
	int tSizeX = 2;
	int tSizeY = 2;
	int** pImageArray = new int* [tSizeX];
	for (int i = 0; i < tSizeX; ++i) {
		pImageArray[i] = new int[tSizeY];
	}
	std::cout << "The value of the int in array are : ";
	for (int x = 0; x < tSizeX; ++x)
	{
		for (int y = 0; y < tSizeY; ++y)
		{
			pImageArray[x][y] = GenerateRandomHex();
			std::cout << pImageArray[x][y];
			if (y != tSizeY - 1 || x != tSizeX - 1)
			{
				std::cout << " ,";
			}
		}
	}
	std::cout << std::dec << std::endl;
	//convert array color into grayscale
	ConvertIntoGreyScale(pImageArray, tSizeX, tSizeY);
	Delete2DArray(pImageArray, tSizeX);
	std::cout << std::endl << std::endl << std::dec;
	//Wait for input don't work on coliru, so i"ll comment it.
	cout << "Press enter to continue" << endl;
	cin.get();
	system("CLS");
	cout << flush;
}
