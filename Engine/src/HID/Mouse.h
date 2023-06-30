#pragma once
#include <queue>



struct MousePosition {
	int x, y;
};

class MouseEvent {
public:
	enum EventType {
		LPress,
		LRelease,
		RPress,
		RRelease,
		MPress,
		MRelease,
		ScrollUp,
		ScrollDown,
		Move,
		MoveRaw,
		Invalid
	};

	MouseEvent();
	MouseEvent(const EventType& event, const int& posX, const int& posY);

	
	bool IsValid() const;
	EventType GetType() const;
	MousePosition GetPos() const;
	int GetPosX() const;
	int GetPosY() const;
private:
	EventType type;
	int x, y;
};


class Mouse {
public:
	Mouse();
	void OnLeftDown(const int & x, const int & y);
	void OnLeftUp(const int & x, const int & y);
	void OnRightDown(const int & x, const int & y);
	void OnRightUp(const int & x, const int & y);
	void OnMidDown(const int & x, const int & y);
	void OnMidUp(const int & x, const int & y);
	void OnScrollUp(const int & x, const int & y);
	void OnScrollDown(const int & x, const int & y);
	void OnMove(const int & x, const int & y);
	void OnMove(const MousePosition & position);
	void OnRawMove(const int & x, const int & y);
	void OnRawMove(const MousePosition & position);

	void ResetRaw();

	MouseEvent ReadEvent();
	bool IsEventBufferEmpty() const;
	bool IsLeftDown() const;
	bool IsRightDown() const;
	bool IsMidDown() const;
	int GetPosX() const;
	int GetPosY() const;
	MousePosition GetPos() const;
	int GetRawX() const;
	int GetRawY() const;
	MousePosition GetRaw() const;
	int GetWheelAngle() const;
private:
	std::queue<MouseEvent>		m_EventBuffer;

	bool    m_LeftDown;
	bool    m_RightDown;
	bool    m_MidDown;
	int     m_x;
	int     m_y;
	int     m_rawX;
	int	    m_rawY;
	int     m_wheelAngle;
};