#pragma once
#include "EnemyBase.h"
class TestEnemy : public EnemyBase
{
public:
	TestEnemy();
	~TestEnemy();
	void Init() override;
	void Load() override;
	void Release() override;
	void Update() override;
	void Draw3D() override;
	void Draw2D() override;

	void Damage(int damage);
	void Damage();

private:
	int mHP;
};