#include "RankingWidget.h"

RankingWidget::RankingWidget(QWidget *parent)
	:QWidget(parent)
{
	main_layout = new QVBoxLayout();
	main_layout->setContentsMargins(10, 10, 10, 10);

	QVBoxLayout *layout = new QVBoxLayout();
	layout->setContentsMargins(10, 10, 10, 10);
	layout->addLayout(main_layout);
	layout->addStretch();

	setLayout(layout);
}

RankingWidget::~RankingWidget()
{
	delete main_layout;
}

void RankingWidget::addItem(RankingLabel *label)
{
	main_layout->addWidget(label);
	this->setMinimumWidth(label->width());
}