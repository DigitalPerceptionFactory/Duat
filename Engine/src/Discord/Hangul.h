#pragma once
#include <string>


// 44032 - 55171

struct Hangul
{
	Hangul(std::wstring wide) { value = wide.size() != 0 ? (int)wide[0] - 44032 : 0; }
	Hangul(std::wstring l, std::wstring v, std::wstring t) {
		value = (int)t[0] + ((int)v[0] - 1) * 28 + ((int)l[0] - 1) * 588;
	}
	int get_lead() { return 1 + (int)(value / 588); };
	int get_vowel() { return 1 + (value - get_tail()) % 588 / 28; };
	int get_tail() { return value % 28; };

	int value;
};