#pragma once
#include <queue>
#include <bitset>


class KeyboardEvent {
public:
	enum EventType {
		Press,
		Release,
		Invalid
	};
	KeyboardEvent();
	KeyboardEvent(const EventType & eventType, const unsigned char & key);

	bool IsPress() const;
	bool IsRelease() const;
	bool IsValid() const;
	unsigned char GetKeyCode() const;
	EventType GetType() const;
private:
	EventType type;
	unsigned char keycode;
};


class Keyboard
{
public:
	Keyboard();
	bool IsKeyDown(const unsigned char & key) const;
	void Press(const unsigned char & key);
	void Release(const unsigned char & key);
	void InputChar(const unsigned char & key);
	bool IsCharBufferEmpty() const;
	bool isEventBufferEmpty() const;
	unsigned char ReadChar();
	KeyboardEvent ReadEvent();
	void SetCharAutorepeat(const bool & yn);
	void SetKeyAutorepeat(const bool & yn);
	bool IsCharAutorepeat() const;
	bool IsKeyAutorepeat() const;
	void ClearState();
private:
	bool charAutorepeat;
	bool keyAutorepeat;
	std::queue<unsigned char> m_CharBuffer;
	std::queue<KeyboardEvent> m_EventBuffer;
	std::bitset<256> m_KeyStates;
};