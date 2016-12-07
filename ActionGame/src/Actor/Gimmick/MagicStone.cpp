#include "MagicStone.h"
#include"../UI/TextDraw.h"
#include"../Player/Player.h"

MagicStone::MagicStone(IWorld * world, std::string name, Vector3 & position, MagicList magic) :
Actor(world,name,position, { Line(position,position + Vector3(0,0,0)),10.0f }),
mMagicName(magic),
mTimer(0),
mListSize(-1),
isDraw(false)
{
	mPlayer = mWorld->FindActor("Player");
	mModelHandle = MV1LoadModel("./res/MagicStone/MagicStone.mv1");
}

MagicStone::~MagicStone()
{
	MV1DeleteModel(mModelHandle);
}

void MagicStone::onUpdate(float deltaTime)
{
	OverLapSearch();
	Move(deltaTime);
}

void MagicStone::onDraw() const
{
	MV1SetMatrix(mModelHandle, MMult(MGetRotY(mTimer), GetPose()));
	if(isDraw)MV1DrawModel(mModelHandle);
}

void MagicStone::onCollide(Actor & other)
{
	if (other.GetTag() == Tag::PLAYER)
	{
		other.HandleMessage(EventMessage::MAGIC_GET,(void*)&mMagicName);
		mWorld->AddActor(ActorGroup::UI, std::make_shared<TextDraw>(mWorld, mName+"の魔法を手に入れた"));
		Dead();
	}
}

void MagicStone::onMessage(EventMessage message, void * p)
{

}

void MagicStone::OverLapSearch()
{
	//プレイヤーが持っている魔法の検索
	if (!mPlayer) return;
	auto magiclist = ((Player*)mPlayer.get())->GetHaveMagic();

	//プレイヤーの持ってる魔法数が変わったら検索開始
	//if (mListSize == magiclist.size()) return;
	//mListSize = magiclist.size();

	//プレイヤーが魔法を一つも持ってなかったら描画
	if (magiclist.size() == 0)
	{
		isDraw = true; 
		return;
	}

	//プレイヤーが同じ魔法を持っていたら自身を消滅
	for (int i = 0; i < magiclist.size(); i++)
	{
		if (mMagicName == magiclist[i])
		{
			Dead();
		}
		else
		{
			isDraw = true;
		}
	}
}

void MagicStone::Move(float deltaTIme)
{
	mTimer += deltaTIme;
	mPosition.y += sin(mTimer) * 0.03f;
}
