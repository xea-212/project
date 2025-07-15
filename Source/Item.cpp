#include "Item.h"
#include "Stage.h"
#include "Player.h"
#include <assert.h>

Item::Item(VECTOR3 pos, int number)
{
	transform.position = pos;
	itemId = number;

	switch (itemId)
	{
	case 9:
		hModel = MV1LoadModel("data/models/redpepper.mv1");
		assert(hModel >= 0);
		break;
	}
}

Item::~Item()
{
}

void Item::Update()
{
	Stage* st = FindGameObject<Stage>();
	Player* p = FindGameObject<Player>();
	if (st->CheckHitItem(transform.position + VECTOR3(0, 50, 0)))
	{
		switch (itemId)
		{
		case 9:
			const float goalPos = p->GetTransform().position.x + 3400; 
			float pPos = p->GetTransform().position.x;
			if (goalPos > pPos)
			{
				p->PapperSride();
			}
			break;
		}
	}
}
