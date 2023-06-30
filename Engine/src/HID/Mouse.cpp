#include "Mouse.h"



//-------------------- MOUSE EVENT --------------------\\

MouseEvent::MouseEvent()
	: type(Invalid), x(0), y(0)
{}

MouseEvent::MouseEvent(const EventType& event, const int& posX, const int& posY)
	: type(event), x(posX), y(posY)
{}


bool MouseEvent::IsValid() const {
	return type != Invalid;
}

MouseEvent::EventType MouseEvent::GetType() const {
	return type;
}

MousePosition MouseEvent::GetPos() const {
	return { x,y };
}

int MouseEvent::GetPosX() const {
	return x;
}

int MouseEvent::GetPosY() const {
	return y;
}






//-------------------- MOUSE --------------------\\

Mouse::Mouse() {
	m_x = m_y = 0;
	m_LeftDown = m_RightDown = m_MidDown = 0;
}

void Mouse::OnMove(const int & x, const int & y) {
	m_x = x;
	m_y = y;
	m_EventBuffer.push(MouseEvent(MouseEvent::EventType::Move, m_x, m_y));
}

void Mouse::OnMove(const MousePosition & position) {
	m_x = position.x;
	m_y = position.y;
	m_EventBuffer.push(MouseEvent(MouseEvent::EventType::Move, m_x, m_y));
}

void Mouse::OnRawMove(const int & x, const int & y) {
	m_rawX = x;
	m_rawY = y;
	m_EventBuffer.push(MouseEvent(MouseEvent::EventType::MoveRaw, m_rawX, m_rawY));
}

void Mouse::OnRawMove(const MousePosition & position) {
	m_rawX = position.x;
	m_rawY = position.y;
	m_EventBuffer.push(MouseEvent(MouseEvent::EventType::MoveRaw, m_rawX, m_rawY));
}

void Mouse::ResetRaw()
{
	m_rawX = 0;
	m_rawY = 0;
}

void Mouse::OnLeftDown(const int & x, const int & y) {
	m_x = x;
	m_y = y;
	m_LeftDown = true;
	m_EventBuffer.push(MouseEvent(MouseEvent::LPress, m_x, m_y));
}

void Mouse::OnLeftUp(const int & x, const int & y) {
	m_x = x;
	m_y = y;
	m_LeftDown = false;
	m_EventBuffer.push(MouseEvent(MouseEvent::LRelease, m_x, m_y));
}

void Mouse::OnRightDown(const int & x, const int & y) {
	m_x = x;
	m_y = y;
	m_RightDown = true;
	m_EventBuffer.push(MouseEvent(MouseEvent::RPress, m_x, m_y));
}

void Mouse::OnRightUp(const int & x, const int & y) {
	m_x = x;
	m_y = y;
	m_RightDown = false;
	m_EventBuffer.push(MouseEvent(MouseEvent::RRelease, m_x, m_y));
}

void Mouse::OnMidDown(const int & x, const int & y) {
	m_x = x;
	m_y = y;
	m_MidDown = true;
	m_EventBuffer.push(MouseEvent(MouseEvent::MPress, m_x, m_y));
}

void Mouse::OnMidUp(const int & x, const int & y) {
	m_x = x;
	m_y = y;
	m_MidDown = false;
	m_EventBuffer.push(MouseEvent(MouseEvent::MRelease, m_x, m_y));
}

void Mouse::OnScrollUp(const int & x, const int & y) {
	m_x = x;
	m_y = y;
	m_wheelAngle += 1;
	m_EventBuffer.push(MouseEvent(MouseEvent::EventType::ScrollUp, m_x, m_y));
}

void Mouse::OnScrollDown(const int & x, const int & y) {
	m_x = x;
	m_y = y;
	m_wheelAngle -= 1;
	m_EventBuffer.push(MouseEvent(MouseEvent::EventType::ScrollDown, m_x, m_y));
}

MouseEvent Mouse::ReadEvent() {
	if (m_EventBuffer.empty())
		return MouseEvent();
	else
	{
		MouseEvent e = m_EventBuffer.front();
		m_EventBuffer.pop();
		return e;
	}
}

bool Mouse::IsEventBufferEmpty() const {
	return m_EventBuffer.empty();
}

bool Mouse::IsLeftDown() const {
	return m_LeftDown;
}

bool Mouse::IsRightDown() const {
	return m_RightDown;
}

bool Mouse::IsMidDown() const {
	return m_MidDown;
}

int Mouse::GetPosX() const {
	return m_x;
}

int Mouse::GetPosY() const {
	return m_y;
}

MousePosition Mouse::GetPos() const {
	return { m_x,m_y };
}

int Mouse::GetRawX() const {
	return m_rawX;
}

int Mouse::GetRawY() const {
	return m_rawY;
}

MousePosition Mouse::GetRaw() const {
	return { m_rawX, m_rawY };
}

int Mouse::GetWheelAngle() const {
	return m_wheelAngle;
}