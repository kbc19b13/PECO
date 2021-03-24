#include "stdafx.h"
#include "IActor.h"

void IActor::Draw(EnRenderMode rendermode)
{
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix(),
		rendermode
	);
}

float IActor::GetDistance(const CVector3& v1, const CVector3& v2)
{
	//�v���C���[����G�l�~�[�ɐL�т�x�N�g�����v�Z�B
	CVector3 d_Vec = v1 - v2;
	//�v���C���[�ƃG�l�~�[�̋������v�Z�B
	float distance = d_Vec.Length();

	return distance;
}