#include "loadingscreen.hpp"
#include "ui_loadingscreen.h"

LoadingScreen::LoadingScreen(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::LoadingScreen)
{
	ui->setupUi(this);
}

LoadingScreen::~LoadingScreen()
{
	delete ui;
}

void LoadingScreen::setMaximumProgress(int progress)
{
	ui->progressBar->setMaximum(progress);
}

void LoadingScreen::progress()
{
	ui->progressBar->setValue(ui->progressBar->value() + 1);
}
