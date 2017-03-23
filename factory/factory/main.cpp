#include "stdafx.h"
#include "Canvas.h"
#include "Designer.h"
#include "Painter.h"
#include "Client.h"


int main()
{
	CCanvas canvas;
	CDesigner designer;
	CPainter painter;
	CClient client(designer, painter);
	client.TurnToDesigner(std::cin);
	client.TurnToPainter(canvas);
	
    return 0;
}

