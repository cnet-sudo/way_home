#include "GameLibrary.h"

string game::IntToStr(int number)  // ���������� �������������� ���� � ����������
{

    ostringstream TextString;    // �������� ����������
    TextString << number;		//������� � ��� ����� �����, �� ���� ��������� ������
    
    return TextString.str();
}



