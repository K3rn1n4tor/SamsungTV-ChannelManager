#ifndef CHANNELMANAGER_H
#define CHANNELMANAGER_H

#include <QtWidgets/QMainWindow>
#include "ui_channelmanager.h"

class ChannelManager : public QMainWindow
{
	Q_OBJECT

public:
	ChannelManager(QWidget *parent = 0);
	~ChannelManager();

private:
	Ui::ChannelManagerClass ui;
};

#endif // CHANNELMANAGER_H
