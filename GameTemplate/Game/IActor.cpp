#include "stdafx.h"
#include "IActor.h"

void IActor::Draw(int rendermode)
{
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix(),
		rendermode
	);
}