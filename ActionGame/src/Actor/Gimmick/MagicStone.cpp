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
		mWorld->AddActor(ActorGroup::UI, std::make_shared<TextDraw>(mWorld, mName+"�̖��@����ɓ��ꂽ"));
		Dead();
	}
}

void MagicStone::onMessage(EventMessage message, void * p)
{

}

void MagicStone::OverLapSearch()
{
	//�v���C���[�������Ă��閂�@�̌���
	if (!mPlayer) return;
	auto magiclist = ((Player*)mPlayer.get())->GetHaveMagic();

	//�v���C���[�̎����Ă閂�@�����ς�����猟���J�n
	//if (mListSize == magiclist.size()) return;
	//mListSize = magiclist.size();

	//�v���C���[�����@����������ĂȂ�������`��
	if (magiclist.size() == 0)
	{
		isDraw = true; 
		return;
	}

	//�v���C���[���������@�������Ă����玩�g������
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
