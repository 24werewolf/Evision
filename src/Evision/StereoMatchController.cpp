#include "StereoMatchController.h"
#include <QMessageBox>
#include <QFileDialog>
#include "StereoMatch.h"

StereoMatchController::StereoMatchController(QObject *parent)
	: QObject(parent)
{
	m_entity = StereoMatchParamEntity::getInstance();
}

StereoMatchController::~StereoMatchController()
{
}
//����:ƥ��Ĭ�ϲ���
void StereoMatchController::setDefaultMatchParamCommand()
{
	if (m_entity->getBM())
	{
		m_entity->setUniradio(5);
		m_entity->setPrefilcap(31);
		m_entity->setSpecwinsz(69);
		m_entity->setSadWinsz(21);
		m_entity->setMinDisp(-3);
		m_entity->setNumDisparities(144);
		m_entity->setSpecrange(34);
		m_entity->setMaxdifdisp12(2);
		m_entity->setTextThread(50);

	}
	else if (m_entity->getSGBM())
	{
		m_entity->setUniradio(5);
		m_entity->setPrefilcap(47);
		m_entity->setSpecwinsz(1);
		m_entity->setSadWinsz(17);
		m_entity->setMinDisp(1);
		m_entity->setNumDisparities(64);
		m_entity->setSpecrange(14);
		m_entity->setMaxdifdisp12(1);
		m_entity->setMODE_HH(true);
	}
	else if (m_entity->getMODE_HH())
	{
		m_entity->setMinDisp(-64);
		m_entity->setNumDisparities(64);
	}
	else
	{
		QMessageBox::information(NULL, QStringLiteral("����"), QStringLiteral("û��ѡ��ƥ���㷨"), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
	}
}
//����:ƥ��
void StereoMatchController::MatchCommand()
{
	QFileDialog * fileDialog = new QFileDialog();
	fileDialog->setWindowTitle(QStringLiteral("��ѡ��������ͷ�����ͼƬ"));
	fileDialog->setNameFilter(QStringLiteral("ͼƬ�ļ�(*.jpg *.png *.jpeg)"));
	fileDialog->setFileMode(QFileDialog::ExistingFile);
	if (fileDialog->exec() == QDialog::Accepted)
	{
		ImageL = fileDialog->selectedFiles().at(0);
		fileDialog->setWindowTitle(QStringLiteral("��ѡ��������ͷ�����ͼƬ"));
		if (fileDialog->exec() == QDialog::Accepted)
		{
			ImageR = fileDialog->selectedFiles().at(0);
			if (!ImageL.isEmpty() && !ImageR.isEmpty())
			{
				//����ͼƬ�ļ�����
				QFileDialog * fileDialog2 = new QFileDialog();
				fileDialog2->setWindowTitle(QStringLiteral("��ѡ����������ļ�"));
				fileDialog2->setNameFilter(QStringLiteral("YML/XML�ļ�(*.yml *.yaml *.xml)"));
				fileDialog2->setFileMode(QFileDialog::ExistingFile);
				if (fileDialog2->exec() == QDialog::Accepted)
				{
					paramsFile = fileDialog2->selectedFiles().at(0);
					if (!paramsFile.isEmpty())
					{
						//�����ļ�����
						StereoMatch *_stereoMatch = new StereoMatch(ImageL.toStdString(),
							ImageR.toStdString(), paramsFile.toStdString());
						if (_stereoMatch->init())
						{
							connect(_stereoMatch, SIGNAL(openMessageBox(QString, QString)), this, SLOT(onOpenMessageBox(QString, QString)));
							_stereoMatch->start();
						}
						else
						{
							QMessageBox::information(NULL, QStringLiteral("����"), QStringLiteral("ƥ���ʼ��ʧ��!"));
							return;
						}
						
					}
					else
					{
						QMessageBox::information(NULL, QStringLiteral("����"), QStringLiteral("��ѡ����Ч����������ļ�!"));
						return;
					}
				}
				else
				{
					return;
				}

			}
			else
			{
				QMessageBox::information(NULL, QStringLiteral("����"), QStringLiteral("��ѡ����Ч������ͼƬ!"));
				return;
			}

		}
		else
		{
			return;
		}
	}
	else
	{
		return;
	}
}
//����:ˢ���Ӳ�ͼ
void StereoMatchController::RefreshStereoMatchCommand()
{
	StereoMatch *_stereoMatch = new StereoMatch(ImageL.toStdString(),
		ImageR.toStdString(), paramsFile.toStdString());
	if (_stereoMatch->init())
	{
		connect(_stereoMatch, SIGNAL(openMessageBox(QString, QString)), this, SLOT(onOpenMessageBox(QString, QString)));
		_stereoMatch->start();
	}
	else
	{
		QMessageBox::information(NULL, QStringLiteral("����"), QStringLiteral("ƥ���ʼ��ʧ��!"));
	}
}
//��Ϣ��Ӧ:�����Ի���
void StereoMatchController::onOpenMessageBox(QString title, QString msg)
{
	QMessageBox::information(NULL, title, msg);
}
