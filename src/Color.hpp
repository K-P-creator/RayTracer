#pragma once
//simple color struct (R,B,G) oops
#include <fstream>
struct Color
{
    int m_red;
    int m_blue;
    int m_green;

    Color() { m_red = m_blue = m_green = 0; }
    Color(int red, int green, int blue) { m_red = red; 
                                          m_green = green; 
                                          m_blue = blue; }
    Color (const Color & color){ m_red = color.m_red;
                                 m_blue = color.m_blue;
                                 m_green = color.m_green;
    }

    Color operator = (Color& rhs) { m_red = rhs.m_red; m_blue = rhs.m_blue; m_green = rhs.m_green; return *this; }
    Color operator = (const Color& rhs) { m_red = rhs.m_red; m_blue = rhs.m_blue; m_green = rhs.m_green; return *this; }

    Color operator + (Color& rhs) {return Color(m_red += rhs.m_red,
                                                m_blue += rhs.m_blue,
                                                m_green += rhs.m_green);
    }
    Color operator + (const Color& rhs) { return Color(m_red += rhs.m_red, 
                                                       m_blue += rhs.m_blue, 
                                                       m_green += rhs.m_green); }
    friend std::ofstream& operator << (std::ofstream& out, const Color& color) {
        out << color.m_red << '\n';
        out << color.m_green << '\n';
        out << color.m_blue << "\n";
        return out;
    }
    friend bool operator==(Color& lhs, Color& rhs) {
        if (lhs.m_blue == rhs.m_blue &&
            lhs.m_green == rhs.m_green &&
            lhs.m_red == rhs.m_red) {
            return true;} else { return false; }}
        };




