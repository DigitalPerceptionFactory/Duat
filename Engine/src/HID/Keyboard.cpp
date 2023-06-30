#include "Keyboard.h"



//-------------------- KEYBOARD EVENT --------------------\\

KeyboardEvent::KeyboardEvent() :
	type(Invalid), keycode(0u)
{}

KeyboardEvent::KeyboardEvent(const EventType & eventType, const unsigned char & key)
	: type(eventType), keycode(key)
{}

bool KeyboardEvent::IsPress() const {
	return type == Press;
}

bool KeyboardEvent::IsRelease() const {
	return type == Release;
}

bool KeyboardEvent::IsValid() const {
	return type != Invalid;
}

unsigned char KeyboardEvent::GetKeyCode() const {
	return keycode;
}

KeyboardEvent::EventType KeyboardEvent::GetType() const {
	return type;
}








//-------------------- KEYBOARD --------------------\\

Keyboard::Keyboard() {
	m_KeyStates.reset();
	charAutorepeat = keyAutorepeat = 0;
}

bool Keyboard::IsKeyDown(const unsigned char & key) const {
	return m_KeyStates[key];
}

void Keyboard::Press(const unsigned char & key) {
	m_KeyStates[key] = 1;
	m_EventBuffer.push(KeyboardEvent(KeyboardEvent::EventType::Press, key));
}

void Keyboard::Release(const unsigned char & key) {
	m_KeyStates[key] = 0;
	m_EventBuffer.push(KeyboardEvent(KeyboardEvent::EventType::Release, key));
}

void Keyboard::InputChar(const unsigned char & key) {
	m_CharBuffer.push(key);
}

unsigned char Keyboard::ReadChar() {
	if (m_CharBuffer.empty())
		return 0u;
	else
	{
		unsigned char c = m_CharBuffer.front();
		m_CharBuffer.pop();
		return c;
	}
}

KeyboardEvent Keyboard::ReadEvent() {
	if (m_EventBuffer.empty())
		return KeyboardEvent();
	else
	{
		KeyboardEvent e = m_EventBuffer.front();
		m_EventBuffer.pop();
		return e;
	}
}

bool Keyboard::IsCharBufferEmpty() const {
	return m_CharBuffer.empty();
}

bool Keyboard::isEventBufferEmpty() const {
	return m_EventBuffer.empty();
}

void Keyboard::SetCharAutorepeat(const bool& yn) {
	charAutorepeat = yn;
}

void Keyboard::SetKeyAutorepeat(const bool& yn) {
	keyAutorepeat = yn;
}

bool Keyboard::IsCharAutorepeat() const {
	return charAutorepeat;
}

bool Keyboard::IsKeyAutorepeat() const {
	return keyAutorepeat;
}

void Keyboard::ClearState() {
	m_KeyStates.reset();
}