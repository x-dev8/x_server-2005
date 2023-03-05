#include "Font3D.h"
#include "Font3DManager.h"

void Font3D::Destroy()
{
	BillboardManager<Billboard3D>::Instance()->DeleteBillboard( billboard_ );

    device_ = 0;
}

void Font3D::CreateVertex()
{
	billboard_ = BillboardManager<Billboard3D>::Instance()->CreateBillboard();
}