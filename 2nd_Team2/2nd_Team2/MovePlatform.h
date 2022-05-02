#pragma once
#include "Obj.h"
class CMovePlatform : public CObj
{
public:
	CMovePlatform();
	~CMovePlatform();

	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;
	void CollisionEnter(CObj* _sour) override;

	void SetSize(const float _width, const float _height) {
		m_tInfo.fWidth = _width;
		m_tInfo.fHeight = _height;
	}

	void SetDirection(const Vector2D _dir) {
		m_tDir = _dir;
	};
	void SetArea(const RECT _area) {
		m_area = _area;
	};

private:
	Vector2D m_tDir;
	RECT m_area;
};

