#ifndef CHANGECOLOR_H
#define CHANGECOLOR_H

#include <string>

std::string ChangeColor(std::string text, int pos);

#endif // CHANGECOLOR_H

std::string ChangeColor(std::string text, int pos)
{
    std::string textColor = text.substr(0, pos);

    textColor += "<font color=\"red\">";
    textColor += text[pos];
    textColor += "</font>";
    textColor += text.substr(pos+1);

    return textColor;
}
