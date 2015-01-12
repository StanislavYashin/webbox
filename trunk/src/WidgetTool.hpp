#pragma once

#include <QtWidgets>

void traversalControl(const QObjectList& q,)
{
	for (int i = 0; i < q.length(); i++)
	{
		if (!q.at(i)->children().empty())
		{
			traversalControl(q.at(i)->children());
		}
		else
		{
			QObject* o = q.at(i);
			if (o->inherits("QPushButton")) {
				QPushButton* b = qobject_cast<QPushButton*>(o);
				b->setText("<>");
			}
		}
	}
}
