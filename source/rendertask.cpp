#include "rendertask.h"

RenderTask::RenderTask()
{
	mBackground = QBrush(QColor(46,46,46));
}

RenderTask::~RenderTask()
{

}

void RenderTask::paint(QPainter* painter, QPaintEvent* event)
{
	painter->fillRect(event->rect(), mBackground);
}