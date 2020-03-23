#include "rendertask.h"

RenderTask::RenderTask()
{
	mBackground = QBrush(QColor(46,46,46));
}

RenderTask::~RenderTask()
{

}

void RenderTask::RenderFrame(QPainter* painter, QPaintEvent *event, QImage image, QPoint pos, qreal scale)
{
	painter->save();
	painter->fillRect(event->rect(), mBackground);

	painter->scale(scale, scale);

	if (&image != NULL)
	{
		painter->drawImage(pos, image);
	}
	
	painter->restore();
}